#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#define tam 100

//Estruturas de uma arvore binaria:

typedef struct No* Raiz;

typedef struct No{
    float matricula;
    char nome[tam];
    struct No* esquerda;
    struct No* direita;
}No;

Raiz* criar_arvore(void){
    Raiz* arvore= (Raiz*)malloc(sizeof(Raiz));
    if(arvore != NULL)
        *arvore= NULL;
    return arvore;
}

void liberaNo(No* no){
    if(no == NULL)
        return;
    liberaNo(no->esquerda);
    liberaNo(no->direita);
    free(no);
    no= NULL;
}

void liberaArvore(Raiz* arvore){
    if(arvore == NULL)
        return;
    liberaNo(*arvore);
    free(arvore);
}

//Altura da arvore e contagem de elementos: conta os nos da esquerda e da direita e retorna o maior somando +1
int alturaArvore(Raiz *arvore){
    if(arvore == NULL)
        return 0;
    if(*arvore == NULL)
        return 0;
    int no_esqd= alturaArvore(&(*arvore)->esquerda);
    int no_dirt= alturaArvore(&(*arvore)->direita);
    if(no_esqd > no_dirt){
        return (no_esqd +1);}
    else{
        return (no_dirt +1);}
}

int contarNo(Raiz *arvore){
    if(arvore == NULL)
        return 0;
    if(*arvore == NULL)
        return 0;
    int no_esqd= contarNo(&(*arvore)->esquerda);
    int no_dirt= contarNo(&(*arvore)->direita);
    
    return (no_esqd+no_dirt +1);
}

//Inserção: Valores maiores que a raiz ficam a direita e valores menores a esquerda, assim temos uma arvore binaria de busca 
void insereArvore(Raiz *arvore,char *nome, char*matricula){
    if(arvore == NULL){
        printf("Erro\n");
        return;
    }
    struct No* novo;
    novo= (No*)malloc(sizeof(No));
    if(novo == NULL){
        wprintf(L"Erro ao alocar memória\n");
        return;
    }
    novo->matricula = atof(matricula);
    strcpy(novo->nome, nome);
    novo->esquerda= NULL;
    novo->direita= NULL;

    if(*arvore == NULL){
        *arvore= novo;}
    else{
        No* atual = *arvore;
        No* ant = NULL;
        int cmp = 0;
        while(atual != NULL){
            ant = atual;
            cmp = strcmp(novo->nome, atual->nome);
            if(cmp == 0){
                free(novo);
                wprintf(L"Aluno já cadastrado\n");
                return;
            }
            if(cmp > 0){
                atual = atual->direita;
            } else {
                atual = atual->esquerda;
            }
        }
        if(cmp > 0){
            ant->direita = novo;
        } else {
            ant->esquerda = novo;
        }
    }
}

// Insere um nó na árvore de notas, ordenando pela média
void inserePorMedia(Raiz *arvore, char *nome, float media) {
    if(arvore == NULL){
        printf("Erro\n");
        return;
    }
    struct No* novo = (No*)malloc(sizeof(No));
    if(novo == NULL){
        wprintf(L"Erro ao alocar memória\n");
        return;
    }
    novo->matricula = media;
    strcpy(novo->nome, nome);
    novo->esquerda = NULL;
    novo->direita = NULL;

    if(*arvore == NULL){
        *arvore = novo;
    } else {
        No* atual = *arvore;
        No* ant = NULL;
        int lado = 0;
        while(atual != NULL){
            ant = atual;
            if(novo->matricula > atual->matricula){
                atual = atual->direita;
                lado = 1;
            } else {
                atual = atual->esquerda;
                lado = 0;
            }
        }
        if(lado)
            ant->direita = novo;
        else
            ant->esquerda = novo;
    }
}

//Percorrendo e imprimindo a arvore:
//Em Ordem: esquerda --> raíz --> direita
// tive que separar em duas funções com funções especificas pois da outra forma estava dando recursao infinita.
void emOrdem(Raiz* arvore){  // so vai percorer e imprimier os alunos
    if(arvore == NULL || *arvore == NULL){
        return;
    }
    if(*arvore != NULL){
        emOrdem(&(*arvore)->esquerda);
        printf("|%-16s|    %.2f      |\n", (*arvore)->nome, (*arvore)->matricula);
        emOrdem(&(*arvore)->direita);
    }
}


void cabecalho(Raiz* arvore){  // autoexplicativo
    if(arvore == NULL || *arvore == NULL){
        return;
    }
    printf("\n|===============================|\n");
    printf("|        LISTA DE ALUNOS        |");
    printf("\n|===============================|\n");
    wprintf(L"|NOME               | MATRÍCULA |\n");
    printf("|===============================|\n");
    emOrdem(arvore);  
    printf("|===============================|\n");
}


void emOrdem_decrescente(Raiz* arvore){
    if(arvore == NULL || *arvore == NULL){
        return;
    }
    if(*arvore != NULL){
        emOrdem_decrescente(&(*arvore)->direita);
        printf("|%-16s|    %.2f      |\n", (*arvore)->nome, (*arvore)->matricula);
        emOrdem_decrescente(&(*arvore)->esquerda);
    }
}

// Busca um aluno pelo nome na árvore binária
No* buscarPorNome(Raiz* arvore, const char* nome) {
    if (arvore == NULL || *arvore == NULL) return NULL;
    No* atual = *arvore;
    int cmp;
    while (atual != NULL) {
        cmp = strcmp(nome, atual->nome);
        if (cmp == 0) {
            return atual;
        }
        if (cmp > 0) {
            atual = atual->direita;
        } else {
            atual = atual->esquerda;
        }
    }
    return NULL;
}
// Verifica se o aluno está na árvore principal e se já está na árvore de notas
// Retorna 1 se pode lançar nota, 0 se não pode (não existe ou já tem nota)
int podeLancarNota(Raiz* arvore, Raiz* arvore_notas, const char* nome) {
    No* aluno = buscarPorNome(arvore, nome);
    if (aluno == NULL) {
        wprintf(L"Aluno não encontrado na turma.\n");
        return 0;
    }
    No* aluno_nota = buscarPorNome(arvore_notas, nome);
    if (aluno_nota != NULL) {
        wprintf(L"Aluno já possui nota lançada.\n");
        return 0;
    }
    return 1;
}
// Busca um aluno pelo nome e retorna apenas o nome (ou NULL se não encontrar)
const char* buscarNome(Raiz* arvore, const char* nome) {
    No* resultado = buscarPorNome(arvore, nome);
    if (resultado != NULL) {
        return resultado->nome;
    }
    return NULL;
}

//Remoção de um elemento:

//Após encontrar o nó que será removido, a função tratarNo é responsavel por remover o nó e garantir o encadeamento correto seguindo as regras de uma arvore de busca binaria. 
No* tratarNo(No* atual){
    No* no1, *no2;
    if(atual->esquerda == NULL){
        no2 = atual->direita;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esquerda;
    while(no2->direita != NULL){
        no1 = no2;
        no2 = no2->direita;
    }
    if(no1 != atual){
        no1->direita = no2->esquerda;
        no2->esquerda = atual->esquerda;
    }
    no2->direita = atual->direita;
    free(atual);
    return no2;
}

//A fun��o removeNo � responsavel por encontrar o n� a ser removido
void removeNo(Raiz* arvore, const char* nome){
    if(arvore == NULL){
        wprintf(L"Árvore vazia.\n");
        return;
    }
    No* ant = NULL;
    No* atual = *arvore;
    int cmp = 0;
    while(atual != NULL){
        cmp = strcmp(nome, atual->nome);
        if(cmp == 0){
            if(atual == *arvore){
                *arvore = tratarNo(atual);
            } else {
                if(ant->direita == atual){
                    ant->direita = tratarNo(atual);
                } else {
                    ant->esquerda = tratarNo(atual);
                }
            }
            return;
        }
        ant = atual;
        if(cmp > 0){
            atual = atual->direita;
        } else {
            atual = atual->esquerda;
        }
    }
    printf("Aluno não encontrado.\n");
    system("pause");
}

//entrada de dados: 
void maiuscula(char *nome){
    int tamanho= strlen(nome);
    for(int i= 0; i < tamanho; i++){
        if(nome[0] == ' '){
            wprintf(L"Sem espaços no inicio do nome.\n");
            system("pause");
            return;
        }
        if(isdigit(nome[i])){
            wprintf(L"Nomes não podem conter numeros.\n");
            system("pause");
            return;
        }
        nome[i] = toupper(nome[i]);
    }
}

void cadastrarAluno(Raiz *arvore){
    // setlocale(LC_ALL, "Portuguese");
    static int contador_matricula = 1;
    char nome[tam];
    float matricula;
    printf("Digite o nome do aluno: ");
    scanf("%[^\n]", nome);
    maiuscula(nome);
    matricula = 2025.00f + (float)contador_matricula / 100.0f;
    contador_matricula++;
    char matricula_str[32];
    sprintf(matricula_str, "%f", matricula);
    insereArvore(arvore, nome, matricula_str);
}

void removerAluno(Raiz *arvore, Raiz *arvore_notas){
    char nome[tam];
    printf("Digite o nome do aluno a ser removido: ");
    scanf("%[^\n]", nome);
    maiuscula(nome);
    removeNo(arvore, nome);
    // Remover também da árvore de notas, se existir
    No* aluno_nota = buscarPorNome(arvore_notas, nome);
    if (aluno_nota != NULL) {
        removeNo(arvore_notas, nome);
    }
}

void pegar_notas(Raiz* arvore, Raiz* arvore_notas){
    printf("Digite o nome do aluno:\n");
    char nome[tam];
    scanf("%[^\n]", nome);
    maiuscula(nome);
    if (!podeLancarNota(arvore, arvore_notas, nome)) {
        system("pause");
        return;
    }
    printf("Digite as 5 notas do aluno %s (separadas por espaco):\n", nome);
    double notas[5];
    for(int i = 0; i < 5; i++) {
        scanf("%lf", &notas[i]);
    }
    double media = ((notas[0] * 2) + (notas[1] * 1.5) + (notas[2] * 1.5) + (notas[3] * 2.5) + (notas[4] * 2.5)) / 10;
    char aluno_nome_buffer[tam];
    printf("Media do aluno %s: %.2lf\n", nome, media);
    system("pause");
    strncpy(aluno_nome_buffer, nome, tam - 1);
    aluno_nome_buffer[tam - 1] = '\0';
    inserePorMedia(arvore_notas, aluno_nome_buffer, media);
}
