#include <stdlib.h>
#include <stdio.h>


void max_heapify(int *A, int m, int i){
    int e = 2*i +1;
    int d = 2*i + 2;
    int maior;
    if(e <= m && A[e] > A[i]){maior = e;}
    else{maior = i;}

    if (d <= m && A[d] > A[maior]){maior = d;}

    if(maior != i){
        int temp = A[i];
        A[i] = A[maior];
        A[maior] = temp;
        max_heapify(A, m, maior);
    }

}

void build_max_heap(int *A, int n){
    for (int i = n/2; i >= 0; i--){
        max_heapify(A,n, i);
    }
}


void heapsort2(int *A, int n){

    build_max_heap(A,n);
    int m = n-1;
    int temp;
    

    for(int i = n-1; i >= 1; i--){
        temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        m = m-1;
        max_heapify(A, m, 0);
    }
}

int main(){
    int A[] = {1,2,3,4,5,6,8};
    heapsort2(A,7);
    printf("[");
    for(int i = 0; i < 7; i++){
        printf("%d,", A[i]);
    }

}