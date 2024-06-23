#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����ü ����
typedef struct Platform {
    char name[50];
    char id[50];
    char password[50];
    char category[50];
    struct Platform* next;
} Platform;

//��带 ����
Platform* createNode(char* name, char* id, char* password, char* category) {
    Platform* newNode = (Platform*)malloc(sizeof(Platform));
    strcpy(newNode->name, name);
    strcpy(newNode->id, id);
    strcpy(newNode->password, password);
    strcpy(newNode->category, category);
    newNode->next = NULL;
    return newNode;
}

// ��� ����Ʈ�� �߰��ϱ�
void addPlatform(Platform** head, char* name, char* id, char* password, char* category) {
    Platform* newNode = createNode(name, id, password, category);
    newNode->next = *head;
    *head = newNode;
}

// ���� ���� ��Ű��
void sortByName(Platform** head) {
    if (*head == NULL) return;

    Platform* sorted = NULL;
    Platform* current = *head;
    Platform* next = NULL;

    while (current != NULL) {
        next = current->next;
        if (sorted == NULL || strcmp(current->name, sorted->name) < 0) {
            current->next = sorted;
            sorted = current;
        }
        else {
            Platform* temp = sorted;
            while (temp->next != NULL && strcmp(temp->next->name, current->name) < 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;
}

// ����Ʈ�� ���Ͽ� ����
//3�� ���� �������� ���� �� �ϰ� ������ �� ���
void saveToFile(Platform* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("���� ���� ����.\n");
        return;
    }

    Platform* current = head;
    while (current != NULL) {
        fprintf(file, "Name: %s, ID: %s, Password: %s, Category: %s\n", current->name, current->id, current->password, current->category);
        current = current->next;
    }

    fclose(file);  // ���� ��Ʈ�� �ݱ�
}

// ���Ͽ��� �÷��� ������ �о���̴� �Լ�
void loadFromFile(Platform** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("���� ���� ����\n");
        return;
    }

    char buffer[256];
    char name[50], id[50], password[50], category[50];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (sscanf(buffer, "Name: %49[^,], ID: %49[^,], Password: %49[^,], Category: %49[^\n]", name, id, password, category) == 4) {
            addPlatform(head, name, id, password, category);
        }
    }

    fclose(file);  // ���� ��Ʈ�� �ݱ�
}

// �÷��� ������ �Է¹޴� �Լ�
// 1�� ���� !!
void Add_Platform(const char* filename) {
    char name[50];
    char id[50];
    char password[50];
    char category[50];
    printf("=============== ID KEEPER ================\n\n");
    printf(" �� ���õ� �ɼ� : �÷��� �߰�\n\n");
    printf(" �� �߰��� �÷��� >>> ");
    scanf("%49s", name);
    printf("\n �� �÷��� ID >>> ");
    scanf("%49s", id);
    printf("\n �� �÷��� Password >>> ");
    scanf("%49s", password);
    printf("\n �� �÷��� ī�װ� >>> ");
    scanf("%49s", category);

    // ���Ͽ� �߰� ���� ����
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf(" ���� ���� ����");
        return;
    }

    fprintf(file, "Name: %s, ID: %s, Password: %s, Category: %s\n", name, id, password, category);
    fclose(file);  // ���� ��Ʈ�� �ݱ�
    printf("\n\n �� ���̵�/��й�ȣ �߰��� �Ϸ� �Ǿ����ϴ�!");
}

// �÷��� ������ �˻��Ͽ� ����ϴ� �Լ�
// 2�� ���� !!
void SearchPlatform(const char* filename) {
    Platform* head = NULL;
    loadFromFile(&head, filename);

    char name[50];
    printf("=============== ID KEEPER ================\n\n");
    printf(" �� ���õ� �ɼ� : �÷��� �˻�\n\n");
    printf(" �� �˻� �� �÷��� �Է�>>> ");
    scanf("%49s", name);

    Platform* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            system("cls");
            printf("=============== ID KEEPER ================\n\n");
            printf(" �� ���õ� �ɼ� : �÷��� �˻�\n\n");
            printf(" <�÷��� : %s>\n\n �� ID       : %s\n �� Password : %s\n �� ī�װ� : %s\n", current->name, current->id, current->password, current->category);
            return;
        }
        current = current->next;
    }
    printf(" �� �������� �ʴ� �÷��� �Դϴ�.\n", name);
}

// �÷��� ������ �����ϴ� �Լ�
//3�� ���� �� -> �����Ұ� = ���̵�/��й�ȣ ����
void updatePlatform(Platform* head, char* name) {
    Platform* current = head;
    system("cls");
    printf("=============== ID KEEPER ================\n\n");
    printf(" �� ���õ� �ɼ� : �÷��� ����\n\n");
    printf(" �� ������ �÷��� : %s", name);
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            int choice;
            printf("\n\n 1. ID ���� \n\n");
            printf(" 2. Password ����\n\n");
            printf(" 3. ī�װ� ����\n\n");
            printf("=========================�� �ɼ� ���� >>> ");
            scanf("%d", &choice);

            //3�� ���� �� 1�� ���� : ID ����
            if (choice == 1) {
                system("cls");
                printf("=============== ID KEEPER ================\n\n");
                printf(" �� ������ �÷��� : %s\n\n", name);
                printf(" �� ������ �ɼ� : ID\n\n");
                printf(" �� ���� ID : %s\n\n", current->id);
                char newId[50];
                printf(" �� ���ο� ID �Է� >>> ");
                scanf("%49s", newId);
                strcpy(current->id, newId);
                system("cls");
                printf("=============== ID KEEPER ================\n\n");
                printf(" �� ������ �÷��� : %s\n\n", name);
                printf(" �� ������ �ɼ� : ID\n\n");
                printf(" �� ���ο� ID : %s\n\n", current->id);
                printf("\n\n �� ID ������Ʈ �Ϸ�");
            }
            //3�� ���� �� 2�� ���� : ��й�ȣ ����
            else if (choice == 2) {
                system("cls");
                printf("=============== ID KEEPER ================\n\n");
                printf(" �� ������ �÷��� : %s\n\n", name);
                printf(" �� ������ �ɼ� : Password\n\n");
                printf(" �� ���� Password : %s\n\n", current->password);
                char newPassword[50];
                printf(" �� ���ο� Password �Է� >>> ");
                scanf("%49s", newPassword);
                strcpy(current->password, newPassword);
                system("cls");
                printf("=============== ID KEEPER ================\n\n");
                printf(" �� ������ �÷��� : %s\n\n", name);
                printf(" �� ������ �ɼ� : Password\n\n");
                printf(" �� ���ο� Password : %s\n\n", current->password);
                printf("\n\n �� Password ������Ʈ �Ϸ�");
            }
            ///3�� ���� �� 3�� ���� : ī�װ� ����
            else if (choice == 3) {

                system("cls");
                printf("=============== ID KEEPER ================\n\n");
                printf(" �� ������ �÷��� : %s\n\n", name);
                printf(" �� ������ �ɼ� : ī�װ�\n\n");
                printf(" �� ���� ī�װ� : %s\n\n", current->category);
                char newCategory[50];
                printf(" �� ���ο� ī�װ� �Է� >>> ");
                scanf("%49s", newCategory);
                strcpy(current->category, newCategory);
                system("cls");
                printf("=============== ID KEEPER ================\n\n");
                printf(" �� ������ �÷��� : %s\n\n", name);
                printf(" �� ������ �ɼ� : ī�װ�\n\n");
                printf(" �� ���ο� ī�װ� : %s\n\n", current->category);
                printf("\n\n �� ī�װ� ������Ʈ �Ϸ�");
            }
            else {
                printf(" �� �ɼ� ���� ���� ! \n");
            }
            return;
        }
        current = current->next;
    }
    printf("\n\n �� %s�� ã�� �� �����ϴ�. �ٽ� Ȯ�����ּ���.\n", name);
}

//3�� ����!!
//ID �Ǵ� Password ����
void Change_ID_Password(const char* filename) {
    Platform* head = NULL;
    loadFromFile(&head, filename);

    char name[50];
    printf("=============== ID KEEPER ================\n\n");
    printf(" �� ���õ� �ɼ� : �÷��� ����\n\n");
    printf(" �� ���� �� �÷��� �Է�>>> ");
    scanf("%49s", name);

    updatePlatform(head, name);
    saveToFile(head, filename);
}

// �÷��� ������ �����ϴ� �Լ�
// 4�� ���� �� 
void deletePlatform(Platform** head, char* name) {
    Platform* current = *head;
    Platform* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                *head = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
            system("cls");
            printf("=============== ID KEEPER ================\n\n");
            printf(" �� ���õ� �ɼ� : �÷��� ����\n\n");
            printf(" �� ���� �� �÷��� : %s", name);
            printf("\n\n �� %s(��)�� ���������� �����Ǿ����ϴ�.", name);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("\n �� %s�� �������� �ʽ��ϴ�.\n�ٽ� Ȯ�� ��Ź�帳�ϴ�.\n", name);
}

//4�� ���� !!
//�÷��� �Է� �ް� ������Ű��
void deletePlatformInFile(const char* filename) {
    Platform* head = NULL;
    loadFromFile(&head, filename);

    char name[50];
    printf("=============== ID KEEPER ================\n\n");
    printf(" �� ���õ� �ɼ� : �÷��� ����\n\n");
    printf(" �� ������ �÷��� �Է� >>> ");
    scanf("%49s", name);

    deletePlatform(&head, name);
    saveToFile(head, filename);
}

// ī�װ����� �����ϴ� �Լ�
void printByCategory(Platform* head, char* category) {
    Platform* current = head;
    int num = 1;
    int Sizeof = 0;
    int currentPage = 1;
    int itemsPerPage = 4;
    int totalPages = 0;

    //�� ������ ����
    while (current != NULL) {
        if (strcmp(current->category, category) == 0) {
            Sizeof++;
        }
        current = current->next;
    }

    totalPages = (Sizeof + itemsPerPage - 1) / itemsPerPage; //������ �� ���
    current = head;

    while (1) {
        system("cls");
        printf("=============== ID KEEPER =================\n\n");
        printf(" �� ���õ� �ɼ� : ���� (ī�װ�)\n\n");
        printf(" �� ���õ� ī�װ� : %s\n\n", category);

        int itemCount = 0;
        num = 1;
        Platform* temp = head;
        while (temp != NULL && itemCount < (currentPage - 1) * itemsPerPage) {
            if (strcmp(temp->category, category) == 0) {
                itemCount++;
            }
            temp = temp->next;
        }

        num = (currentPage - 1) * itemsPerPage + 1; // ���� ������ ���� ��ȣ ���


        itemCount = 0;
        while (temp != NULL && itemCount < itemsPerPage) {
            if (strcmp(temp->category, category) == 0) {
                if (num < 10)
                    printf("-%d----------------------------------------\n", num);
                else
                    printf("-%d---------------------------------------\n", num);

                printf(" <�÷���    : %s>\n �� ID       : %s\n �� Password : %s\n\n", temp->name, temp->id, temp->password);
                num++;
                itemCount++;
            }
            temp = temp->next;
        }

        printf("------------------------------------------\n");
        printf("[���� ������: %d / %d] \n", currentPage, totalPages);
        printf("[���� 1 | 2 ����] [�ʱ�ȭ�� �� 0]\n");
        printf("=========================�� �ɼ� ���� >>> ");
        int choice;
        scanf("%d", &choice);

        if (choice == 2 && currentPage < totalPages) {
            currentPage++;
        }
        else if (choice == 1 && currentPage > 1) {
            currentPage--;
        }
        else if (choice == 0) {
            break;
        }
    }
}


// ��� �÷��� ������ ����ϴ� �Լ�
void printAllPlatforms(Platform* head) {
    Platform* current = head;
    int num = 1;
    int Sizeof = 0;
    int currentPage = 1;
    int itemsPerPage = 4;
    int totalPages = 0;

    // ��ü ����� ������ ����
    while (current != NULL) {
        Sizeof++;
        current = current->next;
    }

    totalPages = (Sizeof + itemsPerPage - 1) / itemsPerPage; // ��ü ������ �� ���
    current = head;

    num = (currentPage - 1) * itemsPerPage + 1; // ���� ������ ���� ��ȣ ���

    while (1) {
        system("cls");
        printf("=============== ID KEEPER ================\n\n");
        printf(" �� ���õ� �ɼ� : ���� (��ü)\n\n");

        int itemCount = 0;
        Platform* temp = head;
        while (temp != NULL && itemCount < (currentPage - 1) * itemsPerPage) {
            itemCount++;
            temp = temp->next;
        }

        itemCount = 0;
        while (temp != NULL && itemCount < itemsPerPage) {
            if (num < 10)
                printf("-%d----------------------------------------\n", num);
            else
                printf("-%d---------------------------------------\n", num);
            printf(" <�÷���    : %s (%s)>\n �� ID       : %s\n �� Password : %s\n\n", temp->name, temp->category, temp->id, temp->password);
            num++;
            itemCount++;
            temp = temp->next;
        }

        printf("------------------------------------------\n");
        printf("[���� ������: %d / %d] \n", currentPage, totalPages);
        printf("[���� 1 | 2 ����] [�ʱ�ȭ�� �� 0]\n");
        printf("=========================�� �ɼ� ���� >>> ");


        int choice;
        scanf("%d", &choice);

        if (choice == 2 && currentPage < totalPages) {
            currentPage++;
        }
        else if (choice == 1 && currentPage > 1) {
            currentPage--;
        }
        else if (choice == 0) {
            break;
        }
    }
}


// �߰� ��� �޴�
void additionalFunctions(const char* filename) {
    Platform* head = NULL;
    loadFromFile(&head, filename);

    int choice;
    printf("=============== ID KEEPER ================\n\n");
    printf(" �� ���õ� �ɼ� : ����\n\n");
    printf(" 1. ī�װ����� ���\n\n");
    printf(" 2. ��ü ���(������)\n\n");
    printf("=========================�� �ɼ� ���� >>> ");
    scanf("%d", &choice);

    if (choice == 1) {
        char category[50];
        system("cls");
        printf("=============== ID KEEPER ================\n\n");
        printf(" �� ���õ� �ɼ� : ���� (ī�װ�)\n\n");
        printf(" �� ī�װ� �Է� >>> ");
        scanf("%49s", category);
        system("cls");
        printByCategory(head, category);
    }
    else if (choice == 2) {
        sortByName(&head);
        system("cls");
        printAllPlatforms(head);

    }
    else {
        printf(" �� 1-2�� �ɼ��߿� �Է� �ٶ��ϴ�.\n");
    }
}

void ClearBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int main() {
    Platform* head = NULL;
    int choice;
    while (1) {
        system("cls"); // ȭ���� �����ϰ�
        printf("=============== ID KEEPER ================\n\n");
        printf(" 1. ���̵�/��й�ȣ �߰�\n\n"); //1
        printf(" 2. ���̵�/��й�ȣ �˻�\n\n");
        printf(" 3. ���̵�/��й�ȣ ����\n\n");
        printf(" 4. ���̵�/��й�ȣ ����\n\n");
        printf(" 5. ���̵�/��й�ȣ ����\n\n");
        printf(" 6. ���α׷� ����\n\n");
        printf("=========================�� �ɼ� ���� >>> ");
        scanf("%d", &choice);
        getchar(); // ���ۿ� ���� ���� Ű ����


        //1�� ���� �߰�
        if (choice == 1) {
            system("cls");
            Add_Platform("platforms.txt");
            ClearBuffer(); //���ۿ� ���� ���� ���� �־ getchar ��� ����ȭ ��Ű��
            while (1) {
                printf("\n\n\n�� �� ���� Ű �Է�.\n");
                printf("\n\n=========================================");

                int input = getchar(); // ����ڷκ��� �� ���� �Է� �ޱ�
                if (input == '\n') { // �Է¹��� ���ڰ� '\n'�̸�, �� ���� Ű�̸�
                    break; // while ������ �������� ���� �ܰ�� ����
                }
            }
        }
        //2�� ���� ���̵�/��� �˻� <<�÷��� �̸� �˻��ϱ�
        else if (choice == 2) {
            system("cls");
            SearchPlatform("platforms.txt");
            ClearBuffer(); //���ۿ� ���� ���� ���� �־ getchar ��� ����ȭ ��Ű��
            while (1) {
                printf("\n\n\n�� �� ���� Ű �Է�.\n");
                printf("\n\n=========================================");

                int input = getchar(); // ����ڷκ��� �� ���� �Է� �ޱ�
                if (input == '\n') { // �Է¹��� ���ڰ� '\n'�̸�, �� ���� Ű�̸�
                    break; // while ������ �������� ���� �ܰ�� ����
                }
            }
        }
        //3�� ���� ���̵�/��� ����
        else if (choice == 3) {
            system("cls");
            Change_ID_Password("platforms.txt");
            ClearBuffer(); //���ۿ� ���� ���� ���� �־ getchar ��� ����ȭ ��Ű��
            while (1) {
                printf("\n\n\n�� �� ���� Ű �Է�.\n");
                printf("\n\n=========================================");

                int input = getchar(); // ����ڷκ��� �� ���� �Է� �ޱ�
                if (input == '\n') { // �Է¹��� ���ڰ� '\n'�̸�, �� ���� Ű�̸�
                    break; // while ������ �������� ���� �ܰ�� ����
                }
            }
        }

        //4�� ���� �÷��� �˻� �� ����
        else if (choice == 4) {
            system("cls");
            deletePlatformInFile("platforms.txt");
            ClearBuffer(); //���ۿ� ���� ���� ���� �־ getchar ��� ����ȭ ��Ű��
            while (1) {
                printf("\n\n\n�� �� ���� Ű �Է�.\n");
                printf("\n\n=========================================");

                int input = getchar(); // ����ڷκ��� �� ���� �Է� �ޱ�
                if (input == '\n') { // �Է¹��� ���ڰ� '\n'�̸�, �� ���� Ű�̸�
                    break; // while ������ �������� ���� �ܰ�� ����
                }
            }
        }
        //5�� ���� �� 1�� ���ý� - �÷��� ī�װ��� ���� // 2�� ���ý� - ��ü ���� �� ���
        else if (choice == 5) {
            system("cls");
            additionalFunctions("platforms.txt");
            ClearBuffer(); //���ۿ� ���� ���� ���� �־ getchar ��� ����ȭ ��Ű��
            /*
            while (1) {
                printf("\n\n\n�� �� ���� Ű �Է�.\n");
                printf("\n\n=========================================");
                int input = getchar(); // ����ڷκ��� �� ���� �Է� �ޱ�
                if (input == '\n') { // �Է¹��� ���ڰ� '\n'�̸�, �� ���� Ű�̸�
                    break; // while ������ �������� ���� �ܰ�� ����
                }
            }*/ //function5�� �Լ� �ȿ��� ���� ����
        }

        //�����ϱ�
        else if (choice == 6) {
            break;
        }
        //�ٸ� �� �Է��ϸ�
        else {
            printf("1-6�� �ɼ� �Է��ϼ���.\n");
            while (1) {
                printf("\n\n\n�� �� ���� Ű �Է�.\n");
                int input = getchar(); // ����ڷκ��� �� ���� �Է� �ޱ�
                if (input == '\n') { // �Է¹��� ���ڰ� '\n'�̸�, �� ���� Ű�̸�
                    break; // while ������ �������� ���� �ܰ�� ����
                }
            }
        }
    }

    // �޸� ����
    while (head != NULL) {
        Platform* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
