#include "redeSocial.h"
#include "grafo.h"
#include "lista.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

Pessoa CriarPessoa(char* nome, int id){
	Pessoa p = (Pessoa) malloc(sizeof(pessoa));
	strcpy(p->nome, nome);
	p->amigos = cria_lista();
	p->conhecidos = cria_lista();
	p->transacoes = cria_lista();
	p->rating_provedor = p->rating_cliente = 0;
	p->comentarios = cria_lista();
	p->id = id;
	return p;
}
Produto CriarProduto(char* nome, char* descricao, int tipo, int id){
	Produto p = (Produto) malloc(sizeof(produto));
	strcpy(p->nome, nome);
	strcpy(p->descricao, descricao);
	p->tipo = tipo;
	p->id = id;

	return p;
}
Transacao CriarTransacao(Pessoa cliente, Produto produto, int id){
	Transacao t = (Transacao) malloc(sizeof(transacao));
	t->cliente = cliente;
	t->produto = produto;
	t->provedor = NULL;
	t->status = PEDIDA;
	t->id = id;

	return t;
}
Rede CriarRede(){
	Rede r = (Rede) malloc (sizeof(rede));
	r->pessoas = cria_grafo("Pessoas");
	r->transacoes = cria_lista();
	r->produtos = cria_lista();

	return r;
}
int AdicionarPessoa(Rede rede, Pessoa pessoa){

	if(adiciona_vertice(rede->pessoas, pessoa->id)){
		muda_valor_vertice(rede->pessoas, pessoa->id, pessoa);
		return TRUE;
	}
	return FALSE;

}
void AdicionarProduto(Rede rede, Produto produto){
	rede->produtos = adiciona_no(&(rede->produtos), produto); 

}
void AdicionarTransacao(Rede rede, Transacao transacao){
	rede->transacoes = adiciona_no(&(rede->transacoes), transacao); 

}
int ExcluirPessoa(Rede rede, Pessoa pessoa){

	if (remove_vertice(rede->pessoas, pessoa->id)){
		destroi_lista(pessoa->amigos);
		destroi_lista(pessoa->conhecidos);
		destroi_lista(pessoa->comentarios);
		free(pessoa);
		return TRUE;
	}
	return FALSE;

}
int ExcluirProduto(Rede rede, Produto produto){
	if(remove_no_byvalue(&(rede->produtos), produto)){
		free(produto);
		return TRUE;
	}
	return FALSE;
}
int ExcluirTransacao(Rede rede,Transacao transacao){
	if(remove_no_byvalue(&(rede->transacoes), transacao)){
		free(transacao);
		return TRUE;
	}
	return FALSE;
}
int DeletaRede(Rede rede){
	int flag;
	destroi_lista(rede->produtos);
	destroi_lista(rede->transacoes);

	flag = destroi_grafo(rede->pessoas);

	free(rede);

	return flag;
}
