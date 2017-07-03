#include "redeSocial.h"
#include "grafo.h"
#include "lista.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Pessoa CriarPessoa(char* nome){
	Pessoa p = (Pessoa) malloc(sizeof(pessoa));
	strcpy(p->nome, nome);
	p->amigos = cria_lista();
	p->transacoes = cria_lista();
	p->rating_provedor = p->rating_cliente = 0;
	p->comentarios = cria_lista();
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
Rede CriarRede(){
	Rede r = (Rede) malloc (sizeof(rede));
	r->pessoas = cria_grafo("Pessoas");
	r->transacoes = cria_lista();

	return r;
}
