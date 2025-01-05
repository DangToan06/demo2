#include <stdbool.h>

typedef struct DataDay{
	int day, month, year;
}Data;

typedef struct DataBook{
	char bookId[10];
	char title[30];
	char author[20];
	int quantity;
	double price;
	Data publication;
}Book;

typedef struct DataMember{
	char memberId[10];
	char name[20];
	char phone[10];
	bool status;
	Book BorrowendBooks[];
}Member;

