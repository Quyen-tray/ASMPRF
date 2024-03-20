#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

// Struct để đại diện cho mỗi mục trong tệp
typedef struct {
    char name[MAX_LENGTH];
    int age;
} Person;

// Hàm để tạo mới một mục trong tệp
void createRecord(FILE *file) {
    Person person;
    printf("Nhap ten: ");
    scanf("%s", person.name);
    printf("Nhap tuoi: ");
    scanf("%d", &person.age);

    fprintf(file, "%s %d\n", person.name, person.age);
}

// Hàm để đọc tất cả các mục từ tệp và hiển thị chúng
void readRecords(FILE *file) {
    Person person;
    rewind(file); // Đặt con trỏ tệp ở đầu
    printf("Danh sach muc:\n");
    while (fscanf(file, "%s %d", person.name, &person.age) != EOF) {
        printf("Ten: %s, Tuoi: %d\n", person.name, person.age);
    }
}

// Hàm để cập nhật một mục trong tệp
void updateRecord(FILE *file) {
    char searchName[MAX_LENGTH];
    printf("Nhap ten muon cap nhat: ");
    scanf("%s", searchName);

    FILE *tempFile = fopen("temp.txt", "w");
    Person person;
    while (fscanf(file, "%s %d", person.name, &person.age) != EOF) {
        if (strcmp(person.name, searchName) == 0) {
            printf("Nhap ten moi: ");
            scanf("%s", person.name);
            printf("Nhap tuoi moi: ");
            scanf("%d", &person.age);
        }
        fprintf(tempFile, "%s %d\n", person.name, person.age);
    }

    fclose(file);
    fclose(tempFile);
    remove("data.txt");
    rename("temp.txt", "data.txt");
}

// Hàm để xoá một mục từ tệp
void deleteRecord(FILE *file) {
    char searchName[MAX_LENGTH];
    printf("Nhap ten muon xoa: ");
    scanf("%s", searchName);

    FILE *tempFile = fopen("temp.txt", "w");
    Person person;
    while (fscanf(file, "%s %d", person.name, &person.age) != EOF) {
        if (strcmp(person.name, searchName) != 0) {
            fprintf(tempFile, "%s %d\n", person.name, person.age);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove("data.txt");
    rename("temp.txt", "data.txt");
}

int main() {
    FILE *file = fopen("data.txt", "a+");
    FILE *file = fopen("temp.txt", "a+");

    if (file == NULL) {
        printf("Loi khi mo tep.\n");
        return 1;
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Tao moi\n");
        printf("2. Doc danh sach\n");
        printf("3. Cap nhat\n");
        printf("4. Xoa\n");
        printf("0. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                createRecord(file);
                break;
            case 2:
                readRecords(file);
                break;
            case 3:
                updateRecord(file);
                break;
            case 4:
                deleteRecord(file);
                break;
            case 0:
                printf("Ket thuc chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while(choice != 0);

    fclose(file);
    return 0;
}
