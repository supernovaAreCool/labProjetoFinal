#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#if defined(_WIN32) || defined(_WIN64)
    const char *comando_limp = "cls";
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    const char *comando_limp = "clear";
#else
    const char *comando_limp = "clear";
#endif

enum {
    MENU_CADASTRAR = 1,
    MENU_CONSULTAR,
    MENU_RELATORIO,
    MENU_SAIR
};

typedef enum {
    KEY_ID,
    KEY_NOME
} ProdutoKey;

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
float v_total = 0.0f;
unsigned int q_total = 0;

// Prototipos de função

void reescrever();
void imprimir_produto(produto* p);
void addlista(produto *a);
void imprimir();
produto* pegar_produto(void *key, ProdutoKey t);
produto* criar_no(int id, char *nome, int quantidade, char *desc, float preco, int n_restoque);
void inicializar();
void arquivo_inicial();
void checar_quantidade_produtos();
void mensagem(char msg[]);
void relatorio();
void consulta();
void modificar_produto_quantidade(produto* p);
void esperar();
int menu_generico(char msg[]);
void cadastrar_produto();
void menu();

char* prompt_string(char* buff, char* msg);
int prompt_int(char* buff, char* msg);

void liberar_lista();


// fim dos prototipos, teehee.

int main() {
    menu();
}

char* prompt_string(char* buff, char* msg) {
    printf("%s", msg);
    fgets(buff, 100, stdin);
    buff[strcspn(buff,"\n")] = '\0';

    return buff;
}

int prompt_int(char* buff, char* msg) {
    int i;
    printf("%s", msg);
    fgets(buff, sizeof(buff), stdin);
    i = atoi(buff);
    buff[0] = '\0';

    if (!i) {
        printf("Input Invalido: Não foi possivel detectar numero em buffer.");
        return -1;
    }

    return i;
}

//Essa função serve para escrever o que estiver na lista do programa pro txt, é interessante colocar ela no final de toda função que muda alguma coisa na lista, por exemplo a função adicioinar ou a função remover
void reescrever() {
    produto *atual = inicio;
    FILE * arquivo = fopen("inventario.txt", "w");
    for (int i = 0; i<tam; i++){
        fprintf(arquivo, "%i;%s;%i;%s;%f;%d\n", atual->id, atual->nome, atual->quantidade, atual->desc, atual->preco, atual->n_restoque);
        atual = atual->prox;
    }
    
    fclose(arquivo);
}

// Imprime o produto à tela
void imprimir_produto(produto* p) {
    printf("%-4i %-12s %-10i %-12s %-8.2f %-9d\n", p->id, p->nome, p->quantidade, p->desc, p->preco, p->n_restoque);
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

    printf("%-4s %-12s %-10s %-12s %-8s %-9s\n", "ID", "Nome", "Quantidade", "Descrição", "Preço", "Restoque");

    for (int i = 0; i<tam; i++){
        imprimir_produto(atual);
        atual = atual->prox;
    }
}





// Função generica que retorna um produto de acordo com uma chave. Podendo a chave ser um id ou um nome.
produto* pegar_produto(void *key, ProdutoKey t) {
    bool achado = false;
    produto * atual = inicio;
    
    while (atual != NULL) {
        switch (t) {
            case KEY_ID:
                if (atual->id == *(int*) key)
                    return atual;

            break;
            case KEY_NOME:
                if (strcmp(atual->nome, (char*)key) == 0)
                    return atual;
            break;
            default:
                return NULL;
        }


        atual = atual->prox;
    }


    return NULL;
}


// Cria um produto na lista carregada.
produto* criar_no(int id, char *nome, int quantidade, char *desc, float preco, int n_restoque) {
    produto *produto_n = (produto*)malloc(sizeof(produto));
    if (produto_n == NULL) return NULL;

    produto_n->id = id;
    produto_n->quantidade = quantidade;
    produto_n->preco = preco;
    
    produto_n->nome = strdup(nome);
    produto_n->desc = strdup(desc);

    produto_n->n_restoque = n_restoque;

    produto_n->prox = NULL;

    return produto_n;
}

void inicializar(){
    char linha[1024];
    FILE *arquivo = fopen("inventario.txt", "r");

    if (!arquivo)
        return;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *id = strtok(linha, ";");
        char *nome = strtok(NULL, ";");
        char *quantidade = strtok(NULL, ";");
        char *desc = strtok(NULL, ";");
        char *preco = strtok(NULL, ";");
        char *n_restoque = strtok(NULL, ";\n");

        addlista(criar_no(atoi(id), nome, atoi(quantidade), desc, atof(preco), atoi(n_restoque)));
        
        q_total += atoi(quantidade);
        v_total += atof(preco) * atoi(quantidade);
    }

    fclose(arquivo);
}

// Cria o arquivo inventario inicial se hourver, caso o contrario, apenas abre o arquivo;
void arquivo_inicial() {
    FILE *inventario = fopen("inventario.txt", "a+");

    if (inventario == NULL) {
        printf("Erro ao abrir ou criar o arquivo inventario.txt\n");
        fclose(inventario);
        return;
    }

    fclose(inventario);
    return;
}

void checar_quantidade_produtos() {
    bool achado = false;
    produto * atual = inicio;

    while (atual != NULL) {
        if (atual->quantidade >= atual->n_restoque) {
            printf("\n!!! Produto %s está acima do limite de restoque.", atual->nome);
            achado = true;
        }

        atual = atual->prox;
    }

    if (!achado) { printf("\nNenhum produto está acima do limite de restoque."); }

    return;
}

void mensagem(char msg[]) {
    system(comando_limp);
    printf("%s", msg);
}

void relatorio() {
    imprimir();
    printf("\nTotal de itens: %d\nValor total: %f\nQuantidade total de itens: %u\n", tam, v_total, q_total);

    checar_quantidade_produtos();

    esperar();
}

void consulta() {
    int i;

    i = menu_generico("Consulte via: \n[1] ID\n[2] Nome\n[3] Sair");

    produto* p;
    char buf[128];
    switch (i) {
        case 1:
            int id;
            mensagem("Insira o id: ");
            fgets(buf, sizeof(buf), stdin);
            id = atoi(buf);
            p = pegar_produto(&id, KEY_ID);
        break;
        case 2:
            char nome[100];
            printf("Nome: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome ,"\n")] = '\0';
            p = pegar_produto(nome, KEY_NOME);
        break;
        case 3:
            return;
        break;
    }

    if (!p) {
        mensagem("Produto não encontrado.\n");
        esperar();
        return;
    }

    imprimir_produto(p);
    modificar_produto_quantidade(p);
    
}

void modificar_produto_quantidade(produto* p) {
    int i = menu_generico("[1] Modificar quantidade do produto.\n[2] Sair");

    switch (i) {
        case 1:
            int mod;
            mod = menu_generico("Insira a quantidade para modificar (positivo aumenta, negativo diminui): ");

            if (p->quantidade + mod < 0) {
                printf("\nValor Invalido: quantidade resultante não pode ser menor que zero.");
                return;
            }
            p->quantidade += mod;

            q_total += mod;
            v_total += p->preco * mod;

            printf("Modificado com sucesso. Nova quantidade: %d\n\n", p->quantidade);

            reescrever();
            system(comando_limp);
            modificar_produto_quantidade(p);
        break;
        case 2:
            return;
        break;
    }
        
    
}

void esperar() {
    char s[16];
    prompt_string(s, "");
}

int menu_generico(char msg[]) {
    mensagem(msg);
    char buf[16];

    int op = prompt_int(buf, "\n> ");

    return op;
}

void cadastrar_produto() {
    printf("Cadastro de produto: \n");

    char buf[20];

    char nome[100];
    prompt_string(nome, "Nome: ");

    int quantidade;
    quantidade = prompt_int(buf, "Quantidade: ");

    char desc[100];
    prompt_string(desc, "Descrição: ");

    float preco = 0.0f;
    printf("Preço: ");
    fgets(buf, sizeof(buf), stdin);
    preco = atof(buf);
    buf[0] = '\0';

    int n_restoque;
    n_restoque = prompt_int(buf, "Minimo de Restoque: ");

    q_total += quantidade;
    v_total += preco * quantidade;



    addlista(criar_no(tam+1, nome, quantidade, desc, preco, n_restoque));
    reescrever();

}


void menu() {
    bool funcionar = true;
    int op = 0;
    arquivo_inicial();
    inicializar();
    while (funcionar) {

        op = menu_generico("O que você deseja fazer?\n[1] Cadastrar\n[2] Consultar\n[3] Relatório\n[4] Sair\n");

        switch(op) {
        case MENU_CADASTRAR:
            cadastrar_produto();
        break;
        case MENU_CONSULTAR:
            consulta();
        break;
        case MENU_RELATORIO:
            relatorio();
        break;
        case MENU_SAIR:
            funcionar = false;
            system(comando_limp);
            reescrever();
            liberar_lista();
        break;
        default:
            printf("Numero Invalido! Tente novamente.\n\n");

        }
    }
}

void liberar_lista(void) {
    produto *atual = inicio;
    while (atual) {
        produto *next = atual->prox;
        free(atual->nome);
        free(atual->desc);
        free(atual);
        atual = next;
    }
}

