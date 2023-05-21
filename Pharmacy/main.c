#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

//console window properties
COORD coord = {0, 0};
HANDLE hConsole;
HWND window;

//::::::::::::::::::
/*
	font: Bradley Hand ITC
*/
//::::::::::::::::::
void setWindowPos(){
	if(window != NULL){
		RECT rect;
		int sWidth = GetSystemMetrics(SM_CXSCREEN);
		int sHeight = GetSystemMetrics(SM_CYSCREEN);
		
		GetWindowRect(window, &rect);
		int cWidth = rect.right - rect.left;
		int cHeight = rect.bottom - rect.top;
		
		int positionX = (sWidth - cWidth)/2;
		int positionY = (sHeight - cHeight)/2;
		SetWindowPos(window, NULL, positionX, positionY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);		
	}
}

void setWindowSize(int width, int height){
	if(window != NULL){
		RECT rect;
		GetWindowRect(window, &rect);
		MoveWindow(window, rect.left, rect.top, width, height, TRUE);
	}
}
void pos(int x, int y){
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void consoleWindow(){
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	
	window = GetConsoleWindow();

	if(window != NULL){
		LONG style = GetWindowLong(window, GWL_STYLE);
		style &= ~WS_MAXIMIZEBOX;
		SetWindowLong(window, GWL_STYLE, style);
	}
	if(window != NULL){
		LONG style = GetWindowLong(window, GWL_STYLE);
		style &= ~WS_SIZEBOX;
		SetWindowLong(window, GWL_STYLE, style);
	}
	if(window != NULL){
		SetWindowText(window, "Pharmacy");
	}
	
	if(hConsole != INVALID_HANDLE_VALUE){
		CONSOLE_FONT_INFOEX fontInfo = {0};
		fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
		wcscpy_s(fontInfo.FaceName, LF_FACESIZE, L"Arial Rounded MT");
		fontInfo.dwFontSize.Y = 18;
		fontInfo.FontWeight = 700;		
		SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
	}
	setWindowSize(600, 300);
	setWindowPos();
}

struct drugDetails{
	char drugId [30];
	char drugName[30];
	char manufactureDate[20];
	char expirelyDate [20];
struct prescript{
	int morning;
	int midday;
	int evening;
}p;
	char use[40];
	int price;	
	int quantity;
}d;

struct ctmDetails{
	char firstName [20];
	char surname [20];
	char address [20];
	char gender [20];
	char emailAddress[20];
	char maritalStatus [20];
	char password [20];
	char dateOfBirth [20];
	int phoneNumber;	
}ctm, adm;

struct purchaseDetails{
	char drugId [20];
	char customerName [20];
	char customerSurname[20];
	char customerEmailAddress[20];
	char date[20];
	char time[20];
	int phoneNumber;
	int quantity;
	int totalPayment;
}pd;

long int size;
//my system functions
void menuOptions();
void addDrugs();
void viewRemainingDrugs();
void buyDrugs();
void registration();
void login();
void landingPage();

//including my header files
#include "customer_buy.h"
#include "customer_details.h"

int main (){
	
	consoleWindow();
	landingPage();
	return 0;
	
}


void menuOptions(){
// my code for the menu options
	
	system("cls");
	char * men [4] = {"1. Add drugs", "2. View Remaining Drugs", "3. View Sales Records", "4. exit"};
	int i =0, option;
	
	for(i =0; i < 4; i++){
		printf("%s\n", men[i]);
	}
	
	scanf("%d", &option);
	
	switch(option){
		case 1:{
			addDrugs();
			break;
		}
		case 2:{
			viewRemainingDrugs();
			break;
		}
		default:{
			printf("Invalid input: please check your input");
			break;
		}
	}
}

void addDrugs(){
	system("cls");
	FILE *fp;
	fp = fopen("pharmacy.txt", "ab+");
	
	if(fp == NULL){
		printf("ERROR : file not found");
	}
	else{
		
		printf ("Enter drug ID\n");
		scanf("%s", d.drugId);
		
		printf ("\nEnter drug name\n");
		scanf ("%s", d.drugName);
		
		printf ("\nEnter manufactured date\n");
		scanf ("%s", d.manufactureDate);
		
		printf ("\nEnter expirely date\n");
		scanf ("%s", d.expirelyDate);
	
		printf ("\nEnter prescription\n");
			printf("MORNING : ");
				scanf("%d", &d.p.morning);
			printf("MIDDAY  : ");
				scanf("%d", &d.p.midday);
			printf("EVENING : ");
				scanf("%d", &d.p.evening);
		fflush(stdin);
		printf("\nEnter use\n");
				gets(d.use);
				
		printf ("\nEnter Quantity\n");
		scanf ("%d", &d.quantity);
			
		printf ("\nEnter drug price\n");
		scanf("%d", &d.price);
		
		fwrite(&d, sizeof(d), 1, fp);	
		fclose(fp);	
		
		MessageBox(0,"Data has been successfully recorded","Data Entry",0);
		menuOptions();
	}
}

void viewRemainingDrugs(){
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	WORD originalAttributes = consoleInfo.wAttributes;
	
	system("cls");
	FILE *fp;
	fp = fopen("pharmacy.txt", "rb");
	
	if(fp == NULL){
		MessageBox(0,"FILE NOT FOUND","ERROR 404",0);
		exit(0);
	}
	else{
		int y = 1;
//		table title
		pos(0,0);
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf ("ID");
		pos(10, 0);
		printf ("NAME");
		pos(20, 0);
		printf ("M-Date");
		pos(35, 0);
		printf ("E-Date");
		pos(50, 0);
		printf ("USE");
		pos(70, 0);
		printf ("MM");
		pos(80, 0);
		printf ("MD");
		pos(90, 0);
		printf ("EV");
		pos(100, 0);
		printf ("QTY");
		pos(110, 0);
		printf ("PRICE (mwk)");
		SetConsoleTextAttribute(hConsole, originalAttributes);
			
		while(fread(&d, sizeof(d), 1, fp) != 0){
			pos(0, y);
			printf ("%s", d.drugId);
			pos(10, y);
			printf ("%s", d.drugName);
			pos(20, y);
			printf ("%s", d.manufactureDate);
			pos(35, y);
			printf ("%s", d.expirelyDate);
			pos(50, y);
			printf ("%s", d.use);
			pos(70, y);
			printf ("%d", d.p.morning);
			pos(80, y);
			printf ("%d", d.p.midday);
			pos(90, y);
			printf ("%d", d.p.evening);
			pos(100, y);
			printf ("%d", d.quantity);
			pos(110, y);
			printf ("%d", d.price);
			y++;
		}
		
		printf("\nPress any key to go back..........");
		getche();
		fclose(fp);
		menuOptions();
	}
}

//my landing page
void landingPage(){
	system("cls");
	char choice;
	int i, y = 6;
	char *opt [2]= {"1. Sign Up", "2. Login"};
		for(i =0;  i < 2; ++i){
			pos(26, y);
			printf("%s\n", opt[i]);
			y++;
		}
		pos(28, y+1);
	choice = getche();
	switch(choice){
		case '1':{
			registration();
			break;
		}
		case '2':{
			login();
			break;
		}
		default:{
			printf ("Sorry, invalid choice");
			system("pause");
			system("cls");
			landingPage();
			break;
		}
	}
}

