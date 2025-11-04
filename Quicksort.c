#include <stdlib.h>
#include <stdio.h>


int particao(int *A, int tamanho_vetor){
    int pivo = A[tamanho_vetor-1];

    int i = -1;
    for(int j = 0; j < (tamanho_vetor - 1); j++){
        if(A[j] <= pivo){
            i = i+1;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    int temp = A[i+1];
    A[i+1] = A[tamanho_vetor-1];
    A[tamanho_vetor-1] = temp;
    return i+1;
    
}


void quicksort(int *A, int tamanho_vetor){
    
    if (tamanho_vetor <= 1)
        return;

    int pos_pivo = tamanho_vetor / 2;

    pos_pivo = particao(A, tamanho_vetor);
    quicksort(A, pos_pivo);
    quicksort(A+pos_pivo+1, tamanho_vetor-pos_pivo);
}



int main(){
    int A[] = {0,1,2,3,5,7,3};
    quicksort(A, 7);
    printf("[");
    for(int i = 0; i < 7; i++){
        printf("%d,", A[i]);
        if(i == 6){printf("]\n");}
    }
    return 0;
}