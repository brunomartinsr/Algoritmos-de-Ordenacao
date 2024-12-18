#include <stdio.h>
#include <stdbool.h>
#include <time.h> 

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

// Função para gerar um array de inteiros aleatórios
void gerarArrayAleatorio(int* v, int n) {
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 100000; // Números entre 0 e 99.999
    }
}

// Função para medir o tempo de execução de cada algoritmo
void executarTestesDePerformance() {
    int tamanhos[] = {100, 1000, 10000, 50000, 100000}; // Tamanhos dos arrays
    int numTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("Resultado dos Testes de Performance:\n");

    // Cabeçalho para o gráfico comparativo
    printf("| Tamanho do Array | Bubble Sort | Selection Sort | Insertion Sort | Merge Sort | Quick Sort | Heap Sort |\n");
    printf("|------------------|-------------|----------------|----------------|------------|------------|-----------|\n");

    for (int t = 0; t < numTamanhos; t++) {
        int n = tamanhos[t];
        int* vetor = (int*) malloc(n * sizeof(int)); // Alocar memória para o array

        printf("| %15d |", n);

        // Testar cada algoritmo e medir o tempo
        for (int algoritmo = 1; algoritmo <= 6; algoritmo++) {
            gerarArrayAleatorio(vetor, n); // Gerar novo conjunto de dados para cada teste
            clock_t inicio, fim;
            double tempoExecucao;

            // Medir o tempo de execução de acordo com o algoritmo selecionado
            inicio = clock();
            switch(algoritmo) {
                case 1: bolha(vetor, n); break;
                case 2: selecao(vetor, n); break;
                case 3: insercao(vetor, n); break;
                case 4: mergeSort(vetor, 0, n - 1); break;
                case 5: {
                    item itens[n];
                    for (int i = 0; i < n; i++) itens[i].chave = vetor[i];
                    quickSort(itens, n);
                    for (int i = 0; i < n; i++) vetor[i] = itens[i].chave;
                    break;
                }
                case 6: heapSort(n, vetor); break;
            }
            fim = clock();

            tempoExecucao = ((double) (fim - inicio)) / CLOCKS_PER_SEC;

            // Exibir o tempo de execução para o algoritmo
            printf(" %.6f |", tempoExecucao);
        }

        free(vetor); // Liberar memória alocada
        printf("\n");
    }
}

// Função para rodar a análise comparativa
void analiseComparativa() {
    printf("\nAnálise Comparativa:\n");

    printf("1. O algoritmo Bubble Sort cresce rapidamente e tem um desempenho significativamente mais lento à medida que o tamanho do array aumenta.\n");
    printf("2. O Selection Sort tem um desempenho semelhante ao Bubble Sort, mas realiza um número ligeiramente menor de trocas, o que o torna um pouco mais eficiente.\n");
    printf("3. O Insertion Sort é eficiente para conjuntos de dados pequenos, mas se torna ineficaz para arrays grandes, pois o tempo de execução aumenta rapidamente.\n");
    printf("4. O Merge Sort e o Quick Sort apresentam desempenhos muito melhores para grandes volumes de dados, pois são mais eficientes em comparação com os algoritmos anteriores.\n");
    printf("5. O Heap Sort tem um comportamento semelhante ao Merge Sort e Quick Sort, sendo eficiente para grandes listas, mas com diferenças na implementação e no desempenho em listas já ordenadas.\n");


    printf("\nConclusão da Análise Comparativa:\n");
    printf("- Para arrays pequenos, Insertion Sort ou Selection Sort podem ser viáveis, pois têm uma sobrecarga menor para arrays pequenos.\n");
    printf("- Para arrays grandes, Merge Sort, Quick Sort e Heap Sort são significativamente mais eficientes.\n");
}

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

    // Adicionando as etapas 3 e 4
    executarTestesDePerformance(); // Executa os testes de performance
    analiseComparativa(); // Realiza a análise comparativa

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
