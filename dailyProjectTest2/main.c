#include <stdio.h>
#include <stdlib.h>
#include "function.h" 
#include "datatype.h" 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void displayMenu() {
    printf("\n*====== BANK ACCOUNT MANAGER USING C======*\n");
    printf("1. Display Users\n");//hien thi thong tin nguoi dung 
    printf("2. Add User\n");	 //them nguoi dung 
    printf("3. Exit\n");		 //thoat 
    printf("Enter your choice: ");//nhap lua chon 
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
            	{
            	//In ra danh sach nguoi dung 
                printf("\nUser List:\n");
                printf("+-----------------------------------+\n");
                printf("| %-10s | %-20s |\n", "ID", "Name");
                printf("+-----------------------------------+\n");
                displayUsers();
                printf("+-----------------------------------+\n");
                break;
				}
            case 2:
            	{
            	//them nguoi dung 
                addUser();
                printf("User added successfully!\n");
                break;
                }
            case 3:
            	{
            	//thoat menu hoac thong bao nguoi dung nhap lua chon khong ton tai 
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                }
        }
    } while (choice != 3); 
    
    return 0;
}
 
