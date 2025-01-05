#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include<conio.h>

int main(int argc, char *argv[]){
	int userChoice, choiceUser1, choiceAdmin1, choiceSort;
	int n = 0, nCustomer = 0, countStart = 0;
	char check,checkSort;
	Book book[100];
	Member member[100];
	LoadBookFromFile(&n,book);
	do{
		menu();
		while(1){
			if(scanf("%d", &userChoice) != 1){
				printf("\033[31m\nERROR.YOU MUST ENTER [1][2][0]:\033[0m ");
				while((check = getchar()) != '\n' && check != EOF);
			}else if(userChoice < 0 || userChoice > 3){
				printf("\033[31m\nERROR.YOU MUST ENTER [1][2][0]:\033[0m ");
			}else{
				break;
			}
		}
		switch(userChoice){
			case 1:
				Admin();
				do{
					MenuAdmin();
					while(1){
						if(scanf("%d", &choiceAdmin1) != 1){
							printf("\033[31m\nERROR!!!YOU MUST ENTER [1][2][3][4][5][6][7][0]:\033[0m ");
							while((check = getchar()) != '\n' && check != EOF);
						}else if(choiceAdmin1 < 0 || choiceAdmin1 > 8){
							printf("\033[31m\nERROR!!!YOU MUST ENTER [1][2][3][4][5][6][7][0]:\033[0m ");
						}else{
							break;
						}
					}
					switch(choiceAdmin1){
						case 1:
							AddBook(book,&n);
							break;
						case 2:
							DeleteBook(book,&n,countStart);
							break;
						case 3:
							EditBook(book,n);
							saveBookToFile(book,n,&countStart);
							break;
						case 4:
							showAllBookFile(book, n,countStart);
							break;
						case 5:
							SearchBook(book,n);
							break;
						case 6:
							MenuSorting(book,n);
							break;
						case 7:
							MenuCustomerManagement();
							break;
					}
				}while(choiceAdmin1 != 0 );
				break;
		}
	}while(userChoice != 0);
	End();
	return 0;
}
