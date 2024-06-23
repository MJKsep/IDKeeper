#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 구조체 정의
typedef struct Platform {
    char name[50];
    char id[50];
    char password[50];
    char category[50];
    struct Platform* next;
} Platform;

//노드를 생성
Platform* createNode(char* name, char* id, char* password, char* category) {
    Platform* newNode = (Platform*)malloc(sizeof(Platform));
    strcpy(newNode->name, name);
    strcpy(newNode->id, id);
    strcpy(newNode->password, password);
    strcpy(newNode->category, category);
    newNode->next = NULL;
    return newNode;
}

// 노드 리스트에 추가하기
void addPlatform(Platform** head, char* name, char* id, char* password, char* category) {
    Platform* newNode = createNode(name, id, password, category);
    newNode->next = *head;
    *head = newNode;
}

// 사전 나열 시키기
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

// 리스트를 파일에 저장
//3번 선택 마지막에 수정 다 하고 저장할 때 사용
void saveToFile(Platform* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("파일 열기 실패.\n");
        return;
    }

    Platform* current = head;
    while (current != NULL) {
        fprintf(file, "Name: %s, ID: %s, Password: %s, Category: %s\n", current->name, current->id, current->password, current->category);
        current = current->next;
    }

    fclose(file);  // 파일 스트림 닫기
}

// 파일에서 플랫폼 정보를 읽어들이는 함수
void loadFromFile(Platform** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("파일 열기 실패\n");
        return;
    }

    char buffer[256];
    char name[50], id[50], password[50], category[50];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (sscanf(buffer, "Name: %49[^,], ID: %49[^,], Password: %49[^,], Category: %49[^\n]", name, id, password, category) == 4) {
            addPlatform(head, name, id, password, category);
        }
    }

    fclose(file);  // 파일 스트림 닫기
}

// 플랫폼 정보를 입력받는 함수
// 1번 선택 !!
void Add_Platform(const char* filename) {
    char name[50];
    char id[50];
    char password[50];
    char category[50];
    printf("=============== ID KEEPER ================\n\n");
    printf(" ★ 선택된 옵션 : 플렛폼 추가\n\n");
    printf(" ▶ 추가할 플렛폼 >>> ");
    scanf("%49s", name);
    printf("\n ▶ 플렛폼 ID >>> ");
    scanf("%49s", id);
    printf("\n ▶ 플렛폼 Password >>> ");
    scanf("%49s", password);
    printf("\n ▶ 플렛폼 카테고리 >>> ");
    scanf("%49s", category);

    // 파일에 추가 모드로 열기
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf(" 파일 열기 실패");
        return;
    }

    fprintf(file, "Name: %s, ID: %s, Password: %s, Category: %s\n", name, id, password, category);
    fclose(file);  // 파일 스트림 닫기
    printf("\n\n → 아이디/비밀번호 추가가 완료 되었습니다!");
}

// 플랫폼 정보를 검색하여 출력하는 함수
// 2번 선택 !!
void SearchPlatform(const char* filename) {
    Platform* head = NULL;
    loadFromFile(&head, filename);

    char name[50];
    printf("=============== ID KEEPER ================\n\n");
    printf(" ★ 선택된 옵션 : 플렛폼 검색\n\n");
    printf(" ▶ 검색 할 플렛폼 입력>>> ");
    scanf("%49s", name);

    Platform* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            system("cls");
            printf("=============== ID KEEPER ================\n\n");
            printf(" ★ 선택된 옵션 : 플렛폼 검색\n\n");
            printf(" <플렛폼 : %s>\n\n ※ ID       : %s\n ※ Password : %s\n ※ 카테고리 : %s\n", current->name, current->id, current->password, current->category);
            return;
        }
        current = current->next;
    }
    printf(" → 존재하지 않는 플렛폼 입니다.\n", name);
}

// 플랫폼 정보를 수정하는 함수
//3번 선택 후 -> 수정할거 = 아이디/비밀번호 선택
void updatePlatform(Platform* head, char* name) {
    Platform* current = head;
    system("cls");
    printf("=============== ID KEEPER ================\n\n");
    printf(" ★ 선택된 옵션 : 플렛폼 수정\n\n");
    printf(" ▶ 변경할 플렛폼 : %s", name);
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            int choice;
            printf("\n\n 1. ID 변경 \n\n");
            printf(" 2. Password 변경\n\n");
            printf(" 3. 카테고리 변경\n\n");
            printf("=========================▶ 옵션 선택 >>> ");
            scanf("%d", &choice);

            //3번 선택 후 1번 선택 : ID 수정
            if (choice == 1) {
                system("cls");
                printf("=============== ID KEEPER ================\n\n");
                printf(" ▶ 변경할 플렛폼 : %s\n\n", name);
                printf(" ▶ 변경할 옵션 : ID\n\n");
                printf(" ▶ 현재 ID : %s\n\n", current->id);
                char newId[50];
                printf(" ▶ 새로운 ID 입력 >>> ");
                scanf("%49s", newId);
                strcpy(current->id, newId);
                system("cls");
                printf("=============== ID KEEPER ================\n\n");
                printf(" ▶ 변경할 플렛폼 : %s\n\n", name);
                printf(" ▶ 변경할 옵션 : ID\n\n");
                printf(" ▶ 새로운 ID : %s\n\n", current->id);
                printf("\n\n → ID 업데이트 완료");
            }
            //3번 선택 후 2번 선택 : 비밀번호 수정
            else if (choice == 2) {
                system("cls");
                printf("=============== ID KEEPER ================\n\n");
                printf(" ▶ 변경할 플렛폼 : %s\n\n", name);
                printf(" ▶ 변경할 옵션 : Password\n\n");
                printf(" ▶ 현재 Password : %s\n\n", current->password);
                char newPassword[50];
                printf(" ▶ 새로운 Password 입력 >>> ");
                scanf("%49s", newPassword);
                strcpy(current->password, newPassword);
                system("cls");
                printf("=============== ID KEEPER ================\n\n");
                printf(" ▶ 변경할 플렛폼 : %s\n\n", name);
                printf(" ▶ 변경할 옵션 : Password\n\n");
                printf(" ▶ 새로운 Password : %s\n\n", current->password);
                printf("\n\n → Password 업데이트 완료");
            }
            ///3번 선택 후 3번 선택 : 카테고리 수정
            else if (choice == 3) {

                system("cls");
                printf("=============== ID KEEPER ================\n\n");
                printf(" ▶ 변경할 플렛폼 : %s\n\n", name);
                printf(" ▶ 변경할 옵션 : 카테고리\n\n");
                printf(" ▶ 현재 카테고리 : %s\n\n", current->category);
                char newCategory[50];
                printf(" ▶ 새로운 카테고리 입력 >>> ");
                scanf("%49s", newCategory);
                strcpy(current->category, newCategory);
                system("cls");
                printf("=============== ID KEEPER ================\n\n");
                printf(" ▶ 변경할 플렛폼 : %s\n\n", name);
                printf(" ▶ 변경할 옵션 : 카테고리\n\n");
                printf(" ▶ 새로운 카테고리 : %s\n\n", current->category);
                printf("\n\n → 카테고리 업데이트 완료");
            }
            else {
                printf(" → 옵션 선택 오류 ! \n");
            }
            return;
        }
        current = current->next;
    }
    printf("\n\n → %s을 찾을 수 없습니다. 다시 확인해주세요.\n", name);
}

//3번 선택!!
//ID 또는 Password 변경
void Change_ID_Password(const char* filename) {
    Platform* head = NULL;
    loadFromFile(&head, filename);

    char name[50];
    printf("=============== ID KEEPER ================\n\n");
    printf(" ★ 선택된 옵션 : 플렛폼 수정\n\n");
    printf(" ▶ 변경 할 플렛폼 입력>>> ");
    scanf("%49s", name);

    updatePlatform(head, name);
    saveToFile(head, filename);
}

// 플랫폼 정보를 삭제하는 함수
// 4번 선택 시 
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
            printf(" ★ 선택된 옵션 : 플렛폼 삭제\n\n");
            printf(" ▶ 삭제 할 플렛폼 : %s", name);
            printf("\n\n → %s(이)가 정상적으로 삭제되었습니다.", name);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("\n → %s가 존재하지 않습니다.\n다시 확인 부탁드립니다.\n", name);
}

//4번 선택 !!
//플렛폼 입력 받고 삭제시키기
void deletePlatformInFile(const char* filename) {
    Platform* head = NULL;
    loadFromFile(&head, filename);

    char name[50];
    printf("=============== ID KEEPER ================\n\n");
    printf(" ★ 선택된 옵션 : 플렛폼 삭제\n\n");
    printf(" ▶ 삭제할 플렛폼 입력 >>> ");
    scanf("%49s", name);

    deletePlatform(&head, name);
    saveToFile(head, filename);
}

// 카테고리별로 나열하는 함수
void printByCategory(Platform* head, char* category) {
    Platform* current = head;
    int num = 1;
    int Sizeof = 0;
    int currentPage = 1;
    int itemsPerPage = 4;
    int totalPages = 0;

    //총 사이즈 측정
    while (current != NULL) {
        if (strcmp(current->category, category) == 0) {
            Sizeof++;
        }
        current = current->next;
    }

    totalPages = (Sizeof + itemsPerPage - 1) / itemsPerPage; //페이지 수 계산
    current = head;

    while (1) {
        system("cls");
        printf("=============== ID KEEPER =================\n\n");
        printf(" ★ 선택된 옵션 : 나열 (카테고리)\n\n");
        printf(" ▶ 선택된 카테고리 : %s\n\n", category);

        int itemCount = 0;
        num = 1;
        Platform* temp = head;
        while (temp != NULL && itemCount < (currentPage - 1) * itemsPerPage) {
            if (strcmp(temp->category, category) == 0) {
                itemCount++;
            }
            temp = temp->next;
        }

        num = (currentPage - 1) * itemsPerPage + 1; // 현재 페이지 시작 번호 계산


        itemCount = 0;
        while (temp != NULL && itemCount < itemsPerPage) {
            if (strcmp(temp->category, category) == 0) {
                if (num < 10)
                    printf("-%d----------------------------------------\n", num);
                else
                    printf("-%d---------------------------------------\n", num);

                printf(" <플렛폼    : %s>\n ※ ID       : %s\n ※ Password : %s\n\n", temp->name, temp->id, temp->password);
                num++;
                itemCount++;
            }
            temp = temp->next;
        }

        printf("------------------------------------------\n");
        printf("[현재 페이지: %d / %d] \n", currentPage, totalPages);
        printf("[◀◀ 1 | 2 ▶▶] [초기화면 → 0]\n");
        printf("=========================▶ 옵션 선택 >>> ");
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


// 모든 플랫폼 정보를 출력하는 함수
void printAllPlatforms(Platform* head) {
    Platform* current = head;
    int num = 1;
    int Sizeof = 0;
    int currentPage = 1;
    int itemsPerPage = 4;
    int totalPages = 0;

    // 전체 노드의 개수를 구함
    while (current != NULL) {
        Sizeof++;
        current = current->next;
    }

    totalPages = (Sizeof + itemsPerPage - 1) / itemsPerPage; // 전체 페이지 수 계산
    current = head;

    num = (currentPage - 1) * itemsPerPage + 1; // 현재 페이지 시작 번호 계산

    while (1) {
        system("cls");
        printf("=============== ID KEEPER ================\n\n");
        printf(" ★ 선택된 옵션 : 나열 (전체)\n\n");

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
            printf(" <플렛폼    : %s (%s)>\n ※ ID       : %s\n ※ Password : %s\n\n", temp->name, temp->category, temp->id, temp->password);
            num++;
            itemCount++;
            temp = temp->next;
        }

        printf("------------------------------------------\n");
        printf("[현재 페이지: %d / %d] \n", currentPage, totalPages);
        printf("[◀◀ 1 | 2 ▶▶] [초기화면 → 0]\n");
        printf("=========================▶ 옵션 선택 >>> ");


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


// 추가 기능 메뉴
void additionalFunctions(const char* filename) {
    Platform* head = NULL;
    loadFromFile(&head, filename);

    int choice;
    printf("=============== ID KEEPER ================\n\n");
    printf(" ★ 선택된 옵션 : 나열\n\n");
    printf(" 1. 카테고리별로 출력\n\n");
    printf(" 2. 전체 출력(사전순)\n\n");
    printf("=========================▶ 옵션 선택 >>> ");
    scanf("%d", &choice);

    if (choice == 1) {
        char category[50];
        system("cls");
        printf("=============== ID KEEPER ================\n\n");
        printf(" ★ 선택된 옵션 : 나열 (카테고리)\n\n");
        printf(" ▶ 카테고리 입력 >>> ");
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
        printf(" → 1-2번 옵션중에 입력 바랍니다.\n");
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
        system("cls"); // 화면을 깨끗하게
        printf("=============== ID KEEPER ================\n\n");
        printf(" 1. 아이디/비밀번호 추가\n\n"); //1
        printf(" 2. 아이디/비밀번호 검색\n\n");
        printf(" 3. 아이디/비밀번호 수정\n\n");
        printf(" 4. 아이디/비밀번호 삭제\n\n");
        printf(" 5. 아이디/비밀번호 나열\n\n");
        printf(" 6. 프로그램 종료\n\n");
        printf("=========================▶ 옵션 선택 >>> ");
        scanf("%d", &choice);
        getchar(); // 버퍼에 남은 엔터 키 제거


        //1번 선택 추가
        if (choice == 1) {
            system("cls");
            Add_Platform("platforms.txt");
            ClearBuffer(); //버퍼에 엔터 값이 남아 있어서 getchar 기능 정상화 시키기
            while (1) {
                printf("\n\n\n▶ ▶ 엔터 키 입력.\n");
                printf("\n\n=========================================");

                int input = getchar(); // 사용자로부터 한 문자 입력 받기
                if (input == '\n') { // 입력받은 문자가 '\n'이면, 즉 엔터 키이면
                    break; // while 루프를 빠져나와 다음 단계로 진행
                }
            }
        }
        //2번 선택 아이디/비번 검색 <<플렛폼 이름 검색하기
        else if (choice == 2) {
            system("cls");
            SearchPlatform("platforms.txt");
            ClearBuffer(); //버퍼에 엔터 값이 남아 있어서 getchar 기능 정상화 시키기
            while (1) {
                printf("\n\n\n▶ ▶ 엔터 키 입력.\n");
                printf("\n\n=========================================");

                int input = getchar(); // 사용자로부터 한 문자 입력 받기
                if (input == '\n') { // 입력받은 문자가 '\n'이면, 즉 엔터 키이면
                    break; // while 루프를 빠져나와 다음 단계로 진행
                }
            }
        }
        //3번 선택 아이디/비번 수정
        else if (choice == 3) {
            system("cls");
            Change_ID_Password("platforms.txt");
            ClearBuffer(); //버퍼에 엔터 값이 남아 있어서 getchar 기능 정상화 시키기
            while (1) {
                printf("\n\n\n▶ ▶ 엔터 키 입력.\n");
                printf("\n\n=========================================");

                int input = getchar(); // 사용자로부터 한 문자 입력 받기
                if (input == '\n') { // 입력받은 문자가 '\n'이면, 즉 엔터 키이면
                    break; // while 루프를 빠져나와 다음 단계로 진행
                }
            }
        }

        //4번 선택 플렛폼 검색 후 삭제
        else if (choice == 4) {
            system("cls");
            deletePlatformInFile("platforms.txt");
            ClearBuffer(); //버퍼에 엔터 값이 남아 있어서 getchar 기능 정상화 시키기
            while (1) {
                printf("\n\n\n▶ ▶ 엔터 키 입력.\n");
                printf("\n\n=========================================");

                int input = getchar(); // 사용자로부터 한 문자 입력 받기
                if (input == '\n') { // 입력받은 문자가 '\n'이면, 즉 엔터 키이면
                    break; // while 루프를 빠져나와 다음 단계로 진행
                }
            }
        }
        //5번 선택 후 1번 선택시 - 플렛폼 카테고리별 나열 // 2번 선택시 - 전체 사전 순 출력
        else if (choice == 5) {
            system("cls");
            additionalFunctions("platforms.txt");
            ClearBuffer(); //버퍼에 엔터 값이 남아 있어서 getchar 기능 정상화 시키기
            /*
            while (1) {
                printf("\n\n\n▶ ▶ 엔터 키 입력.\n");
                printf("\n\n=========================================");
                int input = getchar(); // 사용자로부터 한 문자 입력 받기
                if (input == '\n') { // 입력받은 문자가 '\n'이면, 즉 엔터 키이면
                    break; // while 루프를 빠져나와 다음 단계로 진행
                }
            }*/ //function5는 함수 안에서 따로 조절
        }

        //종료하기
        else if (choice == 6) {
            break;
        }
        //다른 거 입력하면
        else {
            printf("1-6번 옵션 입력하세요.\n");
            while (1) {
                printf("\n\n\n▶ ▶ 엔터 키 입력.\n");
                int input = getchar(); // 사용자로부터 한 문자 입력 받기
                if (input == '\n') { // 입력받은 문자가 '\n'이면, 즉 엔터 키이면
                    break; // while 루프를 빠져나와 다음 단계로 진행
                }
            }
        }
    }

    // 메모리 해제
    while (head != NULL) {
        Platform* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
