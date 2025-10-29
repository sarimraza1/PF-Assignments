#include <stdio.h>

int UpdateSector(int arr[100][100])
{
    int r, c, bitChoice, action;

    printf("Enter Row Number Of Sector: ");
    scanf("%d", &r);
    printf("Enter Column Number Of Sector: ");
    scanf("%d", &c);

    printf("Which Status to Modify?\n");
    printf("0. Power Status\n");
    printf("1. Overload Warning\n");
    printf("2. Maintenance Required\n");
    printf("Enter Choice: ");
    scanf("%d", &bitChoice);

    printf("Enter 1 to SET or 0 to CLEAR this status: ");
    scanf("%d", &action);

    if (action == 1)
        arr[r][c] |= (1 << bitChoice);
    else
        arr[r][c] &= ~(1 << bitChoice);

    return 1;
}

int RunQuerySector(int arr[100][100])
{
    int r, c;
    printf("Enter Row Number Of Sector: ");
    scanf("%d", &r);
    printf("Enter Column Number Of Sector: ");
    scanf("%d", &c);

    if ((arr[r][c] & 1) != 0)
    {
        printf("Power is ON\n");
    }
    else
    {
        printf("Power is OFF\n");
    }

    if ((arr[r][c] & 2) != 0)
    {
        printf("Overload Warning!\n");
    }
    else
    {
        printf("Load is Normal\n");
    }

    if ((arr[r][c] & 4) != 0)
    {
        printf("Maintenance Required!\n");
    }
    else
    {
        printf("No Maintenance Required!\n");
    }

    return 1;
}

int RunSystemDiagnostics(int arr[100][100])
{
    int i, j, overloadc = 0, mntncec = 0;

    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 100; j++)
        {
            if ((arr[i][j] & 2) != 0)
            {
                overloadc += 1;
            }
            if ((arr[i][j] & 4) != 0)
            {
                mntncec += 1;
            }
        }
    }

    printf("\nTotal Number of Overload Sectors: %d\n", overloadc);
    printf("Total Number of Sectors that require Maintenance: %d\n", mntncec);
    return 1;
}

int main()
{
    int grid[100][100] = {0};
    int choice;
    int notexit = 1;

    while (notexit)
    {
        printf("\n--------------------------MENU-------------------------\n");
        printf("1. Update Sector\n");
        printf("2. Run Sector Query\n");
        printf("3. Run System Diagnostics\n");
        printf("4. Exit\n");
        printf("------------------------------------------------------------\n");
        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            UpdateSector(grid);
            break;
        case 2:
            RunQuerySector(grid);
            break;
        case 3:
            RunSystemDiagnostics(grid);
            break;
        case 4:
            printf("\n...Exiting...");
            notexit = 0;
            break;
        default:
            printf("Invalid Choice! Try AGAIN\n");
            break;
        }
    }

    return 0;
}
