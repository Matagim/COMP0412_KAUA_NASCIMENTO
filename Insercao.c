#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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
        A[i+1] = chave;
    }
    

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

    FILE *f = fopen("tempos_insercao.csv", "w");
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
                insercao(A,n);
                clock_t fim = clock();

                soma_quick += (double)(fim - inicio) / CLOCKS_PER_SEC;
            }

            double media = soma_quick / repeticoes;
            char *tipo_do_vetor = (tipo == 0 ? "Aleatorio" : tipo == 1 ? "Crescente" : "Decrescente");

            fprintf(f, "%d,%s,insercao,%.7f\n", n, tipo_do_vetor, media);
        }

        free(A);
    }

    fclose(f);
    return 0;
}