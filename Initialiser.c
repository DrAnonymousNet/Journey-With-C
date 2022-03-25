#include <stdio.h>

struct ClientData{
	int accountNum;
	char firstname[20];
	char lastname[20];
	double balance;
};

int main(int argc, char *argv[])
{
	FILE *cPtr;
	struct ClientData BlankData = {0, "", "", 0.0};
	
	if((cPtr = fopen("clients.dat","wb")) == NULL){
		puts("unable to open file");
	}
	else{
		for(int i = 1; i <= 100;i++){
			fwrite(&BlankData, sizeof(struct ClientData), 1, cPtr);
		}
	}
	fclose(cPtr);
}
