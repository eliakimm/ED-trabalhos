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
    char matricula[tam];
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
    strcpy(novo->matricula, matricula);
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

//Percorrendo e imprimindo a arvore:

//Em Ordem: esquerda --> raíz --> direita
void emOrdem(Raiz* arvore){
    if(arvore == NULL){
        printf("Arvore vazia\n");
        return;}
    if(*arvore != NULL){
        emOrdem(&(*arvore)->esquerda);
        printf("%s : %s\n", (*arvore)->nome, (*arvore)->matricula);
        emOrdem(&(*arvore)->direita);}
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
        printf("Arvore vazia\n");
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
            printf("Nomes nao podem conter numeros.\n");
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
    char matricula[tam];
    printf("Digite o nome do aluno: ");
    scanf("%[^\n]", nome);
    maiuscula(nome);
    sprintf(matricula, "2025-%02d", contador_matricula);
    contador_matricula++;
    insereArvore(arvore, nome, matricula);
}

void removerAluno(Raiz *arvore){
    char nome[tam];
    printf("Digite o nome do aluno a ser removido: ");
    scanf("%[^\n]", nome);
    maiuscula(nome);
    removeNo(arvore, nome);
}
