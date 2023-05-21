void registration(){
	system("cls");
	char password1 [20];
	char password2 [20];
	FILE *fp;
	fp = fopen("ctmCredentials.txt", "ab+");
	if(fp == NULL){
		printf("sorry, file not found");
		exit(0);
	}else{
		printf("Enter your FirstName\n");
			printf ("::> ");
			scanf("%s", ctm.firstName);
		printf("Enter your Surname\n");
			printf ("::> ");
			scanf("%s", ctm.surname);
		printf ("Enter date of Birth\n");
			printf("::> ");
			scanf("%s", ctm.dateOfBirth);
		printf("Enter your Gender\n");
			printf ("::> ");
			scanf("%s", ctm.gender);
		printf ("Enter marital status\n");
			printf ("::> ");
			scanf("%s", ctm.maritalStatus);
		printf ("Enter your Physical Address\n");
			printf ("::> ");
			scanf("%s", ctm.address);
		printf ("Enter your Email Address\n");
			printf ("::> ");
			scanf("%s", ctm.emailAddress);
		printf ("Enter your Phone Number\n");
			printf ("::> ");
			scanf("%d", &ctm.phoneNumber);
		printf ("Create your password (*must at be 8 characters long)\n");
			printf ("::> ");
			scanf("%s", password1);
			
			if(strlen(password1) < 8){
				printf ("\nPassword too short (*must at be 8 characters long\n)");
				system("pause");
				registration();
			}
		
		printf ("Confirm your password\n");
			printf ("::> ");
			scanf("%s", password2);
			
			if(strcmp(password1, password2) == 0){
				strcat(ctm.password, password1);
				fwrite(&ctm, sizeof(ctm), 1, fp);
				fclose(fp);
				MessageBox(0,"Registered Successfuly", "Registration",0);
				system("pause");
				landingPage();
			}else{
				printf ("\nSorry, Passwords don't match\n");
				system("pause");
				registration();
			}
				
	}
}

void login(){
	system("cls");
	char tempPassword [20];
	char tempEmailAddress[20];
	int status = 0;
	FILE *fp;
	pos(22, 4);
	printf ("Enter Email Address\n");
	pos(22, 5);
		printf ("::> ");
		scanf("%s", tempEmailAddress);
	pos(22, 7);
	printf ("Enter Password\n");
	pos(22, 8);
		printf("::> ");
		scanf("%s", tempPassword);
	
	
	fp = fopen("ctmCredentials.txt", "rb+");
	if(fp == NULL){
		printf ("sorry, file not found");
		exit(0);
	}else{
		while(fread(&ctm, sizeof(ctm), 1, fp) != 0){
			if(strcmp(tempPassword, ctm.password) == 0 && strcmp(tempEmailAddress, ctm.emailAddress) ==0){
				status = 1;
			}
		}
		if(status == 1){
			customerMenu();
		}else{
			printf ("Sorry, No account by that Email Address was found\n");
			system("pause");
			landingPage();
		}
	}
}
