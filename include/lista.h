/** @file lista.h
 *  @brief LISTA.C header file
 *
 *  Implementa uma biblioteca simples de listas genericas
 *  
 *	@author Eduardo Sousa (eduardoforca) Ana Pergentino(AnaPergentino)
 *  @date 4 Jul 2017
 
**/

#ifndef _LISTA_H_
#define _LISTA_H_

/**
*	List is defined as a pointer to a struct listNode
**/
typedef struct listNode* List;

/**
* 	@brief A generic unordered Linked List
* 	@var	void* value - Pointer to a generic value
*	@var	List next - Pointer to the rest of the list
**/
typedef struct listNode {
	List next;
	void* value;
} *List;

/**
* @brief Creates an empty list
* @return a pointer to the empty list created by the function 
**/
List cria_lista();

/**
* @brief Appends a node to the beginning of a list, doesn't modify the list
* @param List a_list - list where the node will be appended
* @param void* value - generic pointer to the value carried by the node
* @return  a pointer to the head of the list, which is the new node
**/
List adiciona_no(List* a_list, void* value);

/**
* @brief Finds the size of the list
* @param List a_list - list where the node will be appended
* @retval tamanho_list - size of list
**/
int tamanho_list(List a_list);

/**
* @brief Removes a node of a list
* @param List a_list - list where the node will be removed from
* @param int index - location of the node
* @retval 0 - index not on list
* @retval	1 -	node removed succesfully
**/
int remove_no(List* a_list, int index);

/**
* @brief Removes a node of a list by value
* @param List a_list - list where the node will be removed from
* @param void* value - generic pointer to the value carried by the node
* @retval 0 - index not on list
* @retval	1 -	node removed succesfully
**/
int remove_no_byvalue(List* a_list, void* value);

/**
* @brief Destroys a list from the memory, deallocates all nodes
* @param List a_list - list to be destroyed
**/
void destroi_lista(List a_list);

#endif