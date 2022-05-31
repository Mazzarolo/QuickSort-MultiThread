#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define TAM 100000000
#define NUM_THREADS 2

typedef struct params
{
     int *vet;
     int esq;
     int dir;
} Params;

void mostra(int *vet, int tam)
{
     for (int i = 0; i < tam; i++)
     {
          printf("%i / ", vet[i]);
     }
     printf("\n");
}

void genVet(int *vet, int tam)
{
     srand(time(NULL));
     for (int i = 0; i < tam; i++)
     {
          vet[i] = rand() % 100;
     }
}

int modulo(int n)
{
     if (n >= 0)
          return n;
     else
          return -n;
}

int findPivot(int *vet, int tam)
{
     int max = vet[0], min = vet[0], idx = 0;
     for (int i = 0; i < tam; i++)
     {
          if (vet[i] > max)
               max = vet[i];
          if (vet[i] < min)
               min = vet[i];
     }
     int med = (max + min) / 2;
     int aprox = modulo(med - vet[0]);
     for (int i = 0; i < tam; i++)
     {
          if (modulo(med - vet[i]) < aprox)
          {
               idx = i;
               aprox = modulo(med - vet[i]);
          }
     }
     return idx;
}

void *quick_sort(void *params)
{
     Params *p = (Params *)params;
     int *vet = p->vet;
     int esq = p->esq;
     int dir = p->dir;
     int pivot = vet[(esq + dir) / 2];
     int i = esq;
     int j = dir;
     if (esq >= dir)
          return NULL;

     do
     {
          while (vet[i] < pivot && i <= j)
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

     if (j > esq)
     {
          p->dir = j;
          quick_sort((void *)p);
     }

     if (i < dir)
     {
          p->esq = i;
          p->dir = dir;
          quick_sort((void *)p);
     }
}

void *quick_sort_par(void *params)
{
     Params *p = (Params *)params;
     int *vet = p->vet;
     int esq = p->esq;
     int dir = p->dir;
     int pivot = vet[findPivot(vet, dir)];
     int i = esq;
     int j = dir;
     if (esq >= dir)
          return NULL;

     pthread_t threads[NUM_THREADS]; // vetor de threads

     do
     {
          while (vet[i] < pivot && i <= j)
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

     if (j > esq)
     {
          p->dir = j;
          pthread_create(&(threads[0]), NULL, quick_sort, (void *)p);
     }

     if (i < dir)
     {
          p->esq = i;
          p->dir = dir;
          pthread_create(&(threads[1]), NULL, quick_sort, (void *)p);
          quick_sort((void *)p);
     }

     pthread_join(threads[0], NULL);
     pthread_join(threads[1], NULL);
}

void ordena(int *vet, int tam)
{
     Params *p = (Params *)malloc(sizeof(Params));

     p->vet = vet;
     p->esq = 0;
     p->dir = tam - 1;

     quick_sort((void *)p);

     free(p);
}

int main()
{
     double exeTime;

     clock_t begin, end;

     int *vet = (int *)malloc(sizeof(int) * TAM);

     genVet(vet, TAM);

     begin = clock();

     ordena(vet, TAM);

     end = clock();

     exeTime = (double)(end - begin) / CLOCKS_PER_SEC;

     // mostra(vet, TAM);

     printf("Tempo: %.3f segundos.\n", exeTime);
}
