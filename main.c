#include <stdio.h>
#include <stdbool.h>

// Estrutura item para quicksort
typedef struct {
    int chave; // campo chave para ordenação
} item;

// Declarações das funções de ordenação
void bolha(int* v, int n); // Bubble sort
void selecao(int* v, int n); // Selection sort
void insercao(int* v, int n); // Insertion sort
void merge(int vetor[], int inicio, int meio, int fim); // Função auxiliar do Merge sort
void mergeSort(int v[], int esq, int dir); // Merge sort
void particao(int esq, int dir, int* i, int* j, item* a); // Função auxiliar do Quick sort
void ordena(int esq, int dir, item *a); // Função auxiliar do Quick sort
void quickSort(item *a, int n); // Quick sort
void heapSort(int n, int* V); // Heap sort
void formarFilaPrioridades(int n, int* V); // Função auxiliar do Heap sort
void OrdenarFilaPrioridades(int n, int* V); // Função auxiliar do Heap sort

int main() {
    int vetor[] = {42, 35, 12, 77, 5, 101}; // Declaração do vetor de inteiros
    int n = sizeof(vetor) / sizeof(vetor[0]); // Calculando o número de elementos do vetor
    int opcao; // Variável que armazena a opção escolhida
    // Menu de seleção
    printf("1- Bubble sort\n");
    printf("2- Selection sort\n");
    printf("3- Insertion sort\n");
    printf("4- Merge sort\n");
    printf("5- Quick sort\n");
    printf("6- Heap sort\n");
    printf("Selecione uma das opções: ");
    scanf("%d", &opcao); // Lendo a opção do usuário
    
    printf("Vetor original: "); // Exibição do vetor original
    for(int i = 0; i < n; i++) {
        printf("%d ", vetor[i]); // Exibindo cada elemento do vetor
    }
    printf("\n");

    switch(opcao) { // Chamando a função que contem o algoritmo escolhido
        case 1:
            bolha(vetor, n); // Bubble Sort
            break;
        case 2:
            selecao(vetor, n); // Selection Sort
            break;
        case 3:
            insercao(vetor, n); // Insertion Sort
            break;
        case 4:
            mergeSort(vetor, 0, n - 1); // Merge Sort
            break;
        case 5: { // Quick Sort
            item itens[n]; // Array de itens para armazenar as chaves
            for (int i = 0; i < n; i++) {
                itens[i].chave = vetor[i]; // Transferindo valores para o array de itens
            }
            quickSort(itens, n); // Chamada do Quick Sort
            for (int i = 0; i < n; i++) {
                vetor[i] = itens[i].chave; // Transferindo valores ordenados de volta ao vetor
            }
            break;
        }
        case 6:
            heapSort(n, vetor); // Heap Sort
            break;
        default:
            printf("Opção inválida!\n");
            return 1; // Saída do programa com erro se a opção for inválida
    }

    printf("Vetor organizado: "); // Exibindo o vetor ordenado
    for(int i = 0; i < n; i++) {
        printf("%d ", vetor[i]); // Exibindo cada elemento do vetor ordenado
    }
    printf("\n");

    return 0;
}

// Funções de ordenação

// Bubble Sort
void bolha(int* v, int n) {
    int i, j, aux; // Declaração dos índices e auxiliar
    for(i = 0; i < n - 1; i++) { // Laço para percorrer os elementos do vetor
        for(j = 1; j < n - i; j++) {
            if(v[j] < v[j-1]) { // Verifica se o elemento é menor que o anterior
                aux = v[j]; // Troca de posição entre os elementos
                v[j] = v[j-1];
                v[j-1] = aux;
            }
        }
    }
}

// Selection Sort
void selecao(int* v, int n) {
    int i, j, min, aux; // Declaração das variáveis
    for(i = 0; i < n; i++) { // Laço para percorrer os elementos
        min = i; // Inicializa o menor índice
        for(j = i + 1; j < n; j++) {
            if(v[j] < v[min]) { // Verifica se há um valor menor
                min = j; // Atualiza o menor índice
            }
        }
        aux = v[min]; // Troca os elementos
        v[min] = v[i];
        v[i] = aux;
    }
}

// Insertion Sort
void insercao(int* v, int n) {
    int i, j, aux;
    for(i = 1; i < n; i++) { // Laço para percorrer os elementos
        aux = v[i]; // Armazena o valor atual
        j = i - 1;
        while((j >= 0) && (aux < v[j])) { // Move os elementos maiores
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = aux; // Insere o valor atual na posição correta
    }
}

// Merge Sort
void merge(int vetor[], int inicio, int meio, int fim) { // Função que realiza a mesclagem
    int tamanho = fim - inicio + 1; // Calcula o tamanho da seção a ser mesclada
    int temp[tamanho]; // Vetor temporário para armazenar os elementos mesclados
    int i = inicio, j = meio + 1, k = 0; // Índices para a mesclagem

    while (i <= meio && j <= fim) { // Mescla até que uma das metades acabe
        if (vetor[i] <= vetor[j]) {
            temp[k++] = vetor[i++]; // Copia o menor elemento para o temporário
        } else {
            temp[k++] = vetor[j++];
        }
    }

    while (i <= meio) {
        temp[k++] = vetor[i++]; // Copia os elementos restantes da primeira metade
    }

    while (j <= fim) {
        temp[k++] = vetor[j++]; // Copia os elementos restantes da segunda metade
    }

    for (k = 0, i = inicio; i <= fim; i++, k++) {
        vetor[i] = temp[k]; // Copia os elementos do temporário para o vetor original
    }
}

void mergeSort(int v[], int esq, int dir) {
    if (dir > esq) {
        int meio = (esq + dir) / 2; // Calcula o meio
        mergeSort(v, esq, meio); // Ordena a primeira metade
        mergeSort(v, meio + 1, dir); // Ordena a segunda metade
        merge(v, esq, meio, dir); // Mescla as duas metades
    }
}

// Quick Sort
void particao(int esq, int dir, int* i, int* j, item* a) {
    item x, aux; // Declaração das variáveis
    *i = esq, *j = dir;
    x = a[(*i + *j) / 2]; // Pivô

    do {
        while(x.chave > a[*i].chave) (*i)++; // Encontra posição correta
        while(x.chave < a[*j].chave) (*j)--;
        if(*i <= *j) {
            aux = a[*i], a[*i] = a[*j], a[*j] = aux; // Troca os elementos
            (*i)++, (*j)--;
        }
    } while(*i <= *j);
}

void ordena(int esq, int dir, item *a) {
    int i, j;
    particao(esq, dir, &i, &j, a); // Chama a função de partição
    if(esq < j) ordena(esq, j, a); // Ordena a primeira parte
    if(i < dir) ordena(i, dir, a); // Ordena a segunda parte
}

void quickSort(item *a, int n) {
    ordena(0, n - 1, a); // Inicia o Quick Sort
}

// Heap Sort
void formarFilaPrioridades(int n, int* v) {
    int i, j, temp;
    for(i = n - 2; i >= 0; i--) { // Loop para ajustar a árvore
        j = i;
        while(j < n-1 && v[j] < v[n - (n - j) / 2]) {
            temp = v[j]; // Troca elementos para ajustar a árvore
            v[j] = v[n - (n - j) / 2];
            v[n - (n - j) / 2] = temp;
            j = n - (n - j) / 2;
        }
    }
}

void OrdenarFilaPrioridades(int n, int* v) {
    int i, temp;
    for(i = n - 1; i > 0; i--) { // Loop para ordenar os elementos
        temp = v[0];
        v[0] = v[i];
        v[i] = temp;
        formarFilaPrioridades(i, v); // Ajusta a árvore
    }
}

void heapSort(int n, int* v) {
    formarFilaPrioridades(n, v); // Chama para ajustar o heap
    OrdenarFilaPrioridades(n, v); // Ordena o heap
}
