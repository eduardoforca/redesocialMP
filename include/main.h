/** @file main.h
 *  @brief MAIN.C header file
 *
 *  Utiliza biblioteca NCURSES para a View da Rede Social
 *  
 *	@author Eduardo Sousa (eduardoforca) Ana Pergentino(AnaPergentino)
 *  @date 4 Jul 2017
 */
#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdio.h>
#include <stdlib.h>
#include "redeSocial.h"
#include <ncurses.h>

/**
* @brief Janela principal do usuário logado
* @param Pessoa p
* @retval 0 - para deslogar
**/
int userMainWindow(Pessoa p);
/**
* @brief Janela para adicionar amizade
* @param Pessoa p
* @retval 0 - para sair da opção adicionar amizade
**/
int amizadeWindow(Pessoa p);

/**
* @brief Janela para impressão de lista
* @param int type - tipo de lista pode ser de pessoa, produtos ou transacao
* @param List lista - a lista que será impressa
* @retval 0 - para sair da repetição
* @retval 1 - caso a lista sejá igual a null
**/
int listWindow(int type, List lista, int mode);

/**
* @brief Janela para cadastro
* @retval 1 - para sair da repetição
**/

int signupWindow();
/**
* @brief Janela para login
* @retval 1 - para sair da repetição
**/
int loginWindow();
/**
* @brief Janela de filtros de usuário
* @param Transacao t
* @retval 1 - Transações filtradas
**/
int filtroUserWindow(Transacao t);
/**
* @brief Janela de Painel do administrador para remoção ou adição de produto
* @retval 1 - para sair da repetição
**/
int addRemoveWindow();
/**
* @brief Janela de Painel do administrador
* @retval 1 - para sair da repetição
**/
int adminWindow();
/**
* @brief editar nome de pessoa no cadastro
* @param Pessoa p
* @retval 1 - Pessoa editada
**/
int editPessoa(Pessoa p);

/**
* @brief adicionar transacao
* @param Pessoa p
* @retval 1 - para sair da repetição de criação de transações
**/
int addTransaction(Pessoa p);
/**
* @brief Janela de aceitar transação via notificações
* @param Pessoa p
* @retval 1 - para sair da repetição
**/
int acceptTransaction(Pessoa p);
/**
* @brief Janela de transaçoes pendentes
* @param Pessoa p
* @retval 1 - para sair da repetição de busca percorrendo pendencias
**/
int pendentesWindow(Pessoa p);
/**
* @brief Janela de oferta
* @param Pessoa p
* @retval 1 - para sair da repetição
**/
int offersWindow(Pessoa p);
/**
* @brief Janela de deletar usuário
* @param Pessoa p
* @retval 1 - para confirmar
* @retval 0 - para cancelar
**/
int deleteUserWindow(Pessoa p);
/**
* @brief Janela para remover amizade
* @param Pessoa p
* @retval 0 - para sair da opção remover amizade
**/
int deleteAmizadeWindow(Pessoa p);

/**
 * @brief Imprime dados de pessoa
 * 
 * @param p
 */
void printPessoa(Pessoa p);

/**
 * @brief Imprime dados de produto
 * 
 * @param p
 */
void printProduto(Produto p);
/**
 * @brief Imprime dados da transacao
 * 
 * @param t
 */
void printTransacao(Transacao t);

/**
 * @brief Imprime dados basicos de pessoa
 * 
 * @param p
 */
void printPessoaSimples(Pessoa p);
/**
 * @brief Imprime dados basicos de produto
 * 
 * @param p
 */
void printProdutoSimples(Produto p);
/**
 * @brief Imprime dados basicos da transacao
 * 
 * @param t
 */
void printTransacaoSimples(Transacao t);
/**
 * @brief Tela para visualizar informacoes detalhadas
 * 
 * @param p
 * 
* @retval 1 - para sair da repetição
 */
int detailWindow(Pessoa p);

enum Types{
	PRODUTOS, TRANSACAO, PESSOA
};

#endif