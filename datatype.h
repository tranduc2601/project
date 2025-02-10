//import thu vien, khai bao cac struct
#include <stdbool.h>
#ifndef DATATYPE_H  
#define DATATYPE_H  


struct Date{
	int day,month,year;
};


struct Transaction{
	char transferID[10];
	char receivingID[10];
	char amount ;
	char type[10];//deposit/transfer/withdraw
	char message[50];
	struct Date transactionDate;
};


struct AccountInfo{
	char userID[20];
	float balance;
	bool status;
	char username[20];
	char password[10];
	struct Transaction transactionHistory[];
};

struct User {
	char userID[10];
	char name [20];
	struct Date dateOfBirth;
	bool gender;
	char phone[10];
	char email[20];
};

//ket thuc include guard, neu khong ket thuc se bi loi 
#endif 
