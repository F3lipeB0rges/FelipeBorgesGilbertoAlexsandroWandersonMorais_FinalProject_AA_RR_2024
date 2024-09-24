#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TREE_HT 100

struct MinHeapNode {
    char data; 
    unsigned freq;
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->data = data;
    temp->freq = freq;
    temp->left = temp->right = NULL;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}


void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

int isLeaf(struct MinHeapNode* root) {
    return !(root->left) && !(root->right);
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;

    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap); 
}

void calculateFrequencies(char* str, char* data, int* freq, int* size) {
    int ascii[256] = {0};
    int str_len = strlen(str);
    for (int i = 0; i < str_len; i++) {
        ascii[(int)str[i]]++;
    }

    *size = 0;
    for (int i = 0; i < 256; i++) {
        if (ascii[i] > 0) {
            data[*size] = (char)i;
            freq[*size] = ascii[i];
            (*size)++;
        }
    }
}

struct MinHeapNode* HuffmanCodesFromHTML(char* filename, char data[], int freq[], int* size) {
    // Abrir arquivo HTML
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = (char*)malloc(fsize + 1);
    fread(content, 1, fsize, file);
    content[fsize] = '\0';
    fclose(file);

    printf("Conteúdo do arquivo HTML:\n%s\n", content);

    calculateFrequencies(content, data, freq, size);

    struct MinHeapNode* root = buildHuffmanTree(data, freq, *size);

    free(content);
    return root;
}

void generateDot(struct MinHeapNode* root, FILE* file) {
    if (root == NULL)
        return;

    if (isLeaf(root)) {
        fprintf(file, "    \"%c\" [label=\"%c\\n%d\"];\n", root->data, root->data, root->freq);
    } else {
        fprintf(file, "    \"%d\" [label=\"%d\"];\n", root->freq, root->freq);
    }

    if (root->left) {
        if (isLeaf(root->left)) {
            fprintf(file, "    \"%d\" -> \"%c\" [label=\"0\"];\n", root->freq, root->left->data);
        } else {
            fprintf(file, "    \"%d\" -> \"%d\" [label=\"0\"];\n", root->freq, root->left->freq);
        }
        generateDot(root->left, file);
    }

    if (root->right) {
        if (isLeaf(root->right)) {
            fprintf(file, "    \"%d\" -> \"%c\" [label=\"1\"];\n", root->freq, root->right->data);
        } else {
            fprintf(file, "    \"%d\" -> \"%d\" [label=\"1\"];\n", root->freq, root->right->freq);
        }
        generateDot(root->right, file);
    }
}

void writeDotFile(struct MinHeapNode* root) {
    FILE* file = fopen("huffman_time.dot", "w");
    if (!file) {
        printf("Erro ao criar arquivo DOT.\n");
        return;
    }

    fprintf(file, "digraph HuffmanTree {\n");
    generateDot(root, file);
    fprintf(file, "}\n");

    fclose(file);
    printf("Arquivo DOT gerado com sucesso!\n");
}

int main() {
    char data[256];
    int freq[256];
    int size;

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    struct MinHeapNode* root = HuffmanCodesFromHTML("CS Summations.html", data, freq, &size);
    end = clock();

    if (root != NULL) {
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Tempo para construir o heap e a árvore de Huffman: %f segundos\n", cpu_time_used);

        writeDotFile(root);
    }

    return 0;
}
