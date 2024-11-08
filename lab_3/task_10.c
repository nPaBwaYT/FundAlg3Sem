#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum Errors {
    ERROR = -1,
    SUCCESS,
};

typedef struct Node {
    char exp[BUFSIZ];
    struct Node** children;
    int child_count;
} Node;


Node* createNode(const char* exp) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) return NULL;
    strncpy(node->exp, exp, BUFSIZ - 1);
    node->exp[BUFSIZ - 1] = '\0';
    node->children = NULL;
    node->child_count = 0;
    return node;
}


int addChild(Node* parent, Node* child) {
    if (!parent || !child) return -1;
    Node** new_children = (Node**)realloc(parent->children, sizeof(Node*) * (parent->child_count + 1));
    if (!new_children) return -1;
    parent->children = new_children;
    parent->children[parent->child_count++] = child;
    return 0;
}



int freeTree(Node* node) {
    if (!node) return ERROR;
    for (int i = 0; i < node->child_count; i++) {
        freeTree(node->children[i]);
    }
    free(node->children);
    free(node);
    return SUCCESS;
}

Node* parseExpression(const char* expression, int* pos) {
    char exp[BUFSIZ];
    int exp_len = 0;


    while (expression[*pos] != '(' && expression[*pos] != ',' && expression[*pos] != ')' && expression[*pos] != '\0') {
        exp[exp_len++] = expression[*pos];
        (*pos)++;
    }
    exp[exp_len] = '\0';

    Node* node = createNode(exp);
    if (!node) return NULL;


    if (expression[*pos] == '(') {
        (*pos)++;
        while (expression[*pos] != ')' && expression[*pos] != '\0') {
            Node* child = parseExpression(expression, pos);
            if (!child || addChild(node, child) != 0) {
                freeTree(node);
                return NULL;
            }
            if (expression[*pos] == ',') (*pos)++;
        }
        (*pos)++;
    }

    return node;
}


int printTree(FILE* output, Node* node, int level, int is_last) {
    if (!node || !output) return ERROR;

    for (int i = 0; i < level - 1; i++) {
        fprintf(output, "│   ");
    }
    if (level > 0) {
        fprintf(output, is_last ? "└── " : "├── ");
    }
    fprintf(output, "%s\n", node->exp);

    for (int i = 0; i < node->child_count; i++) {
        printTree(output, node->children[i], level + 1, i == node->child_count - 1);
    }
    return SUCCESS;
}



int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Использование: %s входной_файл выходной_файл\n", argv[0]);
        return EXIT_FAILURE;
    }


    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    if (!input || !output) {
        printf("Ошибка открытия файлов.\n");
        if (input) fclose(input);
        if (output) fclose(output);
        return ERROR;
    }


    char expression[BUFSIZ];
    while (fgets(expression, sizeof(expression), input) != NULL) {
        int pos = 0;
        Node* root = parseExpression(expression, &pos);
        if (!root) {
            fprintf(stderr, "Ошибка при построении дерева.\n");
            fclose(input);
            fclose(output);
            return ERROR;
        }

        if (printTree(output, root, 0, 1) != 0) {
            printf("Ошибка при выводе дерева.\n");
            fclose(input);
            fclose(output);
            freeTree(root);
            return ERROR;
        }
        fprintf(output, "\n");
        freeTree(root);
    }

    fclose(input);
    fclose(output);

    return SUCCESS;;
}
