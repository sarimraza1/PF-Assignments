#include <stdio.h>

int Push(int arr[], int top, int maxsize)
{
    int value;
    top += 1;
    if (top == maxsize)
    {
        printf("\nStack Is Full!");
        return top;
    }
    else
    {
        printf("Enter Element you would like to add in Stack: ");
        scanf("%d", &arr[top]);
        printf("\nElement added Succesfully!");
        return top;
    }
}

int Pop(int arr[], int top)
{
    if (top == -1)
    {
        printf("\nStack is Empty!");
        return top;
    }
    else
    {
        printf("\n %d Popped out of stack", arr[top]);
        arr[top] = 0;
        top -= 1;
        return top;
    }
}

int Peek(int arr[], int top)
{
    if (top == -1)
    {
        printf("\nStack is Empty!");
        return top;
    }
    else
    {
        printf("\nElement At Top of the Stack : %d", arr[top]);
        return 1;
    }
}

int Display(int arr[], int top)
{
    int i;
    if (top == -1)
    {
        printf("\nStack is Empty!");
        return 1;
    }
    else
    {
        printf("\nStack: ");
        for (i = top; i >= 0; i--)
        {
            printf(" %d ", arr[i]);
        }
    }
    return 1;
}

int main()
{
    int Stack[100] = {0};
    int size = 100, top = -1, choice, notexit = 1;

    while (notexit)
    {
        printf("\n");
        printf("\n--------------------------MENU-------------------------\n");
        printf("1. Push into Stack\n");
        printf("2. Pop out of Stack\n");
        printf("3. Peek into Stack\n");
        printf("4. Display Full Stack\n");
        printf("5. Exit\n");
        printf("------------------------------------------------------------\n");
        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            top = Push(Stack, top, size);
            break;
        case 2:
            top = Pop(Stack, top);
            break;
        case 3:
            Peek(Stack, top);
            break;
        case 4:
            Display(Stack, top);
            break;
        case 5:
        {
            printf("\nExiting...");
            notexit = 0;
            break;
        }
        default:
            printf("\nInvalid Choice! Try AGAIN\n");
            break;
        }
    }

    return 0;
}