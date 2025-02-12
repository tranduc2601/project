// function.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "function.h"

#define USER_FILE "./user.bin"

void initializeSystem() {
    printf("System initialized...\n");
}

// kiem tra trung lap sdt, ID, email
int isDuplicateUser(User newUser) {
    FILE *file = fopen(USER_FILE, "rb");
    if (!file) return 0;
    
    User user;
    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(user.userID, newUser.userID) == 0 ||
            strcmp(user.phone, newUser.phone) == 0 ||
            strcmp(user.email, newUser.email) == 0) {
            fclose(file);
            return 1; // trung du lieu 
        }
    }
    fclose(file);
    return 0;
}

void displayUsers() {
    FILE *file = fopen(USER_FILE, "rb");
    if (!file) {
        printf("No users found.\n");
        return;
    }
    
    printf("+------------+----------------------+-----------------+----------------------+");
    printf("\n| %-10s | %-20s | %-15s | %-20s |");
    printf("\n+------------+----------------------+-----------------+----------------------+");
    
    User user;
    while (fread(&user, sizeof(User), 1, file)) {
        printf("\n| %-10s | %-20s | %-10s | %-20s |", user.userID, user.name, user.phone, user.email);
    }
    
    printf("\n+------------+----------------------+-----------------+----------------------+");
    fclose(file);
}

void addUser() {
    User user;
    printf("Enter User ID: ");
    scanf("%s", user.userID);
    getchar();
    printf("Enter User Name: ");
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = 0; 
    printf("Enter Phone Number: ");
    scanf("%s", user.phone);
    getchar();
    printf("Enter Email: ");
    scanf("%s", user.email);
    getchar();
    printf("Enter Gender (0 for Female, 1 for Male): ");
    scanf("%d", &user.gender);
    getchar();
    printf("Enter Date of Birth (dd mm yyyy): ");
    scanf("%d %d %d", &user.dateOfBirth.day, &user.dateOfBirth.month, &user.dateOfBirth.year);
    getchar();
    
    if (isDuplicateUser(user)) {
        printf("Error: Duplicate user ID, phone, or email!\n");
        return;
    }
    
    FILE *file = fopen(USER_FILE, "ab");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    fwrite(&user, sizeof(User), 1, file);
    fclose(file);
    printf("User added successfully!\n");
}

void searchUser() {
    char searchName[20];
    printf("Enter name to search: ");
    scanf("%s", searchName);
    getchar();
    
    FILE *file = fopen(USER_FILE, "rb");
    if (!file) {
        printf("No users found.\n");
        return;
    }
    
    int found = 0;
    User user;
    printf("+------------+----------------------+-----------------+----------------------+");
    printf("\n| %-10s | %-20s | %-15s | %-20s |");
    printf("\n+------------+----------------------+-----------------+----------------------+");
    
    while (fread(&user, sizeof(User), 1, file)) {
        if (strstr(user.name, searchName)) {
            printf("\n| %-10s | %-20s | %-15s | %-20s |", user.userID, user.name, user.phone, user.email);
            found = 1;
        }
    }
    
    printf("\n+------------+----------------------+-----------------+----------------------+");
    fclose(file);
    
    if (!found) {
        printf("\nNo user found with name '%s'.\n", searchName);
    }
}

