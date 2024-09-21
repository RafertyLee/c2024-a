#include <stdio.h>
#include <ncursesw/ncurses.h>
#include <stdlib.h>

int main() {
    initscr();            // 初始化屏幕
    int n = 0;
    int v = 1;



    while(1) {

        curs_set(FALSE);
        mvprintw( 0,n,"Hello World");
        refresh();
        n += v;
        if (n > COLS-11){
            v = -1;
        }
        else if (n < 0) {
            v = 1;
        }
        _sleep(100);
        clear();

    }

    refresh();

    endwin();
    return 0;
}
