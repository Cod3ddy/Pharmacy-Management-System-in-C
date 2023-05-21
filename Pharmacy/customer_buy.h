//fseek(buy, -size, SEEK_CUR)
//fwrite(&d, sizeof(d), 1, buy)

void customerMenu(){
	setWindowSize(900, 500);
	setWindowPos();
	system("cls");
	printf ("Welcome %s %s\n", ctm.firstName, ctm.surname);
	char *men [4] = {"1. Buy medicine", "2. Check Transaction History", "3. Talk to a medical personnel", "4. Exit"};
	int i = 0, option;
	
	for(i =0; i < 3; i++){
		printf ("%s\n", men[i]);
	}
	
	scanf("%d",&option);
	
	switch(option){
		case 1:{
			buyDrugs();
			break;
		}		
		default:{
			printf("\nSorry, wrong input\n");
			system("pause");
			customerMenu();
			break;
		}
	}
}
void buyDrugs(){
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	WORD originalAttributes = consoleInfo.wAttributes;
	
	char name [20];
	int flag = 0;
	char DATE [20] = __DATE__;
	char TIME [20] = __TIME__;
	int quant, priceToPay, checkOut;
	int y = 1;
	size = sizeof(d);
	system("cls");
	FILE *buy;
	FILE *purchaseRecord;
	
	buy = fopen("pharmacy.txt", "rb+");
	
	if(buy == NULL){
		MessageBox(0,"SORRY, FILE NOT FOUND", "ERROR 404" ,0);
	}
	else{
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
		printf ("PRICE (mwk)");
		SetConsoleTextAttribute(hConsole, originalAttributes);
		while(fread(&d, sizeof(d), 1, buy) != 0){
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
			printf ("%d", d.price);
			y++;
		}
		printf ("\nEnter drug name");
		printf ("\n::>  ");
		scanf ("%s", name);
//transaction details		
		buy = fopen("pharmacy.txt", "rb+");	
		purchaseRecord = fopen("transactionHistory.txt", "ab+");
		
		if(buy == NULL && purchaseRecord == NULL){
			MessageBox(0,"Somethig went wrong", "ERROR 404" ,0);
		}else{
			while(fread(&d, sizeof(d),1, buy) !=0){
				if(strcmp(name, d.drugName) == 0){
					flag = 1;
					break;
				}
			}
			
			if(flag == 1){
					SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					
					printf("\n%s ", strupr(d.drugName));
					SetConsoleTextAttribute(hConsole, originalAttributes);
					printf("prescription\n");
					printf ("MORNING : take %d\n", d.p.morning);
					printf ("MID-DAY : take %d\n", d.p.midday);
					printf ("EVENING : take %d\n", d.p.evening);
					
					printf ("\nEnter Quantity (%s)\n", d.drugName);
					scanf("%d", &quant);
					
//					calculate total amount to pay

					priceToPay = d.price * quant;
					
					printf ("\nTotal price to pay : K %d", priceToPay);	
					printf("\nCONTINUE TO CHECK OUT??\n");
					printf("1.Yes\n");
					printf("2.No\n");
					scanf("%d", &checkOut);
					
					switch(checkOut){
						case 1:{
							d.quantity = d.quantity - quant;
							fseek(buy, -size, SEEK_CUR);
							fwrite(&d, sizeof(d), 1, buy);
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::	
							
//							inserting customer details in the file
							strcpy(pd.drugId, d.drugId);
							strcpy(pd.customerName, ctm.firstName);
							strcpy(pd.customerSurname, ctm.surname);
							strcpy(pd.customerEmailAddress, ctm.emailAddress);
							strcat(pd.date, DATE);
							strcat(pd.time, TIME);
							pd.phoneNumber = ctm.phoneNumber;
							pd.quantity = d.quantity;
							pd.totalPayment = priceToPay;
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::							
							fwrite(&pd, sizeof(pd), 1, purchaseRecord);
							fclose(purchaseRecord);
							fclose(buy);	
							printf ("\nTransction successfull\n");
							system("pause");		
							customerMenu();
							break;
						}
						case 2:{
							system("pause");
							customerMenu();
							break;
						}
						default:{
							printf("\nSorry, Invalid choice\n");
							system("pause");
							customerMenu();
							break;
						}
					}		
					
			}else{
				printf("\nSorry we currently don't have that in our stores");
			}
	}
		fclose(buy);	
	}
}
