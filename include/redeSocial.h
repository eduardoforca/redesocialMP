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
/**
* @struct pessoa
**/
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
/**
* @brief Função para criar uma instância de Pessoa
* @param[in] nome 
* @param[in] id
* @details inicializa variáveis da estrutura Pessoa
* @return ponteiro Pessoa p
**/
Pessoa CriarPessoa(char* nome, int id);
/**
* @brief Função para criar uma instância de Produto
* @param[in] nome
* @param[in] descrição
* @param[in] tipo(servico ou produto)
* @param[in] id
* @details inicializa variáveis da estrutura Produto
* @return ponteiro Produto p
**/
Produto CriarProduto(char* nome, char* descricao, int tipo, int id);
/**
* @brief Função para criar uma instância de Transacao
* @param[in] Pessoa cliente que está requisitando um serviço ou produto
* @param[in] Produto
* @param[in] id da transação
* @details inicializa variáveis da estrutura Transação
* @return ponteiro Transação t
**/
Transacao CriarTransacao(Pessoa cliente, Produto produto, int id);
/**
* @brief Função para criar a rede social
* @details Inicializa as variaveis da estrutura rede
* @return rede r vazia
**/
Rede CriarRede();
/**
* @brief Função para adicionar uma pessoa a Rede
* @param[in] rede
* @param[in] pessoa
* @details insere a pessoa no grafo
* @return validação da inserção
**/
int AdicionarPessoa(Rede rede, Pessoa pessoa);
/**
* @brief Função para adicionar produto na rede
* @param[in] rede
* @param[in] produto
**/
void AdicionarProduto(Rede rede, Produto produto);
/**
* @brief Função para adicionar transacao na rede
* @param[in] rede
* @param[in] transacao
**/
void AdicionarTransacao(Rede rede, Transacao transacao);
/**
* @brief Função para excluir pessoa da rede
* @param rede
* @param pessoa
* @return a validação da exclusão
**/
int ExcluirPessoa(Rede rede, Pessoa pessoa);
/**
* @briefFunção para excluir produto da rede
* @param rede
* @param produto
* @return a validação da exclusão
**/
int ExcluirProduto(Rede rede, Produto produto);
/**
* @brief Função para excluir transacao da rede
* @param rede
* @param transacao
* @return a validação da exclusão
**/
int ExcluirTransacao(Rede rede, Transacao transacao);
/**
* @brief Função para deletar a rede
* @param rede
* @details remove a rede da memoria
* @return a validação da exclusão
**/
int DeletaRede(Rede rede);
/**
* @brief Função para adicionar amizades
* @param rede 
* @param pessoa 1
* @param pessoa 2
* @details adiciona uma aresta entre as duas pessoas (amizade)
**/
void AdicionarAmizade(Rede rede, Pessoa pessoa1, Pessoa pessoa2);
/**
* @brief Função para remover amizades
* @param rede 
* @param pessoa 1
* @param pessoa 2
* @details remove a aresta entre as duas pessoas 
* @return validação da remoção
**/
int RemoverAmizade(Rede rede, Pessoa pessoa1, Pessoa pessoa2);
/**
* @brief Função para notificar transações
* @param rede 
* @param transacao
* @param filtro
* @details notifica todos usuários que passarem no filtro da transação
**/
void NotificarTransacao(Rede rede, Transacao transacao, int* filtros);
/**
* @brief Função para aceitar transações
* @param rede 
* @param transacao
* @param pessoa
* @details a pessoa aceita a transacao envia uma oferta para o cliente
**/
void AceitarTransacao(Rede rede, Transacao transacao);
/**
* @brief Função para aceitar oferta
* @param rede 
* @param oferta
* @param pessoa
* @details o cliente aceita a oferta e a funcao inicializa a transação
**/
void AceitarOferta(Rede rede, Transacao oferta, Pessoa pessoa);
/**
* @brief Função para concluir transacao
* @param rede 
* @param transacao
* @details adiciona uma aresta entre as pessoas envolvidas na transacao
**/
void IniciarTransacao(Rede rede, Transacao oferta);
/**
* @brief Função para avaliar transacao
* @param rede 
* @param transacao
* @param avaliador 
* @param comentario
* @param rating (avaliacao em pontos)
* @details grava comentário e calcula o rating
**/
void AvaliarTransacao(Rede rede, Transacao oferta, Pessoa avaliador, char* comentario, int rating);
/**
* @brief Função para filtrar transacoes
* @param rede 
* @param filtros
* @details filtra as transacoes da rede 
* @return lista de transacoes filtradas
**/
Transacao* FiltrarTransacao(Rede rede, int* filtros);

Rede RedeFile(char* nomeArquivo);
/**
* @brief Função para retornar produto por ID
* @param rede 
* @param id de produto
* @details percorre lista de produtos
* @return produto
**/
Produto ProdutoByID(Rede rede, int id);
/**
* @brief Função para retornar transacao por ID
* @param rede 
* @param id de transacao
* @details percorre lista de transacoes
* @return transacao
**/
Transacao TransacaoByID(Rede rede, int id);
/**
* @brief Função para retornar pessoa por ID
* @param rede 
* @param id de pessoa
* @details percorre lista de pessoas
* @return pessoa
**/
Pessoa PessoaByID(Rede rede, int id);

/**
* @brief salva a rede no arquivo
* @param rede
* @param string nome do arquivo
* @details abre arquivo e escreve a rede nele. 
**/
void SalvaRede(Rede rede, char* nomeArquivo);
/**
* @brief escreve transacao no arquivo de rede
* @param transacao
* @param arquivo da rede
* @details abre arquivo e escreve a transacao nele
**/
void WriteTransacao(Transacao t, FILE* fp);
void WritePessoa(Pessoa p, FILE* fp);
void WriteGrafo(Graph g, FILE*fp);

/**
* @brief escreve produto no arquivo de rede
* @param produto
* @param arquivo da rede
* @details abre arquivo e escreve na rede
**/
void WriteProduto(Produto p, FILE* fp);
Transacao ReadTransacao(Rede r, FILE* fp);
Pessoa ReadPessoa(FILE* fp);
Graph ReadGrafo(FILE*fp);
/**
* @brief le produto no arquivo de rede
* @param arquivo da rede
* @details abre arquivo e le produto da rede nele
* @return produto
**/
Produto ReadProduto(FILE* fp);
void ResolvePessoas(Rede r);
#endif
