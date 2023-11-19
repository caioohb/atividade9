#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <time.h>

#ifdef __linux__
#include <sys/time.h>
#else
#include <windows.h>
#endif

void get_time(struct timespec *ts) {
#ifdef __linux__
    clock_gettime(CLOCK_MONOTONIC, ts);
#else
    LARGE_INTEGER frequency, ticks;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&ticks);
    ts->tv_sec = ticks.QuadPart / frequency.QuadPart;
    ts->tv_nsec = ((ticks.QuadPart % frequency.QuadPart) * 1e9) / frequency.QuadPart;
#endif
}

double elapsed_time(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;
}

int main(int argc, char *argv[]) {
    No *lista_nao_ordenada = NULL;
    No *lista_ordenada = NULL;

    FILE *arquivo = fopen("1kk_rand_float.csv", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char linha[50];
    float numero;

    struct timespec inicio, fim;
    double tempo_nao_ordenado, tempo_ordenado;
    int cont = 0;

    get_time(&inicio);

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        numero = strtof(linha, NULL);

        No *novo_no = no(numero, NULL);

        lista_inserir_no(lista_nao_ordenada, novo_no);
        lista_inserir_no_ordenado(lista_ordenada, novo_no);

        cont++;
    }

    get_time(&fim);

    tempo_nao_ordenado = elapsed_time(inicio, fim);

    rewind(arquivo);
    cont = 0;

    get_time(&inicio);

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        numero = strtof(linha, NULL);

        No *novo_no = no(numero, NULL);

        lista_inserir_no_ordenado(lista_ordenada, novo_no);

        cont++;
    }

    get_time(&fim);

    tempo_ordenado = elapsed_time(inicio, fim);

    printf("Tempo medio de insercao (nao ordenada): %.6f segundos\n", tempo_nao_ordenado / cont);
    printf("Tempo medio de insercao (ordenada): %.6f segundos\n", tempo_ordenado / cont);

    fclose(arquivo);

    lista_liberar(lista_nao_ordenada);
    lista_liberar(lista_ordenada);

    return 0;
}
