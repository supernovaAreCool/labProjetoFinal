#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
    const char *comando_limp = "cls";
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    const char *comando_limp = "clear";
#else
    const char *comando_limp = "clear";
#endif

typedef struct produto {
    int id;
    char * nome;
    int quantidade;
    int n_restoque;
    char * desc;
    float preco;
    struct produto *prox;
} produto;

//Duas variáveis globais referentes à lista de produtos
produto *inicio = NULL;
int tam = 0;

//Essa função serve para escrever o que estiver na lista do programa pro txt, é interessante colocar ela no final de toda função que muda alguma coisa na lista, por exemplo a função adicioinar ou a função remover
void reescrever(){
    produto *atual = inicio;
    FILE * arquivo = fopen("inventario.txt", "w");
    for (int i = 0; i<tam; i++){
        fprintf(arquivo, "%i;%s;%i;%s;%f\n", atual->id, atual->nome, atual->quantidade, atual->desc, atual->preco);
        atual = atual->prox;
    }
}

//Adiciona um item ao começo da lista
void addlista(produto *a){
    if (tam == 0){
        inicio = a;
    }else{
        a->prox = inicio;
        inicio = a;
    }
    tam++;
}

//Imprime todos os produtos(i.e cada um de seus 'atributos') percorrendo a lista
void imprimir(){
    produto * atual = inicio;
    for (int i = 0; i<tam; i++){
        printf("%i %s %i %s %f\n", atual->id, atual->nome, atual->quantidade, atual->desc, atual->preco);
        atual = atual->prox;
    }
}

//Pergunta ao usuário qual identificador(pode ser o código do produto ou o nome dele) ele vai usar para remover o produto e depois remove ele, não vai apagar na memória porque deu preguiça
void removerlista(){
    int opcao;
    char * identificador;
    produto * atual = inicio;
    printf("Você deseja remover com base no:\n[1] - Código do produto\n[2] - Nome do produto");
    scanf("%i", &opcao);
    if (opcao==1){
        printf("Qual o código do produto?\n");
        gets(identificador);
        if (inicio->id == atoi(identificador)){
            inicio = inicio->prox;
        }
        for (int i=0; i<tam-1;i++){
            if (atual->prox->id == atoi(identificador)){
                atual->prox = atual->prox->prox;
            }
        }
    }
    if (opcao==2){
        printf("Qual o nome do produto?\n");
        gets(identificador);
        if(*(inicio->nome) == identificador){
            inicio = inicio->prox;
        }
        for (int i = 0; i<tam-1;i++){
            if (atual->prox->nome = identificador){
                atual->prox = atual->prox->prox;
            }
        }
    }
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


void inicializar(){
    char linha[1024];
    FILE *arquivo = fopen("inventario.txt", "r");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *id = strtok(linha, ";");
        char *nome = strtok(NULL, ";");
        char *quantidade = strtok(NULL, ";");
        char *desc = strtok(NULL, ";");
        char *preco = strtok(NULL, ";");
        addlista(criar_no(atoi(id), strdup(nome), atoi(quantidade), strdup(desc), atof(preco)));
    }
}

// Cria o arquivo inventario inicial se hourver, caso o contrario, apenas abre o arquivo;
FILE* arquivo_inicial() {
    FILE *inventario = fopen("inventario.txt", "a+");

    if (inventario == NULL) {
        printf("Erro ao abrir ou criar o arquivo inventario.txt\n");
        return NULL;
    }
}

void checar_quantidade_produtos(produto *p) {
    if (p->quantidade >= p->n_restoque) 
        printf("!!! Produto %s está acima do limite de restoque.", p->nome);

    return;
}

void mensagem(char msg[]) {
    system(comando_limp);
    printf("%s", msg);
}

void menu() {
    int funcionar = 1, opcao;
    FILE *inventario = arquivo_inicial();
    inicializar();
    while (funcionar){
        mensagem("O que você deseja fazer?\n1- Cadastrar\n2- Consultar\n3- Entradas/Saídas\n4- Relatório\n5- Sair\n");
        scanf("%i", &opcao);
        if (opcao==1){
            
        }
        if (opcao==2){
            imprimir();
        }
        if (opcao==3){

        }
        if (opcao==4){

        }
        if (opcao==5){
            funcionar = 0;
            system(comando_limp);
            reescrever();
        }
    }
    return 0;
}

int main() {
    menu();
}