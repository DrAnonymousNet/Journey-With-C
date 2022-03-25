#include <stdio.h>

struct clientData{
	int acctNum;
	char firstname[20];
	char lastname[20];
	double balance;
};

void newRecord(FILE *);
void updateRecord(FILE *);
void deleteRecord(FILE *);
void printFile(FILE *);
unsigned getChoice(void);


int main(int argc, char *argv[])
{
	//void (*editor[])(FILE *ptr) = { updateRecord, newRecord,deleteRecord};
	FILE *fPtr;
	unsigned int choice;
	
	if((fPtr = fopen("clients.dat", "rb+")) == NULL){
		puts("Unable to open file");
	}
	else{
		while(choice = getChoice()){
			//(*editor[choice])( fPtr);
			switch(choice){
				case 1:
					printFile(fPtr);
					break;
				case 2:
					updateRecord(fPtr);
					break;
				case 3:
					newRecord(fPtr);
					break;
				case 4:
					deleteRecord(fPtr);
					break;
			
			}
			
			
		}
	}
				
	
}

unsigned int getChoice(){
	unsigned int menu;
	
	 printf( "%s", "\nEnter your choice\n"
	 "1 - store a formatted text file of accounts called\n"  "    \"accounts.txt\" for printing\n"
	 "2 - update an account\n"
	 "3 - add a new account\n"
	 "4 - delete an account\n"
	 "5 - end program\n? " );
	 
	 
	 scanf("%d", &menu);
	 return menu;
}

void printFile(FILE *cPtr){
	struct clientData allData;
	
	rewind(cPtr);
		printf( "%-3s %-6s%-16s%-11s%10s\n","S/N", "Acct", "Last Name", "First Name","Balance" );
	
	int i = 1;
	while(!feof(cPtr)){
		
		fread(&allData, sizeof(struct clientData), 1, cPtr );
		if(allData.acctNum != 0){
			printf("%-3d%-6d%-16s%-11s%10.2lf\n",i, allData.acctNum, allData.lastname, allData.firstname, allData.balance);
			i++;
		}
	}
}



void updateRecord(FILE *cPtr){
	struct clientData cusData = {0, "","",0.0};
	
	enum data {firstname = 1, lastname, balance};
	char operators;
	double update;
	unsigned int account, choice;
	//struct clientData cusData;
	
	
	printf("Enter your account number: ");
	scanf("%d", &account);
	
	fseek(cPtr, (account-1)*sizeof(struct clientData), SEEK_SET);
	fread(&cusData,  sizeof(struct clientData),1, cPtr);
	
	
	if(cusData.acctNum == 0){
		printf("This account number is not associated with any customer: ");
	}
	else{
		printf("what do you want to update (Firstname, Lastname, Balance? ");
		scanf("%d", &choice);
		
		switch(choice){
			case firstname:
				printf("Enter your new Firstname: ");
				scanf("%19s", cusData.firstname);
				break;
			case lastname:
				printf("Enter your new lastname: ");
				scanf("%19s", cusData.lastname);
				puts("Lastname updated !!!");
				break;
			case balance:
				
				printf("Enter your ±balance : ");
				scanf("%lf",&update);
				cusData.balance += update;
				

				//cusData.balance = (operators == '+') ? (cusData.balance + update) : (cusData.balance - update);
				puts("Balance updated !!! ");
				
				break;
		}
		fseek(cPtr, (cusData.acctNum-1) * sizeof(struct clientData), SEEK_SET);
		
		//fwrite(&BlankData, sizeof(struct clientData),1, cPtr);
		fwrite(&cusData, sizeof(struct clientData),1, cPtr);
	}
}

void newRecord(FILE *cPtr){
	
	struct clientData newData;
	
	unsigned int account;
	
	printf("Enter your account number: ");
	scanf("%d", &account);
	
	fseek(cPtr,(account-1)* sizeof(struct clientData),SEEK_SET);
	
	fread(&newData, sizeof(struct clientData), 1, cPtr);
	
	if(newData.acctNum != 0){
		printf("This user already exist !");
	}
	
	else{
	  printf( "%s", "Enter lastname, firstname, balance\n? " );
	  scanf( "%19s%19s%lf", newData.lastname, newData.firstname ,&newData.balance );
	  if((newData.firstname) && (newData.lastname) && (newData.balance)){
	  	newData.acctNum = account;
	  	fseek(cPtr, (newData.acctNum - 1) * sizeof(struct clientData), SEEK_SET);
	  	
	  	fwrite(&newData, sizeof(struct clientData),1, cPtr);
	  }
	}
	
	
}

void deleteRecord(FILE *cPtr){
	
	struct clientData BlankData = {0, "","",0.0};
	struct clientData oldData;
	unsigned int account;
	printf("Enter the account number you want to delete\n");
	scanf("%d", &account);
	fseek(cPtr, (account-1)*sizeof(struct clientData), SEEK_SET);
	
	fread(&oldData, sizeof(struct clientData),1, cPtr);
	if(oldData.acctNum == 0){
		printf("This account number is not assigned to anyone");
		}
	else{
		fseek(cPtr, (account-1)*sizeof(struct clientData), SEEK_SET);
		
		fwrite(&BlankData, sizeof(struct clientData),1, cPtr);
	}
}
		
