# Alunos:
Eliakim Pereira da Silva - 231021440
Matheus Nunes Ferreira - 231021511

# Trabalho 01: Controle de alunos aprovados

Um sistema que calcula a nota de alunos cadastrados e retorna uma fila com os alunos reprovados.

Caso o aluno seja reprovado na matéria será removido da lista de alunos cadastrados na matéria, caso contrario o aluno mantem seu cadastro na matéria.

## OBJETIVOS:

### 1º Criar um sistema de cadastro para os alunos;

Modelo de entrada:

nome completo
matricula

      caso flag == 0: sua nota não foi lida;

      caso flag == 1: nota lida e aprovado; 

### 2º Percorrer a lista de alunos cadastrados e ler suas notas;

O aluno terá 3 notas (n1, n2, n3), a partir delas será calculado a sua media final: 
      
      ((n1*2)+(n2*3)+(n3*5))/10

## Entradas:

### OPÇÃO 1 (Cadastrar alunos):
Caso o usuário digite a opção 1 (Cadastrar alunos), devera ser digitado o seu nome completo e seu numero de matricula em linhas diferentes;

### OPÇÃO 2 (Lançar notas):
Caso seja digitado a opção 2 (lançar notas), deverá ser digitado a matricula do aluno que vai receber as notas e ser digitado as 3 notas decimais(float);

### OPÇÃO 3 (Impressão da Turma/Reprovados):
Caso seja digitado a opção 3, havera a impressão da turma, aprovados na parte de cima e reprovados em baixo;

### OPÇÃO 4:
Essa opção encerra o código, e libera a memoria utilizada.

