#include <stdio.h>
#include <stdlib.h>
#include "function.h" 
#include "datatype.h" 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void display_menu() {
    printf("\n====== BANK ACCOUNT MANAGER ======\n");
    printf("1. Display Users\n");
    printf("2. Add User\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

int main(int argc, char *argv[]) {


    int choice;
    initializeSystem();
    
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                printf("\nUser List:\n");
                printf("-----------------------------------\n");
                printf("| %-10s | %-20s |\n", "ID", "Name");
                printf("-----------------------------------\n");
                displayUsers();
                printf("-----------------------------------\n");
                break;
            case 2:
                addUser();
                printf("User added successfully!\n");
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
    
    return 0;
}
 
