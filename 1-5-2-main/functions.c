#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<ctype.h> 
//logic ham

void showLibrary(struct Book *book, int n){
	int back;
	do{
	struct Book readFile[1000];
	FILE *fptr= fopen("libraryData.bin","rb");
	if (fptr == NULL){
		printf("Error!!!\n");
		printf("Press any key to return!!\n");
		getchar();
		return;
	}
	n=fread(readFile,sizeof(struct Book),1000,fptr);
	system("cls");
    printf("--------LIBRARY--------\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| Book ID    | Title                        | Price           | Author                       | Quantity | Publication Date    |\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
    int i;
    for (i = 0; i < n; i++) {
        printf("| %-10d | %-28s | %-15.3lf | %-28s | %-8d | %02d/%02d/%04d          |\n", 
               book[i].bookId, 
               book[i].title, 
               book[i].price, 
               book[i].author,
               book[i].quantity,
               book[i].publication.day, 
               book[i].publication.month, 
               book[i].publication.year);
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
    }
    printf("Press 0 to go back the main menu\n");
	scanf("%d",&back); 
	}while(back!=0);
}

void updateBook(struct Book *book,int n){

	system("cls");   
	int flag=0;
	int i;
	int bookId;
	do{
	printf("Enter the ID of book:",n);
	scanf("%d",&bookId);
	getchar();
	flag=0;
	for(i=0;i<n;i++){
		if(book[i].bookId==bookId){
			flag=1;	
			printf("BOOK INFORMATION\n");
			printf("----------------\n");
			printf("Book ID:%d\n",book[i].bookId);
			printf("Book Title:%s\n",book[i].title);
			printf("Book price:%d\n",book[i].price);
			printf("Book author:%d/%d/%d\n",book[i].publication.day,book[i].publication.month,book[i].publication.year);
			printf("\n");
			printf("Update book:\n");
			printf("Update title of book :");
			fgets(book[i].title,30,stdin);
			book[i].title[strcspn(book[i].title,"\n")]='\0';
			format(book[i].title);
			printf("Enter price of book:");
			scanf("%d",&book[i].price);
			getchar();
			printf("Enter author book:");
			fgets(book[i].author,30,stdin);
			book[i].author[strcspn(book[i].author,"\n")]='\0';
			format(book[i].author);
			printf("Update book successfully!\n");
			break;
		}
	}
	if(flag==0){
		printf("This book does not exist!\n");
	}
	} while (flag==0);


}

void deleteBook(struct Book **book, int *n) {
    int back;
    do {
        system("cls");
        printf("Enter the ID of the book to delete: ");
        int bookId;
        scanf("%d", &bookId);
        getchar();
        int flag = 0;
        int i, j;
        for (i = 0; i < *n; i++) {
            if ((*book)[i].bookId == bookId) {
                flag = 1;
                printf("Are you sure you want to delete the book with ID %d? (y/n): ", bookId);
                char confirmation;
                scanf(" %c", &confirmation);
                if (confirmation=='y'||confirmation=='Y') {
                    for (j = i;j<*n-1;j++) {
                    (*book)[j] = (*book)[j + 1];
                    }
                    (*n)--;
                    *book = (struct Book*)realloc(*book, (*n) * sizeof(struct Book));
                    if (*book == NULL && *n > 0) {
                    printf("Memory reallocation failed!\n");
                    exit(1);
                    }
                    printf("Delete book successfully!\n");
                } else {
                    printf("Book deletion canceled.\n");
                }
                break;
            }
        }
        if (flag == 0) {
            printf("This book does not exist.\n");
        }
        printf("Press 0 to go back to the main menu or any other key to delete another book: ");
        scanf("%d", &back);
    } while (back != 0);
}

void sortByPrice(struct Book *book,int n){
	system("cls");
	printf("a. Sort ascending.\n");
	printf("b. Sort descending.\n");
	char option;
	do{
		printf("Choose a or b:");
		scanf(" %c",&option);
	}while(option!='a'&&option!='b');
	if(option=='a'){
		printf("Sort in ascending order...\n");
		int i;
		for(i=0;i<n-1;i++){
			int temp=i;
			int j;
			for(j=i+1;j<n;j++){
				if(book[j].price<book[temp].price){
					temp=j;
				}
			}
			if(temp!=i){
				swap(&book[i],&book[temp]);
			}
		}
	}
	if(option=='b'){
		printf("Sort in descending order...\n");
		int i;
		for(i=0;i<n-1;i++){
			int temp=i;
			int j;
			for(j=i+1;j<n;j++){
				if(book[j].price>book[temp].price){
					temp=j;
				}
			}
			if(temp!=i){
				swap(&book[i],&book[temp]);
			}
		}
	}
	printf("--------LIBRARY--------\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| Book ID    | Title                        | Price           | Author                       | Quantity | Publication Date    |\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
    int i;
    for (i = 0; i < n; i++) {
        printf("| %-10d | %-28s | %-15.3lf | %-28s | %-8d | %02d/%02d/%04d          |\n", 
               book[i].bookId, 
               book[i].title, 
               book[i].price, 
               book[i].author,
               book[i].quantity,
               book[i].publication.day, 
               book[i].publication.month, 
               book[i].publication.year);
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
    }
	printf("Sorting the library by price was successfully!\n");	
}

void searchBook(struct Book *book,int n){
	int back;
	getchar();
	system("cls");
	do{
	printf("Enter title of book :");
	char title[30];
	fgets(title,30,stdin);
	title[strcspn(title,"\n")]='\0';
	format(title);
	int flag=-1;
	int i;
	for(i=0;i<n;i++){
		if(strstr(book[i].title,title)!=NULL){
			flag=i;
		}
	}
	if(flag!=-1){
		printf("--------LIBRARY--------\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| Book ID    | Title                        | Price           | Author                       | Quantity | Publication Date    |\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-10d | %-28s | %-15.3lf | %-28s | %-8d | %02d/%02d/%04d          |\n", 
               book[flag].bookId, 
               book[flag].title, 
               book[flag].price, 
               book[flag].author,
               book[flag].quantity,
               book[flag].publication.day, 
               book[flag].publication.month, 
               book[flag].publication.year);
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
    
	}
	else {
		printf("Book does not exist!\n");
	}
	        printf("Press 0 to go back to the main menu: ");
        scanf("%d", &back);
}while(back!=0);
}

void checkPrice(double *n){
	char check;
	while(1){
		if(scanf("%lf",n)!=1){
			printf("ERROR");
			while((check=getchar())!='\n'&&check!=EOF);
			
		}else if(*n<0){
			printf("ERROR");	
		}else{
			
		}
	}
}
void getPassWord(char *pass,int n){
	int i=0;
	char character;
	while(i<n-1){
		character=getchar();//getch():lay ky tu tu ban phim ma ko hien thi
		if(character==13){//Enter=13
			break;
		} 
		if(character==8){//phim <-back=8
			if(i>0){
				printf("\b \b");
				i--;
			}
		} else {
			printf("*");
			pass[i++]=character;//luu vao mang va tang chi so
		}
	}
	pass[i]='\0';
} 
void Admin(){
	system("cls");
	printf("***LIBRARY MANAGEMENT***\n");
	printf("LOG IN\n");
	getchar();
	char AdminInput[20];
	char AdminPass[20];
	printf("Admin: ");
	fgets(AdminInput, sizeof(AdminInput), stdin);
	AdminInput[strlen(AdminInput) - 1] = '\0';
	printf("Password(max 20): ");
	getPassWord(AdminPass,20);
	printf("\n");
	getchar();
}
void menu(){
	system("cls");
	printf("***LIBRARY MANAGEMENT***\n");
	printf("\n    CHOOSE YOUR ROLE");
	printf("\n========================");
	printf("\n[1] Admin.");
	printf("\n[0] Exit the Program.");
	printf("\n========================");
	printf("\nEnter The Choice: ");
}
void printMenu(){
	system("cls");
	printf("***QUAN LY THU VIEN***\n");
	printf("\n");
	printf("\t-Menu-\n");
	printf("1.Add Book\n");
	printf("2.Show library\n");
	printf("3.Change book information\n") ;
	printf("4.Delete book\n");
	printf("5.Searching book by name\n");
	printf("6.Sort by price\n");
	printf("7.Exit\n");
} 
void checkInputPublication(int *day, int *month, int *years){
    int checkDay, checkMonth, checkYear;
    do {
        checkDay = 0, checkMonth = 0, checkYear = 0;
        scanf("%d %d %d", day, month, years);

        if (*years > 0) {
            checkYear = 1;
        }

        switch (*month) {
            case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
                if (*day <= 31 && *day >= 1) {
                    checkDay = 1;
                }
                checkMonth = 1;
                break;
            case 2:
                if (*years % 400 == 0 || (*years % 4 == 0 && *years % 100 != 0)) {
                    if (*day <= 29 && *day >= 1) {
                        checkDay = 1;
                    }
                } else {
                    if (*day <= 28 && *day >= 1) {
                        checkDay = 1;
                    }
                }
                checkMonth = 1;
                break;
            case 4:
			case 6:
			case 9:
			case 11:
                if (*day <= 30 && *day >= 1) {
                    checkDay = 1;
                }
                checkMonth = 1;
                break;
        }

        if (!checkDay || !checkMonth || !checkYear) {
            printf("Date is invalid,please re-enter: ");
        }
    } while (!checkDay || !checkMonth || !checkYear);
}

void swap(struct Book *x,struct Book*y){
	struct Book temp=*x;
	*x=*y;
	*y=temp;
}
void saveAccToFile(struct Book book[], int n){
	getchar();
	int choice;
	FILE *fptr = fopen("dataMember.bin", "wb");
	if(fptr == NULL){
		printf("Error open file!!!\n");
		printf("PLEASE ENTER RANDOM KEYBOARD TO EXIT!!!");
		getchar();
		return;
	}
	fwrite(book,sizeof(struct Book),n,fptr);
	printf("Save the file successfully!!!");
	fclose(fptr);
	printf("\nEnter '0' to Exit: ");
	scanf("%d", &choice);
}
void saveBookToFile(struct Book book[], int n){
	getchar();
	int choice;
	FILE *fptr = fopen("libraryData.bin", "wb");
	if(fptr == NULL){
		printf("Error open file!!!\n");
		printf("PLEASE ENTER RANDOM KEYBOARD TO EXIT!!!");
		getchar();
		return;
	}
	fwrite(book,sizeof(struct Book),n,fptr);
	printf("Save the file successfully!!!");
	fclose(fptr);
	printf("\nEnter '0' to Exit: ");
	scanf("%d", &choice);
}

void format(char *name){
	size_t len=strlen(name);
	int newword=1;
	int i;
	for(i=0;i<len;i++){
		if(isspace(*(name+i))){
			newword=1;
		}
		else if(newword==1){
			*(name+i)=toupper(*(name+i));
			newword=0;
		}
		else{
			*(name+i)=tolower(*(name+i));
		}
	}
}


void libraryInput(struct Book **book, int *n) {
	int done=0;
    system("cls");
    int currentBook=*n; 
    printf("Enter number of book you want to add: ");
    int newBook;
    scanf("%d", &newBook);
    if (newBook < 1) {
        printf("Plese enter again!\n");
        exit(1); 
    }
    *book=(struct Book*)realloc(*book,(currentBook+newBook)*sizeof(struct Book));
    if (*book==NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    int i;
    for (i=0;i<newBook;i++) {
        printf("Enter book %d:\n",currentBook + i + 1);
        (*book)[currentBook + i].bookId=currentBook+i+1;
        while(1){
            printf("Enter title book: ");
            fflush(stdin);
            fgets((*book)[currentBook+i].title, 30, stdin);
            (*book)[currentBook+i].title[strcspn((*book)[currentBook+i].title,"\n")]='\0';
            format((*book)[currentBook+i].title);
            int titleAvalible=0;
            int j;
            int space=1,checkSpace;
			for(checkSpace=0;checkSpace<strlen((*book)[currentBook+i].title);checkSpace++){
				if(!isspace((*book)[currentBook + i].title[checkSpace])){//ham isspace kiem tra khoang trang,!(dao nguoc toan tu, true==> flase)
					space=0; 
					break;
				}
			}
            for (j=0; j<currentBook+i;j++) {
                if (strcmp((*book)[j].title, (*book)[currentBook + i].title) == 0) {
                    titleAvalible = 1;
                    break;
                }
            }
            if(space){
            	printf("Please enter again\n");
			}
            if (strlen((*book)[currentBook + i].title) == 0) {
                printf("Please enter again\n");
            } else if (titleAvalible) {
                printf("Title already exists, please enter again.\n");
            } else {
            	done=1;
                break;
            }
        } 
        printf("Enter author book: ");
        getchar();
        fgets((*book)[currentBook + i].author, 30, stdin);
        (*book)[currentBook + i].author[strcspn((*book)[currentBook + i].author, "\n")] = '\0';
        format((*book)[currentBook + i].author);
        
        	int test;
        	int index;
        	char input1[10];
        	char *input;
        	printf("Enter price of book: ");
        	checkPrice(&book[currentBook + i]->price);
//			while (1) {
//        		if (scanf("%lf", &book[currentBook + i]) != 1) {
//            		printf("Invalid input. Please enter a valid number.\n");
//            			char c;
//            			while ((c = getchar()) != '\n' && c != EOF);
//            			
//        		}else if((book[currentBook + i] < 1)){
//        			printf("Price must be greater than 0. Please enter again.\n");
//				}else{
//					break;
//				}
//    		}
    	getchar();	
    	fflush(stdin);

        
        while (1) {
            printf("Enter quantity of book: ");
            scanf("%d", &(*book)[currentBook + i].quantity);
            if ((*book)[currentBook + i].quantity <= 0) {
                printf("Quantity must be greater than 0. Please enter again.\n");
            } else {
                break;
            }
        }
        printf("Enter publication date (dd mm yyyy): ");
        checkInputPublication(&(*book)[currentBook + i].publication.day, &(*book)[currentBook + i].publication.month, &(*book)[currentBook + i].publication.year);
        printf("\n");
        *n = currentBook + newBook;
    }
 
}
//void libraryInput(struct Book **book,int *n){
//	system("cls");
//	if(*book!=NULL){
//		free(*book);
//	}
//	int count=*n;
//	int newcount;
//	printf("Enter the number of books :");
//	scanf("%d",&newcount);
//	if(newcount<1){
//		printf("Invalid number of book !\n");
//		exit(1);
//	}
//	*book=(struct Book*)malloc(*n*sizeof(struct Book));
//	if(*book==NULL){
//		printf("Memory allocation failed !\n");
//		exit(1);
//	}
//	int i;
//	for (i=0;i<newcount;i++){
//		printf("Enter book %d:\n",count+i+1);
//		(*book)[count+i].bookId=count+i+1;
//		while(1){
//		printf("Enter title book :");
//		getchar();
//		fgets((*book)[count+i].title,30,stdin);
//		(*book)[count+i].title[strcspn((*book)[count+i].title,"\n")]='\0';
//		format((*book)[count+i].title);
//		int titleAvalible=0;
//		int j;
//		for(j=0;j<count+i;j++){
//		if (strcmp((*book)[j].title, (*book)[count + i].title) == 0) {{
//				titleAvalible=1;
//				break;
//			}
//		}
//		if(strlen((*book)[i].title)==0){
//		printf("Please enter again");
//		getchar();
//		}else if(strcmp((*book)[i].title,"Book ID")==0){
//		printf("Title cant not be the same as ID book,please enter again.\n");
//		getchar;
//		} else{
//			break;
//		}
//	}
//		printf("Enter price book:");
//		scanf("%d",&(*book)[i].price);
//		getchar();
//		printf("Enter author book:");
//		getchar();
//		fgets((*book)[count+i].author,30,stdin);
//		(*book)[count+i].author[strcspn((*book)[count+i].author,"\n")]='\0';
//		format((*book)[count+i].author);
//		printf("Enter quantity of book:");
//		scanf("%d",&(*book)[i].quantity);
//		getchar();
//		printf("Enter publication date (dd mm yyyy): ");
//        checkInputPublication(&(*book)[i].publication.day, &(*book)[i].publication.month, &(*book)[i].publication.year);
//		printf("\n");
//		
//	}	
//	*n=count+newcount;
//}





//void deleteBook(struct Book **book, int *n) {
//    int back;
//    do {
//        system("cls");
//        printf("Enter the ID of the book to delete: ");
//        int bookId;
//        scanf("%d", &bookId);
//        getchar();
//        int flag = 0;
//        int i, j;
//        for (i = 0; i < *n; i++) {
//            if ((*book)[i].bookId == bookId) {
//                for (j=i;j<*n - 1; j++) {
//                    (*book)[j]=(*book)[j + 1];
//                }
//                flag = 1;
//                (*n)--; 
//                *book = (struct Book*)realloc(*book, (*n) * sizeof(struct Book));
//                if (*book == NULL && *n > 0) {
//                    printf("Memory reallocation failed!\n");
//                    exit(1);
//                }
//                printf("Delete book successfully!\n");
//                break; 
//            }
//        }
//        if(flag==0) {
//            printf("This book does not exist.\n");
//        }
//        printf("Press 0 to go back to the main menu: ");
//        scanf("%d", &back);
//    } while (back != 0);
//}

//void add_book(struct Book **book,int *n){
//	*n+=1;
//	*book=(struct Book *)realloc(*book,*n*sizeof(struct Book));
//	printf("Enter the location(0-%d):",*n);
//	int pos;
//	scanf("%d",&pos);
//	getchar();
//	if(pos==0){
//		pos=1;
//	}
//	if(pos<1||pos>*n){
//		printf("Invalid location!\n");
//		return;
//	}
//	for(int i=*n;i>=pos;i--){
//		book[i]=book[i-1];
//	}
//	printf("New book:\n");
//	(*book)[pos-1].code=*n+1000-1;
//	printf("Enter title of book :");
//	fgets((*book)[pos-1].title,30,stdin);
//	(*book)[pos-1].title[strcspn((*book)[pos-1].title,"\n")]='\0';
//	format((*book)[pos-1].title);
//	printf("Enter price of book:");
//	scanf("%d",&(*book)[pos-1].price);
//	getchar();
//	printf("Enter author book:");
//	fgets((*book)[pos-1].author,30,stdin);
//	(*book)[pos-1].author[strcspn((*book)[pos-1].author,"\n")]='\0';
//	format((*book)[pos-1].author);
//	printf("Add book successfully!\n");
//}








