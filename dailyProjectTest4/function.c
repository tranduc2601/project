#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "function.h"

#define USER_FILE "./user.bin"
#define ACCOUNT_FILE "./account.bin"

// Hi?n th? màn h?nh ðãng nh?p
void loginScreen(const char *role) {
    char email[50], password[50];
    printf("***********************************************\n");
    printf("***    Bank Management System Using C    ***\n");
    printf("***********************************************\n");
    printf("\n");
    printf("                   LOGIN                   \n");
    printf("===========================================\n");
    printf("Role: %s\n", role);
    printf("Email: ");
    scanf("%s", email);
    printf("Password: ");
    scanf("%s", password);
    printf("===========================================\n");
    printf("Login successful! Redirecting to menu...\n");
}

// Ki?m tra thông tin nh?p vào h?p l?
int isValidInput(const char *input, int maxLength) {
    return (strlen(input) > 0 && strlen(input) < maxLength);
}

// Ki?m tra trùng l?p ngý?i dùng
int isDuplicateUser(struct User user) {
    FILE *file = fopen(USER_FILE, "rb");
    if (!file) return 0;
    struct User temp;
    while (fread(&temp, sizeof(struct User), 1, file)) {
        if (strcmp(temp.userID, user.userID) == 0 || strcmp(temp.phone, user.phone) == 0 || strcmp(temp.email, user.email) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// Thêm ngý?i dùng m?i
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
    user.status = 1;
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

// Hi?n th? danh sách ngý?i dùng dý?i d?ng b?ng
void displayUsers() {
    FILE *file = fopen(USER_FILE, "rb");
    if (!file) {
        printf("No users found!\n");
        return;
    }
    printf("==============================================================\n");
    printf("%-10s %-20s %-20s %-10s %-10s\n", "ID", "Name", "Email", "Gender", "Status");
    printf("==============================================================\n");
    struct User user;
    while (fread(&user, sizeof(struct User), 1, file)) {
        printf("%-10s %-20s %-20s %-10s %-10s\n",
               user.userID, user.name, user.email,
               user.gender ? "Male" : "Female",
               user.status ? "Active" : "Locked");
    }
    fclose(file);
}

// T?m ki?m ngý?i dùng theo tên
void searchUser() {
    char searchName[50];
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
    printf("==============================================================\n");
    printf("%-10s %-20s %-20s %-10s %-10s\n", "ID", "Name", "Email", "Gender", "Status");
    printf("==============================================================\n");
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (strstr(user.name, searchName)) {
            printf("%-10s %-20s %-20s %-10s %-10s\n", 
                   user.userID, user.name, user.email,
                   user.gender ? "Male" : "Female",
                   user.status ? "Active" : "Locked");
            found = 1;
        }
    }
    printf("==============================================================\n");
    fclose(file);
    if (!found) {
        printf("No user found with name '%s'.\n", searchName);
    }
}

