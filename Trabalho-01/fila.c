#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 typedef struct filaNo filaNo;

 struct filaNo{
    char aluno[50];
    int matricula;
    filaNo* prox;
 };
     
typedef struct primElemento{
    filaNo* prim;
    filaNo* ult;
}fila;

fila* criar(void){
    fila* f= (fila*) malloc(sizeof(fila));
    f->prim= NULL;
    f->ult= NULL;
    return f;
}

void insere(fila *f, int matricula, char *nome);
void imprimir(fila *f);
void liberarFila(fila *f);

int main(){
    fila *f;
    f= criar();

    insere(f, 330125447, "Eliakim Silva");
    insere(f, 322122443, "fulano da Silva");
    insere(f, 330123476, "sei nao Silva");
    insere(f, 330535447, "Sei la Silva");

    imprimir(f);
    liberarFila(f);
    imprimir(f);

    return 0;
}


void insere(fila* f, int matricula, char* nome){
    filaNo* novo= (filaNo*) malloc(sizeof(filaNo));
    novo->matricula= matricula;
    novo->prox= NULL;
    strcpy(novo->aluno,nome);
    if(f->prim == NULL){
        f->prim=novo;}
    else{
        f->ult->prox= novo;
    }
    f->ult= novo;
}

void imprimir(fila *f){
    if(f->prim==NULL){
        printf("Nao ha alunos cadastrados");}
    else{
        printf("***************************\n");
        for(filaNo *aux= f->prim; aux != NULL; aux= aux->prox){
            printf("Nome: %s\n", aux->aluno);
            printf("Matricula: %d\n", aux->matricula);
            printf("***************************\n");
        }
    }
}

void liberarFila(fila *f){
    filaNo *aux= f->prim;
    while(aux != NULL){
        filaNo *tem= aux->prox;
        free(aux);
        aux= tem;}
    f->prim= NULL;
    f->ult= NULL;
}