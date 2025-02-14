//function.c 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "function.h"

#define USER_FILE "./user.bin"
#define ACCOUNT_FILE "./account.bin"


struct User {
    int id;
    char name[50];
    char email[50];
    int gender; // 0: Female, 1: Male
    int isActive; // 1: Active, 0: Locked
};

void toggleUserStatus() {
    FILE *file = fopen(USER_FILE, "rb+");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    int userId, found = 0;
    printf("Enter user ID to lock/unlock: ");
    scanf("%d", &userId);

    struct User user;
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (user.id == userId) {
            found = 1;
            printf("User %s is currently %s. Do you want to %s? (1: Yes, 0: No): ",
                   user.name, user.isActive ? "Active" : "Locked",
                   user.isActive ? "lock" : "unlock");
            int confirm;
            scanf("%d", &confirm);
            if (confirm) {
                user.isActive = !user.isActive;
                fseek(file, -sizeof(struct User), SEEK_CUR);
                fwrite(&user, sizeof(struct User), 1, file);
                printf("User %s has been %s successfully!\n", user.name, user.isActive ? "unlocked" : "locked");
            }
            break;
        }
    }
    
    if (!found) {
        printf("User ID not found!\n");
    }

    fclose(file);
}


void initializeSystem() {
    printf("System initialization...\n");
}

// kiem tra tinh trung lap  
int isDuplicateUser(struct User newUser) {
    FILE *file = fopen(USER_FILE, "rb");
    if (!file) return 0;
    
    struct User user;
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (strcmp(user.userID, newUser.userID) == 0 ||
            strcmp(user.phone, newUser.phone) == 0 ||
            strcmp(user.email, newUser.email) == 0) {
            fclose(file);
            return 1; // Data already exists
        }
    }
    fclose(file);
    return 0;
}

void displayUsers() {
    FILE *file = fopen(USER_FILE, "rb");
    if (!file) {
        printf("No users found!\n");
        return;
    }

    printf("%-10s %-20s %-20s %-10s %-10s\n", "ID", "Name", "Email", "Gender", "Status");
    printf("==========================================================\n");
    struct User user;
    while (fread(&user, sizeof(struct User), 1, file)) {
        printf("%-10d %-20s %-20s %-10s %-10s\n",
               user.id, user.name, user.email,
               user.gender ? "Male" : "Female",
               user.isActive ? "Active" : "Locked");
    }
    fclose(file);
}

int compareByID(const void *a, const void *b) {
    return ((struct User*)a)->id - ((struct User*)b)->id;
}
int compareByName(const void *a, const void *b) {
    return strcmp(((struct User*)a)->name, ((struct User*)b)->name);
}

void sortUsers() {
    FILE *file = fopen(USER_FILE, "rb");
    if (!file) {
        printf("No users to sort!\n");
        return;
    }

    struct User users[100];
    int count = 0;
    while (fread(&users[count], sizeof(struct User), 1, file)) {
        count++;
    }
    fclose(file);

    int choice;
    printf("Sort by:\n1. ID\n2. Name\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        qsort(users, count, sizeof(struct User), compareByID);
    } else if (choice == 2) {
        qsort(users, count, sizeof(struct User), compareByName);
    } else {
        printf("Invalid choice!\n");
        return;
    }

    file = fopen(USER_FILE, "wb");
    fwrite(users, sizeof(struct User), count, file);
    fclose(file);

    printf("Users sorted successfully!\n");
    displayUsers();
}

int main() {
    int choice;
    do {
        printf("\n1. Lock/Unlock User\n2. Display Users\n3. Sort Users\n4. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: toggleUserStatus(); break;
            case 2: displayUsers(); break;
            case 3: sortUsers(); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);
    return 0;
}

void addUser() {
    struct User user;
    printf("Enter user ID: ");
    scanf("%s", user.userID);
    getchar();
    printf("Enter user name: ");
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = 0; 
    printf("Enter phone number: ");
    scanf("%s", user.phone);
    getchar();
    printf("Enter email: ");
    scanf("%s", user.email);
    getchar();
    printf("Enter gender (0: Female, 1: Male): ");
    scanf("%d", &user.gender);
    getchar();
    printf("Enter birth date (dd mm yyyy): ");
    scanf("%d %d %d", &user.dateOfBirth.day, &user.dateOfBirth.month, &user.dateOfBirth.year);
    getchar();
    
    if (isDuplicateUser(user)) {
        printf("Error: ID, phone number, or email already exists!\n");
        return;
    }
    
    FILE *file = fopen(USER_FILE, "ab");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    fwrite(&user, sizeof(struct User), 1, file);
    fclose(file);
    printf("User added successfully!\n");
}
//tim nguoi dung theo ten 
void searchUser() {
    char searchName[20];
    printf("Enter the user name to search: ");
    scanf("%s", searchName);
    getchar();
    
    FILE *file = fopen(USER_FILE, "rb");
    if (!file) {
        printf("No users found.\n");
        return;
    }
    
    int found = 0;
    struct User user;
    printf("==============================================================================================================\n");
    printf("| %-15s | %-20s | %-30s | %-15s | %-8s | %-15s |\n", "ID", "Name", "Email", "Phone", "Gender", "Status");
    printf("==============================================================================================================\n");
    
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (strstr(user.name, searchName)) {
            printf("| %-15s | %-20s | %-30s | %-15s | %-8s | %-15s |\n", 
                   user.userID, user.name, user.email, user.phone, user.gender ? "Male" : "Female", user.status ? "Active" : "Inactive");
            found = 1;
        }
    }
    
    printf("==============================================================================================================\n");
    fclose(file);
    
    if (!found) {
        printf("No user found with name '%s'.\n", searchName);
    }
}

void viewUserDetails() {
    char searchID[20];
    printf("Enter user ID: ");
    scanf("%s", searchID);
    getchar();
    
    FILE *userFile = fopen(USER_FILE, "rb");
    FILE *accountFile = fopen(ACCOUNT_FILE, "rb");
    if (!userFile || !accountFile) {
        printf("Error opening file.\n");
        return;
    }
    
    struct User user;
    struct AccountInfo account;
    int found = 0;
    
    while (fread(&user, sizeof(struct User), 1, userFile)) {
        if (strcmp(user.userID, searchID) == 0) {
            found = 1;
            printf("\nUser Details:\n");
            printf("ID: %s\n", user.userID);
            printf("Name: %s\n", user.name);
            printf("Phone: %s\n", user.phone);
            printf("Email: %s\n", user.email);
            printf("Gender: %s\n", user.gender ? "Male" : "Female");
            printf("Birth Date: %02d/%02d/%04d\n", user.dateOfBirth.day, user.dateOfBirth.month, user.dateOfBirth.year);
            break;
        }
    }
    
    while (fread(&account, sizeof(struct AccountInfo), 1, accountFile)) {
        if (strcmp(account.userID, searchID) == 0) {
            printf("Balance: %.2f\n", account.balance);
            printf("Status: %s\n", account.status ? "Active" : "Inactive");
            break;
        }
    }
    
    fclose(userFile);
    fclose(accountFile);
    if (!found) {
        printf("No user found with ID '%s'.\n", searchID);
    }
    printf("Press any key to return to the main menu...\n");
    getchar();
}

