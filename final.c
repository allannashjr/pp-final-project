#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <stdbool.h>
#include <string.h>

int MAX_SIZE = 32;
struct order{
    char item[32];
    double price;
    char User[32];
    int orderNum;
    int sum;
};

typedef struct order Order;
bool loop = true;

int Process_Order(Order *orderArray, int *orderSize, char orderName[10]);
void Print_Order(Order *orderArray, int orderSize);

int main(int argc, char* argv[]) {
    Order *orderArray = (Order*)malloc(1000*sizeof(Order));
    char orderName[10];
    int userInput;
    int orderSize = 0;
    int sum;
    while(loop == true) {
        printf("****************************************************\n");
        printf("\tWelcome to John's and Allan's Shop\n");
        printf("****************************************************\n");
        printf("\t\t1) Search for User\n");
        printf("\t\t2) Process an Order\n");
        printf("\t\t3) View All Items\n");
        printf("\t\t4) View Past Orders\n");
        printf("\t\t5) Exit\n");
        printf("****************************************************\n");

        printf("\t\tSelection - ");
        scanf("%d", &userInput);
        printf("****************************************************\n");
    	switch(userInput) {
            case 1 : 
                printf("\tSearch for User\n");
            	printf("****************************************************\n");
                break;
            case 2 : 
                printf("\t\tProcess an Order\n");
		printf("\tOrder Name: ");
		scanf("%s", orderName);
		sum = Process_Order(orderArray, &orderSize, orderName);
                printf("****************************************************\n");
                break;
            case 3 : 
               	printf("\t\tPrinting Order\n");
		Print_Order(orderArray, orderSize);
    		printf("****************************************************\n");
                break;
            case 4 : 
                printf("\t\tView Past Orders\n");
                printf("****************************************************\n");
                break;
            case 5 : 
                printf("\t\tClosing, Thank you!\n");
                printf("****************************************************\n");
                loop = false;
                break;
    	}
    }

    return 0;
}

int Process_Order(Order *orderArray, int *orderSize, char orderName[10]) {

     FILE *fin;
     fin = fopen(orderName, "r");
    int total;
    total = 0;
    if (fin == NULL) {
	printf("Cannot open file\n");
    }
// fill order array from file
    else {	
        // header
	if (!feof(fin)) {
            fscanf(fin, "Order %d: User: %s\n", &orderArray[(*orderSize)].orderNum, orderArray[(*orderSize)].User);
            printf("\tOrder %d:, User: %s\n", orderArray[(*orderSize)].orderNum, orderArray[(*orderSize)].User);
        }

        // order contents
	while (!feof(fin)) {
	    if (fscanf(fin, "%s $%lf", orderArray[(*orderSize)].item, &orderArray[(*orderSize)].price) == 2) {
            	printf("\tItem %d: %s, Price: $%0.2f\n", (*orderSize), orderArray[(*orderSize)].item, orderArray[(*orderSize)].price);
            	total += orderArray[(*orderSize)].price;
                (*orderSize)++;
            }
    	}
    }
    orderArray[(*orderSize)].sum = total;
    printf("\tTotal: $%d\n", orderArray[(*orderSize)].sum);
    fclose(fin);
    return orderArray[(*orderSize)].sum;
}

void Print_Order(Order *orderArray, int orderSize) {
    int total;
    total = 0;
    for (int i = 0; i < orderSize; i++) {
    	Order *o = &orderArray[i];
    	printf("\tItem %d: %s Price: $%0.2f\n", i, o->item, o->price);
        total += o->price;
    }
    printf("\tTotal: $%d\n", total);
}
