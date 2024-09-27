#include <ncursesw/ncurses.h>
#include <ctype.h>
#include <stdlib.h>

char order;

typedef struct pt {
    char c;
    struct pt *next;
} pt;

typedef struct ct {
    char c;
    struct ct *next;
} ct;

int main() {
    const int shift = 4;
    struct pt *pth, *ptp, *ptt;
    struct ct *cth, *ctp, *ctt;
    pth = malloc(sizeof(pt));
    cth = malloc(sizeof(ct));
    ptt = malloc(sizeof(pt));
    ctt = malloc(sizeof(ct));
    ptp = pth;
    ptp->next = ptt;
    ctp = cth;
    ctp->next = ctt;

    // 初始化 ncurses
    initscr();
    cbreak();
    keypad(stdscr, TRUE);

input:
    clear();

    printw("Decrypt or Encrypt (\"D\" or \"E\") : ");
    order = getch();
    refresh();
    if (order != 'D' && order != 'E' && order != 'd' && order != 'e') {
        printw("\nInvalid Input\n");
        printw("Press Enter To Continue\n");
        getch();
        goto input;
    }

    if (order == 'D' || order == 'd') {
        printw("\nDecrypt\n");
        printw("Enter the encrypted content :\n");
        while (1) {
            ctp->c = getch();
            refresh();
            if (ctp->c == '\n' || ctp->c == '\r' || ctp->c == EOF) {
                break;
            }
            if (!isalpha(ctp->c) && ctp->c != ' ') {
                printw("\nInvalid Input: %c\n", ctp->c);
                printw("Press Enter To Continue\n");
                getch();
                goto input;
            }


            ctp->next = malloc(sizeof(ct));
            ctp = ctp->next;
            ctp->next = ctt;
        }
    } else {
        printw("\nEncrypt\n");
        printw("Enter the content to encrypt :\n");
        while (1) {
            ptp->c = getch();
            refresh();
            if (ptp->c == '\n' || ptp->c == '\r' || ptp->c == EOF) {
                break;
            }
            if (!isalpha(ptp->c) && ptp->c != ' ') {
                printw("\nInvalid Input: %c\n", ptp->c);
                printw("Press Enter To Continue\n");
                getch();
                goto input;
            }

            ptp->next = malloc(sizeof(pt));
            ptp = ptp->next;
            ptp->next = ptt;
        }
    }

    ptp = pth;
    ctp = cth;
    if (order == 'D' || order == 'd') {
        printw("\nPlainText:\n");
        while (1) {
            if (ctp->c == '\n' || ctp->c == '\r' || ctp->c == EOF) {
                ptp->c = ctp->c;
                break;
            }
            if (ctp->c == ' ') {
                ptp->c = ' ';
            } else if (islower(ctp->c)) {
                ptp->c = ctp->c - shift;
                if (ptp->c < 'a') {
                    ptp->c = ptp->c + 26;
                }
            } else {
                ptp->c = ctp->c - shift;
                if (ptp->c < 'A') {
                    ptp->c = ptp->c + 26;
                }
            }


            ptp->next = malloc(sizeof(pt));
            ptp = ptp->next;
            ptp->next = ptt;
            ctp = ctp->next;
        }

        ptp = pth;
        ctp = cth;
        while (1) {
            if (ptp->c == '\n' || ptp->c == '\r' || ptp->c == EOF) {
                break;
            }
            printw("%c", ptp->c);
            ptp = ptp->next;
        }
    } else {
        printw("\nCipherText:\n");
        while (1) {
            if (ptp->c == '\n' || ptp->c == '\r' || ptp->c == EOF) {
                ctp->c = ptp->c;
                break;
            }
            if (ptp->c == ' ') {

                ctp->c = ' ';
            } else if (islower(ptp->c)) {
                ctp->c = ptp->c + shift;
                if (ctp->c > 'z') {
                    ctp->c = ctp->c - 26;
                }
            } else {
                ctp->c = ptp->c + shift;
                if (ctp->c > 'Z') {
                    ctp->c = ctp->c - 26;
                }
            }


            ctp->next = malloc(sizeof(ct));
            ctp = ctp->next;
            ctp->next = ctt;
            ptp = ptp->next;
        }

        ptp = pth;
        ctp = cth;
        while (1) {
            if (ctp->c == '\n' || ctp->c == '\r' || ctp->c == EOF) {
                break;
            }
            printw("%c", ctp->c);
            ctp = ctp->next;
        }
    }

    printw("\n");
    getch();
    refresh();
quit_check:
    printw("\nQuit or Return (\"Q\" or \"R\") : \n");
    order = getch();
    if (order != 'Q' && order != 'R') {
        refresh();
        printw("\nInvalid Input\n");
        printw("Press Enter To Continue\n");
        getch();
        clear();
        goto quit_check;
    }
    if (order == 'R') {
        refresh();
        goto input;
    }


    endwin();
    return 0;
}
