#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <ncursesw/ncurses.h>
#define LEVEL_LIMIT 60
#define LOAD 0
#define META 8
#define MAP_SIZE 30
enum obj { BLANK = 0, WALL = 1, DESTINATION = 2, MAN = 3, BOX = 6, ROW_END = 9, UNEXPECTED = 100 };

unsigned short map[60][MAP_SIZE][MAP_SIZE];
unsigned short tmp[MAP_SIZE][MAP_SIZE];
int score[60];
int start_line[60];
unsigned short level_count = 0;
int man_position[2] = {0, 0};

void initialize() {
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 30; j++) {
            for (int k = 0; k < 30; k++) {
                map[i][j][k] = 0;
            }
        }
        score[i] = 100000000;
        start_line[i] = 0;
    }
}

bool goToLine(FILE *file, int lineNumber) {
    rewind(file);
    char buffer[256];
    for (int i = 0; i < lineNumber; i++) {
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            return false;
        }
    }
    return true;
}

bool moveLine(FILE *file, int lineNumber) {
    char buffer[256];
    for (int i = 0; i < lineNumber; i++) {
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            return false;
        }
    }
    return true;
}

unsigned short trans(char origin_char) {
    switch (origin_char) {
        case 'X':
            return WALL;
        case '.':
            return DESTINATION;
        case '@':
            return MAN;
        case '*':
            return BOX;
        case '\n':
            return ROW_END;
        case ' ':
            return BLANK;
        case '&':
            return BOX+DESTINATION;
        default:
            printf("Trans Error");
            return UNEXPECTED;
    }
}

bool load(FILE *file) {
    rewind(file);
    char buffer;
    start_line[0] = 0;
    for (int i = 0; i < LEVEL_LIMIT; i++) {
        unsigned short line_lenth = 0;
        if (moveLine(file, META) == false) { return false; };
        line_lenth += META;
        for (int j = 0; j < MAP_SIZE; j++) {
            for (int k = 0; k < MAP_SIZE; k++) {
                buffer = fgetc(file);
                map[i][j][k] = trans(buffer);
                if (buffer == '\n') {
                    if (k == 0) {
                        line_lenth += j;
                        line_lenth += 1;
                        if(i<LEVEL_LIMIT-1){start_line[i+1] = line_lenth+start_line[i];}
                        goto finish;
                    }
                    break;
                }
            }
        }
    finish:

    }
    return true;
}

void refresh_score(bool read , bool write) {
    FILE *file;
    if (read) {
        bool flag = true;
        int level_num = 0;
        int buffer = 0;
        file = fopen("./score","r");
        if ('\n' == fgetc(file)) {
            flag = false;
        }
        if (file != NULL || flag) {
            while (!feof(file)) {
                fscanf(file,"%d:%d",&level_num,&buffer);
                score[level_num]=buffer;
            }

        }
        fclose(file);
    }
    if (write) {
        file = fopen("./score","w");
        for (int i = 0; i <LEVEL_LIMIT; i++) {
            fprintf(file,"%d:%d\n",i,score[i]);
        }
        fclose(file);
    }

}
void score_change(int level_count,int level_score) {
    score[level_count]= level_score;
    refresh_score(false,true);
}


unsigned short set_level(void) {
    clear();
    mvprintw(3, 5, "Enter a map number:");
    refresh();
    unsigned short ch1 = getch();
    if (ch1 > '0' && ch1 <= '9') {
        clear();
        mvprintw(3, 5, "Enter a map number:%c",ch1);
        refresh();
        unsigned short ch2 = getch();
        if (ch2 == '\n') {
            return ch1 - '0';
        }
        if (ch2>='0' && ch2<='9') {
            return (ch1-'0')*10+(ch2 - '0');
        }
    }
    clear();
    mvprintw(3, 5, "Error ! Press Any Key to Continue.");
    refresh();
    getch();
    return set_level();


}
int render_wall(void) {
    for (int j = 0;j<=MAP_SIZE ;j++) {
        for (int k = 0;k<=MAP_SIZE ;k++) {
            if (tmp[j][k] == WALL) {
                mvprintw(j, k, "#");
            }
            if (tmp[j][k] == ROW_END) {
                if (k == 0) {
                    return 0;
                }
                break;
            }
        }
    }

    return -1;
}

int render_man(void) {
    init_pair(4,COLOR_RED,COLOR_BLACK);
    for (int j = 0;j<=MAP_SIZE;j++) {
        for (int k = 0;k<=MAP_SIZE ;k++) {
            if (tmp[j][k] == MAN || tmp[j][k] == MAN + DESTINATION) {
                man_position[0] = j;
                man_position[1] = k;
                attron(COLOR_PAIR(4));
                mvprintw(j, k, "@");
                attroff(COLOR_PAIR(4));
                return 0;
            }
        }
    }
    return -1;
}

void render_destination(void) {
    init_pair(1,COLOR_YELLOW,COLOR_BLACK);
    for (int j = 0; j < MAP_SIZE; j++) {
        for (int k = 0; k < MAP_SIZE; k++) {
            if (tmp[j][k] == DESTINATION) {
                attron(COLOR_PAIR(1));
                mvprintw(j, k, "D");
                attroff(COLOR_PAIR(1));
            }
        }
    }
}

int render_box(void) {
    init_pair(2,COLOR_BLUE,COLOR_BLACK);
    init_pair(3,COLOR_GREEN,COLOR_BLACK);
    for (int j = 0; j < MAP_SIZE; j++) {
        for (int k = 0; k < MAP_SIZE; k++) {
            if (tmp[j][k] == BOX) {
                attron(COLOR_PAIR(2));
                mvprintw(j, k, "B");
                attroff(COLOR_PAIR(2));
            } else if (tmp[j][k] == BOX + DESTINATION) {
                attron(COLOR_PAIR(3));
                mvprintw(j, k, "B");
                attroff(COLOR_PAIR(3));
            }
            if (tmp[j][k] == ROW_END) {
                if (k == 0) {
                    return 0;
                }
                break;
            }
        }
    }
    return -1;
}
void render_meta(int level_score) {
    mvprintw(1, MAP_SIZE, "Level %d",level_count+1);
    mvprintw(3, MAP_SIZE, "Highest Score %d",score[level_count]);
    mvprintw(5, MAP_SIZE, "Current Score %d",level_score);
}

int trans0(unsigned short ser,int ch, int dis) {
    if (0 == (int)((ch - KEY_DOWN )/2 - ser)) {
        return man_position[ser]-dis*((int)((ch-KEY_DOWN-0.5-(ser*2))*2))*pow(-1,ser);
    }
    return man_position[ser];

}
unsigned short trans1(int ch,int dis) {
    return tmp[trans0(0,ch,dis)][trans0(1,ch,dis)];
}
void trans2(int ch,int dis , int op) {
    tmp[trans0(0,ch,dis)][trans0(1,ch,dis)] += op;
}
void check_move(int ch,int* level_score) {
    if (trans1(ch,1)!=WALL) {
        if (trans1(ch,1)!=BOX&&trans1(ch,1)!=BOX+DESTINATION) {
            trans2(ch,0,-MAN);
            trans2(ch,1,MAN);
            *level_score += 1;
            return;
        }
        if (trans1(ch,2)!=BOX && trans1(ch,2)!=WALL&&trans1(ch,2)!=BOX+DESTINATION) {
            trans2(ch,0,-MAN);
            trans2(ch,1,MAN-BOX);
            trans2(ch,2,BOX);
            *level_score += 1;
        }
    }
}
int operator(int* level_score) {
    int ch = getch();
    if (ch == 'R' || ch == 'r') {
        return -1;
    }
    if (ch == 'E' || ch == 'e') {
        return -2;
    }
    if (ch == 'D' || ch == 'd') {
        return -3;
    }
    check_move(ch,level_score);
    return 0;
}

bool check(void){
    for (int i = 0; i <MAP_SIZE ; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (tmp[i][j] == BOX) {
                return false;
            }
        }
    }
    return true;
}
void write_score(FILE *file,int level_score) {
    goToLine(file,start_line[level_count]+META);
    fprintf(file,"Score: %d", level_score);
    fflush(file);
    score[level_count]= level_score;
}
int play_level() {
    int level_score = 0;
    bool break_signal = false;
    int flag = 0;
    begin:
    level_score = 0;
    break_signal = false;
    flag = 0;

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            tmp[i][j] = map[level_count][i][j];
        }
    }
    while (true) {
        clear();
        render_wall();
        render_man();
        render_box();
        render_destination();
        render_meta(level_score);
        refresh();
        flag = operator(&level_score);
        if(flag==-1) {
            goto begin;
        }
        if(flag==-2) {
            return -1;
        }


        break_signal= check();

        if(flag==-3) {
            break_signal = true;
            level_score = 100;
        }


        if (break_signal) {
            if (level_score < score[level_count]) {
                score_change(level_count,level_score);
            }


            return 0;
        }
    }
}

// int get_score(FILE *file) {
//     char line[64];
//     int score;
//     fgets(line, sizeof(line), file);
//     if (line[0] == '\n') {
//         return 99999999;
//     }
//     if (sscanf(line, "Score: %d", &score) == 1) {
//         return score;
//     }
//     return 0;
//
// }

int main() {
    initialize();
    FILE *map_file;
    if ((map_file = fopen("./map", "r+")) == NULL) {
        printf("Open File Failed");
        return -1;
    }
    load(map_file);
    fclose(map_file);
    refresh_score(true,false);
    initscr();
    keypad(stdscr,true);
    curs_set(FALSE);
    start_color();
    while (1) {
        level_count = set_level()-1;
        if(play_level()==-1) {
            break;
        }
    }

    endwin();

    return 0;
}
