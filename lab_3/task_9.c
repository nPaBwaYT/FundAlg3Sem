#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* word;
    int count;
    struct Node* left;
    struct Node* right;
} Node;


Node* createNode(const char* word) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->word = strdup(word);
    node->count = 1;
    node->left = node->right = NULL;
    return node;
}


Node* insert(Node* root, const char* word) {
    if (root == NULL) return createNode(word);
    
    int cmp = strcmp(word, root->word);
    if (cmp == 0) {
        root->count++;
    } else if (cmp < 0) {
        root->left = insert(root->left, word);
    } else {
        root->right = insert(root->right, word);
    }
    return root;
}


Node* find(Node* root, const char* word) {
    if (root == NULL) return NULL;
    int cmp = strcmp(word, root->word);
    if (cmp == 0) return root;
    return cmp < 0 ? find(root->left, word) : find(root->right, word);
}

void processFile(Node** root, const char* filename, const char* delimiters) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
    
    char word[BUFSIZ];
    while (fscanf(file, "%255s", word) == 1) {
        char* token = strtok(word, delimiters);
        while (token != NULL) {
            *root = insert(*root, token);
            token = strtok(NULL, delimiters);
        }
    }
    fclose(file);
}



void collectNodes(Node* root, Node* array[], int* index) {
    if (root == NULL) return;
    
    collectNodes(root->left, array, index);
    array[(*index)++] = root;
    collectNodes(root->right, array, index);
}


int compareNodes(const void* a, const void* b) {
    Node* nodeA = *(Node**)a;
    Node* nodeB = *(Node**)b;
    return nodeB->count - nodeA->count; 
}

void printMostFrequent(Node* root, int n) {

    int nodeCount = 0;
    Node* tempArray[BUFSIZ];

    collectNodes(root, tempArray, &nodeCount);


    qsort(tempArray, nodeCount, sizeof(Node*), compareNodes);


    for (int i = 0; i < n && i < nodeCount; i++) {
        printf("%s: %d раз\n", tempArray[i]->word, tempArray[i]->count);
    }
}

int findLongestShortest(Node* root, Node** longest, Node** shortest) {
    if (root == NULL) return -1;
    if (!*longest || strlen(root->word) > strlen((*longest)->word)) *longest = root;
    if (!*shortest || strlen(root->word) < strlen((*shortest)->word)) *shortest = root;
    findLongestShortest(root->left, longest, shortest);
    findLongestShortest(root->right, longest, shortest);
    return 0;
}

int findDepth(Node* root) {
    if (root == NULL) return 0;
    int leftDepth = findDepth(root->left);
    int rightDepth = findDepth(root->right);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

void saveTree(Node* root, FILE* file) {
    if (root == NULL) {
        fprintf(file, "() ");
        return;
    }
    fprintf(file, "(%s %d ", root->word, root->count);
    saveTree(root->left, file);
    saveTree(root->right, file);
    fprintf(file, ") ");
}

Node* loadTree(FILE* file) {
    char word[BUFSIZ];
    int count;
    if (fscanf(file, " ( %255s %d ", word, &count) != 2) return NULL;
    if (strcmp(word, "()") == 0) return NULL;

    Node* root = createNode(word);
    root->count = count;
    root->left = loadTree(file);
    root->right = loadTree(file);
    fscanf(file, " ) ");
    return root;
}

void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }
    

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Использование: %s <файл> <сепараторы>\n", argv[0]);
        return 1;
    }

    Node* root = NULL;
    processFile(&root, argv[1], argv[2]);

    int choice;
    char word[BUFSIZ];
    int n;
    Node *minNode = NULL, *maxNode = NULL;

    while (1) {
        printf("\nВыберите опцию:\n");
        printf("1. Узнать, сколько раз слово встречалось в файле\n");
        printf("2. Вывести n наиболее часто встречающихся слов\n");
        printf("3. Найти самое длинное и самое короткое слово\n");
        printf("4. Найти глубину дерева\n");
        printf("5. Сохранить дерево\n");
        printf("6. Загрузить дерево\n");
        printf("7. Выйти\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите слово: ");
                scanf("%s", word);
                Node *found = find(root, word);
                if (found) {
                    printf("Слово \"%s\" встречается %d раз(а).\n", word, found->count);
                } else {
                    printf("Слово \"%s\" не найдено.\n", word);
                }
                break;
            case 2:
                printf("Введите значение n: ");
                scanf("%d", &n);
                printMostFrequent(root, n);
                break;
            case 3:
                if (findLongestShortest(root, &maxNode, &minNode) == 0 && minNode && maxNode) {
                    printf("Самое короткое слово: %s\n", minNode->word);
                    printf("Самое длинное слово: %s\n", maxNode->word);
                }
                break;
            case 4:
                printf("Глубина дерева: %d\n", findDepth(root));
                break;
            case 5:
                FILE* file = fopen("tree.txt", "w");
                saveTree(root, file);
                fclose(file);
                break;
            case 6:
                FILE* fileRead = fopen("tree.txt", "r");
                root = loadTree(fileRead);
                fclose(fileRead);
                break;
            case 7:
                printf("Выход из программы.\n");
                freeTree(root);
                return 0;
            default:
                printf("Некорректный выбор.\n");
        }
    }
    return 0;
}
