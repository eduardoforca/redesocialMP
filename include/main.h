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
int amizadeWindow(Pessoa p);
int listWindow(int type, List lista);
int userMainWindow(Pessoa p);
int amizadeWindow(Pessoa p);
int listWindow(int type, List lista);
int signupWindow();
int loginWindow();
int filtroUserWindow(Transacao t);
int addRemoveWindow();
int adminWindow();
int editPessoa(Pessoa p);
int addTransaction(Pessoa p);
int acceptTransaction(Pessoa p);
int pendentesWindow(Pessoa p);
int offersWindow(Pessoa p);

enum Types{
	PRODUTOS, TRANSACAO, PESSOA
};

#endif