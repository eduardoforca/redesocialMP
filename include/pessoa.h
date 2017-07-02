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
	char* comentarios[1000];	
};

struct transacao{

	Pessoa provedor;
	Pessoa cliente;
	Produto produto;
	int status;
};

struct produto{

	int tipo;
	char descricao[500];
	char nome[50];
	
};

#endif