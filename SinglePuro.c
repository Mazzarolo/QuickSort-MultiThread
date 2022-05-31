#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define TAM 100000000
#define NUM_THREADS 2

void _qs(int *vet, int l, int r){
    int pivot = vet[(l+r)/2];
    int i = l;
    int j = r;
    if( i >= j) return; //so um elemento

    do{ //particao
        while(vet[i] < pivot && j >= i) i++;
        while(vet[j] > pivot && j >= i) j--;

        if(i <= j){
            int aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
            i++;
            j--;
        }
    }while(i < j);

    if(j > l) _qs(vet, l, j);
    if(i < r) _qs(vet, i, r);
}

void ordena(int *vet, int t) {
    _qs(vet, 0, t-1);
}

void mostra(int *vet, int tam){
    printf("[ ");
    for (int i=0; i<tam; i++){
        printf("%i", vet[i]);
        if(i != tam-1){
            printf(", ");
        }
    }
    printf(" ]");
    printf("\n");
}

int main()
{

    double exeTime;

    clock_t begin, end;

    int *vet = (int *)malloc(sizeof(int) * TAM);

    for(int i = 0; i < TAM; i++){
        vet[i] = rand()%100;
    }

    begin = clock();

    ordena(vet, TAM);

    end = clock();

    exeTime = (double)(end - begin) / CLOCKS_PER_SEC;

    // mostra(vet, TAM);

    printf("Tempo: %.3f segundos.\n", exeTime);
}