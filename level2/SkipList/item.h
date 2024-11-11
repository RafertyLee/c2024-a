#ifndef ITEM_H
#define ITEM_H
#define DB_NAME "wh.db"
#define MAX_LEVEL 32
#include <stdio.h>

struct item {
    char name[64];
    int amount;
    int level;
    struct item *below;
    struct item *next;
    struct item *prev;
};
typedef struct item Item;

Item* item_init(char name[64], int amount);
int build_flag(void);
int name_compare(char name[64], char other[64]);
void item_add(Item *item , char name[64], int amount);
void item_del(Item *item );
void item_change(Item *item, char name[64], int amount);
Item* item_find(Item *item,char name[64]);
void item_print(Item *item);
void item_print_all(Item *item);
void item_print_all_file(Item *item);
void item_read_file(Item *item , FILE *file);

Item *item_insert(Item *root, Item *above, char name[64], int amount);
#endif //ITEM_H
