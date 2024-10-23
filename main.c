//Selection, Bubble, Insertion
#include <stdio.h>

void bolha(int* v, int N); //bubble sort

int main(){
    
    int vetor[] = {42, 35, 12, 77, 5, 101};
    int N = sizeof(vetor) / sizeof(vetor[0]);

    printf("Vetor original: ");
    for(int i = 0; i < N; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n"); 

    bolha(vetor, N);

    printf("Vetor organizado: ");
    for(int i = 0; i < N; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
    
    return 0;
}

//ALGORITMO DE ORDENAÇÃO BUBBLE SORT
void bolha(int* v, int N){
    int i, j;
    int aux;
    for(i = 0; i < N - 1; i++){
        for(j = 1; j < N - i; j++){
            if(v[j] < v[j-1]){
                aux = v[j];
                v[j] = v[j-1];
                v[j-1] = aux;
            }
        }
    }
}