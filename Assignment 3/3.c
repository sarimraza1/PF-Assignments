#include <stdio.h>
#include <string.h>

typedef struct employee
{
    int empid;
    char name[20];
    char designation[20];
    float salary;
} emp;

void input(emp *ar, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Enter Employee ID: ");
        scanf("%d", &ar[i].empid);
        getchar();
        printf("Enter Employee Name: ");
        fgets(ar[i].name, 20, stdin);
        ar[i].name[strcspn(ar[i].name, "\n")] = 0;
        printf("Enter Employee Designation: ");
        fgets(ar[i].designation, 20, stdin);
        ar[i].designation[strcspn(ar[i].designation, "\n")] = 0;
        printf("Enter Employee Salary: ");
        scanf("%f", &ar[i].salary);
    }
}

void displayEmployees(emp *p, int n)
{
    printf("\n==== Employee Details ====\n");
    printf("Employee ID\tEmployee Name\tEmployee Designation\tEmployee Salary\n");
    for (int i = 0; i < n; i++)
    {
        printf("%-10d\t%-15s\t%-20s\t%.2f\n", p[i].empid, p[i].name, p[i].designation, p[i].salary);
    }
}

void findHighestSalary(emp *p, int n)
{
    float high = 0.0;
    int in = 0;
    for (int i = 0; i < n; i++)
    {
        if (p[i].salary > high)
        {
            high = p[i].salary;
            in = i;
        }
    }
    printf("\n==== Employee with Highest Salary ====\n");
    printf("Employee ID: %d\n", p[in].empid);
    printf("Employee Name: %s\n", p[in].name);
    printf("Employee Designation: %s\n", p[in].designation);
    printf("Employee Salary: %.2f\n", high);
}

void searchEmployee(emp *p, int n)
{
    int choice;
    printf("Enter 1 to search by ID or 0 to search by Name: ");
    scanf("%d", &choice);
    getchar();
    if (choice == 1)
    {
        int id;
        printf("Enter Employee ID: ");
        scanf("%d", &id);
        for (int i = 0; i < n; i++)
        {
            if (p[i].empid == id)
            {
                printf("Employee Found:\n");
                printf("ID: %d, Name: %s, Designation: %s, Salary: %.2f\n", p[i].empid, p[i].name, p[i].designation, p[i].salary);
                return;
            }
        }
        printf("Employee with ID %d not found.\n", id);
    }
    else
    {
        char name[20];
        printf("Enter Employee Name: ");
        fgets(name, 20, stdin);
        name[strcspn(name, "\n")] = 0;
        for (int i = 0; i < n; i++)
        {
            if (strcmp(p[i].name, name) == 0)
            {
                printf("Employee Found:\n");
                printf("ID: %d, Name: %s, Designation: %s, Salary: %.2f\n", p[i].empid, p[i].name, p[i].designation, p[i].salary);
                return;
            }
        }
        printf("Employee with Name %s not found.\n", name);
    }
}

void applyBonus(emp *p, int n, float threshold)
{
    for (int i = 0; i < n; i++)
    {
        if (p[i].salary < threshold)
        {
            p[i].salary *= 1.1;
        }
    }
    printf("Salaries updated for employees earning below %.2f.\n", threshold);
}

// To modify the existing program  we can update the searchEmployee
// function to include the ability to directly modify an employees
// salary. Since the array of structures is already passed by reference
// we can first find the employee as the function already does
// then access their salary field and update it directly
// This ensures the salary is modified in the original array

int main()
{
    int n;
    printf("Enter the number of employees: ");
    scanf("%d", &n);
    emp employees[n];

    input(employees, n);
    displayEmployees(employees, n);
    findHighestSalary(employees, n);
    searchEmployee(employees, n);

    float threshold;
    printf("Enter salary threshold to apply bonus: ");
    scanf("%f", &threshold);
    applyBonus(employees, n, threshold);
    displayEmployees(employees, n);

    return 0;
}