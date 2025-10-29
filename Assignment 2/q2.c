#include <stdio.h>
#include <string.h>

int CustomerInformation(char *name, int *ptr)
{
    printf("Enter Your Name: ");
    fgets(name, 50, stdin);

    for (int i = 0; name[i] != '\0'; i++)
    {
        if (name[i] == '\n')
        {
            name[i] = '\0';
            break;
        }
    }

    printf("Enter Your Cnic: ");
    scanf("%d", ptr);
    getchar();
    return 1;
}

int DisplayInventory(int arr[4][3])
{
    int i, j;

    printf("\n%-15s %-15s %-25s\n", "Product Code", "Quantity in Stock", "    Price Per Product");
    printf("-------------------------------------------------------------\n");

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%-22d", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int AddItemToCart(int arr[4][3], int *total)
{
    int id, bill = 0, qn, k;

    printf("\nEnter Product Code of Item you wish to buy: ");
    scanf("%d", &id);

    while (id > 4 || id < 1)
    {
        printf("INVALID Product Code! Try Again\n");
        printf("Enter Product Code of Item you wish to buy: ");
        scanf("%d", &id);
    }

    printf("Enter Quantity: ");
    scanf("%d", &qn);

    int index = id - 1;

    if (qn > arr[index][1])
    {
        printf("Not Enough Stock Available\n");
        return 0;
    }
    else
    {
        arr[index][1] -= qn;
        bill = arr[index][2] * qn;
        printf("Item Added to the Cart Successfully!\n");
    }

    *total += bill;

    printf("\nEnter 1 if you would like to add more items to cart or Press 0 to Checkout: ");
    scanf("%d", &k);

    return k;
}

int DisplayBill(int total, char *name, int cnic)
{
    int has;
    printf("\nWe Are Offering a Promocode of EID2025\n");
    printf("Do you have a Voucher? Enter 1 for yes or 0 for no: ");
    scanf("%d", &has);

    printf("\n---------------------------------INVOICE-------------------------------------\n");
    printf("%-20s %-20s %-20s %-20s\n", "Customer Name", "Customer Cnic", "Total Bill", "Total Discount");

    if (has == 1)
    {
        printf("%-20s %-20d %-20d %-20.2f\n", name, cnic, total, total * 0.25);
        printf("\n");
        printf("Amount after Discount: %.2f\n", total * 0.75);
    }
    else
    {
        printf("%-20s %-20d %-20d %-20.2f\n", name, cnic, total, 0.00);
        printf("\n");
        printf("Amount after Discount: %.2f\n", (float)total);
    }

    printf("\n-----------------------------|...Exiting....|--------------------------------------\n");
    return 1;
}

int main()
{
    char name[50];
    int cnic, totalbill = 0, istrue;

    int ProductDetails[4][3] = {
        {1, 50, 100},
        {2, 10, 200},
        {3, 20, 300},
        {4, 8, 150}};

    CustomerInformation(name, &cnic);
    DisplayInventory(ProductDetails);

    istrue = AddItemToCart(ProductDetails, &totalbill);

    while (istrue)
    {
        DisplayInventory(ProductDetails);
        istrue = AddItemToCart(ProductDetails, &totalbill);
    }

    DisplayBill(totalbill, name, cnic);

    return 0;
}
