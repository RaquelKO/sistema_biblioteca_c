# sistema_biblioteca_c
Projeto da disciplina de Programação Estruturada da FACENS


- Manter o nome e tipo das variaveis e os membros das estruturas fornecidos pela professora.
- Utilizar: alocação dinâmica, ponteiros para memória e ponteiros para arquivos.

### 1ª etapa - Fazer menu e rotina para:
- Arquivo: alunos.bin e Cadastro de ALUNOS contendo uma estrutura com:
  * nome
  * RA
  * quantidade de livros emprestados (máximo 3)
  * quantidade de livros reservados (máximo 1)
  * tabela 0 (irá conter o status e o nº de registro do 1º livro, se for o caso)
  * tabela 1 (irá conter o status e o nº de registro do 2º livro, se for o caso)
  * tabela 2 (irá conter o status e o nº de registro do 3º livro, se for o caso)
  * tabela 3 (irá conter o status e o nº de registro do 4º livro, se for o caso)
    * as tabelas devem ser struct
    * as tabelas devem ser inicializadas com “L” – livre
<br></br>
- Consulta da situação do aluno – 2 tipos de consulta:
  * Total
    - mostrar o nome, RA e a quantidade de livros emprestados e reservados (se for o caso – mostrar as tabelas)
  * Parcial
    - o acesso deve ser feito através do RA do aluno
    - mostrar o nome e a quantidade de livros emprestados e reservados (se for o caso – mostrar as tabelas) para aquele aluno
<br></br>
- Arquivo: livros.bin e Cadastro de LIVROS contendo uma estrutura com:
  * nº do registro do LIVRO (gerado automaticamente pelo sistema)
  * título
  * autor
  * status irá conter a sigla de status, o RA do aluno, data da retirada e data de devolução (7 dias após retirada), se for o caso<br>
  L – livre<br>
  E – emprestado<br>
  R – reservado (data da retirada – 1 dia após a devolução do livro)<br>
    * status deve ser struct
    * o status deve ser inicializado com “L” – livre
    * cada livro poderá ter apenas 1 empréstimo e 1 reserva
<br></br>
- Consulta de LIVROS:
  * Total
    * mostrar o nº do registro, título, autor e status (se for o caso, mostras as tabelas)
  * Parcial (status)
    * deve-se escolher um determinado STATUS (L, E ou R)
    * mostrar o nº do registro, o autor e status (se for o caso, mostras as tabelas)
  * Parcial (título)
    * a escolha do titulo, deve ser feita pelo usuário
    * mostrar nº do registro, autor e status (se for o caso – mostrar as tabelas)
<br></br>
### 2ª etapa - Fazer menu e rotina para:
- Fazer rotina para empréstimo - reserva:
  * o acesso deve ser feito através do RA
  * verificar se é aluno permitido, isto é, quantidade de empréstimos inferior a 3 ou quantidade de reserva inferior a 1, caso positivo:
<br></br>
    * entrar com o título do livro a ser emprestado/reservado
    * verificar no cadastro de livro:
<br></br>
       >se status L (livre), caso positivo, alterar:
        - cadastro de livro - status do livro para E + RA + data retirada + data devolução
        - cadastro de alunos – alterar quantidade de empréstimo + a tabela para E + nº de registro do livro
<br></br>
      >se status E (emprestado), caso positivo, verificar se livro não tem reserva, caso positivo:
        - cadastro de livro - status do livro para R + RA + data retirada + data devolução
        - cadastro de alunos – alterar quantidade de reserva + a tabela para R + nº de registro do livro
<br></br>
      >se status R (reservado), caso positivo:
        - mensagem de livro já reservado, mostrar RA e data de devolução da reserva
<br></br>
    * mostrar nº do registro, título, autor e status alterado (mostrar as tabelas)
    * mostrar o nome, RA e a quantidade de livros emprestados e reservados (mostrar as tabelas)
<br></br>
### 3ª etapa - Fazer menu e rotina para:
- Fazer rotina para devolução:
  * o acesso deve ser feito através do RA
  * entrar com o título do livro a ser devolvido e a data atual
  * verificar no cadastro de livro se status E e RA confere com o do empréstimo, caso positivo:
  <br></br>
    * verificar a data prevista de devolução e calcular a multa, se for o caso, considerar R$ 3,00 por dia de atraso
    * verificar no cadastro de livro:
<br></br>
       >se há reserva para esse livro, caso positivo:
        - cadastro de livro - fazer a rotina de empréstimo para o aluno cujo RA está reservado, ou seja, a reserva deixa de existir virando empréstimo
        - cadastro de alunos - através do número de registro do livro, alterar a tabela para E
<br></br>
      >caso contrário:
        - cadastro de livro - alterar status do livro para L
        - cadastro de alunos - através do número de registro do livro, alterar a tabela para L
<br></br>
    * mostrar nº do registro, título, autor e status alterado (mostrar as tabelas)
    * mostrar o nome, RA e a quantidade de livros emprestados e reservados (mostrar as tabelas)
