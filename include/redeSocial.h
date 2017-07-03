#ifndef _REDESOCIAL_H_
#define _REDESOCIAL_H_

#include "grafo.h"
#include "lista.h"

typedef struct pessoa* Pessoa;
typedef struct transacao* Transacao;
typedef struct produto* Produto;
typedef struct rede* Rede;

struct pessoa{
	char nome[50];
	List amigos;
	List transacoes;
	List notificacoes;
	float rating_provedor;
	float rating_cliente;
	List comentarios;	
};

struct transacao{

	Pessoa provedor;
	Pessoa cliente;
	Produto produto;
	int status;
	char comentario_cliente[1000];
	char comentario_provedor[1000];
};

struct produto{

	int tipo;
	char descricao[500];
	char nome[50];
	
};

struct rede{

	Graph pessoas;
	List transacoes;
	
};

enum tipo_produto
{
	PRODUTO, SERVICO   
};

enum status_transacao
{
	PEDIDA, INICIADA, CONCLUIDA
	
};

Pessoa CriarPessoa(char* nome);
Produto CriarProduto(char* nome, char* descricao, int tipo);
Transacao CriarTransacao(Pessoa provedor, Produto produto);
Rede CriarRede();

#endif