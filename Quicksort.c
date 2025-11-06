#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int particao(int *A, int tamanho_vetor){
    int pivo = A[tamanho_vetor-1];
    int i = -1;

    for(int j = 0; j < tamanho_vetor - 1; j++){
        if(A[j] <= pivo){
            i++;
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
    if (tamanho_vetor <= 1) return;

    int pos_pivo = particao(A, tamanho_vetor);
    quicksort(A, pos_pivo);
    quicksort(A + pos_pivo + 1, tamanho_vetor - pos_pivo - 1);
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

    FILE *f = fopen("tempos_quicksort.csv", "w");
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
                quicksort(A,n);
                clock_t fim = clock();

                soma_quick += (double)(fim - inicio) / CLOCKS_PER_SEC;
            }

            double media = soma_quick / repeticoes;
            char *tipo_do_vetor = (tipo == 0 ? "Aleatorio" : tipo == 1 ? "Crescente" : "Decrescente");

            fprintf(f, "%d,%s,Quicksort,%.7f\n", n, tipo_do_vetor, media);
        }

        free(A);
    }

    fclose(f);
    return 0;
}
