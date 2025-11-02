#include <stdio.h>
#include <string.h>

// Function declarations
void CustomerInfo(char name[], char CNIC[]);
void DisplayInventory(int productscode[], int prices[], int stock[], int size);
void AddToCart(int productscode[], int prices[], int stock[], int cart[], int size);
void UpdateInventory(int productscode[], int stock[], int cart[], int size);
float DisplayBill(int productscode[], int prices[], int cart[], int size);
void ShowInvoice(char name[], char CNIC[], float totalBill);

int main() {
    char name[50], CNIC[50];
    int productscode[4] = {1, 2, 3, 4};
    int prices[4] = {100, 200, 300, 150};
    int stock[4] = {50, 10, 20, 8};
    int cart[4] = {0};
    int choice;
    float totalBill = 0.0;

    // Step 1: Get customer info
    CustomerInfo(name, CNIC);

    do {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Display Inventory\n");
        printf("2. Add to Cart\n");
        printf("3. Update Inventory\n");
        printf("4. Display Bill\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                DisplayInventory(productscode, prices, stock, 4);
                break;
            case 2:
                AddToCart(productscode, prices, stock, cart, 4);
                break;
            case 3:
                UpdateInventory(productscode, stock, cart, 4);
                break;
            case 4:
                totalBill = DisplayBill(productscode, prices, cart, 4);
                ShowInvoice(name, CNIC, totalBill);
                break;
            case 5:
                printf("Exiting system... Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while(choice != 5);

    return 0;
}

// ------------------- Function Definitions -------------------

void CustomerInfo(char name[], char CNIC[]) {
    printf("\nEnter Customer Name: ");
    scanf(" %[^\n]", name);
    printf("Enter Customer CNIC: ");
    scanf("%s", CNIC);
}

void DisplayInventory(int productscode[], int prices[], int stock[], int size) {
    printf("\nProduct Code\tPrice\tQuantity\n");
    printf("---------------------------------\n");
    for(int i = 0; i < size; i++) {
        printf("%d\t\t%d\t%d\n", productscode[i], prices[i], stock[i]);
    }
}

void AddToCart(int productscode[], int prices[], int stock[], int cart[], int size) {
    int code, quantity, found = 0;
    printf("Enter product code to add to cart: ");
    scanf("%d", &code);

    for(int i = 0; i < size; i++) {
        if(productscode[i] == code) {
            found = 1;
            printf("Enter quantity: ");
            scanf("%d", &quantity);

            if(quantity <= stock[i]) {
                cart[i] += quantity;
                printf("Added %d items of product %d to cart.\n", quantity, code);
            } else {
                printf("Not enough stock available!\n");
            }
            break;
        }
    }

    if(!found) {
        printf("Product not found!\n");
    }
}

void UpdateInventory(int productscode[], int stock[], int cart[], int size) {
    for(int i = 0; i < size; i++) {
        if(cart[i] > 0) {
            stock[i] -= cart[i];
            cart[i] = 0;  // empty cart after purchase
        }
    }
    printf("Inventory updated successfully!\n");
}

float DisplayBill(int productscode[], int prices[], int cart[], int size) {
    float total = 0;
    printf("\n===== BILL DETAILS =====\n");
    printf("Code\tQty\tPrice\tSubtotal\n");
    printf("----------------------------------\n");

    for(int i = 0; i < size; i++) {
        if(cart[i] > 0) {
            float subtotal = prices[i] * cart[i];
            printf("%d\t%d\t%d\t%.2f\n", productscode[i], cart[i], prices[i], subtotal);
            total += subtotal;
        }
    }

    printf("----------------------------------\n");
    printf("Total Bill: %.2f\n", total);
    return total;
}

void ShowInvoice(char name[], char CNIC[], float totalBill) {
    char ans[10], promo[20];
    float discountedBill = totalBill;

    printf("\nDo you have a promo code? (yes/no): ");
    scanf("%s", ans);

    if(strcmp(ans, "yes") == 0) {
        printf("Enter promo code: ");
        scanf("%s", promo);

        if(strcmp(promo, "Eid2025") == 0) {
            discountedBill = totalBill * 0.75; // 25% off
            printf("Promo applied! You got 25%% discount.\n");
        } else {
            printf("Invalid promo code.\n");
        }
    }

    printf("\n========== INVOICE ==========\n");
    printf("Customer Name: %s\n", name);
    printf("CNIC: %s\n", CNIC);
    printf("Total Bill: %.2f\n", totalBill);
    printf("Final Bill after discount: %.2f\n", discountedBill);
}