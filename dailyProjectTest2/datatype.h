// import thu vien, khai bao cac struct 
#include <stdbool.h>
#ifndef DATATYPE_H  
#define DATATYPE_H  

// khai bao struct ngay, thang, nam 
typedef struct {
    int day, month, year;
} Date;

//khai bao struct ID nguoi dung nhap 
typedef struct {
    char transferID[10];
    char receivingID[10];
    float amount;
    char type[10];  // deposit/transfer/withdraw
    char message[50];
    Date transactionDate;
} Transaction;

//
typedef struct {
    char userID[20];
    float balance;
    bool status;
    char username[20];
    char password[10];
    Transaction transactionHistory[100];  // Ð?nh kích thý?c c? ð?nh
} AccountInfo;

typedef struct {
    char userID[10];
    char name[20];
    Date dateOfBirth;
    bool gender;
    char phone[10];
    char email[20];
} User;

// Ket thuc include guard
#endif 

