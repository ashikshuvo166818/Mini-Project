#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Customer {
    char Customer_name[50];
    int account_number;
    double balance;
    struct Customer *next;
};

struct Bank {
    struct Customer *Customers;
    struct Bank *next;
};

typedef struct Bank b;

b *start;

void show() {
    b *p;
    p = start;
    while (p != NULL) {
        struct Customer *customer = p->Customers;
        while (customer != NULL) {
            printf("Account Number : %d\n", customer->account_number);
            printf("Name : %s\n", customer->Customer_name);
            printf("Balance : %lf\n", customer->balance);
            customer = customer->next;
        }
        p = p->next;
    }
}

void AddAccount() {
    b *p;
    p = start;
    while (p->next != NULL) {
        p = p->next;
    }
    b *newAccount;
    newAccount = (b *)malloc(sizeof(b));
    newAccount->Customers = (struct Customer *)malloc(sizeof(struct Customer));

    printf("Enter Account number : ");
    scanf("%d", &newAccount->Customers->account_number);
    printf("Enter Name (Holder) : ");
    scanf("%s", newAccount->Customers->Customer_name);
    printf("Enter Balance : ");
    scanf("%lf", &newAccount->Customers->balance);
    newAccount->Customers->next = NULL;
    p->next = newAccount;
    newAccount->next = NULL;
}

void search(int key) {
    b *p;
    p = start;
    while (p != NULL) {
        struct Customer *customer = p->Customers;
        while (customer != NULL) {
            if (customer->account_number == key) {
                printf("Account Found:\n");
                printf("Account Number : %d\n", customer->account_number);
                printf("Name : %s\n", customer->Customer_name);
                printf("Balance : %lf\n", customer->balance);
                return;
            }
            customer = customer->next;
        }
        p = p->next;
    }
    printf("Account with account number %d not found.\n", key);
}

void DeleteAccount(int search) {
    b *p = start;
    b *previous = NULL;
    while (p != NULL) {
        struct Customer *customer = p->Customers;
        struct Customer *prevCustomer = NULL;
        while (customer != NULL) {
            if (customer->account_number == search) {
                if (prevCustomer == NULL) {
                    p->Customers = customer->next; // Update head of the Customers list
                } else {
                    prevCustomer->next = customer->next;
                }
                free(customer); // Free memory for the deleted customer
                return;
            }
            prevCustomer = customer;
            customer = customer->next;
        }
        previous = p;
        p = p->next;
    }
    printf("Account with account number %d not found.\n", search);
}

void Deposit(int search, double value) {
    b *p = start;
    while (p != NULL) {
        while (p->Customers != NULL) {
            if (p->Customers->account_number == search) {
                p->Customers->balance += value;
                printf("Deposited %lf into account %d.\n", value, search);
                return;
            }
            p->Customers = p->Customers->next;
        }
        p = p->next;
    }
    printf("Account with account number %d not found.\n", search);
}

void Withdraw(int search, double value) {
    b *p = start;
    while (p != NULL) {
        while (p->Customers != NULL) {
            if (p->Customers->account_number == search) {
                if (p->Customers->balance >= value) {
                    p->Customers->balance -= value;
                    printf("Withdrawn %lf from account %d.\n", value, search);
                } else {
                    printf("Insufficient balance for account %d.\n", search);
                }
                return;
            }
            p->Customers = p->Customers->next;
        }
        p = p->next;
    }
    printf("Account with account number %d not found.\n", search);
}

int main() {
    start = (b *)malloc(sizeof(b));
    start->Customers = (struct Customer *)malloc(sizeof(struct Customer));

    strcpy(start->Customers->Customer_name, "Ashik Shuvo");
    start->Customers->account_number = 157861;
    start->Customers->balance = 500;
    start->next = NULL;

    int choice;
    int accountToOperate;
    double amount;

    do {
        printf("\nMenu:\n");
        printf("1. Show Accounts\n");
        printf("2. Add Account\n");
        printf("3. Search Account\n");
        printf("4. Delete Account\n");
        printf("5. Deposit\n");
        printf("6. Withdraw\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                show();
                break;
            case 2:
                AddAccount();
                break;
            case 3:
                printf("Enter Account number to search: ");
                scanf("%d", &accountToOperate);
                search(accountToOperate);
                break;
            case 4:
                printf("Enter Account number to delete: ");
                scanf("%d", &accountToOperate);
                DeleteAccount(accountToOperate);
                break;
            case 5:
                printf("Enter Account number to deposit to: ");
                scanf("%d", &accountToOperate);
                printf("Enter deposit amount: ");
                scanf("%lf", &amount);
                Deposit(accountToOperate, amount);
                break;
            case 6:
                printf("Enter Account number to withdraw from: ");
                scanf("%d", &accountToOperate);
                printf("Enter withdrawal amount: ");
                scanf("%lf", &amount);
                Withdraw(accountToOperate, amount);
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
