#include<stdio.h>
#include"functions.h"
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>

int add() {
  static int total = 0;
  total ++;
  return total;
}

int LoadBookFromFile(int *n, Book book[]){
	FILE *file = fopen("dataBook.bin", "rb");
	if(file == NULL){
		printf("\n\033[31mERROR.Not open file!!!\033[0m");
		return 0;
	}
	*n = 0;
    while (fscanf(file, "%[^,],%[^,],%[^\n]\n", book[*n].bookId, book[*n].title, book[*n].author) == 3){
        (*n)++;
        if (*n >= 100) {
            printf("Lỗi: Số lượng sách vượt quá giới hạn!\n");
            break;
        }
	}
	fclose(file);
    return 1;
}

void menu(){
	system("cls");
	printf("\033[32m***LIBRARY MANAGEMENT***\033[0m");
	printf("\n    CHOOSE YOUR ROLE");
	printf("\n========================");
	printf("\n[1] Admin.");
	printf("\n[0] Exit the Program.");
	printf("\n========================");
	printf("\nEnter The Choice: ");
}

void getPassWordAdmin(char *pass, int length){
    int i = 0;
    char ch;
    while (i < length - 1) {
        ch = getch();
		if(length > 21){
			break;
		}
        if (ch == 13){
            break;
        }
        if (ch == 8){
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else {
            printf("*");
            pass[i++] = ch;
        }
    }
    pass[i] = '\0';
}

void checkInput(int *n){
	char check;
	while(1){
		if(scanf("%d", n) != 1){
			printf("\033[31m\nERROR!!!YOU MUST ENTER INTEGEN:\033[0m ");
			while((check = getchar()) != '\n' && check != EOF);
		}else if(*n < 0){
			printf("\033[31mERROR.Negative Number!!!\033[0m");
		}else{
			break;
		}
	}
}

void checkInputFloat(double *n){
	char check;
	while(1){
		if(scanf("%lf", n) != 1){
			printf("\033[31m\nERROR!!!YOU MUST ENTER INTEGEN OR FLOAT:\033[0m ");
			while((check = getchar()) != '\n' && check != EOF);
		}else if(*n < 0){
			printf("\033[31mERROR.Negative Number!!!\033[0m");
		}else{
			break;
		}
	}
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
            printf("\033[31mWARNING: THE DATE YOU ENTER IS INVALID. PLEASE RE-ENTER:\033[0m ");
        }
    } while (!checkDay || !checkMonth || !checkYear);
}

int checkInputCharater(char *string, char charater){

	for(int i = 0; i < strlen(string); i++){
		string[i] = toupper(string[i]);
		if(string[i] == charater){
			return 1;
		}
	}
	return 0;
}

int checkNameBook(Book book[], int bookCount, const char *title) {
	Book readFile[100];
	FILE *fptr = fopen("dataBook.bin","rb");
	int n = fread(readFile,sizeof(Book),100,fptr);
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(book[i].title, title) == 0) {
			fclose(fptr);
            return 1;
        }
    }
	for (int i = 0; i < n; i++) {
		if (strcmp(readFile[i].title,title) == 0) {
			fclose(fptr);
            return 1;
        }
    }

	fclose(fptr);
    return 0;
}

int checkBookId(Book book[], int bookCount, const char *id) {
	Book readFile[100];
	FILE *fptr = fopen("dataBook.bin","rb");
	int n = fread(readFile,sizeof(Book),100,fptr);
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(book[i].bookId,id) == 0) {
			fclose(fptr);
            return 1;
        }
    }
	for (int i = 0; i < n; i++) {
		if (strcmp(readFile[i].bookId,id) == 0) {
			fclose(fptr);
            return 1;
        }
    }

	fclose(fptr);
    return 0;
}

void checkInputId(char id[], int length,Book book[], int n){
	while(1){
		fgets(id,10,stdin);
		id[strcspn(id,"\n")] = '\0';
		if(strchr(id,' ') != NULL){
			printf("\n\033[31mERROR.ID not have space!!!\033[0m");
		}else if(checkBookId(book,n,id)){
			printf("\n\033[31mERROR.The title already exit!!!Enter again!!!\033[0m\n");
		}else{
			break;
		}
	}
}

void Admin(){
	system("cls");
	printf("\033[32m***LIBRARY MANAGEMENT***\033[0m\n");
	printf("LOG IN\n");
	printf("========================\n");
	getchar();
	char AdminInput[20]; char AdminPass[20];
	printf("Admin: ");
	fgets(AdminInput, sizeof(AdminInput), stdin);
	AdminInput[strlen(AdminInput) - 1] = '\0';
	printf("Password(max 20 charate): ");
	getPassWordAdmin(AdminPass,20);
	printf("\n========================\n");
	getchar();
}

void End(){
	system("cls");
	printf("========= THANK YOU =========\n");
	printf("======== SEE YOU SOON =======\n");
	printf("\n");
	printf("_____________________________\n");
}

void MenuAdmin(){
	system("cls");
	printf("\033[32m***LIBRARY MANAGEMENT***\033[0m\n");
	printf("Menu admin\n");
	printf("========================\n");
	printf("[1] Add a new book.\n");
	printf("[2] Delete a book.\n");
	printf("[3] Edit a book.\n");
	printf("[4] Show all books.\n");
	printf("[5] Search a book,\n");
	printf("[6] Sorting.\n");
	printf("[7] Customer Management.\n");
	printf("[0] Exit program.\n");
	printf("========================\n");
	printf("Enter the choice: ");
}

void MenuSorting(Book book[], int n){
	int choice = -1;
	char check;
	system("cls");
	printf("\033[32m***LIBRARY MANAGEMENT***\033[0m\n");
	printf("Menu Status\n");
	printf("========================\n");
	printf("[1] Up sort.\n");
	printf("[2] Down sort.\n");
	printf("========================\n");
	printf("Enter the choice: ");
	while(1){
		if(scanf("%d", &choice) != 1){
			printf("\033[31m\nERROR!!!YOU MUST ENTER [1][2]:\033[0m ");
			while((check = getchar()) != '\n' && check != EOF);
		}else if(choice < 0 || choice > 3){
			printf("\033[31m\nERROR!!!YOU MUST ENTER [1][2]:\033[0m ");
		}else{
			break;
		}
	}
	switch (choice){
		case 1:
			UpSort(book,n);
			saveSortBook(book,n);
			break;
		case 2:
			DownSort(book,n);
			saveSortBook(book,n);
			break;
	}
}

void UpSort(Book book[], int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n - i - 1; j++){
			if(book[j].price < book[j+1].price){
				Book temp = book[j];
				book[j] = book[j + 1];
				book[j + 1] = temp;
			}
		}
	}

}

void DownSort(Book book[], int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n - i - 1; j++){
			if(book[j].price > book[j+1].price){
				Book temp = book[j];
				book[j] = book[j + 1];
				book[j + 1] = temp;
			}
		}
	}
}

void AddBook(Book book[],int *n){
	int number;
	char check;
	int countStart;
	system("cls");
	printf("\033[32m***LIBRARY MANAGEMENT***\033[0m\n");
	printf("========================\n");
	getchar();
	while(1){
		printf("Enter Book Id: ");
		checkInputId(book[*n].bookId,10,book,*n);
		printf("Enter name book: ");
		InformationCannotBeLeftBlank(book[*n].title,30,book,*n);
		printf("Enter author book: ");
		InformationCannotBeLeftBlank(book[*n].author,20,book,*n);
		lowercaseSwap(book[*n].author,strlen(book[*n].author));
		uppercaseFirstLetter(book[*n].author);
		book[*n].author[strcspn(book[*n].author,"\n")] = '\0';
		printf("Enter quantity: ");
		checkInput(&book[*n].quantity);
		printf("Enter price: ");
		checkInputFloat(&book[*n].price);
		getchar();
		printf("Enter publication: ");
		checkInputPublication(&book[*n].publication.day, &book[*n].publication.month, &book[*n].publication.year);
		getchar();
		FILE *fptr = fopen("dataBook.bin", "ab");
		if(fptr == NULL){
			printf("\033[31mError open file!!!\n");
			printf("PLEASE ENTER RANDOM KEYBOARD TO EXIT!!!\033[0m");
			getchar();
			return;
		}
		fwrite(book,sizeof(Book),1,fptr);
		printf("\033[32mSave the file successfully!!!\033[0m");
		fclose(fptr);
		char choice;
		*n = add();
        printf("\nDo you want continue? (y/n): ");
        scanf(" %c", &choice);
        // clearInputBuffer();
        if (choice == 'n' || choice == 'N') {
            break;
        }
		getchar();
	}
		
}
void deleteBufferMemory(){
	int c;
    while ((c = getchar()) != '\n' && c != EOF){
    }
}

void InformationCannotBeLeftBlank(char str[], int length,Book book[], int n){
	while(1){
		fgets(str,length,stdin);
		lowercaseSwap(book[n].title,strlen(book[n].title));
		uppercaseFirstLetter(book[n].title);
		str[strcspn(str,"\n")] = '\0';
		if (strlen(str) == length - 1 && str[length - 2] != '\0') {
            printf("\n\033[31mError: String max length!!!Enter again.\033[0m");
            deleteBufferMemory();
        } else if (strlen(str) == 0) {
            printf("\n\033[31mError: String cannot be left blank!!!Enter again.\033[0m");
        } else if (checkNameBook(book,n,str)) {
			printf("\n\033[31mError: The title already exists!!!Enter again.\033[0m");
		}else {
            break;
        }
	}
}

void checkInputInformationCustomer(char str[], int length,Member member[], int n){
	while(1){
		fgets(str,length,stdin);
		str[strcspn(str,"\n")] = '\0';
		if (strlen(str) == length - 1 && str[length - 2] != '\0') {
            printf("\n\033[31mError: String max length!!!Enter again.\033[0m");
            deleteBufferMemory();
        } else if (strlen(str) == 0) {
            printf("\n\033[31mError: String cannot be left blank!!!Enter again.\033[0m");
        } else if (member,n,str) {
			printf("\n\033[31mError: String cannot be left blank!!!Enter again.\033[0m");
		}else {
            break;
        }
	}
}

void saveBookToFile(Book *book, int n,int *countStart){
	getchar();
	int choice;
	FILE *fptr = fopen("dataBook.bin", "ab");
	if(fptr == NULL){
		printf("\033[31mError open file!!!\n");
		printf("PLEASE ENTER RANDOM KEYBOARD TO EXIT!!!\033[0m");
		getchar();
		return;
	}
	fwrite(book,sizeof(Book),n,fptr);
	printf("\033[32mSave the file successfully!!!\033[0m");
	fclose(fptr);
	printf("\nEnter '0' to Exit: ");
	scanf("%d", &choice);
}

void saveSortBook(Book book[], int n){
	getchar();
	int choice;
	FILE *fileOpen = fopen("sortBook.bin", "wb");
	if(fileOpen == NULL){
		printf("\033[31mError open file!!!\n");
		printf("PLEASE ENTER RANDOM KEYBOARD TO EXIT!!!\033[0m");
		getchar();
		return;
	}
	fwrite(book,sizeof(Book),n,fileOpen);
	fclose(fileOpen);
	Book readFile[1000];
	FILE *fileRead = fopen("sortBook.bin", "rb");
	if(fileRead == NULL){
		printf("\033[31mError open file!!!\n");
		printf("PLEASE ENTER RANDOM KEYBOARD TO EXIT!!!\033[0m");
		getchar();
		return;
	}
	n = fread(readFile, sizeof(Book), 1000, fileRead);
	printf("\n***BOOKS AFTER SORTNG***\n\n");
	printf("|==========|==============================|====================|==========|====================|==========|");
	printf("\n|ID\t   |BOOK\t\t\t  |AUTHOR\t       |QUANTITY  |PRICE\t       |PUBL\t  |\n");
	printf("|==========|==============================|====================|==========|====================|==========|");
	for(int i=0;i<n;i++){
		printf("\n|%-10s|",book[i].bookId);
		printf("%-30s|",book[i].title);
		printf("%-20s|",book[i].author);
		printf("%-10d|",book[i].quantity);
		printf("%-20.3lf|",book[i].price);
		printf("%-2d/%-2d/%-4d|", book[i].publication.day, book[i].publication.month, book[i].publication.year);
		printf("\n|----------|------------------------------|--------------------|----------|--------------------|----------|");
	}
	
	printf("\n\n\033[32mSorting success!!!\033[0m\n");
	fclose(fileRead);
	sortIdBook(book, n);
	printf("\nEnter '0' to back: ");
	scanf("%d", &choice);
}

void sortIdBook(Book book[], int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n - i - 1; j++){
			if(book[j].bookId > book[j + 1].bookId){
				Book temp = book[j];
				book[j] = book[j+1];
				book[j + 1] = temp;
			}
		}
	}
}

void showAllBookFile(Book book[], int n,int countStart){
	system("cls");
	int choice;
	Book readFile[1000];
	FILE *fptr = fopen("dataBook.bin", "rb");
	if(fptr == NULL){
		printf("\033[31mError open file!!!\n");
		printf("PLEASE ENTER RANDOM KEYBOARD TO EXIT!!!\033[0m");
		getchar();
		return;
	}
	n = fread(readFile, sizeof(Book), 1000, fptr);
	printf("***ALL BOOKS***\n\n");
	printf("|==========|==============================|====================|==========|====================|==========|");
	printf("\n|ID\t   |BOOK\t\t\t  |AUTHOR\t       |QUANTITY  |PRICE\t       |PUBL\t  |\n");
	printf("|==========|==============================|====================|==========|====================|==========|");
	for(int i=0;i<n;i++){
		printf("\n|%-10s|",readFile[i].bookId);
		printf("%-30s|",readFile[i].title);
		printf("%-20s|",readFile[i].author);
		printf("%-10d|",readFile[i].quantity);
		printf("%-20.3lf|",readFile[i].price);
		printf("%-2d/%-2d/%-4d|", readFile[i].publication.day, readFile[i].publication.month, readFile[i].publication.year);
		printf("\n|----------|------------------------------|--------------------|----------|--------------------|----------|");
	}
	
	printf("\n\n\033[32mLAY DU LIEU THANH CONG\033[0m\n");
	fclose(fptr);
	printf("\nEnter '0' to back: ");
	scanf("%d", &choice);
}

void EditBook(Book book[], int n){
	sortIdBook(book, n);
	system("cls");
	getchar();
	int flag = -1;
	char position[10];
	printf("Enter the book id you want to edit: ");
	scanf("%s", position);
	do{
	flag = -1;
	for(int i = 0; i < n; i++){
		if(strcmp(book[i].bookId, position) == 0){
			flag = i;
		}
	}
	if(flag == -1){
		printf("\033[31mBook id dose NOT EXSIT!!\033[0m");
		printf("\033[31m\nPLEASE ENTER AGAIN: \033[0m");
		scanf("%s", position);
	}
	}while(flag == -1);
	printf("\n\033[36m***THE INFOR OLD BOOK***\033[0m\n");
	printf("\nBook id: %s",book[flag].bookId);
	printf("\nBook name: %s",book[flag].title);
	printf("\nAuthor: %s",book[flag].author);
	printf("\nQuantity: %d",book[flag].quantity);
	printf("\nPrice: %.3lf",book[flag].price);
	printf("\nPublication: %d/%d/%d\n", book[flag].publication.day, book[flag].publication.month, book[flag].publication.year);
	printf("\n\033[36m***UPDATE THE NEW BOOK***\033[0m\n");
	getchar();
	printf("Enter name book: ");
	fgets(book[flag].title,30,stdin);
	book[flag].title[strcspn(book[flag].title,"\n")] = '\0';
	printf("Enter author book: ");
	fgets(book[flag].author,20,stdin);
	book[flag].author[strcspn(book[flag].author,"\n")] = '\0';
	printf("Enter quantity: ");
	checkInput(&book[flag].quantity);
	printf("Enter price: ");
	checkInputFloat(&book[flag].price);
	getchar();
	printf("Enter publication: ");
	checkInputPublication(&book[flag].publication.day, &book[flag].publication.month, &book[flag].publication.year);
}

void Delete(Book book[], int *n, char positionDelele[],int countStart){
	for(int i = atoi(positionDelele) - 2; i < *n; i++){
		book[i] = book[i+1];
	}
	*n = *n - 1;
	saveBookToFile(book,*n,&countStart);
}
   
void DeleteBook(Book book[], int *n,int countStart){
	system("cls");
	getchar();
	int flag = -1;
	char position[10];
	char userChoice[10];
	char temp[10];
	printf("Enter id you want to delete: ");
	scanf("%s", position);
	do{
		flag = -1;
		for(int i = 0; i < *n; i++){
			if(strcmp(book[i].bookId , position) == 0){
				flag = i;
			}
		}
		if(flag == -1){
			printf("\033[31mBook id dose NOT EXSIT!!\033[0m");
			printf("\033[31m\nPLEASE ENTER AGAIN:\033[0m ");
			scanf("%s", position);
		}
	}while(flag == -1);
	Book readBook[10];
	FILE *fptr = fopen("dataBook.bin", "rb");
	if(fptr == NULL){
		printf("\033[31mERROR OPEN FILE!!!");
		printf("PLEASE ENTER RANDOM KEYBOARD TO EXIT!!!\033[0m");
		getchar();
		return;
	}
	*n = fread(readBook,sizeof(Book),10,fptr);
	printf("\n\033[36m***BOOKS BEFORE DELETE***\033[0m\n");
	printf("\nBook id: %s",readBook[flag].bookId);
	printf("\nBook name: %s",readBook[flag].title);
	printf("\nAuthor: %s",readBook[flag].author);
	printf("\nQuantity: %d",readBook[flag].quantity);
	printf("\nPrice: %.3lf",readBook[flag].price);
	printf("\nPublication: %d/%d/%d\n", readBook[flag].publication.day, readBook[flag].publication.month, readBook[flag].publication.year);
	fclose(fptr);
	printf("\n\033[36mAre you sure want to delete this book? (Y/N):\033[0m ");
	int check = 0;
	char yes = 'Y';
	char no = 'N';
	scanf("%s", userChoice);
	while(1){
		if(checkInputCharater(userChoice,yes)){
			printf("\n\033[32mBooks delete success!!!\033[0m\n");
			for(int i = atoi(position) - 2; i < *n; i++){
				book[i] = book[i+1];
			}
			*n = *n - 1;
			saveBookToFile(book,*n,&countStart);
			getchar();
			break;
		}else if(checkInputCharater(userChoice,no)){
			printf("\n\033[33mBooks delete failed!!!\033[0m");
			printf("\nPLEASE ENTER RANDOM KEYBOARD TO EXIT!!!");
			getchar();
			getchar();
			break;
		}else{
			printf("\n\033[31mERROR.You must enter [Y/N], enter again:\033[0m ");
			scanf("%s", userChoice);
		}
	}
	
}

void uppercaseFirstLetter(char nameBook[]) {
    int check = 0;
	int length = strlen(nameBook);
    for(int i = 0; i < length; i++){
    	if(!check&& isalpha(nameBook[i])){
			nameBook[i] = toupper(nameBook[i]);
			check = 1;    		
		}else if(isspace(nameBook[i])){
			check = 0;
		}
	}
}

void lowercaseSwap(char nameBook[], int n){
	for(int i = 0; i < n; i++){
		nameBook[i] = tolower(nameBook[i]);
	}
}

void SearchBook(Book book[], int n){
	system("cls");
	getchar();
	char inportNameBook[30];
	printf("Enter the book title: ");
	fgets(inportNameBook,30,stdin);
	inportNameBook[strcspn(inportNameBook,"\n")] = '\0';
	Book readFile[1000];
	FILE *fptr = fopen("dataBook.bin", "rb");
	if(fptr == NULL){
		printf("\033[31mError open file!!!\n");
		printf("PLEASE ENTER RANDOM KEYBOARD TO EXIT!!!\033[0m");
		getchar();
		return;
	}
	int check = 0;
	n = fread(readFile, sizeof(Book), 1000, fptr);
	printf("\n|==========|==============================|====================|==========|====================|==========|");
	printf("\n|ID\t   |BOOK\t\t\t  |AUTHOR\t       |QUANTITY  |PRICE\t       |PUBL\t  |\n");
	printf("|==========|==============================|====================|==========|====================|==========|");
	for(int i = 0; i < n; i++){
		if(strstr(book[i].title,inportNameBook)!=NULL){
			printf("\n|%-10s|",readFile[i].bookId);
			printf("%-30s|",readFile[i].title);
			printf("%-20s|",readFile[i].author);
			printf("%-10d|",readFile[i].quantity);
			printf("%-20.3lf|",readFile[i].price);
			printf("%-2d/%-2d/%-4d|", readFile[i].publication.day, readFile[i].publication.month, readFile[i].publication.year);
			printf("\n|----------|------------------------------|--------------------|----------|--------------------|----------|");
			check++;
		} 
	}
	if(check == 0){
		printf("\n\033[31mBOOK NOT FOUND\033[0m");
		printf("\nEnter random keyboard to continute....");
		getchar();
	}
	fclose(fptr);
	printf("\nPLEASE PRESS ENTER TO EXIT...\033[0m");
	getchar();
}

void MenuCustomerManagement(){
	int countStart;
	int choice = -1;
	char check;
	Member member[100];
	int n = 0;
	do{
		system("cls");
		printf("\033[32m***LIBRARY MANAGEMENT***\033[0m\n");
		printf("Menu Customer Management\n");
		printf("========================\n");
		printf("[1] All Customer.\n");
		printf("[2] Add Customer.\n");
		printf("[3] Edit Infomation Customer.\n");
		printf("[4] Block customer.\n");
		printf("[5] Search Custormer.\n");
		printf("[6] Lend Books.\n");
		printf("[7] Return borrowed books.\n");
		printf("[0] Back.\n");
		printf("========================\n");
		printf("Enter the choice: ");
		while(1){
			if(scanf("%d", &choice) != 1){
				printf("\033[31m\nERROR!!!YOU MUST ENTER [1][2][3][4][5][6][7][0]:\033[0m ");
				while((check = getchar()) != '\n' && check != EOF);
			}else if(choice < 0 || choice > 8){
				printf("\033[31m\nERROR!!!YOU MUST ENTER [1][2][3][4][5][6][7][0]:\033[0m ");
			}else{
				break;
			}
		}
		switch(choice){
			case 1:
				ShowAllInformationCustomer(member,n,countStart);
				break;
			case 2:
				AddCustomer(member, &n);
				SaveInfomationToFile(member,n);
				break;
			case 3:
				EditInformationCustomer(member,n);
				SaveInfomationToFile(member,n);
				break;
			case 4:
				break;
			case 5:
				SearchCustomer(member,n);
				break;
			case 6:
				break;
			case 7:
				break;
		}
	}while(choice != 0);
}

void ShowAllInformationCustomer(Member member[], int n,int countStart){
	system("cls");
	int choice;
	Member readInforMember[1000];
	FILE *fptr = fopen("dataMember.bin", "rb");
	if(fptr == NULL){
		printf("\033[31mError open file!!!\n");
		printf("PLEASE ENTER RANDOM KEYBOARD TO EXIT!!!\033[0m");
		getchar();
		return;
	}
	int v = 0;
	n = fread(readInforMember, sizeof(Member), 1000, fptr);
	printf("***ALL Member***\n\n");
	printf("|==========|====================|==========|==========|=========================|");
	printf("\n|ID\t   |Name\t\t|Phone\t   |Status    |BorrowendBooksE\t        |\n");
	printf("|==========|====================|==========|==========|=========================|");
	for(int i=0;i<n;i++){
		printf("\n|%-10s|",readInforMember[i].memberId);
		printf("%-20s|",readInforMember[i].name);
		printf("%-10s|",readInforMember[i].phone);
		printf("%-10d|",readInforMember[i].status);
		printf("%-25d|", v);
		printf("\n|----------|--------------------|----------|----------|-------------------------|");
	}
	
	printf("\n\n\033[32mLAY DU LIEU THANH CONG\033[0m\n");
	fclose(fptr);
	printf("\nEnter '0' to back: ");
	scanf("%d", &choice);
}

int countIdCustomer() {
    static int id = 0;
    id++;
    return id;
}

void AddCustomer(Member member[],int *n){
	int number;
	char check;
	system("cls");
	getchar();
	printf("\033[32m***CUSTOMER MANAGEMENT***\033[0m\n");
	printf("========================\n");
	sprintf(member[*n].memberId, "%d", countIdCustomer());
	printf("Enter name customer: ");
	checkInputInformationCustomer(member[*n].name,20,member,*n);
	lowercaseSwap(member[*n].name,strlen(member[*n].name));
	uppercaseFirstLetter(member[*n].name);
	member[*n].name[strcspn(member[*n].name,"\n")] = '\0';
	printf("Enter phone: ");
	fgets(member[*n].phone,10,stdin);
	member[*n].phone[strcspn(member[*n].phone,"\n")] = '\0';
	(*n)++;	
}

void SaveInfomationToFile(Member member[], int n){
	int choice;
	FILE *fptr = fopen("dataMember.bin", "wb");
	if(fptr == NULL){
		printf("\033[31mError open file!!!\n");
		printf("PLEASE ENTER RANDOM KEYBOARD TO EXIT!!!\033[0m");
		getchar();
		return;
	}
	fwrite(member,sizeof(Member),n,fptr);
	printf("\033[32mSave the file successfully!!!\033[0m");
	fclose(fptr);
	printf("\nEnter '0' to Exit: ");
	scanf("%d", &choice);
}

void EditInformationCustomer(Member member[], int n){
	system("cls");
	getchar();
	int flag = -1;
	char position[10];
	printf("Enter the customer id you want to edit: ");
	scanf("%s", position);
	do{
	flag = -1;
	for(int i = 0; i < n; i++){
		if(strcmp(member[i].memberId, position) == 0){
			flag = i;
		}
	}
	if(flag == -1){
		printf("\033[31mCustomer id dose NOT EXSIT!!\033[0m");
		printf("\033[31m\nPLEASE ENTER AGAIN: \033[0m");
		scanf("%s", position);
	}
	}while(flag == -1);
	Member readMember[1000];
	FILE *fptr = fopen("dataMember.bin", "rb");
	if(fptr == NULL){
		printf("\033[31mError open file!!!\n");
		printf("PLEASE ENTER RANDOM KEYBOARD TO EXIT!!!\033[0m");
		getchar();
		return;
	}
	n = fread(readMember, sizeof(Member), 1000, fptr);
	printf("\n\033[36m***THE INFOR OLD CUSTOMER***\033[0m\n");
	printf("\nCustomer id: %s",readMember[flag].memberId);
	printf("\nName: %s",readMember[flag].name);
	printf("\nPhone: %s",readMember[flag].phone);
	fclose(fptr);
	printf("\n\033[36m***UPDATE THE NEW INFORMATION CUSTOMER***\033[0m\n");
	getchar();
	printf("Enter name customer: ");
	fgets(member[flag].name,20,stdin);
	member[flag].name[strcspn(member[flag].name,"\n")] = '\0';
	printf("Enter phone: ");
	fgets(member[flag].phone,10,stdin);
	member[flag].phone[strcspn(member[flag].phone,"\n")] = '\0';
	printf("\n\033[33mEdit information customer success!!!\033[0m");
	getchar();
}

void SearchCustomer(Member member[], int n){
	system("cls");
	getchar();
	char inportNameCutomer[20];
	int flag = -1;
	printf("Enter the customer name: ");
	fgets(inportNameCutomer,20,stdin);
	inportNameCutomer[strcspn(inportNameCutomer,"\n")] = '\0';
	lowercaseSwap(inportNameCutomer,strlen(inportNameCutomer));
	uppercaseFirstLetter(inportNameCutomer);
	for(int i = 0; i < n ; i++){
		if(strcmp(member[i].name,inportNameCutomer) == 0){
			flag = i;
		}
	}
	if(flag == -1){
		printf("\n\033[31mCUSTOMER NOT FOUND\033[0m");
		printf("\nEnter random keyboard to continute....");
		getchar();
	}else{
		int choice;
		Member readInforMember[1000];
		FILE *fptr = fopen("dataMember.bin", "rb");
		if(fptr == NULL){
			printf("\033[31mError open file!!!\n");
			printf("PLEASE ENTER RANDOM KEYBOARD TO EXIT!!!\033[0m");
			getchar();
			return;
		}
		int v = 0;
		n = fread(readInforMember, sizeof(Member), 1000, fptr);
		printf("***ALL Member***\n\n");
		printf("|==========|====================|==========|==========|=========================|");
		printf("\n|ID\t   |Name\t\t|Phone\t   |Status    |BorrowendBooksE\t        |\n");
		printf("|==========|====================|==========|==========|=========================|");
		printf("\n|%-10s|",readInforMember[flag].memberId);
		printf("%-20s|",readInforMember[flag].name);
		printf("%-10s|",readInforMember[flag].phone);
		printf("%-10d|",readInforMember[flag].status);
		printf("%-25d|", v);
		printf("\n|----------|--------------------|----------|----------|-------------------------|");
		printf("\n\n\033[32mLAY DU LIEU THANH CONG\033[0m\n");
		fclose(fptr);
		printf("\nEnter '0' to back: ");
		scanf("%d", &choice);
		}
}

