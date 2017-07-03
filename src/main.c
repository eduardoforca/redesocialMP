#include <stdio.h>
#include <stdlib.h>
#include "redeSocial.h"
int main(){
	int opcao;
	printf("USUARIO ----- Escolha uma opcao:\n");
	printf("1 - Criar Pessoa\n");
	printf("2 - Editar Pessoa\n");
	printf("3 - Buscar Transacao\n");
	printf("4 - Fazer uma Transacao\n");
	scanf("%d", &opcao);
	switch(opcao){
		default: break;
	}
	printf("ADMIN ----- Escolha uma opcao:\n");
	printf("1 - Visualizar Grafo\n");
	printf("2 - Cadastrar/Excluir Transacao\n");
	printf("3 - Lista de Transacoes\n");
	printf("4 - Salvar Rede Social em Arquivo\n");
	scanf("%d", &opcao);
	switch(opcao){
		default: break;
	}

	return 0;	
}