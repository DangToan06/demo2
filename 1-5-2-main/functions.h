#include "datatypes.h"
//nguyen mau ham
void Admin();
void menu();
void printMenu();
void format(char *name); 
void libraryInput(struct Book **book,int *n);
void updateBook(struct Book *book,int n);
void showLibrary(struct Book *book,int n); 
void deleteBook(struct Book **book,int *n);
void addBook(struct Book **book, int *n);
void saveBookToFile(struct Book book[], int n);
void swap(struct Book *x,struct Book*y);
void checkInputPublication(int *day, int *month, int *years);
void sortByPrice(struct Book *book,int n);
void searchBook(struct Book *book,int n);

//void checkDate(struct Date )
//void checkIdBook
//	
