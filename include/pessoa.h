#ifndef _PESSOA_H_
#define _PESSOA_H_
typedef struct pessoa* Pessoa;
typedef struct transacao* Transacao;
typedef struct produto* Produto;

struct pessoa{
	char nome[50];
	Pessoa* amigos;
	Transacao* transacoes;
	Transacao* notificacoes;
	float rating_provedor;
	float rating_cliente;	
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
#endif