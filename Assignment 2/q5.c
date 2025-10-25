#include <stdio.h>
#include <string.h>

int Encode(char arr[])
{
    int i, asci, modasci;
    char temp;
    int len = strlen(arr);

    if (arr[len - 1] == '\n')
    { // remove newline if present
        arr[len - 1] = '\0';
        len--;
    }

    char modarr[len + 1];

    // reverse
    for (i = 0; i < len / 2; i++)
    {
        temp = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = temp;
    }

    printf("Reversed String : %s\n", arr);

    // toggle 2nd and 5th bit
    for (i = 0; i < len; i++)
    {
        asci = arr[i];
        modasci = asci ^ ((1 << 1) | (1 << 4));
        modarr[i] = modasci;
    }
    modarr[len] = '\0';

    printf("Encoded Message : %s\n", modarr);

    // copy back so main can reuse it
    strcpy(arr, modarr);
    return 1;
}

int Decode(char arr[])
{
    int i, asci, modasci;
    int len = strlen(arr);

    // ✅ FIX 1: remove newline before decoding
    if (arr[len - 1] == '\n')
    {
        arr[len - 1] = '\0';
        len--;
    }

    char modarr[len + 1];

    for (i = 0; i < len; i++)
    {
        asci = arr[i];
        modasci = asci ^ ((1 << 1) | (1 << 4));
        modarr[len - i - 1] = modasci;
    }

    modarr[len] = '\0';

    // ✅ FIX 2: print clearly
    printf("Decoded Message : %s\n", modarr);

    return 1;
}

int main()
{
    char message[100];
    char enc[100];

    printf("Enter message to encode: ");
    fgets(message, sizeof(message), stdin);
    Encode(message);

    printf("\nEnter encoded message to decode: ");
    fgets(enc, sizeof(enc), stdin);
    Decode(enc);

    return 0;
}
