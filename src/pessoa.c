#include "pessoa.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Pessoa CriarPessoa(char* nome){
	Pessoa p = (Pessoa) malloc(sizeof(pessoa));
	strcpy(p->nome, nome);
	p->amigos = (Pessoa*) malloc(sizeof(Pessoa));
	p->transacoes = (Transacao*) malloc(sizeof(Transacao));
	p->rating_provedor = p->rating_cliente = 0;
	return p;
}
Produto CriarProduto(char* nome, char* descricao, int tipo){
	Produto p = (Produto) malloc(sizeof(produto));
	strcpy(p->nome, nome);
	strcpy(p->descricao, descricao);
	p->tipo = tipo;

	return p;
}
Transacao CriarTransacao(Pessoa provedor, Produto produto){
	Transacao t = (Transacao) malloc(sizeof(transacao));
	t->provedor = provedor;
	t->produto = produto;
	t->cliente = NULL;
	t->status = PEDIDA;

	return t;
}