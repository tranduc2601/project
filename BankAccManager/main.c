#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main() {
    int choice;
    while (1) {
        printf("=================================\n");
        printf(" ***Student Management System Using C*** \n");
        printf("=================================\n");
        printf(" CHOOSE YOUR ROLE \n");
        printf("=================================\n");
        printf(" [1] Admin Login.\n");
        printf(" [2] User Login.\n");
        printf(" [0] Exit the Program.\n");
        printf("=================================\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminLogin();
                break;
            case 2:
                userLogin();
                break;
            case 0:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
