#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
//   WHY DYNAMIC ALLOCATION IS MORE EFFICIENT:
//
//   With static arrays, we must reserve a fixed amount of memory upfront,
//   which wastes space if we only have a few short lines. Dynamic allocation
//   lets us allocate exactly what we need for each line.
//   We can also grow the editor to handle any number of lines using realloc
//   while static arrays have a hard limit. When inserting or deleting lines
//   we only move pointers  not entire strings making operations much faster.
//   This approach saves memory and improves performance.

#define INITIAL_CAPACITY 4
#define MAX_INPUT_LENGTH 1024

typedef struct
{
    char **content;
    int lineCount;
    int capacity;
} TextEditor;

TextEditor *initializeEditor()
{
    TextEditor *editor = (TextEditor *)malloc(sizeof(TextEditor));
    if (!editor)
    {
        fprintf(stderr, "Error: Unable to allocate memory for editor.\n");
        return NULL;
    }

    editor->content = (char **)malloc(INITIAL_CAPACITY * sizeof(char *));
    if (!editor->content)
    {
        fprintf(stderr, "Error: Unable to allocate memory for lines.\n");
        free(editor);
        return NULL;
    }

    editor->lineCount = 0;
    editor->capacity = INITIAL_CAPACITY;
    return editor;
}

int expandCapacity(TextEditor *editor)
{
    int newCapacity = editor->capacity * 2;
    char **newContent = (char **)realloc(editor->content, newCapacity * sizeof(char *));
    if (!newContent)
    {
        fprintf(stderr, "Error: Unable to expand capacity.\n");
        return 0;
    }

    editor->content = newContent;
    editor->capacity = newCapacity;
    return 1;
}

int addLine(TextEditor *editor, int position, const char *line)
{
    if (!editor || !line)
        return 0;
    if (position < 0 || position > editor->lineCount)
    {
        fprintf(stderr, "Error: Invalid position %d.\n", position);
        return 0;
    }

    if (editor->lineCount >= editor->capacity)
    {
        if (!expandCapacity(editor))
            return 0;
    }

    char *newLine = (char *)malloc((strlen(line) + 1) * sizeof(char));
    if (!newLine)
    {
        fprintf(stderr, "Error: Unable to allocate memory for new line.\n");
        return 0;
    }
    strcpy(newLine, line);

    if (position < editor->lineCount)
    {
        memmove(&editor->content[position + 1], &editor->content[position],
                (editor->lineCount - position) * sizeof(char *));
    }

    editor->content[position] = newLine;
    editor->lineCount++;
    return 1;
}

int removeLine(TextEditor *editor, int position)
{
    if (!editor)
        return 0;
    if (position < 0 || position >= editor->lineCount)
    {
        fprintf(stderr, "Error: Invalid position %d.\n", position);
        return 0;
    }

    free(editor->content[position]);

    if (position < editor->lineCount - 1)
    {
        memmove(&editor->content[position], &editor->content[position + 1],
                (editor->lineCount - position - 1) * sizeof(char *));
    }

    editor->lineCount--;
    return 1;
}

void displayLines(TextEditor *editor)
{
    if (!editor)
        return;

    printf("\n=== Text Editor Content ===\n");
    if (editor->lineCount == 0)
    {
        printf("[No lines to display]\n");
        return;
    }

    for (int i = 0; i < editor->lineCount; i++)
    {
        printf("%d: %s\n", i + 1, editor->content[i]);
    }
}

int shrinkMemory(TextEditor *editor)
{
    if (!editor || editor->lineCount == 0)
        return 0;

    if (editor->lineCount < editor->capacity)
    {
        char **newContent = (char **)realloc(editor->content, editor->lineCount * sizeof(char *));
        if (!newContent)
        {
            fprintf(stderr, "Warning: Unable to shrink memory.\n");
            return 0;
        }

        editor->content = newContent;
        editor->capacity = editor->lineCount;
        return 1;
    }
    return 0;
}

int saveToFile(TextEditor *editor, const char *filename)
{
    if (!editor || !filename)
        return 0;

    FILE *file = fopen(filename, "w");
    if (!file)
    {
        fprintf(stderr, "Error: Unable to open file %s.\n", filename);
        return 0;
    }

    for (int i = 0; i < editor->lineCount; i++)
    {
        fprintf(file, "%s\n", editor->content[i]);
    }

    fclose(file);
    return 1;
}

int loadFromFile(TextEditor *editor, const char *filename)
{
    if (!editor || !filename)
        return 0;

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Error: Unable to open file %s.\n", filename);
        return 0;
    }

    char buffer[MAX_INPUT_LENGTH];
    while (fgets(buffer, MAX_INPUT_LENGTH, file))
    {
        buffer[strcspn(buffer, "\n")] = 0;
        if (!addLine(editor, editor->lineCount, buffer))
        {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

void freeEditor(TextEditor *editor)
{
    if (!editor)
        return;

    for (int i = 0; i < editor->lineCount; i++)
    {
        free(editor->content[i]);
    }

    free(editor->content);
    free(editor);
}

void showMenu()
{
    printf("\n=== Simple Text Editor ===\n");
    printf("1. Add a line\n");
    printf("2. Remove a line\n");
    printf("3. Display all lines\n");
    printf("4. Shrink memory\n");
    printf("5. Save to file\n");
    printf("6. Load from file\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

int main()
{
    TextEditor *editor = initializeEditor();
    if (!editor)
        return 1;

    int choice, position;
    char input[MAX_INPUT_LENGTH], filename[100];

    while (1)
    {
        showMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            printf("Enter position (1 to %d): ", editor->lineCount + 1);
            scanf("%d", &position);
            getchar();
            printf("Enter text: ");
            fgets(input, MAX_INPUT_LENGTH, stdin);
            input[strcspn(input, "\n")] = 0;
            addLine(editor, position - 1, input);
            break;

        case 2:
            printf("Enter position to remove: ");
            scanf("%d", &position);
            getchar();
            removeLine(editor, position - 1);
            break;

        case 3:
            displayLines(editor);
            break;

        case 4:
            shrinkMemory(editor);
            break;

        case 5:
            printf("Enter filename: ");
            scanf("%s", filename);
            getchar();
            saveToFile(editor, filename);
            break;

        case 6:
            printf("Enter filename: ");
            scanf("%s", filename);
            getchar();
            loadFromFile(editor, filename);
            break;

        case 7:
            freeEditor(editor);
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}