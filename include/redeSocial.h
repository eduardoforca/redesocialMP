#ifndef _REDESOCIAL_H_
#define _REDESOCIAL_H_

#include "grafo.h"
#include "lista.h"

typedef struct pessoa* Pessoa;
typedef struct transacao* Transacao;
typedef struct produto* Produto;
typedef struct rede* Rede;

struct pessoa{
	int id;
	char nome[50];
	List amigos;
	List conhecidos;//Ja fez transacao
	List transacoes;
	List notificacoes;
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
	PEDIDA, INICIADA, CONCLUIDA
	
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

#endif