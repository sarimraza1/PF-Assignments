#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char name[100];
    char batch[20];
    char membership[10];
    char registrationDate[11];
    char dateOfBirth[11];
} Student;

Student *students = NULL;
int count = 0;
int capacity = 0;

void loadDB(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        printf("No existing database found.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (fileSize > 0)
    {
        count = fileSize / sizeof(Student);
        capacity = count;
        students = (Student *)malloc(capacity * sizeof(Student));
        fread(students, sizeof(Student), count, file);
        printf("Loaded %d students.\n", count);
    }
    fclose(file);
}

void saveDB(const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        perror("Error saving");
        return;
    }
    if (count > 0)
        fwrite(students, sizeof(Student), count, file);
    fclose(file);
}

int findStudent(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
            return i;
    }
    return -1;
}

void addStudent(Student s)
{
    if (findStudent(s.id) != -1)
    {
        printf("Error: ID already exists.\n");
        return;
    }

    if (count >= capacity)
    {
        capacity = (capacity == 0) ? 10 : capacity * 2;
        students = (Student *)realloc(students, capacity * sizeof(Student));
    }

    students[count++] = s;
    printf("Student added.\n");
}

void updateStudent()
{
    int id;
    printf("Enter ID: ");
    scanf("%d", &id);

    int index = findStudent(id);
    if (index == -1)
    {
        printf("Student not found.\n");
        return;
    }

    printf("Enter new Batch: ");
    scanf("%s", students[index].batch);
    printf("Enter new Membership: ");
    scanf("%s", students[index].membership);
    printf("Updated.\n");
}

void deleteStudent()
{
    int id;
    printf("Enter ID: ");
    scanf("%d", &id);

    int index = findStudent(id);
    if (index == -1)
    {
        printf("Student not found.\n");
        return;
    }

    for (int i = index; i < count - 1; i++)
        students[i] = students[i + 1];
    count--;
    printf("Deleted.\n");
}

void viewAll()
{
    if (count == 0)
    {
        printf("No students.\n");
        return;
    }
    printf("\n--- All Students ---\n");
    for (int i = 0; i < count; i++)
    {
        printf("ID: %d | Name: %s | Batch: %s | Membership: %s | DOB: %s | Reg: %s\n",
               students[i].id, students[i].name, students[i].batch,
               students[i].membership, students[i].dateOfBirth, students[i].registrationDate);
    }
}

void batchReport()
{
    char batch[20];
    printf("Enter Batch: ");
    scanf("%s", batch);

    printf("\n--- Report: %s ---\n", batch);
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].batch, batch) == 0)
        {
            printf("ID: %d | Name: %s | Membership: %s\n",
                   students[i].id, students[i].name, students[i].membership);
            found++;
        }
    }
    if (!found)
        printf("No students found.\n");
}

int main()
{
    const char *FILENAME = "members.dat";
    loadDB(FILENAME);

    int choice;
    do
    {
        printf("\n1.Add 2.Update 3.Delete 4.View 5.Report 6.Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            Student s;
            printf("ID: ");
            scanf("%d", &s.id);
            printf("Name: ");
            scanf("%s", s.name);
            printf("Batch: ");
            scanf("%s", s.batch);
            printf("Membership: ");
            scanf("%s", s.membership);
            printf("Reg Date (YYYY-MM-DD): ");
            scanf("%s", s.registrationDate);
            printf("DOB (YYYY-MM-DD): ");
            scanf("%s", s.dateOfBirth);
            addStudent(s);
            saveDB(FILENAME);
            break;
        }
        case 2:
            updateStudent();
            saveDB(FILENAME);
            break;
        case 3:
            deleteStudent();
            saveDB(FILENAME);
            break;
        case 4:
            viewAll();
            break;
        case 5:
            batchReport();
            break;
        case 6:
            saveDB(FILENAME);
            free(students);
            printf("Exit.\n");
            break;
        default:
            printf("Invalid.\n");
        }
    } while (choice != 6);

    return 0;
}