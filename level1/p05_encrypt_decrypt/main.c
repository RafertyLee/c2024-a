#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
char order;

typedef struct pt{
    char c;
    struct pt *next;
} pt;

typedef struct ct{
    char c;
    struct ct *next;
} ct;


int main() {
    const int shift = 4;
    struct pt *pth;
    struct pt *ptp;
    struct pt *ptt;
    struct ct *cth;
    struct ct *ctp;
    struct ct *ctt;
    pth = malloc(sizeof(pt));
    cth = malloc(sizeof(ct));
    ptt = malloc(sizeof(pt));
    ctt = malloc(sizeof(ct));
    ptp = pth;
    ptp->next = ptt;
    ctp = cth;
    ctp->next = ctt;
input:
    printf("Decrypt or Encrypt (\"D\" or \"E\") : ");
    order = getchar();
    if (order != 'D' && order != 'E' && order != 'd' && order != 'e') {
        printf("Wrong Input\n");
        goto input;
    }
    if (order == 'D' || order == 'd') {
        printf("Decrypt\n");
        printf("Enter the encrypted content :\n");
        while (1) {
            ctp->c = getchar();
            if (ctp->c >= 'z' || ctp->c <= 'a') {
                if (ctp->c >= 'Z' || ctp->c <= 'A') {
                    printf("Invalid Input: %c\n", ctp->c);
                    goto input;
                }
            }
            if (ctp->c == '\n' || ctp->c == '\r' || ctp->c == '\0' || ctp->c == EOF) {
                break;
            }

            ctp->next = malloc(sizeof(ct));
            ctp = ctp->next;
            ctp->next = ctt;
        }
    } else {
        printf("Encrypt\n");
        printf("Enter the content to encrypt :\n");
        while (1) {
            ptp->c = getchar();
            if (ptp->c >= 'z' || ptp->c <= 'a') {
                if (ptp->c >= 'Z' || ptp->c <= 'A') {
                    printf("Invalid Input: %c\n", ptp->c);
                    goto input;
                }
            }
            if (ctp->c == '\n' || ctp->c == '\r' || ctp->c == '\0' || ctp->c == EOF) {
                break;
            }
            ptp->next = malloc(sizeof(pt));
            ptp = ptp->next;
            ptp->next = ptt;
        }
    }

    ptp = pth;
    ctp = cth;
    if (order == 'D' || order == 'd') {
        printf("PlainText:\n");
        while (1) {
            if (ctp->c == '\n' || ctp->c == '\r' || ctp->c == '\0' || ctp->c == EOF) {
                ptp->c = ctp->c;

                break;
            }
            if (ctp->c < 'z' && ctp->c > 'a') {
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
            if (ptp->c == '\n' || ptp->c == '\r' || ptp->c == '\0' || ptp->c == EOF) {
                break;
            }
            printf("%c", ptp->c);
            ptp = ptp->next;
        }
    } else {
        printf("CipherText:\n");
        while (1) {
            if (ptp->c == '\n' || ptp->c == '\r' || ptp->c == '\0') {
                ctp->c = ptp->c;
                break;
            }
            if (ptp->c < 'z' && ptp->c > 'a') {
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
            if (ctp->c == '\n' || ctp->c == '\r' || ctp->c == '\0' || ctp->c == EOF) {
                break;
            }
            printf("%c", ctp->c);
            ctp = ctp->next;
        }
    }
    return 0;
}