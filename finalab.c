#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    int id;
    char * nome;
    int quantidade;
    char * desc;
    float preco;

    struct no *dir;
    struct no *esq;
} no;

no* criar_no(int id, char *nome, int quantidade, char *desc, float preco) {
    no *novo = (no*)malloc(sizeof(no));
    if (novo == NULL) return NULL;

    novo->id = id;
    novo->quantidade = quantidade;
    novo->preco = preco;
    
    novo->nome = strdup(nome);
    novo->desc = strdup(desc);
    
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

no* inserir(no *raiz, int id, char *nome, int quantidade, char *desc, float preco) {
    if (raiz == NULL) {
        return criar_no(id, nome, quantidade, desc, preco);
    }

    if (preco < raiz->preco) {
        raiz->esq = inserir(raiz->esq, id, nome, quantidade, desc, preco);
    } 
    else {
        raiz->dir = inserir(raiz->dir, id, nome, quantidade, desc, preco);
    }

    return raiz;
}