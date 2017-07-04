/* Trabalho 1 de Metodos de Programacao **
** Aluno: Eduardo Sousa da Silva        **
** Matricula: 13/0108405                */

/* LISTA.H - Header file, implemented by LISTA.C*/

#ifndef _LISTA_H_
#define _LISTA_H_

/*	List is defined as a pointer to a struct listNode*/
typedef struct listNode* List;

/*	Definition: A generic unordered Linked List
	Members:	void* value - Pointer to a generic value
				List next - Pointer to the rest of the list*/
typedef struct listNode {
	List next;
	void* value;
} *List;



/*	Definition: Creates an empty list
	Return: a pointer to the empty list created by the function */
List cria_lista();


/*	Definition: Appends a node to the beginning of a list, doesn't modify the list
	Parameters: List a_list - list where the node will be appended
				void* value - generic pointer to the value carried by the node
	Return: a pointer to the head of the list, which is the new node*/
List adiciona_no(List* a_list, void* value);

int tamanho_list(List a_list);

/*	Definition: Removes a node of a list
	Parameters: List a_list - list where the node will be removed from
				int index - location of the node
	Return: 0 - index not on list
			1 -	node removed succesfully*/
int remove_no(List* a_list, int index);

int remove_no_byvalue(List* a_list, void* value);

/*	Definition: Destroys a list from the memory, deallocates all nodes
	Parameters: List a_list - list to be destroyed*/
void destroi_lista(List a_list);

#endif