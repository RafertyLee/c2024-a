#include <ncursesw/ncurses.h>


int maze[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 0, 0, 0, 1, 1, 1, 0, 1},
    {1, 1, 0, 1, 1, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 0, 1, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int chara[2] = {3, 1};
int destin[2] = {0, 8};
int ch;


int main() {
    initscr();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK); // 红色文字
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    curs_set(0);
    noecho();
    while (1) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (maze[i][j] == 1) {
                    mvprintw(i, j, "#");
                }
            }
        }
        mvprintw(0, 15, "# Wall");
        mvprintw(1, 17, "Character");
        mvprintw(2, 17, "Destin");
        mvprintw(3, 15, "Press Q to Exit");
        attron(COLOR_PAIR(1));
        mvprintw(chara[0], chara[1], "@");
        mvprintw(1, 15, "@");
        attroff(COLOR_PAIR(1));
        attron(COLOR_PAIR(2));
        mvprintw(destin[0], destin[1], "D");
        mvprintw(2, 15, "D");
        attroff(COLOR_PAIR(2));
        refresh();
        ch = getch();
        if (ch == 'q' || ch == 'Q') {
            goto end;
        } else {
            switch (ch) {
                case KEY_UP:
                    if (maze[chara[0] - 1][chara[1]] == 0) {
                        chara[0]--;
                    }
                    break;
                case KEY_DOWN:
                    if (maze[chara[0] + 1][chara[1]] == 0) {
                        chara[0]++;
                    }
                    break;
                case KEY_LEFT:
                    if (maze[chara[0]][chara[1] - 1] == 0) {
                        chara[1]--;
                    }
                    break;
                case KEY_RIGHT:
                    if (maze[chara[0]][chara[1] + 1] == 0) {
                        chara[1]++;
                    }
                    break;
                default: ;
                    break;
            }
        }
        clear();
        if (chara[0] == destin[0] && chara[1] == destin[1]) {
            attron(COLOR_PAIR(2));
            mvprintw(chara[0], chara[1], "You Finished The Maze");
            attroff(COLOR_PAIR(2));
            getch();
            break;
        }
    }
end:
    endwin();
    return 0;
}
