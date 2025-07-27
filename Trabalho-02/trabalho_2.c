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
    Raiz* arvore_notas = criar_arvore();

    do{
        system("clear || cls");
        printf("\n|===============================|\n"); // 33
        printf("|         MENU PRINCIPAL        |");
        printf("\n|===============================|\n");
        printf("|   [1] -> Adicionar aluno      |\n");
        printf("|   [2] -> Remover aluno        |\n");
        printf("|   [3] -> Imprimir Turma       |\n");
        wprintf(L"|   [4] -> Lançar notas         |\n");
        printf("|   [5] -> Imprimir notas       |\n");
        printf("|   [0] -> Sair                 |\n");
        printf("|===============================|\n");
        printf("Escolha: ");

        while(scanf("%d", &escolha) != 1){
            wprintf(L"Entrada inválida. Digite um número entre 0-5: ");  // L permite impressao especial
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
                removerAluno(arvore, arvore_notas);
                break;
            }
            case 3:{
                system("clear || cls");
                if(contarNo(arvore) == 0) {
                    wprintf(L"Nao ha alunos cadastrados.\n");
                    system("pause");
                    break;
                }
                cabecalho(arvore);
                system("pause");
                break;
            }
            case 4:{
                system("clear || cls");
                pegar_notas(arvore, arvore_notas);
                break;
            }
            case 5:{
                system("clear || cls");
                if(contarNo(arvore_notas) == 0) {
                    wprintf(L"Nao ha alunos com notas cadastradas.\n");
                    system("pause");
                    break;
                }
                printf("Alunos com notas: %02d\n", contarNo(arvore_notas));
                printf("|===============================|\n");
                wprintf(L"|NOME            |     NOTA     |\n");
                printf("|===============================|\n");
                emOrdem_decrescente(arvore_notas);
                printf("|===============================|\n");
                system("pause");
                break;
            }
            case 0:{
                system("clear || cls");
                liberaArvore(arvore);
                liberaArvore(arvore_notas);
                printf("Tchau...\n");
                break;
            }
            default:{
                system("clear || cls");
                wprintf(L"Ainda não temos essa opção.\n");
                system("pause");
            }
        }
    } while(escolha != 0);

    system("clear || cls");
    return 0;
}
