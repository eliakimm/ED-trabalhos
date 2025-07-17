#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_NOME 50

// lista so nome e matricula

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

Lista* criar(){
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    return lista;
}
//Estruturas da fila:
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

fila* criar_fila(void){
    fila* f= (fila*) malloc(sizeof(fila));
    f->prim= NULL;
    f->ult= NULL;
    return f;
}

// PROTOTIPOS:
void insere(fila *f, int matricula, char *nome);
void imprimir_reprovados(fila *f);
void liberarFila(fila *f);

void ColocaInicio();
void SaiMLK();
void MostraChamada();
Aluno PegarDados(); 
void Faxina();
void pegar_notas();

// MAIN ↓
int main(){
    Lista* lista = criar();
    fila* fila;
    fila= criar_fila();
    int escolha;

    // vou usar do-switch porque e mais facil
    do{
        printf("\n----- MENU -----\n");
        printf("[1] -> Adicionar aluno\n");
        printf("[2] -> Lancar notas\n");
        printf("[3] -> Imprimir Turma/Reprovados\n");
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
                Aluno aluno = PegarDados(lista);
                ColocaInicio(lista, aluno);
                printf("\nDados cadastrados:\nNome: %s\nMatricula: %d\n", aluno.nome, aluno.matricula);
                break;
            }
            case 2:{
                pegar_notas(lista, fila);
                break;
            }
            case 3:{
                MostraChamada(lista);
                imprimir_reprovados(fila);
                break;
            }
            case 4:{
                printf("Tchau...\n");
                break;
            }
            default:{
                printf("Aina nao temos essa opca4o.");
            }
        }
    } while(escolha != 4);
    Faxina(lista);
    liberarFila(fila);
    return 0;
}
// MAIN ↑

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

void imprimir_reprovados(fila *f){
    if(f->prim==NULL){
        printf("Nao ha alunos reprovados\n");}
    else{
        printf("***************************\n");
        printf("Reprovados:\n");
        for(filaNo *aux= f->prim; aux != NULL; aux= aux->prox){
            printf("***************************\n");
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

void SaiMLK(Lista* lista, fila *f, int matricula){  // 2 no menu
    ListaNo* atual = lista->primeiro;

    while(atual != NULL && atual->aluno.matricula != matricula){
        atual =  atual->proximo;
    }

    if(atual == NULL){ // caso nao exista 
        printf("Matricula: %d nao encontrada.\n", matricula);
        return;
    }

    // aqui vai atualizar os ponteiros 
    insere(f, atual->aluno.matricula, atual->aluno.nome);
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
        printf("***************************\n");
        printf("Chamada sem alunos\n");
        printf("***************************\n");
        return;
    }

    // chamada "organizada" ↓
    printf("***************************\n");
    printf("\n -- CHAMADA --\n");
    while(atual != NULL){
        printf("Aluno: %s | Matricula: %d\n", atual->aluno.nome, atual->aluno.matricula);
        atual = atual->proximo;
    }
}

// tive que fazer isso pra verificar se a matricula ja existe
int Jafoi(Lista* lista, int matricula){
    ListaNo* atual = lista->primeiro;

    while(atual != NULL){
        if(atual->aluno.matricula == matricula){
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

// leitura dos dados dos alunos 
Aluno PegarDados(Lista* lista){
    Aluno aluno;
    int flagNUM;
    int Repetricula;  // Repetição de matricula
    
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

    do{  // adicionei um do-while usando a parte que pegava a matricula
        Repetricula = 1;
        printf("Digite a matricula: \n");
        while(scanf("%d", &aluno.matricula) != 1){ // tem que ter pelo menos um numero
            printf("Matricula deve ter um numero: ");
            while(getchar() != '\n');
        }
        getchar();
    
        // aqui vai checar se matricula ja existe, so a matricula
        if(Jafoi(lista, aluno.matricula)){
            printf("Matricula ja adicionada. Tente outra:\n");
            Repetricula = 0;
        }
    } while(!Repetricula);  

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

int Buscar_aluno(Lista* lista, int matricula){  // 2 no menu
    ListaNo* atual = lista->primeiro;

    while(atual != NULL && atual->aluno.matricula != matricula){
        atual =  atual->proximo;
    }

    if(atual == NULL){ // caso nao exista 
        printf("Matricula: %d nao encontrada.\n", matricula);
        return 1;}
    
    printf("Aluno: %s\n", atual->aluno.nome);
    return 0;
}

void pegar_notas(Lista* lista, fila *fila){
    double notas[3]; 
    double media;
    int matricula;
    printf("Digite a matricula:\n");
    scanf("%d", &matricula);
    if(Buscar_aluno(lista,matricula)) return;

    printf("Digite as notas:\n");
    for(int n=0; n < 3; n++){
        scanf("%lf", &notas[n]);
    }

    media= ((notas[0]*2)+(notas[1]*3)+(notas[2]*5))/10;

    if(media < 5){
        printf("ALuno nao aprovado.\n");
        SaiMLK(lista, fila, matricula);}
    return;
}
