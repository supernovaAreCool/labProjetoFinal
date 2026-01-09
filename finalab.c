#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct produto {
    int id;
    char * nome;
    int quantidade;
    char * desc;
    float preco;
} produto;

//Isso é para criarmos a lista encadeada de produtos
produto *inicio = NULL;
typedef struct listaproduto{
    produto no;
    produto *prox;
    int tam;
};

void addlista(listaproduto lista, produto a){
    if (lista->tam==0){
        inicio = *a;
        lista->tam++;
    }else{
        
    }
    return 0;
}


produto* criar_no(int id, char *nome, int quantidade, char *desc, float preco) {
    produto *produto_n = (produto*)malloc(sizeof(produto));
    if (produto_n == NULL) return NULL;

    produto_n->id = id;
    produto_n->quantidade = quantidade;
    produto_n->preco = preco;
    
    produto_n->nome = strdup(nome);
    produto_n->desc = strdup(desc);

    return produto_n;
}

produto* inserir(int id, char *nome, int quantidade, char *desc, float preco, FILE *inv) {


}

// Cria o arquivo inventario inicial se hourver, caso o contrario, apenas abre o arquivo;
FILE* arquivo_inicial() {
    FILE *inventario = fopen("inventario.txt", "a+");

    if (inventario == NULL) {
        printf("Erro ao abrir ou criar o arquivo inventario.txt\n");
        return NULL;
    }
}

int main() {
    FILE *inventario = arquivo_inicial();



    return 0;
}


//testando esse comentário só para dar git commit e push