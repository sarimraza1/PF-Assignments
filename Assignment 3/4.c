#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int bookID;
    int popularity;
} Book;

int currentSize = 0;

int findBookIndex(Book *shelf, int id, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (shelf[i].bookID == id)
        {
            return i;
        }
    }
    return -1;
}

void addBook(Book *shelf, int capacity, int id, int score)
{
    int index = findBookIndex(shelf, id, currentSize);

    if (index != -1)
    {
        shelf[index].popularity = score;
        Book temp = shelf[index];
        for (int i = index; i < currentSize - 1; i++)
        {
            shelf[i] = shelf[i + 1];
        }
        shelf[currentSize - 1] = temp;
        return;
    }

    if (currentSize == capacity)
    {
        for (int i = 0; i < capacity - 1; i++)
        {
            shelf[i] = shelf[i + 1];
        }
        shelf[capacity - 1].bookID = id;
        shelf[capacity - 1].popularity = score;
    }
    else
    {
        shelf[currentSize].bookID = id;
        shelf[currentSize].popularity = score;
        currentSize++;
    }
}

int accessBook(Book *shelf, int id)
{
    int index = findBookIndex(shelf, id, currentSize);

    if (index == -1)
    {
        return -1;
    }

    int score = shelf[index].popularity;
    Book temp = shelf[index];
    for (int i = index; i < currentSize - 1; i++)
    {
        shelf[i] = shelf[i + 1];
    }
    shelf[currentSize - 1] = temp;

    return score;
}

int main()
{
    int capacity, operations;
    scanf("%d %d", &capacity, &operations);

    Book *shelf = (Book *)malloc(sizeof(Book) * capacity);

    char command[10];
    int id, score;

    for (int i = 0; i < operations; i++)
    {
        scanf("%s", command);

        if (strcmp(command, "ADD") == 0)
        {
            scanf("%d %d", &id, &score);
            addBook(shelf, capacity, id, score);
        }
        else if (strcmp(command, "ACCESS") == 0)
        {
            scanf("%d", &id);
            int result = accessBook(shelf, id);
            printf("%d\n", result);
        }
    }

    free(shelf);
    return 0;
}