
void menuOptions(){
// my code for the menu options
//	setWindowSize(1000, 500);
	char adminName [100] = "";
	char space [3] = " ";
	strcat(adminName, adm.firstName);
	strcat(adminName, space);
	strcat(adminName, adm.surname); 
	
	setWindowState(adminName);                 
	setWindowSize(900, 500);
	
	system("cls");
	printf("Welcome %s\n\n", adminName); 
	
	char * men [5] = {"1. Add drugs", "2. View Remaining Drugs", "3. View Sales Records", "4. Manage Users ", "5. logout"};
	int i =0, option;
	
	for(i =0; i < 5; i++){
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
		case 3:{
			salesRecord();
			break;
		}
		case 4:{
			manageUsers();
			break;
		}
		default:{
			printf("Invalid input: please check your input");
			break;
		}
	}
}

void adminLogin(){
	setWindowSize(900, 500);
	system("cls");
	int uflag = 0;
	int pflag = 0;
	int i = 0;
	char *credentials [2] ={"admin@username.com", "admin@password"};
	char username [30], password [20];
	
	FILE *fp;
		fp = fopen("files/admin/adminCredentials.txt", "rb");
	
	for(i = 0; i < 2; ++i){
		if(strcmp(tempEmailAddress, credentials[i]) == 0){
			uflag = 1;
		}
		if (strcmp(tempPassword, credentials[i]) == 0){
			pflag = 1;	
		}
	}
	
	if(uflag == 1 && pflag == 1){
		menuOptions();
	}else{
		while(fread(&adm, sizeof(adm),1, fp) !=0){
			if(strcmp(tempEmailAddress, adm.emailAddress)==0 && strcmp(tempPassword, adm.password) == 0 ){
				uflag = 2;
				pflag = 2;
				break;
			}
		}
		if(uflag == 2 && pflag == 2){
			menuOptions();
		}else{
			system("cls");
			printf ("Sorry, No account by that Email Address was found\n");
			system("pause");
			landingPage();
		}
	}
}
void addDrugs(){
	setWindowState("Add drugs");
	system("cls");
	FILE *fp;
	fp = fopen("files/pharmacy.txt", "ab+");
	
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
	fp = fopen("files/pharmacy.txt", "rb");
	
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

void salesRecord(){
	system("cls");
	setWindowState("Sales Records");
	setWindowSize(900, 500);
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	WORD originalAttributes = consoleInfo.wAttributes;
	
	int y =1;
	int total = 0;
	FILE *sales;
		sales = fopen("files/transactionHistory.txt", "rb");
		
		if(sales == NULL){
			printf("Sorry something went wrong\n");
			exit(0);
		}else{
		pos(0,0);
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf ("ID");
		pos(10, 0);
		printf ("FirstName");
		pos(25, 0);
		printf ("Surname");
		pos(40, 0);
		printf ("PHONE");
		pos(55, 0);
		printf ("QTY");
		pos(65, 0);
		printf ("DATE");
		pos(80, 0);
		printf ("TIME");
		pos(95, 0);
		printf ("PAYMENT (MWK)");
		SetConsoleTextAttribute(hConsole, originalAttributes);
			while(fread(&pd, sizeof(pd),1,sales) != 0){
				pos(0, y);
				printf("%s", pd.drugId);
				pos(10, y);
				printf("%s", pd.customerName);
				pos(25, y);
				printf("%s", pd.customerSurname);
				pos(40, y);
				printf("0%d", pd.phoneNumber);
				pos(55, y);
				printf("%d", pd.quantity);
				pos(65, y);
				printf("%s", pd.date);
				pos(80, y);
				printf("%s", pd.time);
				pos(95, y);
				printf("%d", pd.totalPayment);
				total = pd.totalPayment + total;
				y++;
			}
			y = y + 1;
			int x=0, i;
			for(i=0; i < 108; ++i){
				pos(x,y);
				printf("%c", 196);
				x++;
			}
			
			pos(80, y+1);
			printf("TOTAL");
			pos(95, y+1);
			printf("K %d", total);
			
			y = y + 2;
			x = 0, i = 0;
			for(i=0; i < 108; ++i){
				pos(x,y);
				printf("%c", 196);
				x++;
			}
			fclose(sales);
			pos(0, y+2);
			system("pause");
			menuOptions();
		}
}

void manageUsers(){
	system("cls");
	int option, i ;
	char *men [5] = {"1. Add admin", "2. Remove Admin", "3. Registered Customers", "4. Admin Login history", "5. Back"};
	for (i =0; i < 5; ++i){
		printf ("%s\n", men[i]);
	}
	
	scanf("%d", &option);
	
	switch(option){
		case 1:{
			addAdmin();
			break;
		}
		case 2:{
			
			break;
		}
		case 3:{
			
			break;
		}
		case 4:{
			
			break;
		}
		case 5:{
			menuOptions();
			break;
		}
		default:{
			printf ("Invalid option\n");
			system("pause");
			manageUsers();
			break;
		}
	}
}

void addAdmin(){
	system("cls");
	setWindowState("Add admin");
	char password1 [20];
	char password2 [20];
	FILE *fp;
		fp = fopen("files/admin/adminCredentials.txt", "ab+");
		if(fp == NULL){
			printf ("something went wrong");
		}
		else{
		printf("Enter FirstName\n");
			printf ("::> ");
			scanf("%s", adm.firstName);
		printf("Enter Surname\n");
			printf ("::> ");
			scanf("%s", adm.surname);
		printf ("Enter date of Birth\n");
			printf("::> ");
			scanf("%s", adm.dateOfBirth);
		printf("Enter Gender\n");
			printf ("::> ");
			scanf("%s", adm.gender);
		printf ("Enter marital status\n");
			printf ("::> ");
			scanf("%s", adm.maritalStatus);
		printf ("Enter Physical Address\n");
			printf ("::> ");
			scanf("%s", adm.address);
		printf ("Enter Email Address\n");
			printf ("::> ");
			scanf("%s", adm.emailAddress);
		printf ("Enter Phone Number\n");
			printf ("::> ");
			scanf("%d", &adm.phoneNumber);
		printf ("Create password (*must at be 8 characters long)\n");
			printf ("::> ");
			scanf("%s", password1);
			
			if(strlen(password1) < 8){
				printf ("\nPassword too short (*must at be 8 characters long\n)");
				system("pause");
				registration();
			}
		
		printf ("Confirm  password\n");
			printf ("::> ");
			scanf("%s", password2);
			
			if(strcmp(password1, password2) == 0){
				strcat(adm.password, password1);
				fwrite(&adm, sizeof(adm), 1, fp);
				fclose(fp);
				MessageBox(0,"Registered Successfuly", "Registration",0);
				system("pause");
				manageUsers();
			}else{
				printf ("\nSorry, Passwords don't match\n");
				system("pause");
				manageUsers();
			}
		}
}

