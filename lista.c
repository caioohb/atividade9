#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

No* no(float valor, No* proximo_no) {
    No* novo_no = malloc(sizeof(No));
    novo_no->valor = valor;
    novo_no->proximo_no = proximo_no;
    return novo_no;
}


void lista_inserir_no(No* L, No* no){
    if(L != NULL){
        if(L->proximo_no == NULL){
            L->proximo_no = no;
        }
        else{
            lista_inserir_no(L->proximo_no, no);
        }
    }
}

void lista_inserir_no_ordenado(No* L, No* no) {
    if (L == NULL) {
        return;
    }

    if (no->valor < L->valor) {
        no->proximo_no = L;
        return;
    }

    No* anterior = L;
    No* atual = L->proximo_no;

    while (atual != NULL) {
        if (no->valor < atual->valor) {
            anterior->proximo_no = no;
            no->proximo_no = atual;
            return;
        }

        anterior = atual;
        atual = atual->proximo_no;
    }

    anterior->proximo_no = no;
}

void lista_imprimir(No* L){
    if(L != NULL){
        printf("%c ", L->valor);
        lista_imprimir(L->proximo_no);
    }
}

int lista_quantidade_nos(No* L){
    if(L != NULL){
        return 1 + lista_quantidade_nos(L->proximo_no);
    }
    return 0;
}

No* lista_copiar(No* L) {
    if (L == NULL) {
        return NULL; 
    }

    No* copia = no(L->valor, NULL); 
    No* atual = copia;
    L = L->proximo_no; 

    while (L != NULL) {
        atual->proximo_no = no(L->valor, NULL); 
        L = L->proximo_no; 
        atual = atual->proximo_no; 
    }

    return copia;
}


void lista_concatenar(No* L, No* Lc){
    lista_inserir_no(L, Lc);
}

void lista_liberar(No* L){
    if(L != NULL){
        lista_liberar(L->proximo_no);
        free(L);
    }
}

int lista_verificar_existencia(No* L, char valor_busca) {
    if (L == NULL) {
        return 0; 
    }

    if (L->valor == valor_busca) {
        return 1; 
    }

    return lista_verificar_existencia(L->proximo_no, valor_busca);
}

int lista_verificar_ocorrencias(No* L, char valor_busca) {
    if (L == NULL) {
        return 0; 
    }

    int ocorrencias = 0;
    if (L->valor == valor_busca) {
        ocorrencias = 1; 
    }

    return ocorrencias + lista_verificar_ocorrencias(L->proximo_no, valor_busca);
}

void lista_imprimir_inversa(No* L) {
    if (L == NULL) {
        return;
    }

    lista_imprimir_inversa(L->proximo_no);
    printf("%c ", L->valor);
}

void lista_inserir_no_i(No* L, int i) {
    if (i < 0) {
        return; 
    }

    if (i == 0) {
        No* novo_no = no('N', L->proximo_no);
        L->proximo_no = novo_no;
    } else {
        lista_inserir_no_i(L->proximo_no, i - 1);
    }
}

void lista_remover_no_i(No* L, int i) {
    if (L == NULL || L->proximo_no == NULL) {
        return;
    }

    if (i == 0) {
        No* no_a_remover = L->proximo_no;
        L->proximo_no = no_a_remover->proximo_no;
        free(no_a_remover);
    } else {
        lista_remover_no_i(L->proximo_no, i - 1);
    }
}

void lista_remover_no(No* L, char valor_busca) {
    if (L == NULL) {
        return;
    }

    if (L->proximo_no != NULL && L->proximo_no->valor == valor_busca) {
        No* no_a_remover = L->proximo_no;
        L->proximo_no = no_a_remover->proximo_no;
        free(no_a_remover);
        lista_remover_no(L, valor_busca);
    } else {
        lista_remover_no(L->proximo_no, valor_busca);
    }
}