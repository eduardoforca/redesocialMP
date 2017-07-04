#include "redeSocial.h"
#include "grafo.h"
#include "lista.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
/*
*Função para criar uma instância de Pessoa
*A Função recebe nome e a id
*inicializa variáveis da estrutura Pessoa
*Retorna ponteiro Pessoa p
*/
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
/*
*Função para criar uma instância de Produto
*A Função recebe nome, descrição, tipo(servico ou produto) e id
*inicializa variáveis da estrutura Produto
*Retorna ponteiro Produto p
*/
Produto CriarProduto(char* nome, char* descricao, int tipo, int id){
	Produto p = (Produto) malloc(sizeof(produto));
	strcpy(p->nome, nome);
	strcpy(p->descricao, descricao);
	p->tipo = tipo;
	p->id = id;

	return p;
}

/*
*Função para criar uma instância de Transacao
*A Função recebe a Pessoa cliente que está requisitando um serviço ou produto, o Produto, e a id da transação
*inicializa variáveis da estrutura Transação
*Retorna ponteiro Transação t
*/
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
/*
*Função para criar a rede social
*Não recebe parâmetros
*Inicializa as variaveis da estrutura rede
*Retorna a rede r vazia
*/
Rede CriarRede(){
	Rede r = (Rede) malloc (sizeof(rede));
	r->pessoas = cria_grafo("Pessoas");
	r->transacoes = cria_lista();
	r->produtos = cria_lista();

	return r;
}
/*
*Função para adicionar uma pessoa a Rede
*recebe rede e pessoa
*insere a pessoa no grafo
*retorna validação da inserção
*/
int AdicionarPessoa(Rede rede, Pessoa pessoa){

	if(adiciona_vertice(rede->pessoas, pessoa->id)){
		muda_valor_vertice(rede->pessoas, pessoa->id, pessoa);
		return TRUE;
	}
	return FALSE;

}
/*
*Função para adicionar produto na rede
*recebe rede e produto
*sem retorno
*/
void AdicionarProduto(Rede rede, Produto produto){
	rede->produtos = adiciona_no(&(rede->produtos), produto); 

}
/*
*Função para adicionar transacao na rede
*recebe rede e transacao
*sem retorno
*/
void AdicionarTransacao(Rede rede, Transacao transacao){
	rede->transacoes = adiciona_no(&(rede->transacoes), transacao); 

}
/*
*Função para excluir pessoa da rede
*recebe rede e pessoa
*retorna a validação da exclusão
*/
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
/*
*Função para excluir produto da rede
*recebe rede e produto
*retorna a validação da exclusão
*/
int ExcluirProduto(Rede rede, Produto produto){
	if(remove_no_byvalue(&(rede->produtos), produto)){
		free(produto);
		return TRUE;
	}
	return FALSE;
}
/*
*Função para excluir transacao da rede
*recebe rede e transacao
*retorna a validação da exclusão
*/
int ExcluirTransacao(Rede rede,Transacao transacao){
	if(remove_no_byvalue(&(rede->transacoes), transacao)){
		destroi_lista(transacao->ofertas);
		free(transacao);
		return TRUE;
	}
	return FALSE;
}
/*
*Função para deletar a rede
*recebe rede
*remove a rede da memoria
*retorna a validação da exclusão
*/
int DeletaRede(Rede rede){
	int flag;
	destroi_lista(rede->produtos);
	destroi_lista(rede->transacoes);

	flag = destroi_grafo(rede->pessoas);

	free(rede);

	return flag;
}
/*
*Função para adicionar amizades
*recebe rede e as duas pessoas que serão amigas
*adiciona uma aresta entre as duas pessoas 
*sem retorno
*/
void AdicionarAmizade(Rede rede, Pessoa pessoa1, Pessoa pessoa2){
	int grau = AMIZADE;
	adiciona_aresta(rede->pessoas, pessoa1->id, pessoa2->id);
	adiciona_aresta(rede->pessoas, pessoa2->id, pessoa1->id);
	muda_valor_aresta(rede->pessoas, pessoa1->id, pessoa2->id, &grau);
	muda_valor_aresta(rede->pessoas, pessoa2->id, pessoa1->id, &grau);

	adiciona_no(&(pessoa1->amigos), pessoa2);
	adiciona_no(&(pessoa2->amigos), pessoa1);
}
/*
*Função para remover amizades
*recebe rede e as duas pessoas que serão amigas
*remove a aresta entre as duas pessoas 
*retorna validação da remoção
*/
int RemoverAmizade(Rede rede, Pessoa pessoa1, Pessoa pessoa2){
	remove_aresta(rede->pessoas, pessoa1->id, pessoa2->id);
	remove_aresta(rede->pessoas, pessoa2->id, pessoa1->id);

	int flag = TRUE;
	flag&=remove_no_byvalue(&(pessoa1->amigos), pessoa2);
	flag&=remove_no_byvalue(&(pessoa2->amigos), pessoa1);
	return(flag);
}
/*
*Função para notificar transações
*recebe rede, transacao e filtro
*notifica todos usuários que passarem no filtro da transação
*sem retorno
*/
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
/*
*Função para aceitar transações
*recebe rede, transacao e pessoa
*a pessoa aceita a transacao envia uma oferta para o cliente
*sem retorno
*/
void AceitarTransacao(Rede rede, Transacao transacao, Pessoa pessoa){//ENVIA OFERTA

	adiciona_no(&(transacao->ofertas), pessoa);
	remove_no_byvalue(&(pessoa->notificacoes), transacao);

}
/*
*Função para aceitar oferta
*recebe rede, oferta e pessoa
*o cliente aceita a oferta
*inicializa a transação
*sem retorno
*/
void AceitarOferta(Rede rede, Transacao oferta, Pessoa pessoa){
	destroi_lista(oferta->ofertas);
	oferta->provedor = pessoa;
	oferta->status = INICIADA;
}
/*
*Função para concluir transacao
*recebe rede e transacao
*adiciona uma aresta entre as pessoas envolvidas na transacao
*sem retorno
*/
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
/*
*Função para avaliar transacao
*recebe rede, transacao, avaliador, comentario e rating (avaliacao em pontos)
*grava comentário e calcula o rating
*sem retorno
*/
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
/*
*Função para filtrar transacoes
*recebe rede e filtros
*filtra as transacoes da rede
*lista transacoes filtradas
*/
Transacao* FiltrarTransacao(Rede rede, int* filtros){
	for(int* i = filtros; *i!= 0; i++){
		int filtro = *i;
		switch(filtro){
			default:
			break;
		}
	}
}
/*
*Função para retornar produto por ID
*recebe rede e id de produto
*percorre lista de produtos
*retorna um produto
*/
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
/*
*Função para retornar transacao por ID
*recebe rede e id de transacao
*percorre lista de transacoes
*retorna uma transacao
*/
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
	    
	    rede->pessoas = ReadGrafo(fp);

	    int tam;
   		fread(&tam, sizeof(int), 1, fp);
   		List list = cria_lista();
   		for (int i = 0; i < tam; i++) { 
			Produto p = ReadProduto(fp);
			adiciona_no(&list, p);
		}
		rede->produtos = list;

		fread(&tam, sizeof(int), 1, fp);
   		list = cria_lista();
   		for (int i = 0; i < tam; i++) { 
			Transacao t = ReadTransacao(rede, fp);
			adiciona_no(&list, t);
		}
		rede->transacoes = list;

		ResolvePessoas(rede);

	    fclose (fp);
	    return rede;
  	}
  	return NULL;
}
void SalvaRede(Rede rede, char* nomeArquivo){

	FILE* fp = fopen(nomeArquivo,"w+b");
	if (fp!=NULL){
	   	
	   	WriteGrafo(rede->pessoas, fp);
	   	int tam = tamanho_list(rede->produtos);
	   	fwrite(&tam, sizeof(int), 1, fp);
	   	for (List n = rede->produtos; n != NULL; n = n->next) { //iterates over all vertices
			Produto p = (Produto)n->value;
			WriteProduto(p, fp);
		}

	   	tam = tamanho_list(rede->transacoes);
	   	fwrite(&tam, sizeof(int), 1, fp);
	   	for (List n = rede->transacoes; n != NULL; n = n->next) { //iterates over all vertices
			Transacao t = (Transacao)n->value;
			WriteTransacao(t, fp);
		}
	    fclose (fp);
  	}

}

void WriteProduto(Produto p, FILE* fp){
	fwrite(&p->id, sizeof(int), 1, fp);
	fwrite(&p->tipo, sizeof(int), 1, fp);
	fwrite(p->nome, sizeof(char), 50, fp);
	fwrite(p->descricao, sizeof(char), 500, fp);

}
Produto ReadProduto(FILE* fp){
	Produto p = (Produto)malloc(sizeof(produto));
	fread(&p->id, sizeof(int), 1, fp);
	fread(&p->tipo, sizeof(int), 1, fp);
	fread(p->nome, sizeof(char), 50, fp);
	fread(p->descricao, sizeof(char), 500, fp);
	return p;
}
void WriteTransacao(Transacao t, FILE* fp){
	fwrite(&t->id, sizeof(int), 1, fp);
	if(t->cliente != NULL){
		fwrite(&t->cliente->id, sizeof(int), 1, fp);
	}else{
		int w = 0;
		fwrite(&w, sizeof(int), 1, fp);
	}
	if(t->provedor != NULL){
		fwrite(&t->provedor->id, sizeof(int), 1, fp);
	}else{
		int w = 0;
		fwrite(&w, sizeof(int), 1, fp);
	}
	fwrite(&t->status, sizeof(int), 1, fp);
	fwrite(&t->produto->id, sizeof(int), 1, fp);
	fwrite(t->comentario_cliente, sizeof(char), 1000, fp);
	fwrite(t->comentario_provedor, sizeof(char), 1000, fp);
	int tam = tamanho_list(t->ofertas);
   	fwrite(&tam, sizeof(int), 1, fp);
	for (List n = t->ofertas; n != NULL; n = n->next) { 
		Pessoa p = (Pessoa)n->value;
		fwrite(&p->id, sizeof(int), 1, fp);
	}	
}

void WritePessoa(Pessoa p, FILE* fp){
	fwrite(&p->id, sizeof(int), 1, fp);
	fwrite(p->nome, sizeof(char), 50, fp);

	int tam = tamanho_list(p->amigos);
   	fwrite(&tam, sizeof(int), 1, fp);
	for (List n = p->amigos; n != NULL; n = n->next) { 
		Pessoa p = (Pessoa)n->value;
		fwrite(&p->id, sizeof(int), 1, fp);
	}

	tam = tamanho_list(p->conhecidos);
   	fwrite(&tam, sizeof(int), 1, fp);
	for (List n = p->conhecidos; n != NULL; n = n->next) { 
		Pessoa p = (Pessoa)n->value;
		fwrite(&p->id, sizeof(int), 1, fp);
	}


	tam = tamanho_list(p->transacoes);
   	fwrite(&tam, sizeof(int), 1, fp);
	for (List n = p->transacoes; n != NULL; n = n->next) { 
		Transacao t = (Transacao)n->value;
		fwrite(&t->id, sizeof(int), 1, fp);	
	}

	tam = tamanho_list(p->notificacoes);
   	fwrite(&tam, sizeof(int), 1, fp);
	for (List n = p->notificacoes; n != NULL; n = n->next) { 
		Transacao t = (Transacao)n->value;
		fwrite(&t->id, sizeof(int), 1, fp);
	}
	fwrite(&p->rating_provedor, sizeof(float), 1, fp);
	fwrite(&p->rating_cliente, sizeof(float), 1, fp);

	tam = tamanho_list(p->comentarios);
   	fwrite(&tam, sizeof(int), 1, fp);
	for (List n = p->comentarios; n != NULL; n = n->next) { 
		char* comentario = (char*)n->value;
		fwrite(comentario, sizeof(char), 1000, fp);
	}	
}

void WriteGrafo(Graph g, FILE*fp){
	fwrite(g->name, sizeof(char), 100, fp);
	int tam = tamanho_list(g->verticesList);
   	fwrite(&tam, sizeof(int), 1, fp);
	for (List n = g->verticesList; n != NULL; n = n->next) { 
		Vertex v = ((Vertex)n->value);

		tam = tamanho_list(v->adjList);
   		fwrite(&tam, sizeof(int), 1, fp);
		for(List m = v->adjList; m != NULL; m = m->next){
			Edge e = ((Edge)m->value);
			fwrite(&(*((int*)e->value)), sizeof(int), 1, fp);
			fwrite(&e->start, sizeof(int), 1, fp);
			fwrite(&e->end, sizeof(int), 1, fp);			
			
		}
		Pessoa p = (Pessoa)v->value;
		WritePessoa(p, fp);
		fwrite(&v->id, sizeof(int), 1, fp);		
	}

}

Transacao ReadTransacao(Rede r, FILE* fp){
	Transacao t = (Transacao)malloc(sizeof(transacao)); 
	fread(&t->id, sizeof(int), 1, fp);
	int cliente_id, provedor_id, produto_id;
	fread(&cliente_id, sizeof(int), 1, fp);
	fread(&provedor_id, sizeof(int), 1, fp);

	t->cliente = PessoaByID(r, cliente_id);
	t->provedor = PessoaByID(r, provedor_id);

	fread(&t->status, sizeof(int), 1, fp);
	fread(&produto_id, sizeof(int), 1, fp);

	t->produto = ProdutoByID(r, produto_id);

	fread(t->comentario_cliente, sizeof(char), 1000, fp);
	fread(t->comentario_provedor, sizeof(char), 1000, fp);
	int tam;
   	fread(&tam, sizeof(int), 1, fp);
   	List list = cria_lista();
	for (int i = 0; i < tam; i++) { 
		int id;
		fread(&id, sizeof(int), 1, fp);
		adiciona_no(&list, PessoaByID(r, id));
	}
	t->ofertas = list;
	return t;
}

Pessoa ReadPessoa(FILE* fp){
	Pessoa p = (Pessoa)malloc(sizeof(pessoa));
	fread(&p->id, sizeof(int), 1, fp);
	fread(p->nome, sizeof(char), 50, fp);

	int tam;
   	fread(&tam, sizeof(int), 1, fp);

	List list = cria_lista();
	for (int i = 0; i < tam; i++) { 
		int id;
		fread(&id, sizeof(int), 1, fp);
		adiciona_no(&list, &id);
	}
	p->amigos = list;
	
	fread(&tam, sizeof(int), 1, fp);

	list = cria_lista();
	for (int i = 0; i < tam; i++) { 
		int id;
		fread(&id, sizeof(int), 1, fp);
		adiciona_no(&list, &id);
	}
	p->conhecidos = list;

	fread(&tam, sizeof(int), 1, fp);

	list = cria_lista();
	for (int i = 0; i < tam; i++) { 
		int id;
		fread(&id, sizeof(int), 1, fp);
		adiciona_no(&list, &id);
	}
	p->transacoes = list;

	fread(&tam, sizeof(int), 1, fp);

	list = cria_lista();
	for (int i = 0; i < tam; i++) { 
		int id;
		fread(&id, sizeof(int), 1, fp);
		adiciona_no(&list, &id);
	}
	p->notificacoes = list;

	fread(&p->rating_provedor, sizeof(float), 1, fp);
	fread(&p->rating_cliente, sizeof(float), 1, fp);

	fread(&tam, sizeof(int), 1, fp);

	list = cria_lista();
	for (int i = 0; i < tam; i++) { 
		char comentario[1000];
		fread(comentario, sizeof(char), 1000, fp);
		adiciona_no(&list, comentario);
	}
	p->comentarios = list;	
	return p;
}

Graph ReadGrafo(FILE*fp){
	Graph g = (Graph)malloc(sizeof(graph));
	fread(g->name, sizeof(char), 100, fp);
	int tam;
   	fread(&tam, sizeof(int), 1, fp);
   	List list = cria_lista();
	for (int i = 0; i < tam; i++) { 
		Vertex v = (Vertex)malloc(sizeof(vertex));

		int tam2;
		fread(&tam2, sizeof(int), 1, fp);
		List list2 = cria_lista();
		for (int j = 0; j < tam2; j++){
			Edge e = (Edge)malloc(sizeof(edge));
			int value;
			fread(&value, sizeof(int), 1, fp);
			e->value = &value;
			fread(&e->start, sizeof(int), 1, fp);
			fread(&e->end, sizeof(int), 1, fp);	
			adiciona_no(&list2, e);				
		}
		v->adjList = list2;
		Pessoa p = ReadPessoa(fp);
		fread(&v->id, sizeof(int), 1, fp);
		v->value = p;
		adiciona_no(&list, v);	
	}
	g->verticesList = list;

}
void ResolvePessoas(Rede r){
	Graph g = r->pessoas;
	for (List n = g->verticesList; n != NULL; n = n->next) { 
		Vertex v = ((Vertex)n->value);
		Pessoa p = (Pessoa)v->value;
		List nova = cria_lista();
		for (List m = p->amigos; m != NULL; m = m->next) { 
			adiciona_no(&nova,PessoaByID(r, *((int*)(m->value))));
		}
		destroi_lista(p->amigos);
		p->amigos = nova;

		nova = cria_lista();
		for (List m = p->conhecidos; m != NULL; m = m->next) { 
			adiciona_no(&nova,PessoaByID(r, *((int*)(m->value))));
		}
		destroi_lista(p->conhecidos);
		p->conhecidos = nova;

		nova = cria_lista();
		for (List m = p->transacoes; m != NULL; m = m->next) { 
			adiciona_no(&nova,TransacaoByID(r, *((int*)(m->value))));
		}
		destroi_lista(p->transacoes);
		p->transacoes = nova;

		nova = cria_lista();
		for (List m = p->notificacoes; m != NULL; m = m->next) { 
			adiciona_no(&nova,TransacaoByID(r, *((int*)(m->value))));
		}
		destroi_lista(p->notificacoes);
		p->notificacoes = nova;
	}
}