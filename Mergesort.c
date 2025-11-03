#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>

void intercala(int *A, int meio, int tamanho_vetor) {
    int tamanho1 = meio;
    int tamanho2 = tamanho_vetor - meio;

    int *L = malloc((tamanho1 + 1) * sizeof(int));
    for (int i = 0; i < tamanho1; i++)
        L[i] = A[i];

    L[tamanho1] = INT_MAX;

    int *R = malloc((tamanho2 + 1) * sizeof(int));
    for (int j = 0; j < tamanho2; j++)
        R[j] = A[meio + j];

    R[tamanho2] = INT_MAX;

    int i = 0, j = 0;
    for (int k = 0; k < tamanho_vetor; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }

    free(L);
    free(R);
}


void mergesort2(int *A, int tamanho_vetor){
    if (tamanho_vetor <= 1)
        return;

    int meio = tamanho_vetor / 2;

    mergesort2(A, meio);
    mergesort2(A, tamanho_vetor-meio);
    intercala(A,meio,tamanho_vetor);  
}




int main(){
    int A[] = {0,1,2,5,4,7,8};

    mergesort2(A, 7);
    printf("[");
    for(int i = 0; i < 7; i++){
        printf("%d,", A[i]);
        if(i == 6){printf("]\n");}
    }

    return 0;
}