/* Trabalho 1 de Metodos de Programacao **
** Aluno: Eduardo Sousa da Silva        **
** Matricula: 13/0108405                */

/* LISTA.C - Implementation of LISTA.H*/

#define TRUE 1
#define FALSE 0

#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

List cria_lista() {
	return NULL;
}

List adiciona_no(List *a_list, void* value) {
	List n = (List)malloc(sizeof(struct listNode));
	n->next = *a_list;
	n->value = value;
	*a_list = n;

	return n;
}

int remove_no(List *a_list, int index) {
	if (*a_list == NULL)
		return FALSE;

	List ptr1 = *a_list;
	List ptr2 = (*a_list)->next;

	//if the node to be removed is the first, it is removed right away
	if (index == 0) {
		free(*a_list);
    	*a_list = ptr2;
		return TRUE;
	}
	
	//otherwise it looks for the item
	int counter = 0;
	while (ptr2 != NULL) { //it keeps looking if the list hasn't ended(index not on list)
		counter++;
		if (index == counter) { //if it is found, removes from mememory and updates references
			ptr1->next = ptr2->next;
			free(ptr2);
			return TRUE;
		}
		ptr1 = ptr2;
		ptr2 = ptr2->next;
	}
	return FALSE;
}

int remove_no_byvalue(List* a_list, void* value){
	if (*a_list == NULL)
		return FALSE;

	int index = -1, i = 0;
	for (List n = *a_list; n != NULL; n = n->next, i++) { //iterates over all vertices
		if (n->value == value) {
			index = i; //Finds the index of the vertex to be removed
			break;
		}
	}

	if(index == -1) //in case it did not find
		return FALSE;

	remove_no(a_list, index); //removes from the graph

	return TRUE;
}

void destroi_lista(List a_list) {
	//Implements a recursive destruction
	if (a_list != NULL) {
		destroi_lista(a_list->next);
	}
	free(a_list);
}
