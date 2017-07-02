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
	p->notificacoes = cria_lista();
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
	t->ofertas = cria_lista();

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
		destroi_lista(transacao->ofertas);
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
void AdicionarAmizade(Rede rede, Pessoa pessoa1, Pessoa pessoa2){
	int grau = AMIZADE;
	adiciona_aresta(rede->pessoas, pessoa1->id, pessoa2->id);
	adiciona_aresta(rede->pessoas, pessoa2->id, pessoa1->id);
	muda_valor_aresta(rede->pessoas, pessoa1->id, pessoa2->id, &grau);
	muda_valor_aresta(rede->pessoas, pessoa2->id, pessoa1->id, &grau);

	adiciona_no(&(pessoa1->amigos), pessoa2);
	adiciona_no(&(pessoa2->amigos), pessoa1);
}
int RemoverAmizade(Rede rede, Pessoa pessoa1, Pessoa pessoa2){
	remove_aresta(rede->pessoas, pessoa1->id, pessoa2->id);
	remove_aresta(rede->pessoas, pessoa2->id, pessoa1->id);

	int flag = TRUE;
	flag&=remove_no_byvalue(&(pessoa1->amigos), pessoa2);
	flag&=remove_no_byvalue(&(pessoa2->amigos), pessoa1);
	return(flag);
}
void NotificarTransacao(Rede rede, Transacao transacao, int* filtros){
	// List pessoas = cria_lista();
	// for(int* i = filtros; i!=NULL && *i!= 0; i++){
	// 	int filtro = *i;
	// 	switch(filtro){
	// 		default:
	// 		break;
	// 	}
	// }
	// for(List pess)
	// adiciona_no(&(p->notificacoes), transacao);

}
void AceitarTransacao(Rede rede, Transacao transacao, Pessoa pessoa){//ENVIA OFERTA

	adiciona_no(&(transacao->ofertas), pessoa);
	remove_no_byvalue(&(pessoa->notificacoes), transacao);

}
void AceitarOferta(Rede rede, Transacao oferta, Pessoa pessoa){
	destroi_lista(oferta->ofertas);
	oferta->provedor = pessoa;
	oferta->status = INICIADA;
}
void ConcluirTransacao(Rede rede, Transacao transacao){
	int grau = NEGOCIOS;
	transacao->status = PENDENTE;
	if(adiciona_aresta(rede->pessoas, transacao->cliente->id, transacao->provedor->id)){
		muda_valor_aresta(rede->pessoas, transacao->cliente->id, transacao->provedor->id, &grau);	
		adiciona_no(&(transacao->cliente->conhecidos), transacao->provedor);
	}

	if(adiciona_aresta(rede->pessoas, transacao->provedor->id, transacao->cliente->id)){		
		muda_valor_aresta(rede->pessoas, transacao->provedor->id, transacao->cliente->id, &grau);
		adiciona_no(&(transacao->provedor->conhecidos), transacao->cliente);
	}
	
}
void AvaliarTransacao(Rede rede, Transacao transacao, Pessoa avaliador, char* comentario, int rating){
	transacao->status = CONCLUIDA;
	if(avaliador == transacao->cliente){
		strcpy(transacao->comentario_cliente, comentario);
		transacao->provedor->rating_provedor += rating; 

	}else{
		strcpy(transacao->comentario_provedor, comentario);
		transacao->provedor->rating_cliente += rating;
	}
}
Transacao* FiltrarTransacao(Rede rede, int* filtros){
	for(int* i = filtros; *i!= 0; i++){
		int filtro = *i;
		switch(filtro){
			default:
			break;
		}
	}
}
Produto ProdutoByID(Rede rede, int id){
	if (rede->produtos == NULL)
		return NULL;

	for (List n = rede->produtos; n != NULL; n = n->next) { //iterates over all vertices
		Produto p = (Produto)n->value;
		if (p->id == id) {
			return p;
		}
	}
	return NULL;
}
Transacao TransacaoByID(Rede rede, int id){
	if (rede->transacoes == NULL)
		return NULL;

	for (List n = rede->transacoes; n != NULL; n = n->next) { //iterates over all vertices
		Transacao p = (Transacao)n->value;
		if (p->id == id) {
			return p;
		}
	}
	return NULL;
}
Pessoa PessoaByID(Rede rede, int id){
	return (Pessoa)retorna_valor_vertice(rede->pessoas, id);

}

Rede RedeFile(char* nome_arquivo){
	FILE* fp = fopen(nome_arquivo,"rb");
	if (fp!=NULL){
	    Rede rede = (Rede)malloc(sizeof(rede));
	    fclose (fp);
  	}
  	return NULL;
}