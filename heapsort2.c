#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void max_heapify(int *A, int m, int i){
    int e = 2*i + 1;
    int d = 2*i + 2;
    int maior;

    if(e <= m && A[e] > A[i])
        maior = e;
    else
        maior = i;

    if (d <= m && A[d] > A[maior])
        maior = d;

    if(maior != i){
        int temp = A[i];
        A[i] = A[maior];
        A[maior] = temp;
        max_heapify(A, m, maior);
    }
}

void build_max_heap(int *A, int n){
    for (int i = n/2 - 1; i >= 0; i--){
        max_heapify(A, n - 1, i);
    }
}

void heapsort2(int *A, int n){
    build_max_heap(A, n);
    int m = n - 1;

    for(int i = n - 1; i >= 1; i--){
        int temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        m = m - 1;
        max_heapify(A, m, 0);
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

    
    int repeticoes = 10;

    FILE *f = fopen("tempos_heapsort.csv", "w");
    fprintf(f, "tamanho,tipo,algoritmo,tempo_medio_s\n");

    for (int t = 5000; t <= 50000; t+=5000) {
        
        int *A = malloc(t * sizeof(int));

        for (int tipo = 0; tipo < 3; tipo++) {
            double soma_quick = 0;

            for(int r = 0; r < repeticoes; r++){
                if(tipo == 0) gerar_vetor_aleatorio(A,t);
                else if(tipo == 1) gerar_vetor_crescente(A,t);
                else gerar_vetor_decrescente(A,t);

                clock_t inicio = clock();
                heapsort2(A,t);
                clock_t fim = clock();

                soma_quick += (double)(fim - inicio) / CLOCKS_PER_SEC;
            }

            double media = soma_quick / repeticoes;
            char *tipo_do_vetor = (tipo == 0 ? "Aleatorio" : tipo == 1 ? "Crescente" : "Decrescente");
            printf("%d,%s,Heapsort,%.7f\n", t, tipo_do_vetor, media);
            fprintf(f, "%d,%s,Heapsort,%.7f\n", t, tipo_do_vetor, media);
        }

        free(A);
    }

    fclose(f);
    return 0;
}