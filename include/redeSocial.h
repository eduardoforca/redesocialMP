/** @file redeSocial.h
 *  @brief REDESOCIAL.C header file
 *
 *  Implementa uma rede social de transacoes
 *  
 *	@author Eduardo Sousa (eduardoforca) Ana Pergentino(AnaPergentino)
 *  @date 4 Jul 2017
 */

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
	PEDIDA, PENDENTE, CONCLUIDA
	
};
enum conexao
{
	AMIZADE, NEGOCIOS 
};
enum filtros_transacao{
	STATUS_PEDIDA, STATUS_PENDENTE, STATUS_CONCLUIDA
};
enum filtros_pessoas{
	AMIGO, AMIGO2, JA_FEZ_NEGOCIO, JA_FEZ_NEGOCIO_AMIGO, ACOSTUMADO
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
* @retval 0 - FALSE
* @retval 1 - TRUE
**/
int AdicionarPessoa(Rede rede, Pessoa pessoa);
/**
* @brief Função para adicionar produto na rede
* @param[in] rede
* @param[in] produto
* @return validação da inserção
* @retval 0 - FALSE
* @retval 1 - TRUE
**/
int AdicionarProduto(Rede rede, Produto produto);
/**
* @brief Função para adicionar transação na rede
* @param[in] rede
* @param[in] transacao
* @return validação da inserção
* @retval 0 - FALSE
* @retval 1 - TRUE
**/
int AdicionarTransacao(Rede rede, Transacao transacao);
/**
* @brief Função para excluir pessoa da rede
* @param rede
* @param pessoa
* @return a validação da exclusão
* @retval 0 - FALSE
* @retval 1 - TRUE
**/
int ExcluirPessoa(Rede rede, Pessoa pessoa);
/**
* @briefFunção para excluir produto da rede
* @param rede
* @param produto
* @return a validação da exclusão
* @retval 0 - FALSE
* @retval 1 - TRUE
**/
int ExcluirProduto(Rede rede, Produto produto);
/**
* @brief Função para excluir transação da rede
* @param rede
* @param transacao
* @return a validação da exclusão
* @retval 0 - FALSE
* @retval 1 - TRUE
**/
int ExcluirTransacao(Rede rede, Transacao transacao);
/**
* @brief Função para deletar a rede
* @param rede
* @details remove a rede da memoria
* @return a validação da exclusão
* @retval 0 - FALSE
* @retval 1 - TRUE
**/
int DeletaRede(Rede rede);
/**
* @brief Função para adicionar amizades
* @param rede 
* @param pessoa 1
* @param pessoa 2
* @details adiciona uma aresta entre as duas pessoas (amizade)
* @return a validacao da adicao
* @retval 0 - FALSE
* @retval 1 - TRUE
**/
int AdicionarAmizade(Rede rede, Pessoa pessoa1, Pessoa pessoa2);
/**
* @brief Função para remover amizades
* @param rede 
* @param pessoa 1
* @param pessoa 2
* @details remove a aresta entre as duas pessoas 
* @return validação da remoção
* @retval 0 - FALSE
* @retval 1 - TRUE
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
* @details a pessoa aceita a transação envia uma oferta para o cliente
**/
void AceitarTransacao(Rede rede, Transacao transacao, Pessoa p);
/**
* @brief Função para aceitar oferta
* @param rede 
* @param oferta
* @param pessoa
* @details o cliente aceita a oferta e a funcao inicializa a transação
**/
void AceitarOferta(Rede rede, Transacao oferta, Pessoa pessoa);

/**
* @brief Função para concluir transação
* @param rede 
* @param transacao
* @details adiciona uma aresta entre as pessoas envolvidas na transação e deixa a transação pendente para avaliacao
**/
void ConcluirTransacao(Rede rede, Transacao transacao);

/**
* @brief Função para avaliar transação
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
* @param status
* @details filtra as transacoes da rede 
* @return lista de transacoes filtradas
**/
List FiltrarTransacao(List transacoes, int status);

/**
 * @brief Funcao que le arquivo contendo a rede
 * @details Le arquivo binario contendo as informacoes de persistencia da rede social
 * 
 * @param nomeArquivo
 * @return rede social
 */
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
* @brief Função para retornar transação por ID
* @param rede 
* @param id de transação
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
/**
* @brief escreve pessoa no arquivo de rede
* @param pessoa
* @param arquivo da rede
* @details abre arquivo e escreve a pessoa nele
**/
void WritePessoa(Pessoa p, FILE* fp);
/**
* @brief escreve grafo no arquivo de rede
* @param grafo
* @param arquivo da rede
* @details abre arquivo e escreve o grafo nele
**/
void WriteGrafo(Graph g, FILE*fp);

/**
* @brief escreve produto no arquivo de rede
* @param produto
* @param arquivo da rede
* @details abre arquivo e escreve o produto na rede
**/
void WriteProduto(Produto p, FILE* fp);
/**
* @brief le transacao no arquivo de rede
* @param arquivo da rede
* @details abre arquivo e le transacao da rede nele
* @return transacao
**/
Transacao ReadTransacao(Rede r, FILE* fp);
/**
* @brief le pessoa no arquivo de rede
* @param arquivo da rede
* @details abre arquivo e le pessoa da rede nele
* @return pessoa
**/
Pessoa ReadPessoa(FILE* fp);
/**
* @brief le grafo no arquivo de rede
* @param arquivo da rede
* @details abre arquivo e le grafo da rede nele
* @return grafo
**/
Graph ReadGrafo(FILE*fp);
/**
* @brief le produto no arquivo de rede
* @param arquivo da rede
* @details abre arquivo e le produto da rede nele
* @return produto
**/
Produto ReadProduto(FILE* fp);

/**
 * @brief Funcao complementar da leitura de arquivos
 * @details Transformar Listas de ids de pessoas no grafo em Listas
 * de pessoas
 * 
 * @param rede contendo as pessoas e referencias
 */
void ResolvePessoas(Rede r);
/**
 * @brief Funcao que retorna se duas pessoas sao amigas
 * @details Checa se existe amizade entre pessoas
 * 
 * @param p1 Pessoa 1
 * @param p2 Pessoa 2
 * 
 * @retval 0 - FALSE
 * @retval 1 - TRUE
 */
int Amigos(Pessoa p1, Pessoa p2);

/**
 * @brief Funcao que retorna se duas pessoas ja fizeram negocios
 * @details Checa se existe relacao de negocios entre pessoas
 * 
 * @param p1 Pessoa 1
 * @param p2 Pessoa 2
 * 
 * @retval 0 - FALSE
 * @retval 1 - TRUE
 */
int Conhecidos(Pessoa p1, Pessoa p2);

/**
 * @brief Funcao que retorna se pessoa é acostumado com um produto
 * @details Checa se existe se pessoa é acostumada com transacoes de um produto
 * 
 * @param p1 Pessoa 1
 * @param prod produto
 * 
 * @retval 0 - FALSE
 * @retval 1 - TRUE
 */
int Acostumado(Pessoa p1, Produto prod);
#endif
