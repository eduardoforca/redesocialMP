#ifndef _REDESOCIAL_H_
#define _REDESOCIAL_H_

#include "redeSocial.h"
#include "grafo.h"
#include "lista.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct pessoa* Pessoa;
typedef struct transacao* Transacao;
typedef struct produto* Produto;
typedef struct rede* Rede;

struct pessoa{
	int id;
	char nome[50];
	List amigos;
	List conhecidos;//Ja fez transacao
	List transacoes;//Transacoes concluidas
	List notificacoes;//Transacoes que pode prover
	float rating_provedor;
	float rating_cliente;
	List comentarios;	
};


struct transacao{

	int id;
	Pessoa provedor;
	Pessoa cliente;
	Produto produto;
	int status;
	char comentario_cliente[1000];
	char comentario_provedor[1000];
	List ofertas;
};

struct produto{

	int id;
	int tipo;
	char descricao[500];
	char nome[50];
	
};

struct rede{

	Graph pessoas;
	List transacoes;
	List produtos;
	
};

enum tipo_produto
{
	PRODUTO, SERVICO   
};

enum status_transacao
{
	PEDIDA, INICIADA, PENDENTE, CONCLUIDA
	
};
enum conexao
{
	AMIZADE, NEGOCIOS 
};
enum filtros_transacao{
	CATEGORIA, GACLIENTE
};
enum filtros_pessoas{
	GA, PRESTASERVICO, RATING
};
Pessoa CriarPessoa(char* nome, int id);
Produto CriarProduto(char* nome, char* descricao, int tipo, int id);
Transacao CriarTransacao(Pessoa cliente, Produto produto, int id);
Rede CriarRede();
int AdicionarPessoa(Rede rede, Pessoa pessoa);
void AdicionarProduto(Rede rede, Produto produto);
void AdicionarTransacao(Rede rede, Transacao transacao);
int ExcluirPessoa(Rede rede, Pessoa pessoa);
int ExcluirProduto(Rede rede, Produto produto);
int ExcluirTransacao(Rede rede, Transacao transacao);
int DeletaRede(Rede rede);
void AdicionarAmizade(Rede rede, Pessoa pessoa1, Pessoa pessoa2);
int RemoverAmizade(Rede rede, Pessoa pessoa1, Pessoa pessoa2);
void NotificarTransacao(Rede rede, Transacao transacao, int* filtros);
void AceitarTransacao(Rede rede, Transacao transacao);
void AceitarOferta(Rede rede, Transacao oferta, Pessoa pessoa);
void IniciarTransacao(Rede rede, Transacao oferta);
void AvaliarTransacao(Rede rede, Transacao oferta, Pessoa avaliador, char* comentario, int rating);
Transacao* FiltrarTransacao(Rede rede, int* filtros);
Rede RedeFile(char* nomeArquivo);
Produto ProdutoByID(Rede rede, int id);
Transacao TransacaoByID(Rede rede, int id);
Pessoa PessoaByID(Rede rede, int id);
void SalvaRede(Rede rede, char* nomeArquivo);
void WriteTransacao(Transacao t, FILE* fp);
void WritePessoa(Pessoa p, FILE* fp);
void WriteGrafo(Graph g, FILE*fp);
void WriteProduto(Produto p, FILE* fp);
Transacao ReadTransacao(Rede r, FILE* fp);
Pessoa ReadPessoa(FILE* fp);
Graph ReadGrafo(FILE*fp);
Produto ReadProduto(FILE* fp);
void ResolvePessoas(Rede r);
#endif