#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_NOME 50

typedef struct lista Lista;
typedef struct listano ListaNo;

// dados do aluno ↓
typedef struct aluno{
    char nome[TAM_NOME];
    int matricula;
} Aluno;

typedef struct listano{
    Aluno aluno;
    struct listano* anterior;
    struct listano* proximo;
} ListaNo;

typedef struct lista {
    ListaNo* primeiro;
    ListaNo* ultimo;
} Lista;


// PROTOTIPOS:
Lista* criar();
void ColocaInicio();
void SaiMLK();
void MostraChamada();

Aluno PegarDados();

void Faxina();

int main(){
    Lista* lista = criar();
    int escolha, matricula;
    float n1 ,n2, n3, media;
    char notas[50];

    // vou usar do-switch porque e mais facil
    do{
        printf("\n----- MENU -----\n");
        printf("[1] -> Adicionar aluno\n");
        printf("[2] -> Retirar matricula\n");
        printf("[3] -> Imprimir\n");
        printf("[4] -> Sair\n");
        printf("_____________________\n");
        printf("Escolha: ");

        while(scanf("%d", &escolha) != 1){
            printf("Entrada invalida. 1-4: ");
            while(getchar() != '\n');
        }
        getchar();
        
        switch ((escolha)){
            case 1:{
                Aluno aluno = PegarDados();
                ColocaInicio(lista, aluno);
                printf("\nDados cadastrados:\nNome: %s\nMatricula: %d\n", aluno.nome, aluno.matricula);
                break;
            }
            case 2:{
                printf("Digite a matricula a ser removida: ");
                scanf("%d", &matricula);
                SaiMLK(lista, matricula);
                break;
            }
            case 3:{
                MostraChamada(lista);
                break;
            }
            case 4:{
                printf("Tchau...\n");
                break;
            }
            default:{
                printf("Ainda nao temos essa opca4o.");
            }
        }
    } while(escolha != 4);
    Faxina(lista);
    return 0;
}

Lista* criar(){
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    return lista;
}

// vamos colocar no inicio
void ColocaInicio(Lista* lista, Aluno aluno){  // 1 no menu
    ListaNo* novo = (ListaNo*)malloc(sizeof(ListaNo));
    novo->aluno = aluno;
    novo->anterior = NULL;
    novo->proximo = lista->primeiro;

    // caso a lista tenha algo, atualiza o anterior do primeiro
    if(lista->primeiro != NULL){  
        lista->primeiro->anterior = novo;
    } else{
        lista->ultimo = novo; // se tiver vazia o novo sera o iltimo
    }
    lista->primeiro = novo; // so aponta pro novo
}

void SaiMLK(Lista* lista, int matricula){  // 2 no menu
    ListaNo* atual = lista->primeiro;

    while(atual != NULL && atual->aluno.matricula != matricula){
        atual =  atual->proximo;
    }

    if(atual == NULL){ // caso nao exista 
        printf("Matricula: %d nao encontrada.\n", matricula);
        return;
    }

    // aqui vai atualizar os ponteiros 
    if(atual->anterior != NULL){
        atual->anterior->proximo = atual->proximo;
    } else{
        lista->primeiro = atual->proximo;
    }
    if(atual->proximo != NULL){
        atual->proximo->anterior = atual->anterior;
    } else{
        lista->ultimo = atual->anterior;
    }

    free(atual);  // libera a memoria onde o no estava
    printf("Aluno removido.\n");
}

void MostraChamada(Lista* lista){  // 3 no menu
    ListaNo* atual = lista->primeiro;

    if(atual == NULL){
        printf("Chamada sem alunos\n");
        return;
    }

    // chamada "organizada" ↓
    printf("\n -- CHAMADA --\n");
    while(atual != NULL){
        printf("Aluno: %s | Matricula: %d\n", atual->aluno.nome, atual->aluno.matricula);
        atual = atual->proximo;
    }
    printf("_____________________\n");
}

// leitura dos dados dos alunos [MELHORADO] 
Aluno PegarDados(){
    Aluno aluno;
    int flagNUM;
    
    do{
        printf("Nome do aluno: \n");
        fgets(aluno.nome, TAM_NOME, stdin);
        aluno.nome[strcspn(aluno.nome, "\n")] = '\0'; // deve remover o enter

        // vai ver se tem apenas letras e espacos 
        flagNUM = 1;
        for(int i = 0; aluno.nome[i] != '\0'; i++){
            if(!isalpha(aluno.nome[i]) && aluno.nome[i] != ' '){
                printf("Ninguem no mundo tem um numero no nome!!!\n");
                flagNUM = 0;
                break;
            }
        }
    } while(!flagNUM);
    printf("Nome do aluno: \n");
    fgets(aluno.nome, TAM_NOME, stdin);
    
    aluno.nome[strcspn(aluno.nome, "\n")] = '\0'; // deve remover o enter

    printf("Digite a matricula: \n");
    while(scanf("%d", &aluno.matricula) != 1){ // tem que ter pelo menos um numero
        printf("Matricula deve ter um numero: ");
        while(getchar() != '\n');
    }
    getchar();

    return aluno;
}

// limpar a sujeira
void Faxina(Lista* lista){
    if(lista != NULL){
        ListaNo* atual = lista->primeiro;

        while(atual != NULL){ // percorre liberando geral
            ListaNo* tempo = atual;
            atual = atual->proximo;
            free(tempo);
        }
        free(lista);
    }
}
