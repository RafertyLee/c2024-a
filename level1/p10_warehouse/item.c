#include <stdlib.h>
#include <time.h>
#include "item.h"

#include <stdio.h>
#include <string.h>

int floor_amount = 0;
typedef struct item Item;

int build_flag() {
    for(int i = 0; i < MAX_LEVEL; i++) {
        if(rand() % 2 == 0 || i == MAX_LEVEL - 1) {
            return i;
        }
    }
}

Item *item_init(char name[64], int amount) {
    Item *below_item = malloc(sizeof(Item));
    below_item->amount = amount;
    strcpy(below_item->name, name);
    below_item->prev = NULL;
    below_item->next = NULL;
    below_item->below = NULL;
    below_item->level = 0;
    for (int i = 1; i < MAX_LEVEL; i++) {
        Item *new_item = malloc(sizeof(Item));
        strcpy(new_item->name, name);
        new_item->amount = amount;
        new_item->prev = NULL;
        new_item->next = NULL;
        new_item->below = below_item;
        new_item->level = i;
        below_item = new_item;
    }
    return below_item;
}

Item *item_insert(Item *root, Item *above, char name[64], int amount) {
    Item *new_item = malloc(sizeof(Item));
    strcpy(new_item->name, name);
    new_item->amount = amount;
    new_item->level = root->level;
    new_item->prev = root;
    new_item->next = root->next;
    new_item->below = NULL;
    if (root->next != NULL) {
        root->next->prev = new_item;
    }
    root->next = new_item;
    if (above != NULL) {
        above->below = new_item;
    }
    return new_item;


}
void item_add(Item *item, char name[64], int amount) {
    printf("adding item %s\n", name);
    int target_level = build_flag();
    Item *root = item;
    Item *above = NULL;

    for (int i = MAX_LEVEL - 1; i >= 0; i--) {
        while (1) {
            if (root->next == NULL) {
                if(root->level <= target_level) {
                    above=item_insert(root,above, name, amount);
                }
                if(root->below == NULL) {
                    return ;
                }

                root=root->below;
                break;
            }
            if (name_compare(root->next->name, name) == -1) {
                root = root->next;
            }
            else if (name_compare(root->next->name, name) == 1) {
                if (root->level <= target_level) {
                    above = item_insert(root, above, name, amount);
                }
                if (root->below == NULL) {
                    return ;
                }
                root=root->below;
            }
        }
    }
}

Item* item_find(Item *item, char name[64]) {
    Item *root = item;

    for (int i = MAX_LEVEL - 1; i >= 0; i--) {
        while (1) {
            if(root==NULL) {
                return NULL;
            }
            if(name_compare(root->name, name) == 0) {
                return root;
            }
            if (root->next == NULL) {
                root = root->below;
                break;

            }
            if (name_compare(root->next->name, name) == -1) {
                root = root->next;

            }else if (name_compare(root->next->name, name) == 0) {
                return root->next;
            }else if (name_compare(root->next->name, name) == 1) {
                root = root->below;
                break;
            }
        }
    }
    return NULL;
}
int name_compare(char name[64],char other[64]) {
    int result = strcmp(name, other);
    if (result < 0) {
        return -1;
    }
    if (result > 0) {
        return 1;
    }
    return 0;
}
void item_del(Item *item) {
    Item *current = item;
    if (current == NULL) {return;}
    while (current->below != NULL) {
        Item *previous = current;
        current = current->below;
        previous->prev->next = previous->next;
        if (previous->next != NULL) {
        previous->next->prev = previous->prev;
        }

        free(previous);
    }
    if (current->next != NULL) {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }else {
        current->prev->next = NULL;
    }
    free(current);
    
    
}
void item_change(Item *item, char name[64], int amount) {
    Item *current = item_find(item, name);
    if (current == NULL) {
        item_add(item, name, amount);
        return;
    }
    if (current->amount +amount ==0) {
        item_del(current);
        return;
    }
    while (1) {
        current -> amount += amount;
        if (current->below == NULL) {return;}
        current = current->below;
    }


}



void item_print(Item *item) {
    printf("Name: %s\n", item->name);
    printf("Amount: %d\n", item->amount);
}

void item_print_all(Item *item) {
    if (item != NULL) {
        while (item->below != NULL) {
            item=item->below;
        }
        if (item->next == NULL) {
            printf("No item added\n");
            return;
        }
        while (1) {
            item=item->next;
            if (item == NULL) {
                return;
            }
            item_print(item);
        }

    }
    printf("Not available list");
}

void item_print_all_file(Item *item) {
    FILE *file = fopen(DB_NAME, "w");
    if (file == NULL) {
        printf("Error writing file");
        getchar();
        fclose(file);
        return;
    }

        while (item->below != NULL) {
            item=item->below;
        }
        if (item->next == NULL) {
            fclose(file);
            return;
        }
        while (1) {
            item=item->next;
            if (item == NULL) {
                fclose(file);
                return;
            }
            fprintf(file, "%s\n", item->name);
            fprintf(file, "%d\n", item->amount);
        }



}
void item_read_file(Item *item , FILE *file) {
    char name[64];
    int amount;
    while(fscanf(file, "%63s", &name) == 1 && fscanf(file, "%d", &amount) == 1) {
        item_add(item, name, amount);
    }
}
