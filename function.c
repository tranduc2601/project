//trien khai cac ham #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "function.h"

#define USER_FILE "./user.bin"


// khai bao he thong 
void initializeSystem() {
    printf("System initialized...\n");
}

// hien thi danh sach nguoi dung tu tep 
void displayUsers() {
    FILE *file = fopen(USER_FILE, "rb");
    if (!file) {
        printf("No users found.\n");
        return;
    }

    User user;
    while (fread(&user, sizeof(User), 1, file)) {
        printf("| %-10s | %-20s | %-10s |\n", user.userID, user.name, user.phone);
    }
    
    fclose(file);
}

//them nguoi dung moi 
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

    FILE *file = fopen(USER_FILE, "ab");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    fwrite(&user, sizeof(User), 1, file);
    fclose(file);

    printf("User added successfully!\n");
}

