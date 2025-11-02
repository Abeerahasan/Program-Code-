#include <stdio.h>
#include <string.h>

void addBook(int isbns[], char titles[][50], float prices[], int quantities[], int *bookCount);
void processSale(int isbns[], int quantities[], int bookCount);
void lowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int bookCount);

int main() {
    int isbns[100];
    char titles[100][50];
    float prices[100];
    int quantities[100];
    int bookCount = 0;
    int choice;

    do {
        printf("\n==== Liberty Books Inventory System ====\n");
        printf("1. Add New Book\n");
        printf("2. Process a Sale\n");
        printf("3. Generate Low-Stock Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addBook(isbns, titles, prices, quantities, &bookCount);
                break;
            case 2:
                processSale(isbns, quantities, bookCount);
                break;
            case 3:
                lowStockReport(isbns, titles, prices, quantities, bookCount);
                break;
            case 4:
                printf("Exiting program... Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 4);

    return 0;
}



void addBook(int isbns[], char titles[][50], float prices[], int quantities[], int *bookCount) {
    int isbn;
    char title[50];
    float price;
    int quantity;

    if (*bookCount >= 100) {
        printf("Cannot add more books! Inventory full.\n");
        return;
    }

    printf("Enter ISBN: ");
    scanf("%d", &isbn);

    for (int i = 0; i < *bookCount; i++) {
        if (isbns[i] == isbn) {
            printf("Book with this ISBN already exists!\n");
            return;
        }
    }

    printf("Enter Title: ");
    scanf(" %[^\n]", title); 
    printf("Enter Price: ");
    scanf("%f", &price);

    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    isbns[*bookCount] = isbn;
    strcpy(titles[*bookCount], title);
    prices[*bookCount] = price;
    quantities[*bookCount] = quantity;

    (*bookCount)++;

    printf("Book added successfully!\n");
}

void processSale(int isbns[], int quantities[], int bookCount) {
    int isbn, sold, found = 0;

    printf("Enter ISBN to sell: ");
    scanf("%d", &isbn);

    for (int i = 0; i < bookCount; i++) {
        if (isbns[i] == isbn) {
            found = 1;
            printf("Enter number of copies sold: ");
            scanf("%d", &sold);

            if (quantities[i] >= sold) {
                quantities[i] -= sold;
                printf("Sale processed! Remaining stock: %d\n", quantities[i]);
            } else {
                printf("Error: Not enough stock available!\n");
            }
            break;
        }
    }

    if (!found)
        printf("Book with ISBN %d not found.\n", isbn);
}

void lowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int bookCount) {
    int found = 0;
    printf("\n--- Low Stock Books (Quantity < 5) ---\n");

    for (int i = 0; i < bookCount; i++) {
        if (quantities[i] < 5) {
            found = 1;
            printf("ISBN: %d | Title: %s | Price: %.2f | Quantity: %d\n",
                   isbns[i], titles[i], prices[i], quantities[i]);
        }
    }

    if (!found)
        printf("No low-stock books found!\n");
}