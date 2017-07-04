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

enum Types{
	PRODUTOS, TRANSACAO, PESSOA
};

#endif