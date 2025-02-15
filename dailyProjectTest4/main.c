#include <stdio.h>
#include <stdlib.h>
#include "function.h"
// main.c


int main() {
    int choice;
    while (1) {
        printf("\nBank Account Management System\n");
        printf("1. Register User\n");
        printf("2. Login User\n");
        printf("3. Toggle User Status\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                toggleUserStatus();
                break;
            case 4:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}






//admin@gmail.com--68686868 

//==============================================================================================================
//| ID           | Name                 | Email                     | Phone        | Gender   | Status         |
//==============================================================================================================
//|26012006      | Tran Minh Duc        | 2601minhduc@gmail.com     | 0347407135   | Nam      | Hoat Dong      |
//|27012006      | Tran Minh Minh       | 2701minhminh@gmail.com    | 0343307211   | Nu       | Khong hoat dong| 
//==============================================================================================================
//Go back(b)? or Exit(0)?:
//==============================================================================================================
//|                                  BANK ACCOUNT MANAGER                                                      |
//==============================================================================================================
//| No    | Options                                                                                            |
//==============================================================================================================
//| 1     | Display Users                           															 |
//| 2     | Add User                                 															 |
//| 3     | Search User by Name                      															 |
//| 4     | Search User by ID                        															 |
//| 5     | Exit                                                                                               |
//==============================================================================================================
//Enter your choice:
