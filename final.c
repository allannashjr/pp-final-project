#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
int MAX_SIZE = 32;
struct order{
    char item[256];
    double price;
    char User[256];
    int orderNum;
    int sum;
};

typedef struct order Order;
bool loop = true;

int Process_Order(Order *orderArray, int orderSize, char orderName[10], int my_rank, int comm_sz);
void Print_Order(Order *orderArray, int orderSize, char orderName[256], int my_rank, int comm_sz);

int main(int argc, char* argv[]) {
    char orderName[256];
    int userInput;
    int orderSize = 0;
    int sum;
    int my_rank;
    int comm_sz = 8;
    omp_lock_t mutex;
    omp_init_lock(&mutex);
    srand(time(0));

    while(loop == true) {
        printf("****************************************************\n");
        printf("\tWelcome to John's and Allan's Shop\n");
        printf("****************************************************\n");
        printf("\t\t1) Process All Orders\n");
        printf("\t\t2) View All Items\n");
        printf("\t\t3) Exit\n");
        printf("****************************************************\n");

        printf("\t\tSelection - ");
        scanf("%d", &userInput);
        printf("****************************************************\n");

        omp_set_num_threads(comm_sz);
        #pragma omp parallel
        {
        Order *orderArray = (Order*)malloc(10000*sizeof(Order));
    	switch(userInput) {
            case 1 : ;
                clock_t begin = clock();
                #pragma omp critical (orderName)
                {
                    my_rank = omp_get_thread_num();
                    switch(my_rank) {
                        case 0:
                                  strcpy(orderName, "order.txt");
                                  break;
                        case 1:
                                  strcpy(orderName, "groceries.txt");
                                  break;
                        case 2:
                                  strcpy(orderName, "graphics.txt");
                                  break;
                        case 3:
                                  strcpy(orderName, "sports.txt");
                                  break;
                        case 4:
                                  strcpy(orderName, "tires.txt");
                                  break;
                        case 5:
                                  strcpy(orderName, "videogames.txt");
                                  break;
                        case 6:
                                  strcpy(orderName, "colors.txt");
                                  break;
                        case 7:
                                  strcpy(orderName, "drinks.txt");
                                  break;
                    }

                    sum = Process_Order(orderArray, orderSize, orderName, my_rank, comm_sz);
                }
                clock_t end = clock();
                double runtime = (double)(end - begin) / CLOCKS_PER_SEC;
                printf("Total Runtime: %f\n", runtime);
                break;
            case 2 :
                #pragma omp critical (orderName)
                {
                    my_rank = omp_get_thread_num();
                    switch(my_rank) {
                        case 0:
                                  strcpy(orderName, "order.txt");
                                  break;
                        case 1:
                                  strcpy(orderName, "groceries.txt");
                                  break;
                        case 2:
                                  strcpy(orderName, "graphics.txt");
                                  break;
                        case 3:
                                  strcpy(orderName, "sports.txt");
                                  break;
                        case 4:
                                  strcpy(orderName, "tires.txt");
                                  break;
                        case 5:
                                  strcpy(orderName, "videogames.txt");
                                  break;
                        case 6:
                                  strcpy(orderName, "colors.txt");
                                  break;
                        case 7:
                                  strcpy(orderName, "drinks.txt");
                                  break;
                    }

                    Print_Order(orderArray, orderSize, orderName, my_rank, comm_sz);
                }
                break;
            case 3 :
                free(orderArray);
                loop = false;
                break;
            }
    	}// end parallel
    }
    printf("\t\tClosing, Thank you!\n");
    printf("****************************************************\n");
    omp_destroy_lock(&mutex);
    return 0;
}

int Process_Order(Order *orderArray, int orderSize, char orderName[256], int my_rank, int comm_sz) {

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
            fscanf(fin, "Order %d: User: %s\n", &orderArray[orderSize].orderNum, orderArray[orderSize].User);
            printf("\tStarting Process %d: Order %d:, User: %s\n", my_rank, orderArray[orderSize].orderNum, orderArray[orderSize].User);
        }

        // order contents
        while (!feof(fin)) {
            if (fscanf(fin, "%s $%lf", orderArray[orderSize].item, &orderArray[orderSize].price) == 2) {
                //printf("\tItem %d: %s, Price: $%0.2f\n", (orderSize), orderArray[orderSize].item, orderArray[orderSize].price);
                total += orderArray[orderSize].price;
                orderSize++;
            }
        }
    }

    orderArray[orderSize].sum = total;
    printf("\tEnding Process %d: Order: %d, Total: $%d\n\n", my_rank, orderArray[0].orderNum, orderArray[orderSize].sum);
    fclose(fin);

    return total;
}

void Print_Order(Order *orderArray, int orderSize, char orderName[256], int my_rank, int comm_sz) {

    FILE *fin;
    fin = fopen(orderName, "r");

    // File is Empty or Invalid
    if (fin == NULL) {
        printf("Cannot open file\n");
    }

    // File is Valid
    else {
        // header
        if (!feof(fin)) {
            fscanf(fin, "Order %d: User: %s\n", &orderArray[orderSize].orderNum, orderArray[orderSize].User);
        }

        // order contents
        while (!feof(fin)) {
            if (fscanf(fin, "%s $%lf", orderArray[orderSize].item, &orderArray[orderSize].price) == 2) {
                printf("\t%s, Price: $%0.2f\n", orderArray[orderSize].item, orderArray[orderSize].price);
                orderSize++;
            }
        }
    }

    fclose(fin);
}
