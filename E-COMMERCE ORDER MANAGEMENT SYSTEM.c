#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_ORDERS 100

struct Order{
    int orderID;
    char customerName[100];
    int customerPhone;
    char productName[100];
    
    int quantity;
    float price;
    char status[20];
};

struct Order orders[MAX_ORDERS];
int orderCount = 0;

void addOrder();
void displayOrders();
void searchOrder();
void updateOrder();
void saveToFile();
void loadFromFile();

// Main menu
int main(){
    int choice;
    loadFromFile(); // Load saved data at start

    while(1){
        printf("\n===== E-Commerce Order Management =====\n");
        printf("1. Add Order\n");
        printf("2. Display All Orders\n");
        printf("3. Search Order\n");
        printf("4. Update Order\n");
        printf("5. Save Orders to File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline from buffer

        switch(choice){
            case 1: addOrder(); break;
            case 2: displayOrders(); break;
            case 3: searchOrder(); break;
            case 4: updateOrder(); break;
            case 5: saveToFile(); break;
            case 6: saveToFile(); printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}



void addOrder(){
    if(orderCount >= MAX_ORDERS){
        printf("Order list is full\n");
        return;
    }

    struct Order newOrder;
    printf("Enter product ID: ");
    scanf("%d", &newOrder.orderID);
    getchar();

    printf("Enter customer name: ");
    fgets(newOrder.customerName, sizeof(newOrder.customerName), stdin);
    newOrder.customerName[strcspn(newOrder.customerName, "\n")] = 0;

    printf("Enter customer phone number: ");
    scanf("%d",&newOrder.customerPhone);

    printf("Enter product name: ");
    scanf(" %[^\n]", newOrder.productName);
    newOrder.productName[strcspn(newOrder.productName, "\n")] = 0;
    

    printf("\nEnter quantity: ");
    scanf("%d", &newOrder.quantity);

    printf("Enter product price: ");
    scanf("%f", &newOrder.price);
    getchar();

    printf("Enter order status (pending or delivered): ");
    fgets(newOrder.status, sizeof(newOrder.status), stdin);
    newOrder.status[strcspn(newOrder.status, "\n")] = 0;

    orders[orderCount++] = newOrder;
    printf("Order added successfully!\n");
}

void displayOrders(){
    if(orderCount==0){
        printf("No order listed yet");
        return;
    }
    
    for (int i=0;i<orderCount;i++){
        printf("...........................................\n");
        printf("Order Id: %d\nCustomer name: %s\nCustomer Phone number: %d\nProduct name: %s\nQuantity: %d\nPrice: %.2f Taka\nTotal price: %2.f Taka\nOrder status: %s\n",
               orders[i].orderID, orders[i].customerName,orders[i].customerPhone,
               orders[i].productName, orders[i].quantity,
               orders[i].price,(orders[i].quantity*orders[i].price), orders[i].status);
        printf("...........................................\n");
    }

}

void searchOrder(){
    int searchChoice;
    printf("Search by: 1. Order ID  2. Customer Name 3. customer phone number\nEnter choice: ");
    scanf("%d", &searchChoice);
    getchar();

    if(searchChoice==1){
        int id;
        printf("Enter product id: ");
        scanf("%d",&id);
        for(int i = 0;i<orderCount;i++){
            if(orders[i].orderID == id){
                printf("Search by: 1. Order ID  2. Customer Name 3. customer phone number\nEnter choice: ",
               orders[i].orderID, orders[i].customerName,
               orders[i].productName, orders[i].quantity,
               orders[i].price, orders[i].status);
               return;
            }
            
        }
    }
    else if(searchChoice==2){
        char name[100];
        printf("Enter customer name: ");
        fgets(name,sizeof(name),stdin);
        for(int i = 0;i<orderCount;i++){
            if(orders[i].customerName==name){
                printf("Search by: 1. Order ID  2. Customer Name 3. customer phone number\nEnter choice: ",
               orders[i].orderID, orders[i].customerName,
               orders[i].productName, orders[i].quantity,
               orders[i].price, orders[i].status);
               return;
            }
            
        }
    }
    if(searchChoice==3){
        int num;
        printf("Enter customer phone number: ");
        scanf("%d",&num);
        for(int i = 0;i<orderCount;i++){
            if(orders[i].customerPhone == num){
                printf("Search by: 1. Order ID  2. Customer Name 3. customer phone number\nEnter choice: ",
               orders[i].orderID, orders[i].customerName,
               orders[i].productName, orders[i].quantity,
               orders[i].price, orders[i].status);
               return;
            }
            
        }
    }
}


void updateOrder(){
    int id, found = 0;
    printf("Enter Order ID to update: ");
    scanf("%d", &id);

    for(int i = 0; i < orderCount; i++){
        if (orders[i].orderID == id) {
            found = 1;
            printf("Enter new Quantity: ");
            scanf("%d", &orders[i].quantity);
            printf("Enter new Price: ");
            scanf("%f", &orders[i].price);
            getchar();
            printf("Enter new Status: ");
            fgets(orders[i].status, sizeof(orders[i].status), stdin);
            orders[i].status[strcspn(orders[i].status, "\n")] = 0;
            printf("Order updated successfully!\n");
            break;
        }
    }
    if(!found){
        printf("Order not found.\n");
    }
}

void saveToFile(){
    FILE *fp = fopen("orders.dat", "wb");
    if(fp == NULL){
        printf("Error saving file!\n");
        return;
    }
    fwrite(&orderCount, sizeof(int), 1, fp);
    fwrite(orders, sizeof(struct Order), orderCount, fp);
    fclose(fp);
    printf("Orders saved to file.\n");
}

void loadFromFile(){
    FILE *fp = fopen("orders.dat", "rb");
    if(fp == NULL){
        return; 
    }
    fread(&orderCount, sizeof(int), 1, fp);
    fread(orders, sizeof(struct Order), orderCount, fp);
    fclose(fp);
}
