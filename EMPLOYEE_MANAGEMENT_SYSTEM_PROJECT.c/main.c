#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for delay function
#include <time.h> // for current time stamp
#define MAX 100

struct Employee {
    int id;
    char name[50];
    char department[30];
    char designation[30];
    float salary;
};

struct Employee empList[MAX];
int count = 0;

void addEmployee() {
    int isDuplicate = 0;  //  to track duplicate IDs
    int id;
    
    do {
        isDuplicate = 0; 
        printf("\n");
        printf("‣ Enter Employee ID: ");
        scanf("%d", &id);
        getchar();  // Clear any buffer 

        // Check for duplicate ID
        for (int i = 0; i < count; i++) {
            if (empList[i].id == id) {
                isDuplicate = 1;  // Duplicate found
                printf("\nDuplicate ID found! Please enter a unique ID.❗️⚠️\n");
                printf("Press Enter to try again...\n");
                getchar();  // Wait for user to press Enter key to continue
                break;
            }
        }
    } while (isDuplicate);  // Loop until a unique ID is entered

    empList[count].id = id;
    if (count < MAX) {
        printf("‣ Enter Employee Name: ");
        fgets(empList[count].name, sizeof(empList[count].name), stdin);
        empList[count].name[strcspn(empList[count].name, "\n")] = 0;
        printf("‣ Enter Employee Department: ");
        fgets(empList[count].department, sizeof(empList[count].department), stdin);
        empList[count].department[strcspn(empList[count].department, "\n")] = 0;
        printf("‣ Enter Employee Designation: ");
        fgets(empList[count].designation, sizeof(empList[count].designation), stdin);
        empList[count].designation[strcspn(empList[count].designation, "\n")] = 0;
        printf("‣ Enter Employee Annual Gross Salary (INR): ");
        scanf("%f", &empList[count].salary);
        getchar();
        count++;
        usleep(80000);
        printf("\nEmployee added successfully! ✅\n");
    } else {
        usleep(80000);
        printf("Employee list full!\n");
    }
}

void viewEmployees() { // employee list
    if (count == 0) {
        usleep(80000);
        printf("\nNo employees to display. ❌\n");
        return;
    }
    printf("\n 💼 Employee List:↴\n\n");
    for (int i = 0; i < count; i++) {
        usleep(50000);
        printf("[%d]. ID: %d | Name: %s | Department: %s | Designation: %s | Gross Salary: %.2f\n",i+1,empList[i].id, empList[i].name, empList[i].department,empList[i].designation, empList[i].salary);
    }
}

void searchEmployee() { // searching of employee
    int id, found = 0;
    usleep(80000);
    printf("\n‣ Enter Employee ID to search 🔎: "); // only by id
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (empList[i].id == id) {
            usleep(80000);
            printf("\n✅ Employee Found:↴\n\n");
            usleep(80000);
            printf("ID: %d | Name: %s | Department: %s | Designation: %s | Gross Salary: %.2f\n", empList[i].id, empList[i].name, empList[i].department,empList[i].designation,empList[i].salary);
            found = 1;
            break;
        }
    }
    if (!found){
    usleep(80000);
        printf("Employee with ID %d not found.❌\n", id);
    }
}

void deleteEmployee() { // deleting of employees
    int choice;
    usleep(80000);
    printf("\nDelete Options:\n1. Delete specific employee by ID\n2. Delete ALL employees\nEnter your choice: ");
    //provide two option to delete employee
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        int id, found = 0;
        usleep(80000);
        printf("\n‣ Enter Employee ID to delete: ");
        scanf("%d", &id);
        getchar();

        for (int i = 0; i < count; i++) {
            if (empList[i].id == id) {
                for (int j = i; j < count - 1; j++)
                    empList[j] = empList[j + 1];
                count--;
                found = 1;
                usleep(80000);
                printf("Employee deleted successfully. ✅\n");
                break;
            }
        }
        if (!found){
        usleep(80000);
            printf("Employee with ID %d not found. ❌\n", id);
        }
    } else if (choice == 2) {
        count = 0;
        usleep(80000);
        printf("All employees deleted successfully. ✅\n");
    } else {
        usleep(80000);
        printf("Invalid choice.❗️⚠️\n");
    }
}

void updateEmployee() { // updation of employees
    int id, found = 0;
    usleep(80000);
    printf("\n‣ Enter Employee ID to update: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (empList[i].id == id) {
            printf("‣ Enter new Employee ID: ");
            scanf("%d", &empList[i].id);
            getchar();
            printf("‣ Enter new Employee Name: ");
            fgets(empList[i].name, sizeof(empList[i].name), stdin);
            empList[i].name[strcspn(empList[i].name, "\n")] = 0;
            printf("‣ Enter new Employee Department: ");
            fgets(empList[i].department, sizeof(empList[i].department), stdin);
            empList[i].department[strcspn(empList[i].department, "\n")] = 0;
            printf("‣ Enter new Employee Designation: ");
            fgets(empList[i].designation, sizeof(empList[i].designation), stdin);
            empList[i].designation[strcspn(empList[i].designation, "\n")] = 0;
            printf("‣ Enter new Annual Gross Salary (INR): ");
            scanf("%f", &empList[i].salary);
            getchar();
            usleep(80000);
            printf("Employee details updated successfully. ✅\n");
            found = 1;
            break;
        }
    }
    if (!found){
    usleep(80000);
        printf("Employee with ID %d not found. ❌\n", id);
    }
}

void sortEmployees() { // sorting of employees
    int choice;
    usleep(50000);
    printf("\nSort by:\n1. ID\n2. Name\nEnter choice: "); // two option to sort employee
    scanf("%d", &choice);
    getchar();

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if ((choice == 1 && empList[i].id > empList[j].id) ||
                (choice == 2 && strcmp(empList[i].name, empList[j].name) > 0)) {
                struct Employee temp = empList[i];
                empList[i] = empList[j];
                empList[j] = temp;
            }
        }
    }
    usleep(80000);
    printf("Employees sorted successfully. ✅\n");
}

void saveToFile() { // save data to binary format
    FILE *fptr = fopen("employees.data", "wb");
    if (fptr == NULL) {
        printf("Error opening file.‼️ \n");
        return;
    }
    fwrite(empList, sizeof(struct Employee), count, fptr);
    fclose(fptr);
}

void loadFromFile() { // data will load from file ,untill file gets deleted
    FILE *fptr = fopen("employees.data", "rb"); 
    if (fptr == NULL) {
        printf("No data file found. Starting fresh.\n");
        return;
    }
    count = fread(empList, sizeof(struct Employee), MAX, fptr);
    fclose(fptr);
    printf("   Data loaded from file successfully. ✅\n");
}

void saveToTextFile() { // deatils save to text file (readable format)
    FILE *fptr = fopen("employees.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file for writing.‼️\n");
        return;
    }
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(fptr, "📊 Report generated on : [ %02d-%02d-%d ]\n\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    for (int i = 0; i < count; i++) {
        fprintf(fptr, "◦ ID: %d\n", empList[i].id);
        fprintf(fptr, "◦ Name: %s\n", empList[i].name);
        fprintf(fptr, "◦ Department: %s\n", empList[i].department);
        fprintf(fptr, "◦ Designation: %s\n", empList[i].designation);
        fprintf(fptr, "◦ Gross Salary: %.2f\n", empList[i].salary);
        fprintf(fptr, "-----------------------------\n");
    }
    fprintf(fptr, "\n💸💸💸 Individual Employee Tax Filing Report (FY 2025-26 New Regime):↴\n");
    fprintf(fptr, "---------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        float grossSalary = empList[i].salary;
        float standardDeduction = 75000.0;
        float taxableIncome = grossSalary - standardDeduction;
        float tax = 0.0;

        if (taxableIncome > 0) {
            if (taxableIncome <= 300000) {
                tax = 0.0;
            } else if (taxableIncome <= 600000) {
                tax = (taxableIncome - 300000) * 0.05;
            } else if (taxableIncome <= 900000) {
                tax = (300000 * 0.05) + (taxableIncome - 600000) * 0.10;
            } else if (taxableIncome <= 1200000) {
                tax = (300000 * 0.05) + (300000 * 0.10) + (taxableIncome - 900000) * 0.15;
            } else if (taxableIncome <= 1500000) {
                tax = (300000 * 0.05) + (300000 * 0.10) + (300000 * 0.15) + (taxableIncome - 1200000) * 0.20;
            } else {
                tax = (300000 * 0.05) + (300000 * 0.10) + (300000 * 0.15) + (300000 * 0.20) + (taxableIncome - 1500000) * 0.30;
            }
            if (taxableIncome <= 700000 && tax > 0) {
                tax -= 25000;
                if (tax < 0) tax = 0;
            }
        } else {
            taxableIncome = 0;
        }

        fprintf(fptr, "ID: %d | Name: %s | Department: %s | Designation: %s\n", empList[i].id, empList[i].name, empList[i].department,empList[i].designation);
        fprintf(fptr, "⇢ Gross Salary: %.2f\n", grossSalary);
        fprintf(fptr, "⇢ Standard Deduction: %.2f\n", standardDeduction);
        fprintf(fptr, "⇢ Taxable Income: %.2f\n", taxableIncome);
        fprintf(fptr, "⇢ Total Tax Payable: %.2f\n", tax);
        fprintf(fptr, "---------------------------------------------------------------------\n");
    }

    fclose(fptr);
    usleep(80000);
    printf("Data saved to file successfully.🗂️ ✅\n");
}

void calculateTax() { // tax calculation
    if (count == 0) {
        printf("\nNo employees to calculate tax.\n");
        return;
    }
    printf("\n💸💸💸 Individual Employee Tax Filing Report (FY 2025–26 New Regime):↴\n");
    printf("---------------------------------------------------------------------\n");
     for (int i = 0; i < count; i++) { // current indian tax slab (real time)
        float grossSalary = empList[i].salary; 
        float standardDeduction = 75000.0; // only standard deduction it includes HRA DA etc.
        float taxableIncome = grossSalary - standardDeduction;
        float tax = 0.0;

        if (taxableIncome > 0) {
            if (taxableIncome <= 300000) {
                tax = 0.0;
            } else if (taxableIncome <= 600000) {
                tax = (taxableIncome - 300000) * 0.05;
            } else if (taxableIncome <= 900000) {
                tax = (300000 * 0.05) + (taxableIncome - 600000) * 0.10;
            } else if (taxableIncome <= 1200000) {
                tax = (300000 * 0.05) + (300000 * 0.10) + (taxableIncome - 900000) * 0.15;
            } else if (taxableIncome <= 1500000) {
                tax = (300000 * 0.05) + (300000 * 0.10) + (300000 * 0.15) + (taxableIncome - 1200000) * 0.20;
            } else {
                tax = (300000 * 0.05) + (300000 * 0.10) + (300000 * 0.15) + (300000 * 0.20) + (taxableIncome - 1500000) * 0.30;
            }
            if (taxableIncome <= 700000 && tax > 0) {
                tax -= 25000; // rebate according to section 87A
                if (tax < 0) tax = 0;
            }
        } else {
            taxableIncome = 0;
        }

        printf("ID: %d | Name: %s | Department: %s | Designation: %s\n", empList[i].id, empList[i].name, empList[i].department,empList[i].designation);
        usleep(50000);
        printf("⇢ Gross Salary: %.2f\n", grossSalary);
        usleep(50000);
        printf("⇢ Standard Deduction: %.2f\n", standardDeduction);
        usleep(50000);
        printf("⇢ Taxable Income: %.2f\n", taxableIncome);
        usleep(50000);
        printf("⇢ Total Tax Payable: %.2f\n", tax);
        usleep(50000);
        printf("---------------------------------------------------------------------\n");
    }
}

void getPassword(char *password, size_t size) {
    printf(" 🔒 Enter password: "); // password will be visible 
    fgets(password, size, stdin);
    password[strcspn(password, "\n")] = 0;
    printf("\n");
}

void login() {
    char username[20], password[20];
    const char correctUsername[] = "admin"; // fixed username 
    const char correctPassword[] = "1234"; // fixed password
    int attempts = 4;

    while (attempts > 0) {
        printf("\n\t----- 🔐 𝐋 𝐎 𝐆 𝑰 𝐍 🔐 -----\n\n");
        printf(" 👤 Enter username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0;

        getPassword(password, sizeof(password));

        if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
            printf("🔓 Login successful! ✅\n");
            printf("   UserType: 𝐀\n"); // if user is admin
            break;
        } else {
            attempts--;
            printf("Invalid username or password.❗️⚠️\n\n");
            printf("UserType: 𝐍\n"); // if normal user 
            printf("Remaining attempts: %d\n", attempts);
            if (attempts == 0) {
                printf("Maximum attempts exceeded. Exiting program.\n");               
                exit(1);       
            }
            printf("Press Enter to try again...\n");
            getchar();
            system("clear");
        }
    }
}

int main() {
    login();
    loadFromFile();
    atexit(saveToTextFile);
    int choice;
    do {
        printf("\n╔════════════════════════════════════════════════════════════════════════════════════════╗\n║                                                                                        ║");
        printf("\n║   ☆~☆~☆~☆ 🏛️  🧑‍💼  𝐄 𝐌 𝐏 𝐋 𝐎 𝐘 𝐄 𝐄  𝐌 𝐀 𝐍 𝐀 𝐆 𝐄 𝐌 𝐄 𝐍 𝐓  𝐒 𝐘 𝐒 𝐓 𝐄 𝐌  🧑‍💼 🏛️ ☆~☆~☆~☆   ║\n║                                                                                        ║\n"); 
        printf("╠════════════════════════════════════════════════════════════════════════════════════════╣\n");
        printf("║ 🅂 🄴 🄻 🄴 🄲 🅃  🄾 🄿 🅃 🄸 🄾 🄽  →                                                            ║\n║                                                                                        ║\n");
        printf("║ ➤ ➕ [1]. Add Employee                                       \t                         ║\n");
        usleep(50000);
        printf("║ ➤ 👥 [2]. View Employees                                                               ║\n");
        usleep(50000);
        printf("║ ➤ 🔍 [3]. Search Employee by ID                                                        ║\n");
        usleep(50000);
        printf("║ ➤ 🗑️  [4]. Delete Employee                                                              ║\n");
        usleep(50000);
        printf("║ ➤ ✏️  [5]. Update Employee Details                                                      ║\n");
        usleep(50000);
        printf("║ ➤ 📊 [6]. Generate Tax Report                                                          ║\n");
        usleep(50000);
        printf("║ ➤ 🔃 [7]. Sort Employees                                                               ║\n");
        usleep(50000);
        printf("║ ➤ 🚪 [8]. Exit                                                                         ║\n");
        usleep(50000);
        printf("╚════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
        printf("➠ Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: viewEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: deleteEmployee(); break;
            case 5: updateEmployee(); break;
            case 6: calculateTax(); break;
            case 7: sortEmployees(); break;
            case 8: saveToFile();
            printf("Exiting");
            for(int i = 0; i<3; i++) { // for attractive effect at exit point
                printf(".");
                fflush(stdout);
                usleep(900000);    
            }
            printf("\r  Exited.   ");
            fflush(stdout);
            printf("\n");
            break;
            default: printf("Invalid choice.⚠️\n");
        }
    } while (choice!=8);

    return 0;
}



