/*Projeto Final (AF) - Programação Estruturada - Projeto Biblioteca

Grupo 5 - Integrantes:
Felipe Victorino Sarubo 200574
Lissa Bruna Urbano 120780
Raquel Kuntz Oliveira 121036

Turma: CP116TIM1*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// -------------------------- Estruturas --------------------------

struct info_livro
{
	char sigla; // [L]ivre, [E]mprestado, [R]eservado
	int reg;	// registro do livro
};

typedef struct aluno
{
	char nome[80];
	char RA[7];
	int emprestado; // qtde de livros emprestados – Max=3
	int reservado;	// qtde de livros reservados – Max =1
	struct info_livro tabela[4];
} aluno;

struct info_aluno
{
	char sigla; // [E]mprestado, [R]eservado
	char RA[7];
	int dia_ret; // dia – máx=31
	int mes_ret; // mes: fev=28 dias
	int dia_dev; // mes: abril=jun=set=nov=30 dias
	int mes_dev; // os demais = 31 dias
};

typedef struct livro
{
	int reg; // gerado automaticamente
	char titulo[80];
	char autor[80];
	struct info_aluno status[2];
} livro;

// -------------------------- Protótipos de Funções --------------------------

void alocaAluno(aluno **p, int tam);
void cadastraAluno(aluno *p);
int leituraAluno(aluno **p);
void adicionaAluno(aluno *p, int tam);
void consultaTotalAluno(aluno *p, int tam);
aluno *consultaIndividual(aluno *p, int tam, char *ra);
void exibeAluno(aluno *p);

void alocaLivro(livro **p, int tam);
void cadastraLivro(livro *p, int qtde);
int leituraLivro(livro **p);
void adicionaLivro(livro *p, int tam);
void consultaTotalLivro(livro *p, int tam);
void consultaStatusLivro(livro *p, int tam);
livro *consultaTituloLivro(livro *p, int tam);
void exibeLivro(livro *p);

void controleLivro(aluno *pA, int tam, livro *pL, int qtde, int *pmaxdiames);
void devolveLivro(aluno *pA, int tam, livro *pL, int qtde, int *pmaxdiames);
void salvarInfoLivro(livro *pLivro, aluno *pAluno, char acao, int *pmaxdiames);
void atualizaArquivos(aluno *pA, int tam, livro *pL, int qtde);
bool validaData(int dia, int mes, int maxdiames);

// -------------------------- Main --------------------------

int main()
{
	int i;
	int *pmaxdiames;
	int maxdiames[12];
	for (i = 0; i < 12; i++)
	{
		if (i == 0 || i == 2 || i == 4 || i == 6 || i == 7 || i == 9 || i == 11)
			maxdiames[i] = 31;
		else if (i == 3 || i == 5 || i == 8 || i == 10)
			maxdiames[i] = 30;
		else if (i == 1)
			maxdiames[i] = 28;
	}
	pmaxdiames = maxdiames;

	int op;
	aluno *p_aluno = NULL;
	livro *p_livro = NULL;

	int tamAluno = leituraAluno(&p_aluno);
	int tamLivro = leituraLivro(&p_livro);

	do
	{
		system("cls");
		printf("\n-----Sistema Biblioteca-----\n\nSelecione uma opcao no menu abaixo.");

		printf("\n\nALUNOS:\n[1] Cadastrar\n[2] Consulta Total\n[3] Consulta Individual");

		printf("\n\nLIVROS:\n[4] Cadastrar\n[5] Consulta Total\n[6] Consulta por Status");
		printf("\n[7] Consulta por Titulo");

		printf("\n\nCONTROLE:\n[8] Emprestimo\n[9] Devolucao");
		printf("\n\n----------------------\n\n[0] Sair\n\nOpcao: ");

		scanf("%i", &op);
		fflush(stdin);

		switch (op)
		{
		case 1:
			alocaAluno(&p_aluno, tamAluno + 1);
			cadastraAluno(p_aluno + tamAluno);
			adicionaAluno(p_aluno + tamAluno, 1);
			tamAluno++;
			printf("\nAluno cadastrado com sucesso!");
			printf("\n\n");
			system("pause");
			break;
		case 2:
			consultaTotalAluno(p_aluno, tamAluno);
			break;
		case 3:
			consultaIndividual(p_aluno, tamAluno, NULL);
			break;
		case 4:
			alocaLivro(&p_livro, tamLivro + 1);
			cadastraLivro(p_livro + tamLivro, tamLivro + 1);
			adicionaLivro(p_livro + tamLivro, 1);
			tamLivro++;
			printf("\nLivro cadastrado com sucesso!");
			printf("\n\n");
			system("pause");
			break;
		case 5:
			consultaTotalLivro(p_livro, tamLivro);
			break;
		case 6:
			consultaStatusLivro(p_livro, tamLivro);
			break;
		case 7:
			consultaTituloLivro(p_livro, tamLivro);
			break;
		case 8:
			controleLivro(p_aluno, tamAluno, p_livro, tamLivro, pmaxdiames);
			atualizaArquivos(p_aluno, tamAluno, p_livro, tamLivro);
			break;
		case 9:
			devolveLivro(p_aluno, tamAluno, p_livro, tamLivro, pmaxdiames);
			atualizaArquivos(p_aluno, tamAluno, p_livro, tamLivro);
			break;
		}
	} while (op >= 1 && op <= 9);
	return 0;
}

// -------------------------- Funções Aluno --------------------------

void alocaAluno(aluno **p, int tam)
{
	if ((*p = (aluno *)realloc(*p, tam * sizeof(aluno))) == NULL)
	{
		printf("\nErro na alocacao. O programa sera encerrado!");
		exit(1);
	}
}

void cadastraAluno(aluno *p)
{
	int i;
	printf("\nNome: ");
	gets(p->nome);
	printf("\nRA: ");
	gets(p->RA);

	for (i = 0; i < 4; i++)
	{
		(p->tabela + i)->sigla = 'L';
		(p->tabela + i)->reg = 000;
	}

	p->emprestado = 0;
	p->reservado = 0;
}

int leituraAluno(aluno **p)
{
	FILE *arquivo = NULL;
	int cont;
	if ((arquivo = fopen("aluno.bin", "rb")) == NULL)
	{
		printf("\nNao ha registros de alunos cadastrados.\n");
		return 0;
	}
	else
	{
		fseek(arquivo, 0, 2);
		cont = ftell(arquivo) / sizeof(aluno);
		alocaAluno(p, cont);
		rewind(arquivo);
		fread(*p, sizeof(aluno), cont, arquivo);
		fclose(arquivo);
		return cont;
	}
}

void adicionaAluno(aluno *p, int tam)
{
	FILE *f = NULL;
	if ((f = fopen("aluno.bin", "ab")) == NULL)
		printf("\nErro ao salvar aluno!");
	else
		fwrite(p, sizeof(aluno), tam, f);
	fclose(f);
}

void consultaTotalAluno(aluno *p, int tam)
{
	int i;
	printf("\nAlunos Cadastrados:\n");
	if (tam == 0)
		printf("\nNao ha registros de alunos cadastrados.");
	else
		for (i = 0; i < tam; i++, p++)
		{
			exibeAluno(p);
			printf("\n");
		}
	printf("\n\n");
	system("pause");
}

aluno *consultaIndividual(aluno *p, int tam, char *ra)
{
	int i;
	char RA_consultado[7];

	if (ra == NULL)
	{
		printf("\nDigite o RA do aluno: ");
		gets(RA_consultado);
	}
	else
	{
		strcpy(RA_consultado, ra);
	}

	for (i = 0; i < tam; i++, p++)
	{
		if (strcmp(RA_consultado, p->RA) == 0)
		{
			exibeAluno(p);
			printf("\n\n");
			system("pause");
			return p;
		}
	}

	printf("\nAluno nao encontrado!");
	printf("\n\n");
	system("pause");
	return NULL;
}

void exibeAluno(aluno *p)
{
	int i;
	printf("\nNome: %s\tRA: %s\tEmp: %i\tRes: %i", p->nome, p->RA, p->emprestado, p->reservado);
	for (i = 0; i < 4; i++)
		printf("\nTabela %i: %c - %i", i, (p->tabela + i)->sigla, (p->tabela + i)->reg);
}

// -------------------------- Funções Livro --------------------------

void alocaLivro(livro **p, int tam)
{
	if ((*p = (livro *)realloc(*p, tam * sizeof(livro))) == NULL)
	{
		printf("\nErro na alocacao. O programa sera encerrado!");
		exit(1);
	}
}

void cadastraLivro(livro *p, int qtde)
{
	int i;
	printf("\nRegistro: %03d", qtde);
	p->reg = qtde;
	printf("\n\nTitulo: ");
	gets(p->titulo);
	printf("\nAutor: ");
	gets(p->autor);

	for (i = 0; i < 2; i++)
	{
		(p->status + i)->sigla = 'L';
		strcpy((p->status + i)->RA, "000000");
		(p->status + i)->dia_ret = 00;
		(p->status + i)->mes_ret = 00;
		(p->status + i)->dia_dev = 00;
		(p->status + i)->mes_dev = 00;
	}
}

int leituraLivro(livro **p)
{
	FILE *arquivo = NULL;
	int cont;
	if ((arquivo = fopen("livro.bin", "rb")) == NULL)
	{
		printf("\nNao ha registros de livros cadastrados.\n");
		return 0;
	}
	else
	{
		fseek(arquivo, 0, 2);
		cont = ftell(arquivo) / sizeof(livro);
		alocaLivro(p, cont);
		rewind(arquivo);
		fread(*p, sizeof(livro), cont, arquivo);
		fclose(arquivo);
		return cont;
	}
}

void adicionaLivro(livro *p, int tam)
{
	FILE *f = NULL;
	if ((f = fopen("livro.bin", "ab")) == NULL)
		printf("\nErro ao salvar livro!");
	else
		fwrite(p, sizeof(livro), tam, f);
	fclose(f);
}

void consultaTotalLivro(livro *p, int tam)
{
	int i;
	printf("\nLivros Cadastrados:\n");
	if (tam == 0)
		printf("\nNao ha registros de livros cadastrados.");
	else
		for (i = 0; i < tam; i++, p++)
		{
			exibeLivro(p);
			printf("\n");
		}

	printf("\n\n");
	system("pause");
}

void consultaStatusLivro(livro *p, int tam)
{
	int i, encontrou = 0;
	char statusConsultado;
	printf("\nDigite o status que deseja consultar: ");
	scanf("%c", &statusConsultado);

	for (i = 0; i < tam; i++, p++)
	{
		if (toupper(statusConsultado) == toupper((p->status)->sigla) || toupper(statusConsultado) == toupper((p->status + 1)->sigla))
		{
			exibeLivro(p);
			printf("\n");
			encontrou = 1;
		}
	}

	if (encontrou == 0)
		printf("\nNao existem livros com esse status!");

	printf("\n\n");
	system("pause");
}

livro *consultaTituloLivro(livro *p, int tam)
{
	int i;
	char tituloConsultado[80], tituloProcurado[80];
	printf("\nDigite o titulo do livro: ");
	gets(tituloConsultado);

	for (i = 0; i < tam; i++, p++)
	{
		strcpy(tituloProcurado, p->titulo);
		strupr(tituloProcurado);

		if (strcmp(strupr(tituloConsultado), tituloProcurado) == 0)
		{
			exibeLivro(p);
			printf("\n\n");
			system("pause");
			return p;
		}
	}

	printf("\nLivro nao encontrado!");
	printf("\n\n");
	system("pause");
	return NULL;
}

void exibeLivro(livro *p)
{
	printf("\nRegistro: %03d\t Titulo: %s\t Autor: %s", p->reg, p->titulo, p->autor);
	printf("\nStatus 0: %c, %s - Retirada:%02d/%02d, Devolucao:%02d/%02d", (p->status)->sigla, (p->status)->RA, (p->status)->dia_ret, (p->status)->mes_ret, (p->status)->dia_dev, (p->status)->mes_dev);
	printf("\nStatus 1: %c, %s - Retirada:%02d/%02d, Devolucao:%02d/%02d", (p->status + 1)->sigla, (p->status + 1)->RA, (p->status + 1)->dia_ret, (p->status + 1)->mes_ret, (p->status + 1)->dia_dev, (p->status + 1)->mes_dev);
}

// -------------------------- Funções Controle --------------------------

void controleLivro(aluno *pA, int tam, livro *pL, int qtde, int *pmaxdiames)
{
	aluno *pAluno = NULL;
	livro *pLivro = NULL;

	pAluno = consultaIndividual(pA, tam, NULL);
	if (pAluno == NULL)
	{
		return;
	}

	if (pAluno->emprestado == 3 && pAluno->reservado == 1)
	{
		printf("\nNao foi possivel completar a solicitacao. O aluno ja atingiu o limite maximo de emprestimos e reservas permitidos.");
		printf("\n\n");
		system("pause");
		return;
	}

	pLivro = consultaTituloLivro(pL, qtde);
	if (pLivro == NULL)
	{
		return;
	}

	if ((pLivro->status + 0)->sigla == 'E' && (pLivro->status + 1)->sigla == 'R')
	{
		printf("\nNao \x82 possivel emprestar/reservar este livro no momento. Livro reservado por %s. Data de Devolucao: %02d/%02d", (pLivro->status + 1)->RA, (pLivro->status + 1)->dia_dev, (pLivro->status + 1)->mes_dev);
		printf("\n\n");
		system("pause");
		return;
	}

	if (pAluno->emprestado == 3 && pAluno->reservado < 1 && (pLivro->status + 0)->sigla == 'L')
	{
		printf("\nLivro disponivel para emprestimo, porem o aluno se encontra com quantidade maxima de emprestimos permitidos.");
		printf("\n\n");
		system("pause");
		return;
	}

	if ((pLivro->status + 0)->sigla == 'L')
	{
		pAluno->emprestado++;
		salvarInfoLivro(pLivro, pAluno, 'E', pmaxdiames);
	}
	else if ((pLivro->status + 1)->sigla == 'L')
	{
		pAluno->reservado++;
		salvarInfoLivro(pLivro, pAluno, 'R', pmaxdiames);
	}
}

void devolveLivro(aluno *pA, int tam, livro *pL, int qtde, int *pmaxdiames)
{
	int i, diaAtual, mesAtual, diasAtraso = 0, dia = 0, mes = 0;
	float multa = 0.0;
	bool validou = false;
	char RA_reservado[7];
	aluno *pAluno = NULL, *pAlunoNovo = NULL;
	livro *pLivro = NULL;

	pAluno = consultaIndividual(pA, tam, NULL);
	if (pAluno == NULL)
	{
		return;
	}

	pLivro = consultaTituloLivro(pL, qtde);
	if (pLivro == NULL)
	{
		return;
	}

	do
	{ //obs: seria legal validar se a data digitada é maior que a data de retirada
		printf("\nPor favor, informe a data de hoje (dd/mm): ");
		scanf("%d/%d", &diaAtual, &mesAtual);
		if (validaData(diaAtual, mesAtual, *(pmaxdiames + mesAtual - 1)))
			validou = true;
	} while (!validou);

	if ((pLivro->status)->sigla == 'E' && strcmp((pLivro->status)->RA, pAluno->RA) == 0)
	{
		pAluno->emprestado--;
		for (i = 0; i < 4; i++)
		{
			if ((pAluno->tabela + i)->reg == pLivro->reg)
			{
				(pAluno->tabela + i)->sigla = 'L';
				(pAluno->tabela + i)->reg = 000;
			}
		}

		dia = (pLivro->status)->dia_ret;
		mes = (pLivro->status)->mes_ret;

		while (dia != diaAtual || mes != mesAtual)
		{
			if ((dia + 1) > *(pmaxdiames + mes - 1))
			{
				dia = 1;
				if (mes < 12)
					mes++;
				else
					mes = 1;
			}
			else
			{
				dia++;
			}

			diasAtraso++;
		}

		multa = (diasAtraso - 7 <= 0) ? 0 : (diasAtraso - 7) * 3.00;
		if (multa > 0)
		{
			printf("\nDevolucao com atraso. Cobrar multa de R$ %.2f.", multa);
			printf("\n\n");
			system("pause");
		}

		if ((pLivro->status + 1)->sigla == 'L')
		{
			(pLivro->status)->sigla = 'L';
			strcpy((pLivro->status)->RA, "000000");
			(pLivro->status)->dia_ret = 00;
			(pLivro->status)->mes_ret = 00;
			(pLivro->status)->dia_dev = 00;
			(pLivro->status)->mes_dev = 00;
		}

		if ((pLivro->status + 1)->sigla == 'R')
		{
			printf("\nLivro reservado por: ");
			pAlunoNovo = consultaIndividual(pA, tam, (pLivro->status + 1)->RA);
			if (pAlunoNovo == NULL)
			{
				return;
			}

			(pLivro->status + 1)->sigla = 'L';
			strcpy((pLivro->status + 1)->RA, "000000");
			(pLivro->status + 1)->dia_ret = 00;
			(pLivro->status + 1)->mes_ret = 00;
			(pLivro->status + 1)->dia_dev = 00;
			(pLivro->status + 1)->mes_dev = 00;

			if (pAlunoNovo->emprestado == 3)
			{
				(pLivro->status)->sigla = 'L';
				strcpy((pLivro->status)->RA, "000000");
				(pLivro->status)->dia_ret = 00;
				(pLivro->status)->mes_ret = 00;
				(pLivro->status)->dia_dev = 00;
				(pLivro->status)->mes_dev = 00;
				printf("\nO livro estava reservado para um aluno que atingiu o limite de emprestimos, portanto o livro foi liberado.");
			}
			else
			{
				pAlunoNovo->reservado--;
				pAlunoNovo->emprestado++;
				for (i = 0; i < 4; i++)
				{
					if ((pAlunoNovo->tabela + i)->reg == pLivro->reg)
					{
						(pAlunoNovo->tabela + i)->sigla = 'E';
					}
				}
				(pLivro->status)->sigla = 'E';
				strcpy((pLivro->status)->RA, pAlunoNovo->RA);
				(pLivro->status)->dia_ret = diaAtual;
				(pLivro->status)->mes_ret = mesAtual;

				if ((diaAtual + 7) > *(pmaxdiames + mesAtual - 1))
				{
					(pLivro->status)->dia_dev = (diaAtual) + 7 - *(pmaxdiames + mesAtual - 1);
					if (mesAtual < 12)
						(pLivro->status)->mes_dev = mesAtual + 1;
					else
						(pLivro->status)->mes_dev = 1;
				}
				else
				{
					(pLivro->status)->dia_dev = (diaAtual + 7);
					(pLivro->status)->mes_dev = mesAtual;
				}

				printf("\n\nEmprestimo realizado com sucesso! Informacoes do aluno:\n");
				exibeAluno(pAlunoNovo);
			}
		}
	}
	else
	{
		printf("\nInformacoes incompativeis com o sistema, nao foi possivel prosseguir com a devolucao.");
		printf("\n\n");
		system("pause");
		return;
	}

	printf("\n\nDevolucao realizada com sucesso! Informacoes do aluno:\n");
	exibeAluno(pAluno);
	printf("\n\nInformacoes do Livro:\n");
	exibeLivro(pLivro);
	printf("\n\n");
	system("pause");
}

void salvarInfoLivro(livro *pLivro, aluno *pAluno, char acao, int *pmaxdiames)
{
	int i, alterou = 0, diaR, mesR;
	bool validou = false;
	struct info_aluno *info = pLivro->status;

	if (acao == 'R')
	{
		info = pLivro->status + 1;
	}

	info->sigla = acao;
	strcpy(info->RA, pAluno->RA);

	do
	{
		printf("\nPor favor, informe a data de hoje (dd/mm): ");
		scanf("%d/%d", &diaR, &mesR);
		if (validaData(diaR, mesR, *(pmaxdiames + mesR - 1)))
		{
			info->dia_ret = diaR;
			info->mes_ret = mesR;

			if ((info->dia_ret + 7) > *(pmaxdiames + info->mes_ret - 1))
			{
				info->dia_dev = (info->dia_ret) + 7 - *(pmaxdiames + info->mes_ret - 1);
				if (info->mes_ret < 12)
					info->mes_dev = info->mes_ret + 1;
				else
					info->mes_dev = 1;
			}
			else
			{
				info->dia_dev = (info->dia_ret + 7);
				info->mes_dev = info->mes_ret;
			}
			validou = true;
		}
	} while (!validou);

	for (i = 0; (i < 4) && (alterou == 0); i++)
		if ((pAluno->tabela + i)->sigla == 'L')
		{
			(pAluno->tabela + i)->sigla = acao;
			(pAluno->tabela + i)->reg = pLivro->reg;
			alterou = 1;
		}

	printf("\n\nEmprestimo/Reserva realizado com sucesso! Informacoes:\n");
	exibeLivro(pLivro);
	exibeAluno(pAluno);
	printf("\n\n");
	system("pause");
}

void atualizaArquivos(aluno *pA, int tam, livro *pL, int qtde)
{
	FILE *f = NULL;

	if ((f = fopen("aluno.bin", "wb+")) == NULL)
		printf("\nErro ao atualizar aluno!");
	else
		fwrite(pA, sizeof(aluno), tam, f);
	fclose(f);

	if ((f = fopen("livro.bin", "wb+")) == NULL)
		printf("\nErro ao atualizar livro!");
	else
		fwrite(pL, sizeof(livro), qtde, f);
	fclose(f);
}

bool validaData(int dia, int mes, int maxdiames)
{
	if (mes > 0 && mes <= 12)
	{
		if (dia > 0 && dia <= maxdiames)
			return true;
	}
	return false;
}