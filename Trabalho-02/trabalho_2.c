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
     // essas coisas estranhas servem para mudar a localidade:
    puts (setlocale(LC_ALL, "Portuguese"));
    system("chcp 1252");  // muda para Windows 1252 que aceita acentos
    
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
            wprintf(L"Entrada inválida. 1-4: ");  // L permite impressao especial
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
                wprintf(L"NOME | MATRÍCULA\n");
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
                wprintf(L"Ainda não temos essa opção.\n");
                system("pause");
            }
        }
    } while(escolha != 4);

    system("clear || cls");
    return 0;
}
