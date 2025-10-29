#include <stdio.h>
#include <string.h>

/*
There was an issue with the letter 'm' — when it was encoded, its ASCII value
became DEL (127), which could not be printed or decoded properly.
After discussing with Sir Talha, he told me to keep 'm' unchanged during both
encoding and decoding so that its bits are not modified and it remains as is.
*/

int Encode(char arr[])
{
    int i, asci, modasci;
    char temp;
    int len = strlen(arr);

    if (arr[len - 1] == '\n')
    {
        arr[len - 1] = '\0';
        len--;
    }

    char modarr[len + 1];

    for (i = 0; i < len / 2; i++)
    {
        temp = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = temp;
    }

    for (i = 0; i < len; i++)
    {
        if (arr[i] == 'm')
        {
            modarr[i] = arr[i];
        }
        else
        {
            asci = arr[i];
            modasci = asci ^ ((1 << 1) | (1 << 4));
            modarr[i] = modasci;
        }
    }

    modarr[len] = '\0';

    printf("Encoded Message : %s\n", modarr);

    strcpy(arr, modarr);
    return 1;
}

int Decode(char arr[])
{
    int i, asci, modasci;
    int len = strlen(arr);

    if (arr[len - 1] == '\n')
    {
        arr[len - 1] = '\0';
        len--;
    }

    char modarr[len + 1];

    for (i = 0; i < len; i++)
    {
        if (arr[i] == 'm')
        {
            modarr[len - i - 1] = arr[i];
        }
        else
        {
            asci = arr[i];
            modasci = asci ^ ((1 << 1) | (1 << 4));
            modarr[len - i - 1] = modasci;
        }
    }

    modarr[len] = '\0';

    printf("Decoded Message : %s\n", modarr);

    return 1;
}

int main()
{
    char message[100];
    char enc[100];
    int istrue = 1, choice;

    while (istrue)
    {
        printf("\n------------------------Menu----------------------------\n");
        printf("1. Encode Message \n2. Decode Message \n3. Exit");
        printf("\n---------------------------------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n')
            ;

        switch (choice)
        {
        case 1:
            printf("Enter message to encode: ");
            fgets(message, sizeof(message), stdin);
            Encode(message);
            break;

        case 2:
            printf("\nEnter encoded message to decode: ");
            fgets(enc, sizeof(enc), stdin);
            Decode(enc);
            break;

        case 3:
            printf("\n\t...Exited...\n");
            istrue = 0;
            break;

        default:
            printf("Invalid Choice!! Try Again\n");
            break;
        }
    }

    return 0;
}
