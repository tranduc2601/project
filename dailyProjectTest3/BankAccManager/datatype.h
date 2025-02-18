#ifndef DATATYPE_H
#define DATATYPE_H

struct Date {
    int day, month, year;
};

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

struct AccountInfo {
    char userID[20];
    double balance;
    int status;
};

#endif
