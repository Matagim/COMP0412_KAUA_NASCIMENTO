#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

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
    mergesort2(A+meio, tamanho_vetor-meio);
    intercala(A,meio,tamanho_vetor);  
}




void gerar_vetor_aleatorio(int *A, int n) {
    for (int i = 0; i < n; i++)
        A[i] = rand() % n;
}

void gerar_vetor_crescente(int *A, int n) {
    for (int i = 0; i < n; i++)
        A[i] = i;
}

void gerar_vetor_decrescente(int *A, int n) {
    for (int i = 0; i < n; i++)
        A[i] = n - i - 1;
}

int main(){
    srand(time(NULL));

    int tamanhos[] = {1000, 5000, 10000, 50000}; 
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
    int repeticoes = 10;

    FILE *f = fopen("tempos_mergesort.csv", "w");
    fprintf(f, "tamanho,tipo,algoritmo,tempo_medio_s\n");

    for (int t = 0; t < num_tamanhos; t++) {
        int n = tamanhos[t];
        int *A = malloc(n * sizeof(int));

        for (int tipo = 0; tipo < 3; tipo++) {
            double soma_quick = 0;

            for(int r = 0; r < repeticoes; r++){
                if(tipo == 0) gerar_vetor_aleatorio(A,n);
                else if(tipo == 1) gerar_vetor_crescente(A,n);
                else gerar_vetor_decrescente(A,n);

                clock_t inicio = clock();
                mergesort2(A,n);
                clock_t fim = clock();

                soma_quick += (double)(fim - inicio) / CLOCKS_PER_SEC;
            }

            double media = soma_quick / repeticoes;
            char *tipo_do_vetor = (tipo == 0 ? "Aleatorio" : tipo == 1 ? "Crescente" : "Decrescente");

            fprintf(f, "%d,%s,Mergesort,%.7f\n", n, tipo_do_vetor, media);
        }

        free(A);
    }

    fclose(f);
    return 0;
}