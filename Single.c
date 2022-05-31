#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define TAM 100000000
#define NUM_THREADS 2

void *funct(void *arg)
{
}

typedef struct params
{
    int *vet;
    int esq;
    int dir;
} Params;

void genVet(int *vet, int tam)
{
    srand(time(NULL));
    for (int i = 0; i < tam; i++)
    {
        vet[i] = rand() % TAM;
    }
}

void _qs(Params *p)
{
    int *vet = p->vet;
    int l = p->esq;
    int r = p->dir;
    int pivot = vet[(l + r) / 2];
    int i = l;
    int j = r;
    if (i >= j)
        return; // so um elemento

    do
    { // particao
        while (vet[i] < pivot && j >= i)
            i++;
        while (vet[j] > pivot && j >= i)
            j--;

        if (i <= j)
        {
            int aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
            i++;
            j--;
        }
    } while (i < j);

    if (j > l)
    {
        p->dir = j;
        _qs(p);
    }
    if (i < r)
    {
        p->dir = r;
        p->esq = i;
        _qs(p);
    }
}

void ordena(int *vet, int tam)
{
    Params *p = (Params *)malloc(sizeof(Params));

    p->vet = vet;
    p->esq = 0;
    p->dir = tam - 1;

    _qs(p);
}

void mostra(int *vet, int tam)
{
    printf("[ ");
    for (int i = 0; i < tam; i++)
    {
        printf("%i", vet[i]);
        if (i != tam - 1)
        {
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

    genVet (vet, TAM);

    begin = clock();

    ordena(vet, TAM);

    end = clock();

    exeTime = (double)(end - begin) / CLOCKS_PER_SEC;

    // mostra(vet, TAM);

    printf("Tempo: %.3f segundos.\n", exeTime);
}