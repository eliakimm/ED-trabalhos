// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #define TAM_NOME 50

// void pegar_notas(Lista* lista, fila *fila){
//     double notas[3]; 
//     double media;
//     int matricula;
//     printf("Digite a matricula:\n");
//     scanf("%d", &matricula);
//     Buscar_aluno(lista,matricula);

//     printf("Digite as notas:\n");
//     for(int n=0; n < 3; n++){
//         scanf("%lf", &notas[n]);
//     }

//     media= ((notas[0]*2)+(notas[1]*3)+(notas[2]*5))/10;

//     if(media < 5){
//         SaiMLK(lista, fila, matricula);}
//     return;
// }


// // int main(){
// //     double notas[10]; 
// //     double media;
// //     for(int n=0; n < 3; n++){
// //         scanf("%lf", &notas[n]);
// //     }
// //     for(int n=0; n < 3; n++){
// //         printf("Nota %d: %.2lf\n",n, notas[n]);
// //     }
// //     media= ((notas[0]*2)+(notas[1]*3)+(notas[2]*5))/10;
// //     printf("%.2lf", media);
// //     return 0;
// // }