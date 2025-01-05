#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include "functions.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int choice;
	int adminChoice;
	int n=0;
	struct Book *book=NULL;
	do{
		menu();
		while(1){
			if(scanf("%d",&adminChoice)!=1){
				printf("Please enter again!\n");
			}else if(adminChoice<0 || adminChoice>1){
				printf("Please enter again!\n");
			}else{
				break;
			}
		}
		switch(adminChoice){
			case 1: 
			Admin();
			do{
				printMenu();
				while(1){
				
				printf("Enter yout choice: ");
				scanf("%d",&choice);
				if(choice<0||choice>7){
					printf("Please enter again");
				}else{
					break;
				}
			}
			switch(choice){
		case 1:
			libraryInput(&book,&n);
			saveBookToFile(book,n);
			printf("Add books to library successfully...\n");
			break;
		case 2:
			showLibrary(book,n);
			printf("Change book information complete...\n");
			break;
		case 3:
			updateBook(book,n);
			saveBookToFile(book,n);
			printf("Update information of books succesfully...\n");
			break;
		case 4:
			deleteBook(&book,&n);
			saveBookToFile(book,n);
			printf("Remove book succesfully...\n");
			break;
		case 5:
			searchBook(book,n);
			break;
		case 6:
			sortByPrice(book,n);
//			saveBookToFile(book,n);
			break;
		case 7:
			printf("DONE!!!");
			break;
			default:
			printf("Choose again!!!\n");
				
			}
		}while(choice!=7);
	}
}while(adminChoice!=0);
return 0;
}
