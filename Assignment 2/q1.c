#include <stdio.h>
#include <string.h>

int AddNewBook(int isbn[], char title[][50], float price[], int quan[], int index)
{

    int id, previd;
    int n = 0;

    getchar();
    printf("Enter Book Name: ");
    fgets(title[index], sizeof(title[index]), stdin);
    for (int i = 0; title[index][i] != '\0'; i++)
    {
        if (title[index][i] == '\n')
        {
            title[index][i] = '\0';
            break;
        }
    }

    printf("Enter Book Price: ");
    scanf("%f", &price[index]);

    printf("Enter Book Quantity: ");
    scanf("%d", &quan[index]);

    printf("Enter Book ISBN: ");
    scanf("%d", &id);

    for (n = 0; n < index; n++)
    {
        if (isbn[n] == id)
        {
            printf("ISBN already exists! Enter a new one: ");
            scanf("%d", &id);
            n = -1;
        }
    }

    isbn[index] = id;
    printf("Book Added Succesfully!");
    return index + 1;
}

int ProcessSale(int isbn[], int quan[], int total)
{
    int no, index = -1, id, i;

    printf("Enter ISBN of Book: ");
    scanf("%d", &id);

    printf("Enter Number of Books Sold: ");
    scanf("%d", &no);

    for (i = 0; i < total; i++)
    {
        if (isbn[i] == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Book not found!\n");
        return 0;
    }

    if (quan[index] >= no)
    {
        quan[index] -= no;
        printf("Sale processed successfully!\n");
        return 1;
    }
    else
    {
        printf("Not enough stock available!\n");
        return 0;
    }
}

int LowStockReport(int isbn[], char title[][50], float price[], int quan[], int index)
{

    int i;

    printf("\n%-15s %-25s %-15s %-10s\n", "ISBN", "TITLE", "QUANTITY", "PRICE");
    printf("--------------------------------------------------------------------------\n");

    for (i = 0; i < index; i++)
    {
        if (quan[i] < 5)
        {
            printf("%-15d %-25s %-15d %-10.2f\n",
                   isbn[i], title[i], quan[i], price[i]);
        }
    }

    return 1;
}

int main()
{
    int isbns[100];
    char titles[100][50];
    float prices[100];
    int quantities[100];
    int i = 0, choice;

    do
    {
        printf("\n-------------------------------MENU--------------------------------\n");
        printf("\t 1. Add New Book\n");
        printf("\t 2. Process a Sale\n");
        printf("\t 3. Generate Low-Stock Report\n");
        printf("\t 4. Exit\n");
        printf("-------------------------------------------------------------------\n");
        printf("\t Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            i = AddNewBook(isbns, titles, prices, quantities, i);
            break;

        case 2:
            if (i == 0)
            {
                printf("\nNo books in the system yet!\n");
                break;
            }
            ProcessSale(isbns, quantities, i);
            break;

        case 3:
            if (i == 0)
            {
                printf("\nNo books in the system yet!\n");
                break;
            }
            LowStockReport(isbns, titles, prices, quantities, i);
            break;

        case 4:
            printf("Exiting program...\n");
            return 0;

        default:
            printf("INVALID CHOICE!\n");
            break;
        }
    } while (1);
}
