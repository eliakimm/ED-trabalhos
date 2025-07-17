#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "arvoreBin.h"
#define tam 100

int main() {
    setlocale(LC_ALL, "");
    int escolha;
    Raiz* arvore = criar_arvore();

    do{
        system("clear || cls");
        printf("\n----- MENU -----\n");
        printf("[1] -> Adicionar aluno\n");
        printf("[2] -> Remover aluno\n");
        printf("[3] -> Imprimir Turma\n");
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
                system("clear || cls");
                cadastrarAluno(arvore);
                break;
            }
            case 2:{
                system("clear || cls");
                removerAluno(arvore);
                break;
            }
            case 3:{
                system("clear || cls");
                printf("NOME | MATRICULA\n");
                emOrdem(arvore);
                system("pause");
                break;
            }
            case 4:{
                system("clear || cls");
                liberaArvore(arvore);
                printf("Tchau...\n");
                break;
            }
            default:{
                system("clear || cls");
                printf("Ainda nao temos essa opcao.\n");
                system("pause");
            }
        }
    } while(escolha != 4);

    system("clear || cls");
    return 0;
}
