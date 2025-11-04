#include <stdio.h>
#include <stdlib.h>



void insercao(int *A, int tamanho_vetor){

    int chave;
    int i;
    for(int j = 1; j < tamanho_vetor; j++){
        chave = A[j];
        i = j-1;
        while(i >= 0 && A[i] >= chave){
            A[i+1] = A[i];
            i = i - 1;
        }
    }
    A[i+1] = chave;

}

int main(){
    int A[] = {0,1,2,3,5,7,3};
    insercao(A, 7);
    printf("[");
    for(int i = 0; i < 7; i++){
        printf("%d,", A[i]);
        if(i == 6){printf("]\n");}
    }
    return 0;
    
}