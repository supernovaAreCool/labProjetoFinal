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
    int n_estoque;
    char * desc;
    float preco;
    struct produto *prox;
    struct produto *prev;
} produto;

//Duas variáveis globais referentes à lista de produtos
produto *inicio = NULL;
int tam = 0;
float v_total = 0.0f;
unsigned int q_total = 0;

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
void addlista(int id, char nome, int quantidade, int estoque, char desc, float preco){
    produto *novo = malloc(sizeof(produto));

    printf("========================ADICIONAR PRODUTOS========================\n");

    printf("ID:\n");
    scanf("%d", &id);

    printf("Nome:\n");
    scanf("%s", &nome);

    printf("Preco:\n");
    scanf("%f", &preco);

    printf("Quantidade:\n");
    scanf("%d", &quantidade);

    novo->prox = inicio;
    inicio = novo;

    inicializar();
}


//Imprime todos os produtos(i.e cada um de seus 'atributos') percorrendo a lista
void imprimir(){
    produto * atual = inicio;

    printf("ID\tNome\t\tQuantidade\tDescrição\t\tPreço\n");

    for (int i = 0; i<tam; i++){
        printf("%i\t%s\t%i\t\t%s\t\t%f\n", atual->id, atual->nome, atual->quantidade, atual->desc, atual->preco);
        atual = atual->prox;
    }
}



//Pergunta ao usuário qual identificador(pode ser o código do produto ou o nome dele) ele vai usar para remover o produto e depois remove ele, não vai apagar na memória porque deu preguiça

produto pegar_p_via_cod(int id) {

}
<<<<<<< HEAD
=======
produto pegar_p_via_nome(char nome[]) {
    
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
>>>>>>> dae228843993f826e415b094b5afd07d23a74924

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

        q_total += atoi(quantidade);
        v_total += atof(preco);
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
    if (p->quantidade >= p->n_estoque) 
        printf("!!! Produto %s está acima do limite de restoque.", p->nome);

    return;
}

void mensagem(char msg[]) {
    system(comando_limp);
    printf("%s", msg);
}

void relatorio() {
    imprimir();
    printf("\nTotal de itens: %d, Valor total: %f, Quantidade total de itens: %u\n", tam, v_total, q_total);

    char s[1];
    scanf("%s", &s);
}

void menu() {
    int funcionar = 1, opcao;
    FILE *inventario = arquivo_inicial();
    inicializar();
    while (funcionar){
        mensagem("O que você deseja fazer?\n1- Cadastrar\n2- Consultar\n3- Relatório\n4- Sair\n");
        scanf("%i", &opcao);
        if (opcao==1){
            
        }
        if (opcao==2){
        }
        if (opcao==3){
            relatorio();
        }
        if (opcao==4){
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