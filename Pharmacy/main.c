#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

//console window properties
COORD coord = {0, 0};
HANDLE hConsole;
HWND window;

//global variables
	char tempPassword [20];
	char tempEmailAddress[20];


//::::::::::::::::::
/*
	font: Bradley Hand ITC
*/
//::::::::::::::::::


void setWindowState(char state [50]){
	if(window != NULL){
		SetWindowText(window, state);
	}
}

void setWindowPos(){
	if(window != NULL){
		RECT rect;
		GetWindowRect(window, &rect);
		int sWidth = GetSystemMetrics(SM_CXSCREEN);
		int sHeight = GetSystemMetrics(SM_CYSCREEN);

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
		fontInfo.dwFontSize.Y = 15;
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
void salesRecord();
void adminLogin();
void manageUsers();
void addAdmin();
//including my header files
#include "headers/customer_buy.h"
#include "headers/customer_details.h"
#include "headers/admin.h"


int main (){
	consoleWindow();
//	menuOptions();
	landingPage();
	return 0;
}

//my landing page
void landingPage(){
	system("cls");
	int choice;
	int i, y = 6;
	char *opt [2]= {"1. Sign Up", "2. Login"};
		for(i =0;  i < 2; ++i){
			pos(26, y);
			printf("%s\n", opt[i]);
			y++;
		}
		pos(28, y+1);
	scanf("%d", &choice);
	switch(choice){
		case 1 :{
			registration();
			break;
		}
		case 2 :{
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

