//function.h 
#ifndef FUNCTION_H
#define FUNCTION_H

#include "datatype.h"

//	menu 
void mainMenu();
//khach hang 
int loginUser();
//admin  
int loginAdmin();
//dang ky 
void registerUser();
//thao tac trang thai 
void toggleUserStatus(); 
//chon vai tro 
void chooseRole();
//man hinh dang nhap 
void loginScreen(const char *role);
//sap xep 
void sortUsers();
//chay he thong 
void initializeSystem();
//trung lap 
int isDuplicateUser(struct User newUser);
//hien thi 
void displayUsers();
//them ngdung 
void addUser();
//tim ngdung 
void searchUser();
//hien thi thong tin 
void viewUserDetails();
void searchUserByID();
void searchUserByName();
void toggleUserActivation();
int compareUsers(const void *a, const void *b);



#endif


