#include <stdio.h>
#include <stdlib.h>
#include "redeSocial.h"
#include <ncurses.h>

Rede rede;
enum Types{
	PRODUTOS, TRANSACAO, PESSOA
};
int amizadeWindow(Pessoa p);
int listWindow(int type, List lista);
int userMainWindow(Pessoa p){
/*
amizades, transações*/

	if (p == NULL)
		return 1;

	WINDOW *win;
	int opcao, back =0;
	win = newwin(3, 10, 0, 0);
	do{
		erase();
		printw("--------HOME----------\n");
		printw("ID:%d\tNome:\t%s\n", p->id, p->nome);
		if (p->amigos != NULL){
			printw("Amizades:\n");
			listWindow(PESSOA, p->amigos);
		}	
		win = newwin(3, 10, 10, 10);
		if (p->transacoes != NULL){
			printw("Transacoes:\t%s\n", p->transacoes);
		}
		printw("1 - Adicionar Amizade\n");
		printw("2 - Voltar\n");
		scanw("%d", &opcao);	
		switch(opcao){
			case 1:
				amizadeWindow(p);
				break;
			case 2:
				back = 1;
			default:break;
		}
	}while(!back);
	endwin();
	return 0;
}
int amizadeWindow(Pessoa p){
	WINDOW *win;
	win = newwin(3, 10, 0, 0);
	int opcao, back = 0;
	int id;
	erase();
	do{
		erase();
		printw("----- ADICIONAR AMIZADE -----\nDigite o ID do usuario que deseja adicionar:\n");
		scanw("%d", &id);
		Pessoa n = PessoaByID(rede, id);
		if(n==p){
			erase();
			printw("----- ADICIONAR AMIZADE -----\nVocê não pode adicionar a si mesmo\n");
			printw("1 - Tentar Novamente\n");
			printw("2 - Cancelar\n");
			scanw("%d", &opcao);	
			switch(opcao){
				case 2:
					back = 1;
					break;
				default:break;
			}
		}else{
			if(n!= NULL){
				AdicionarAmizade(rede, p, n);
				back = 1;
			}
			else{
				erase();
				printw("----- ADICIONAR AMIZADE -----\nUsuario nao existe:\n");
				printw("1 - Tentar Novamente\n");
				printw("2 - Cancelar\n");
				scanw("%d", &opcao);	
				switch(opcao){
					case 2:
						back = 1;
						break;
					default:break;
				}
			}
		}
	}while(!back);
	endwin();
	return 0;

}
int listWindow(int type, List lista){

	if (lista == NULL)
		return 1;

	WINDOW *win;
	win = newwin(3, 10, 0, 0);
	erase();
	printw("---------LISTA----------\n");
	for (List n = lista; n != NULL; n = n->next) { //iterates over all vertices
		switch(type){
			case PESSOA:{
				Pessoa p = (Pessoa)n->value;
				printw("ID:%d\tNome:\t%s\n", p->id, p->nome);
				break;
			}
			case PRODUTOS:{
				Produto p = (Produto)n->value;
				printw("ID:%d\tNome:\t%s\n", p->id, p->nome);
				break;
			}
			case TRANSACAO:{
				Transacao p = (Transacao)n->value;
				printw("ID:%d\tProduto:\t%s\n", p->id, p->produto->nome);
				break;
			}
			default:break;
		}
		wrefresh(win);
	}

	getch();
	endwin();
	return 0;
}
int signupWindow(){
	WINDOW *win = newwin(3, 10, 0, 0);
	int opcao, back =0;
	erase();
	wrefresh(win);
	do{
		erase();
		printw("----- CADASTRO -----\n");
		char nome[50];
		int id;
		printw("Nome do Usuario:");
		scanw("%s", &nome);
		printw("ID do Usuario:");
		scanw("%d", &id);
		Pessoa p = PessoaByID(rede, id);
		if(p== NULL){
			if(AdicionarPessoa(rede, CriarPessoa(nome, id))){
				userMainWindow(PessoaByID(rede, id));
			}
			else{
				printw("----- CADASTRO -----\nErro Desconhecido\n");
				getch();
			}
			back = 1;
		}
		else{
			erase();
			printw("----- CADASTRO -----\nUsuario ja existe:\n");
			printw("1 - Tentar Novamente\n");
			printw("2 - Cancelar\n");
			scanw("%d", &opcao);	
			switch(opcao){
				case 2:
					back = 1;
					break;
				default:break;
			}
		}

	}while(!back);
	erase();
	endwin();
	return back;
}
int loginWindow(){
	WINDOW *win = newwin(3, 10, 0, 0);
	int opcao, back =0, id;
	erase();
	wrefresh(win);
	do{
		erase();
		printw("----- LOGIN -----\nDigite o ID do usuario:\n");
		scanw("%d", &id);
		Pessoa p = PessoaByID(rede, id);
		if(p!= NULL){
			userMainWindow(p);
			back = 1;
		}
		else{
			erase();
			printw("----- LOGIN -----\nUsuario nao existe:\n");
			printw("1 - Tentar Novamente\n");
			printw("2 - Cadastrar Novo Usuario\n");
			scanw("%d", &opcao);	
			switch(opcao){
				case 2:
					back = 1;
					signupWindow();
					break;
				default:break;
			}
		}

	}while(!back);
	erase();
	endwin();
	return back;
}
int addRemoveWindow(){
	WINDOW *win = newwin(3, 10, 0, 0);
	int opcao, back =0;
	do{
		erase();
		printw("----- PAINEL DE ADMIN -----\n----- Adicionar/Remover Produto -----\nEscolha uma opcao:\n");
		printw("1 - Adicionar Produto\n");
		printw("2 - Remover Produto\n");
		printw("3 - Voltar\n");
		scanw("%d", &opcao);
		wrefresh(win);
		erase();
		switch(opcao){
			case 1:{
				char nome[50], descricao[500];
				int id, tipo;
				printw("Nome do Produto:");
				scanw("%s", &nome);
				printw("Descricao do Produto:");
				scanw("%s", &descricao);
				printw("ID do Produto:");
				scanw("%d", &id);
				printw("Tipo do Produto(1 - SERVICO, 2 - PRODUTO):");
				scanw("%d", &tipo);
				AdicionarProduto(rede, CriarProduto(nome, descricao, tipo, id));
			break;
			}
			case 2:{
				int id;
				printw("ID do Produto:");
				scanw("%d", &id);
				Produto p = ProdutoByID(rede, id);
				if(p!=NULL){
					ExcluirProduto(rede, p);
					printw("%s excluido!", p->nome);
				}else{
					printw("ID invalido");
				}
				getch();
			break;
			}
			case 3:
				back = 1;
			break;
			default: break;
		}
	}while(!back);
	endwin();
	return back;
}
int adminWindow(){
	WINDOW *win = newwin(3, 10, 0, 0);
	int opcao, back = 0;
	do{
		erase();
		printw("----- PAINEL DE ADMIN -----\nEscolha uma opcao:\n");
		printw("1 - Visualizar Grafo\n");
		printw("2 - Lista de Produtos\n");
		printw("3 - Cadastrar/Excluir Produto\n");
		printw("4 - Lista de Transacoes\n");
		printw("5 - Voltar\n");
		scanw("%d", &opcao);
		wrefresh(win);
		erase();
		switch(opcao){
			case 2:
				listWindow(PRODUTOS, rede->produtos);
			break;
			case 3:
				addRemoveWindow();
			break;
			case 4:
				listWindow(TRANSACAO, rede->transacoes);
			break;
			case 5:
				back = 1;
			break;
			default: break;
		}
	}while(!back);
	endwin();
	return back;
}
int main(){
	int opcao;

	rede = RedeFile("socialnetwork.bin");
	if(rede == NULL){
		rede = CriarRede();
	}

	initscr();

	WINDOW *main_win;

	main_win = newwin(3, 10, 0, 0);
	int error = 0;

	do{
		error = 0;
		printw("Escolha uma opcao:\n");
		printw("1 - Login\n");
		printw("2 - Cadastro\n");
		printw("3 - Painel de Admin\n");
		printw("4 - Sair\n");		
		scanw("%d", &opcao);
		wrefresh(main_win);
		erase();
		switch(opcao){
			case 1:
				error = loginWindow();
				break;
			case 2:
				error = signupWindow();
				break;
			case 3:
				error = adminWindow();
				break;
			case 4:
				error = 0;
				break;
			default: 
				printw("Entrada invalida\n");
				error = 1;
				break;
		}
	}while(error);

	SalvaRede(rede, "socialnetwork.bin");
	DeletaRede(rede);
	endwin();
	return 0;	
}
