#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
    int id;
    char name[50];
    int age;
};

// ➕ Add Record
void addRecord() {
    FILE *fp = fopen("data.txt", "a");
    struct Record r;

    printf("Enter ID: ");
    scanf("%d", &r.id);

    printf("Enter Name: ");
    scanf("%s", r.name);

    printf("Enter Age: ");
    scanf("%d", &r.age);

    fwrite(&r, sizeof(r), 1, fp);
    fclose(fp);

    printf("Record added!\n");
}

// 📜 View Records
void viewRecords() {
    FILE *fp = fopen("data.txt", "r");
    struct Record r;

    printf("\n--- Records ---\n");

    while (fread(&r, sizeof(r), 1, fp)) {
        printf("\nID: %d", r.id);
        printf("\nName: %s", r.name);
        printf("\nAge: %d\n", r.age);
    }

    fclose(fp);
}

// 🔍 Search Record
void searchRecord() {
    FILE *fp = fopen("data.txt", "r");
    struct Record r;
    int id, found = 0;

    printf("Enter ID to search: ");
    scanf("%d", &id);

    while (fread(&r, sizeof(r), 1, fp)) {
        if (r.id == id) {
            printf("\nRecord Found!");
            printf("\nName: %s", r.name);
            printf("\nAge: %d\n", r.age);
            found = 1;
        }
    }

    if (!found)
        printf("Record not found!\n");

    fclose(fp);
}

// ✏️ Update Record
void updateRecord() {
    FILE *fp = fopen("data.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    struct Record r;
    int id;

    printf("Enter ID to update: ");
    scanf("%d", &id);

    while (fread(&r, sizeof(r), 1, fp)) {
        if (r.id == id) {
            printf("Enter new name: ");
            scanf("%s", r.name);
            printf("Enter new age: ");
            scanf("%d", &r.age);
        }
        fwrite(&r, sizeof(r), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("data.txt");
    rename("temp.txt", "data.txt");

    printf("Record updated!\n");
}

// ❌ Delete Record
void deleteRecord() {
    FILE *fp = fopen("data.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    struct Record r;
    int id;

    printf("Enter ID to delete: ");
    scanf("%d", &id);

    while (fread(&r, sizeof(r), 1, fp)) {
        if (r.id != id) {
            fwrite(&r, sizeof(r), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("data.txt");
    rename("temp.txt", "data.txt");

    printf("Record deleted!\n");
}

// 🏠 Main Menu
int main() {
    int choice;

    while (1) {
        printf("\n1. Add Record\n2. View Records\n3. Search Record\n4. Update Record\n5. Delete Record\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addRecord(); break;
            case 2: viewRecords(); break;
            case 3: searchRecord(); break;
            case 4: updateRecord(); break;
            case 5: deleteRecord(); break;
            default: exit(0);
        }
    }
}