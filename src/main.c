#include <stdio.h>
#include <stdlib.h>
#include "redeSocial.h"
#include <ncurses.h>
#include "main.h"

#define width 3
#define length 10
//TODO
Rede rede;

int main(){
	int opcao;

	rede = RedeFile("socialnetwork.bin");
	if(rede == NULL){
		rede = CriarRede();
	 }
	keypad(stdscr, TRUE);
	initscr();

	WINDOW *main_win;

	main_win = newwin(width, length, 0, 0);
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

	endwin();

	SalvaRede(rede, "socialnetwork.bin");
	DeletaRede(rede);
	return 0;	
}

int filtroUserWindow(Transacao t){
	WINDOW *win = newwin(width, length, 0, 0);
	erase();
	wrefresh(win);
	int keep =TRUE;
	int filtros[10] = {FALSE};
	do{
		int filtro;
		printw("----- ADICIONAR TRANSACAO -----\n");
		printw("Escolha os filtros(OS FILTROS SAO EXCLUSIVOS):\n");
		printw(" 1\tAMIGO\t\t\t\t\t%c\n", (filtros[0]?'X':'O'));
		printw(" 2\tAMIGO DE AMIGO\t\t\t\t%c\n", (filtros[1]?'X':'O'));
		printw(" 3\tJA FIZ NEGOCIO\t\t\t\t%c\n", (filtros[2]?'X':'O'));
		printw(" 4\tAMIGOS JA FIZERAM NEGOCIO\t\t%c\n", (filtros[3]?'X':'O'));
		printw(" 5\tUSUARIO JA NEGOCIOU ESSE PRODUTO\t%c\n", (filtros[4]?'X':'O'));
		printw(" 0\tENVIAR\n");
		scanw("%d", &filtro);
		if(!filtro){
			keep = FALSE;
			NotificarTransacao(rede, t, filtros);
		}else{
			filtros[filtro-1] = !filtros[filtro-1];
		}
		erase();
	}while(keep);
	
	endwin();
	return 1;
}

int editPessoa(Pessoa p){
	WINDOW *win = newwin(width, length, 0, 0);
	erase();
	wrefresh(win);
	printw("----- EDITAR CADASTRO -----\n");
	char nome[50];
	printw("Novo nome de Usuario:");
	scanw("%s", nome);
	strcpy(p->nome, nome);
	erase();
	endwin();
	return 1;
}

int pendentesWindow(Pessoa p){
	WINDOW *win = newwin(width, length, 0, 0);
	int opcao, back =0;
	do{
		erase();
		printw("----- Avalia Transacoes Pendentes -----\nEscolha uma opcao:\n");
		printw("1 - Listar Pendencias\n");
		printw("2 - Avaliar Transacao\n");
		printw("3 - Voltar\n");
		scanw("%d", &opcao);
		wrefresh(win);
		erase();
		switch(opcao){
			case 1:{
				listWindow(TRANSACAO, FiltrarTransacao(p->transacoes, STATUS_PENDENTE), 0);
				getch();
			}
			break;
			case 2:{
				int id;
				printw("ID da Transacao:");
				scanw("%d", &id);
				erase();
				Transacao t = TransacaoByID(rede, id);
				if(t != NULL){
					if(t->status == PENDENTE &&(t->cliente == p || t->provedor == p)){
						int rating;
						char comentario[1000];
						do{
							erase();
							printw("Insira Avaliacao de -5 a 5:\n");
							scanw("%d", &rating);
						}while(rating < -5 || rating > 5);
						scanw("%s", comentario);
						AvaliarTransacao(rede, t, p, comentario, rating);
					}else{
						printw("Transacao Invalida\n");
						getch();
					}
				}else{
					printw("Transacao nao existe\n");
					getch();
				}
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

int addTransaction(Pessoa p){
	WINDOW *win = newwin(width, length, 0, 0);
	int opcao, back =0;
	do{
		erase();
		printw("----- Adicionar Transacao -----\nEscolha uma opcao:\n");
		printw("1 - Listar Produtos\n");
		printw("2 - Iniciar Transacao\n");
		printw("3 - Voltar\n");
		scanw("%d", &opcao);
		wrefresh(win);
		erase();
		switch(opcao){
			case 1:{
				listWindow(PRODUTOS, rede->produtos, 2);
				getch();
			}
			break;
			case 2:{
				int idt, idp;
				printw("ID da Transacao:");
				scanw("%d", &idt);
				printw("ID do Produto:");
				scanw("%d", &idp);
				erase();
				Produto prod = ProdutoByID(rede, idp);
				Transacao t = TransacaoByID(rede, idt);
				if(t == NULL){
					if(prod != NULL){
						printw("Deseja criar transacao de \"%s\"?\n(0 - NAO, 1- SIM)", prod->nome);
						scanw("%d", &opcao);
						switch(opcao){
							case 1:
								if(AdicionarTransacao(rede, CriarTransacao(p, prod, idt))){
									filtroUserWindow(TransacaoByID(rede, idt));
								}else{
									printw("Erro ao criar Transacao\n");
									getch();
								}
							break;
							default:break;
						}
					}else{
						printw("Produto inexistente\n");
						getch();
					}
				}else{
					printw("ID de transacao repetida\n");
					getch();
				}
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


int userMainWindow(Pessoa p){
	if (p == NULL)
		return 1;

	WINDOW *win;
	int opcao, back =0;
	win = newwin(width, length, 0, 0);
	do{
		erase();
		printw("--------HOME----------\n");
		printPessoaSimples(p);
		if (p->amigos != NULL){
			printw("Amizades:\n");
			listWindow(PESSOA, p->amigos, 1);
		}	
		win = newwin(width, length, 10, 10);
		if (p->transacoes != NULL){
			printw("Transacoes:\t%s\n");
			listWindow(TRANSACAO, p->transacoes, 1);
		}
		printw("***Você tem (%d) notificacoes, aceite transacoes****\n", tamanho_list(p->notificacoes));
		printw("1 - Adicionar Amizade\n");
		printw("2 - Editar Dados\n");
		printw("3 - Nova Transacao\n");
		printw("4 - Aceitar Transacao\n");
		printw("5 - Avaliar Transacoes Pendentes\n");
		printw("6 - Ver Ofertas Recebidas\n");
		printw("7 - Excluir Conta\n");
		printw("8 - Excluir Amizade\n");
		printw("9 - Ver Detalhes\n");
		printw("0 - Deslogar\n");
		scanw("%d", &opcao);	
		switch(opcao){
			case 1:
				amizadeWindow(p);
				break;
			case 2:
				editPessoa(p);
				break;
			case 3:
				addTransaction(p);
				break;
			case 4:
				acceptTransaction(p);
				break;
			case 5:	
				pendentesWindow(p);
				break;
			case 6:	
				offersWindow(p);
				break;
			case 7:
				back = deleteUserWindow(p);
				break;
			case 8:
				deleteAmizadeWindow(p);
				break;
			case 9:
				detailWindow(p);
				break;
			default:
				back = 1;
				break;
		}
	}while(!back);
	endwin();
	return 0;
}

int amizadeWindow(Pessoa p){
	WINDOW *win;
	win = newwin(width, length, 0, 0);
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

int deleteAmizadeWindow(Pessoa p){
	WINDOW *win;
	win = newwin(width, length, 0, 0);
	int opcao, back = 0;
	int id;
	erase();
	printw("----- REMOVER AMIZADE -----\nDigite o ID do usuario que deseja remover:\n");
	scanw("%d", &id);
	Pessoa n = PessoaByID(rede, id);
	if(n!= NULL){
		if(!RemoverAmizade(rede, p, n)){
			printw("Nao foi possivel remover amizade\n");
			getch();
		}
	}
	endwin();
	return 0;
}	
int listWindow(int type, List lista, int mode){
	if (lista == NULL)
		return 1;

	WINDOW *win;
	win = newwin(width, length, 0, 0);
	for (List n = lista; n != NULL; n = n->next) { //iterates over all vertices
		switch(type){
			case PESSOA:{
				Pessoa p = (Pessoa)n->value;
				if(mode == 1)
					printPessoaSimples(p);
				else
					printPessoa(p);
				break;
			}
			case PRODUTOS:{
				Produto p = (Produto)n->value;
				if(mode == 1)
					printProdutoSimples(p);
				else
					printProduto(p);
				break;
			}
			case TRANSACAO:{
				Transacao p = (Transacao)n->value;
				if(mode == 1)
					printTransacaoSimples(p);
				else
					printTransacao(p);
				break;
			}
			default:break;
		}
		wrefresh(win);
	}
	endwin();
	return 0;
}

int signupWindow(){
	WINDOW *win = newwin(width, length, 0, 0);
	int opcao, back =0;
	erase();
	wrefresh(win);
	do{
		erase();
		printw("----- CADASTRO -----\n");
		char nome[50];
		int id;
		printw("Nome do Usuario:");
		scanw("%s", nome);
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
	WINDOW *win = newwin(width, length, 0, 0);
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
	WINDOW *win = newwin(width, length, 0, 0);
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
				if(!AdicionarProduto(rede, CriarProduto(nome, descricao, tipo, id))){
					printw("Erro ao Adicionar Produto");
					getch();
				}
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
	WINDOW *win = newwin(width, length, 0, 0);
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
				listWindow(PRODUTOS, rede->produtos, 2);
				getch();
			break;
			case 3:
				addRemoveWindow();
			break;
			case 4:
				listWindow(TRANSACAO, rede->transacoes, 2);
				getch();
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

int acceptTransaction(Pessoa p){
	WINDOW *win = newwin(width, length, 0, 0);
	int opcao, back =0;
	do{
		erase();
		printw("----- NOTIFICACOES -----\n");
		listWindow(TRANSACAO, p->notificacoes, 1);
		printw("Escolha uma opcao:\n");
		printw("1 - Aceitar Transacao\n");
		printw("2 - Voltar\n");
		scanw("%d", &opcao);
		wrefresh(win);
		erase();
		switch(opcao){
			case 1:{
				int id;
				printw("ID da Transacao:");
				scanw("%d", &id);
				erase();
				Transacao t = TransacaoByID(rede, id);
				if(t != NULL){
					if(t->status == PEDIDA){
						AceitarTransacao(rede, t, p);		
					}else{
						printw("Transacao Invalida\n");
						getch();
					}
				}else{
					printw("Transacao nao existe\n");
					getch();
				}
				break;
			}
			break;
			case 2:
				back = 1;
			break;
			default: break;
		}
	}while(!back);
	endwin();
	return back;
}

int offersWindow(Pessoa p){

	WINDOW *win = newwin(width, length, 0, 0);
	int opcao, back =0;
	do{
		erase();
		printw("----- Aceitar Ofertas -----\nEscolha uma opcao:\n");
		printw("1 - Listar Pedidos\n");
		printw("2 - Aceitar Ofertas\n");
		printw("3 - Voltar\n");
		scanw("%d", &opcao);
		wrefresh(win);
		erase();
		switch(opcao){
			case 1:{
				listWindow(TRANSACAO, FiltrarTransacao(p->transacoes, STATUS_PEDIDA), 1);
				getch();
			}
			break;
			case 2:{
				int idt;
				printw("ID da Transacao:");
				scanw("%d", &idt);
				erase();
				Transacao t = TransacaoByID(rede, idt);
				if(t != NULL){
					if(t->status == PEDIDA &&t->cliente == p){
						int idp;
						listWindow(PESSOA, t->ofertas, 2);
						printw("Escolha uma oferta:\n");
						scanw("%d", &idp);
						if(PessoaByID(rede, idp) != NULL){
							AceitarOferta(rede, t, PessoaByID(rede, idp));
						}else{
							printw("Oferta nao existe\n");
							getch();
						}
					}else{
						printw("Transacao Invalida\n");
						getch();
					}
				}else{
					printw("Transacao nao existe\n");
					getch();
				}
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

int deleteUserWindow(Pessoa p){
	WINDOW *win = newwin(width, length, 0, 0);
	erase();
	wrefresh(win);
	printw("----- DELETAR CONTA -----\n");
	int opcao;
	printw("Deseja Deletar sua Conta?\n (0 - NAO, 1 - SIM)\n");
	scanw("%d", &opcao);
	if(opcao){
		ExcluirPessoa(rede, p);
	}
	erase();
	endwin();
	return opcao;
}
void printPessoaSimples(Pessoa p){
	WINDOW *win;
	win = newwin(width, length, 0, 0);
	printw("-------------------------------------------------------/n");
	printw("ID:%d\tNome:%s\nKarma Cliente:%d\tKarma Provedor:%d\t\n", p->id, p->nome, p->rating_cliente, p->rating_provedor);
	printw("-------------------------------------------------------/n");
	endwin();

}
void printPessoa(Pessoa p){
	WINDOW *win;
	win = newwin(width, length, 0, 0);
	printPessoaSimples(p);
	for (List n = p->comentarios; n != NULL; n = n->next) {
		printw("%s/n/n", (char*)n->value);
	}
	printw("-------------------------------------------------------/n");
	getch();
	endwin();

}
void printProdutoSimples(Produto p){
	WINDOW *win;
	win = newwin(width, length, 0, 0);
	printw("-------------------------------------------------------/n");
	printw("ID:%d\tNome:%s\n", p->id, p->nome, p->descricao);
	printw("-------------------------------------------------------/n");
	endwin();
}
void printProduto(Produto p){
	WINDOW *win;
	win = newwin(width, length, 0, 0);
	printProdutoSimples(p);
	printw("Descricao:%s\n", p->descricao);
	printw("-------------------------------------------------------/n");
	endwin();
	getch();
}
void printTransacaoSimples(Transacao t){
	WINDOW *win;
	win = newwin(width, length, 0, 0);
	printw("-------------------------------------------------------/n");
	printw("ID da Transacao: \tProduto: \tID do Produto:\n", t->id,t->produto->nome,t->produto->id);
	printw("-------------------------------------------------------/n");
	endwin();

}
void printTransacao(Transacao t){
	WINDOW *win;
	win = newwin(width, length, 0, 0);
	printTransacaoSimples(t);
	printw("ID do Cliente:%d\tNome:%s\nID do Provedor:%d\tNome:%s\n", t->cliente->id, t->cliente->nome, t->provedor->id, t->provedor->nome);
	printw("Opiniao do Cliente: %s/n", t->comentario_cliente);
	printw("-------------------------------------------------------/n");
	printw("Opiniao do Provedor: %s/n", t->comentario_provedor);
	printw("-------------------------------------------------------/n");
	getch();
	endwin();
}
int detailWindow(Pessoa p){
	WINDOW *win = newwin(width, length, 0, 0);
	int opcao, back =0;
	do{
		erase();
		printw("----- Ver Detalhes -----\nEscolha uma opcao:\n");
		printw("1 - Listar Minhas Transacoes\n");
		printw("2 - Ver Pessoa\n");
		printw("3 - Ver Produto\n");
		printw("4 - Ver Transacao\n");
		printw("5 - Voltar\n");
		scanw("%d", &opcao);
		wrefresh(win);
		erase();
		switch(opcao){
			case 1:{
				listWindow(TRANSACAO, p->transacoes, 2);
				getch();
			}
			break;
			case 2:{
				int id;
				printw("ID da Pessoa:\n");
				scanw("%d", &id);
				Pessoa pess = PessoaByID(rede, id);
				if(pess != NULL){
					printPessoa(pess);
				}else{
					printw("ID invalido\n");
					getch();
				}
				break;
			}
			case 3:{
				int id;
				printw("ID do Produto:\n");
				scanw("%d", &id);
				Produto prod = ProdutoByID(rede, id);
				if(prod != NULL){
					printProduto(prod);
				}else{
					printw("ID invalido\n");
					getch();
				}
				break;
			}
			case 4:{
				int id;
				printw("ID da Transacao:\n");
				scanw("%d", &id);
				Transacao t = TransacaoByID(rede, id);
				if(t != NULL){
					printTransacao(t);
				}else{
					printw("ID invalido\n");
					getch();
				}
				break;
			}
			case 5:
				back = 1;
			break;
			default: break;
		}
	}while(!back);
	endwin();
	return back;

}
