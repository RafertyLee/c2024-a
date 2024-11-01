#include "ui.h"
#include <stdio.h>
int menu(void) {
    int choice;
    printf("------------------------------------------\n");
    printf("Welcome to the Warehouse System UI Program\n");
    printf("------------------------------------------\n");

    printf("\nWarehouse Management Menu:\n");
    printf("1. Display Inventory List\n");
    printf("2. Add to Inventory\n");
    printf("3. Remove from Inventory\n");
    printf("4. Exit Program\n");

    printf("Please select an option (1-4): ");
    scanf("%d", &choice);
    return choice;
}