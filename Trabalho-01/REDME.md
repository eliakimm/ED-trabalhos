# Trabalho 01: Controle de alunos aprovados

Um sistema que calcula a nota de alunos cadastrados e retorna uma fila/pilha com os alunos reprovados.

Caso o aluno seja reprovado na matéria será removido da lista de alunos cadastrados na matéria, caso contrario o aluno mantem seu cadastro na matéria.

## OBJETIVOS:

### 1º Criar um sistema de cadastro para os alunos;

Modelo de entrada:

nome completo + matricula

      caso flag == 0: sua nota não foi lida;

      caso flag == 1: nota lida e aprovado; 

### 2º Percorrer a lista de alunos cadastrados e ler suas notas;

O aluno terá 3 notas (n1, n2, n3), a partir delas será calculado a sua media final: 
      
      ((n1*2)+(n2*3)+(n3*5))/10

## Entradas:

### OPÇÃO 1 (Cadastrar alunos):
Caso o usuário digite a opção 1 (Cadastrar alunos), devera ser digitado o seu nome completo + seu numero de matricula;

### OPÇÃO 2 (Lançar notas):
Caso seja digitado a opção 2 (lançar notas), devera ser digitado 3 decimais(float).

### OPÇÃO 0:
Essa opção encerra o código, e libera a memoria utilizada.

