//function.h 
#ifndef FUNCTION_H
#define FUNCTION_H

#include "datatype.h"

void mainMenu();
int loginUser();
int loginAdmin();
void registerUser();

void chooseRole();
void loginScreen(const char *role);
void toggleUserStatus(); 
void sortUsers();
void initializeSystem();
int isDuplicateUser(struct User newUser);
void displayUsers();
void addUser();
void searchUser();
void viewUserDetails();

#endif


