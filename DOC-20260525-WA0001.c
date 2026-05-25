#include <stdio.h>
#include <stdlib.h>

struct Product
{
    int code;
    char name[50];
    int quantity;
    float price;
    float total;
};

struct Bill
{
    int billNo;
    char customerName[50];
    int itemCount;
    struct Product p[50];
    float subtotal;
    float gst;
    float grandTotal;
};

void createBill()
{
    FILE *fp;
    struct Bill b;

    int i = 0;
    float total = 0;
    char choice;

    fp = fopen("bills.txt", "a");

    printf("\nEnter Bill Number: ");
    scanf("%d", &b.billNo);

    printf("Enter Customer Name: ");
    scanf(" %[^\n]", b.customerName);

    do
    {
        printf("\nProduct %d Details\n", i + 1);

        printf("Enter Product Code: ");
        scanf("%d", &b.p[i].code);

        printf("Enter Product Name: ");
        scanf(" %[^\n]", b.p[i].name);

        printf("Enter Quantity: ");
        scanf("%d", &b.p[i].quantity);

        printf("Enter Unit Price: ");
        scanf("%f", &b.p[i].price);

        b.p[i].total = b.p[i].quantity * b.p[i].price;

        total += b.p[i].total;

        i++;

        printf("\nDo you want to add another item? (y/n): ");
        scanf(" %c", &choice);

    } while(choice == 'y' || choice == 'Y');

    b.itemCount = i;

    b.subtotal = total;
    b.gst = b.subtotal * 0.18;
    b.grandTotal = b.subtotal + b.gst;

    printf("\n=========== FINAL BILL ===========\n");
    printf("Bill Number   : %d\n", b.billNo);
    printf("Customer Name : %s\n", b.customerName);

    printf("\n--------------------------------------------------\n");
    printf("Code\tName\tQty\tPrice\tTotal\n");
    printf("--------------------------------------------------\n");

    for(i = 0; i < b.itemCount; i++)
    {
        printf("%d\t%s\t%d\t%.2f\t%.2f\n",
               b.p[i].code,
               b.p[i].name,
               b.p[i].quantity,
               b.p[i].price,
               b.p[i].total);

        fprintf(fp,
                "%d %s %d %s %d %.2f %.2f\n",
                b.billNo,
                b.customerName,
                b.p[i].code,
                b.p[i].name,
                b.p[i].quantity,
                b.p[i].price,
                b.p[i].total);
    }

    printf("--------------------------------------------------\n");
    printf("Subtotal     : %.2f\n", b.subtotal);
    printf("GST (18%%)    : %.2f\n", b.gst);
    printf("Grand Total  : %.2f\n", b.grandTotal);

    fclose(fp);

    printf("\nBill Saved Successfully!\n");
}

void viewBills()
{
    FILE *fp;
    char ch;

    fp = fopen("bills.txt", "r");

    if(fp == NULL)
    {
        printf("\nNo Bills Found!\n");
        return;
    }

    printf("\n========== SAVED BILLS ==========\n");

    while((ch = fgetc(fp)) != EOF)
    {
        printf("%c", ch);
    }

    fclose(fp);
}

int main()
{
    int choice;

    while(1)
    {
        printf("\n\n===== SHOPKEEPER BILLING SYSTEM =====\n");

        printf("1. Create Bill\n");
        printf("2. View Saved Bills\n");
        printf("3. Exit\n");

        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                createBill();
                break;

            case 2:
                viewBills();
                break;

            case 3:
                printf("\nThank You!\n");
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}
