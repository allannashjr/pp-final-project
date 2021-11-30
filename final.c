#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <stdbool.h>

int MAX_SIZE = 32;
struct order{
    char item[32];
    double price;
    char discount[32];
};

typedef struct order Order;
bool loop = true;

//int Read_Order(const char *filename, Order *orderArray);
//void Print_Order(Order *orderArray, int orderSize);

int main(int argc, char* argv[]) {
    Order *orderArray = (Order*)malloc(1000*sizeof(Order));
    int userInput;
    int orderSize;
    int i = 0;
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
                FILE *fin;
                fin = fopen("order.txt", "r");
                if (fin == NULL) {
                    printf("Cannot open file\n");
                    break;
                }
    		while (!feof(fin)) {
                printf("Scanning item %d\n", i);
    		if (fscanf(fin, "%s $%lf Discount: %s",
                    orderArray[i].item,
            	    &orderArray[i].price,
            	    orderArray[i].discount) == 3) {
                    printf("Item %d: %s Price: $%0.2f Discount: %s \n",
                            i,
                            orderArray[i].item,
                            orderArray[i].price,
                            orderArray[i].discount);
                   i++;
                } else {
                            printf("End of Order\n");
                            break;
                };
                };
    	        fclose(fin);
    		orderSize = i;
                printf("****************************************************\n");
                break;
            case 3 : 
                printf("\t\tView All Items\n");
    		printf("Printing Order\n");
    		/*for (int i = 0; i < orderSize; i++) {
        		Order *o = &orderArray[i];
        		printf("Item %d: %s %d Discount: %s\n",
            		    i,
                            o->item,
            		    o->price,
                            o->discount);
                }*/
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
