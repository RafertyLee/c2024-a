#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncursesw/ncurses.h>
#include <string.h>
#include "ui.h"
#include "item.h"
enum {LIST=1,IN=2,OUT=3,EXIT=4};

int main() {
    srand(time(NULL));
    FILE *file = fopen(DB_NAME, "r");
    char head_name[64];
    memset(head_name, 0, 64);
    Item *list_root = item_init(head_name,0);
    if (file != NULL) {
        item_read_file(list_root,file);
    }
    fclose(file);
    char buffer[64];
    char name[64];
    int amount;

    while(1) {
        memset(buffer, 0, 64);
        memset(name, 0, 64);
        amount = 0;
        int choice=menu();
        switch(choice) {
            case LIST:
                item_print_all(list_root);
            getchar();
            break;

            case IN:
                for(int i=0;i<64;i++) {
                    name[i] = 0;
                }
                printf("Enter name: ");
            scanf("%63s",&buffer);
            strcpy(name,buffer);
            printf("Enter amount: ");
            scanf("%d",&amount);
            if (amount == 0) {
                printf("Invalid Amount\n");
                break;
            }
            item_change(list_root,name,amount);
            break;
            case OUT:
                for(int i=0;i<64;i++) {
                    name[i] = 0;
                }
                printf("Enter name: ");
            scanf("%63s",&buffer);
            strcpy(name,buffer);
            printf("Enter amount: ");
            scanf("%d",&amount);
            amount = -amount;
            item_change(list_root,name,amount);
            break;
            case EXIT:
                item_print_all_file(list_root);
            return 0;
            default:
                printf("Invalid choice\n");
            break;
        }





    }
}