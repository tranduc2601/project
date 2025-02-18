#include "function.h"
#include "datatype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USER_FILE "user.bin"
#define ADMIN_EMAIL "admin@gmail.com"
#define ADMIN_PASS "686868"

int adminLoginAttempts = 0;
int userLoginAttempts = 0;

void menu() {
    int choice;
    while (1) {
        printf("\n=================================\n");
        printf(" *** Student Management System *** \n");
        printf("=================================\n");
        printf(" MENU \n");
        printf("=================================\n");
        printf(" [1] Add A New User\n");
        printf(" [2] Show All Users\n");
        printf(" [3] Search User by ID\n");
        printf(" [4] Search User by Name\n");
        printf(" [5] Sort Users by UserID\n");
        printf(" [6] Activate/Deactivate User\n");
        printf(" [0] Logout\n");
        printf("=================================\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                displayUsers();
                break;
            case 3:
                searchUserByID();
                break;
            case 4:
                searchUserByName();
                break;
            case 5:
                sortUsers();
                break;
            case 6:
                toggleUserActivation();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice, try again.\n");
        }
    }
}

void searchUserByID() {
    char userID[20];
    printf("Enter User ID to search: ");
    scanf("%s", userID);
    
    FILE *file = fopen(USER_FILE, "rb");
    if (!file) {
        printf("No user data found.\n");
        return;
    }
    
    struct User user;
    int found = 0;
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (strcmp(user.userID, userID) == 0) {
            printf("User Found: %s | Phone: %s | Email: %s | Status: %s\n",
                   user.name, user.phone, user.email, user.status == 1 ? "Active" : "Inactive");
            found = 1;
            break;
        }
    }
    fclose(file);
    
    if (!found) {
        printf("User with ID %s not found.\n", userID);
    }
}

void searchUserByName() {
    char name[50];
    printf("Enter Name to search: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    
    FILE *file = fopen(USER_FILE, "rb");
    if (!file) {
        printf("No user data found.\n");
        return;
    }
    
    struct User user;
    int found = 0;
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (strcasecmp(user.name, name) == 0) {
            printf("User Found: %s | Phone: %s | Email: %s | Status: %s\n",
                   user.name, user.phone, user.email, user.status == 1 ? "Active" : "Inactive");
            found = 1;
        }
    }
    fclose(file);
    
    if (!found) {
        printf("User with name '%s' not found.\n", name);
    }
}

void adminLogin() {
    char email[50], password[20];
    printf("Enter Admin Email: ");
    scanf("%s", email);
    printf("Enter Password: ");
    scanf("%s", password);

    if (strcmp(email, ADMIN_EMAIL) == 0 && strcmp(password, ADMIN_PASS) == 0) {
        printf("Admin login successful!\n");
        menu();
    } else {
        printf("Incorrect email or password.\n");
    }
}

int checkUserCredentials(const char *userID, const char *password) {
    FILE *file = fopen(USER_FILE, "rb");
    if (!file) return 0;

    struct User user;
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (strcmp(user.userID, userID) == 0 && strcmp(user.password, password) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void userLogin() {
    char userID[20], password[50];
    printf("Enter User ID: ");
    scanf("%s", userID);
    printf("Enter Password: ");
    scanf("%s", password);

    if (checkUserCredentials(userID, password)) {
        printf("User login successful! Welcome, %s.\n", userID);
    } else {
        printf("Invalid User ID or Password.\n");
    }
}

int isUserIDExists(const char *userID) {
    FILE *file = fopen(USER_FILE, "rb");
    if (!file) return 0;

    struct User user;
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (strcmp(user.userID, userID) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void inputString(const char *prompt, char *str, int maxLen) {
    do {
        printf("%s: ", prompt);
        fgets(str, maxLen, stdin);
        str[strcspn(str, "\n")] = '\0';
        if (strlen(str) == 0) {
            printf("Input cannot be empty! Please try again.\n");
        }
    } while (strlen(str) == 0);
}

int inputInt(const char *prompt, int min, int max) {
    int num;
    while (1) {
        printf("%s (%d-%d): ", prompt, min, max);
        if (scanf("%d", &num) == 1 && num >= min && num <= max) {
            getchar();
            return num;
        }
        printf("Invalid input! Please enter a valid number.\n");
        while (getchar() != '\n');
    }
}

void addUser() {
    struct User user;

    do {
        inputString("Enter User ID", user.userID, sizeof(user.userID));
        if (isUserIDExists(user.userID)) {
            printf("User ID already exists! Please try again.\n\n");
        }
    } while (isUserIDExists(user.userID));

    inputString("Enter Name", user.name, sizeof(user.name));
    inputString("Enter Phone Number", user.phone, sizeof(user.phone));
    inputString("Enter Email", user.email, sizeof(user.email));

    user.gender = inputInt("Enter Gender (0 - Female, 1 - Male)", 0, 1);

    printf("Enter Date of Birth\n");
    user.dateOfBirth.day = inputInt("  Day", 1, 31);
    user.dateOfBirth.month = inputInt("  Month", 1, 12);
    user.dateOfBirth.year = inputInt("  Year", 1900, 2024);

    inputString("Enter Password", user.password, sizeof(user.password));

    user.status = 1;

    FILE *file = fopen(USER_FILE, "ab");
    if (!file) {
        printf("CANNOT OPEN FILE\n");
        return;
    }

    fwrite(&user, sizeof(struct User), 1, file);
    fclose(file);
    printf("User added successfully!\n");
}

void displayUsers() {
    FILE *file = fopen(USER_FILE, "rb");
    if (!file) {
        printf("No user data found.\n");
        return;
    }

    struct User user;
    int count = 0;
    printf("\n===== USER LIST =====\n");
    while (fread(&user, sizeof(struct User), 1, file)) {
        printf("UserID: %s | Name: %s | Phone: %s | Email: %s | Gender: %s | DOB: %02d-%02d-%04d | Status: %s\n",
               user.userID, user.name, user.phone, user.email,
               user.gender == 1 ? "Male" : "Female",
               user.dateOfBirth.day, user.dateOfBirth.month, user.dateOfBirth.year,
               user.status == 1 ? "Active" : "Inactive");
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("No users found in the system.\n");
    }
}

void toggleUserActivation() {
    char userID[20];
    printf("Enter User ID to toggle activation: ");
    scanf("%s", userID);

    FILE *file = fopen(USER_FILE, "rb+");
    if (!file) {
        printf("No user data found.\n");
        return;
    }

    struct User user;
    int found = 0;
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (strcmp(user.userID, userID) == 0) {
            found = 1;
            user.status = !user.status;
            fseek(file, -sizeof(struct User), SEEK_CUR);
            fwrite(&user, sizeof(struct User), 1, file);
            printf("User %s is now %s.\n", user.userID, user.status ? "Active" : "Inactive");
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("User with ID %s not found.\n", userID);
    }
}

void sortUsers() {
    FILE *file = fopen(USER_FILE, "rb");
    if (!file) {
        printf("No user data found.\n");
        return;
    }

    struct User users[100]; 
    int count = 0;

    while (fread(&users[count], sizeof(struct User), 1, file)) {
        count++;
    }
    fclose(file);

    // S?p x?p b?ng Bubble Sort theo userID
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (strcmp(users[i].userID, users[j].userID) > 0) {
                struct User temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }

    // Ghi d? li?u ð? s?p x?p vào file
    file = fopen(USER_FILE, "wb");
    if (!file) {
        printf("CANNOT OPEN FILE\n");
        return;
    }

    for (i = 0; i < count; i++) {
        fwrite(&users[i], sizeof(struct User), 1, file);
    }
    fclose(file);

    printf("Users sorted by UserID successfully!\n");
}

