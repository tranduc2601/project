#ifndef DATATYPE_H
#define DATATYPE_H

//luu ngay thang nam sinh 
struct Date {
    int day, month, year;
};

// luu thogn tin nguoi dung 
struct User {
    char userID[20];
    char name[50];
    char phone[15];
    char email[50];
    int gender;
    struct Date dateOfBirth;
    int status;
    char password[50];
};


//luu thong tin tai khoan 
struct AccountInfo {
    char userID[20];
    double balance;
    int status;
};

#endif


