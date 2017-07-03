/* Trabalho 1 de Metodos de Programacao **
** Aluno: Eduardo Sousa da Silva        **
** Matricula: 13/0108405                */

/* GRAFO.H - Header file, implemented by GRAFO.C*/
#ifndef _GRAFO_H_
#define _GRAFO_H_
#include "lista.h"

/*	Graph is defined as a pointer to a struct graph*/
typedef struct graph *Graph;

/*	Definition: Creates an empty graph called nome
	Parameters: char* nome - string containing the name of the graph
	Return: a pointer to the empty graph created by the function */
Graph cria_grafo(char* name);

/*	Definition: Returns the name of a graph 
	Parameters: Graph a_graph - The pointer to the graph from which you want to get the name
	Return: a string containing the name of a_graph*/
char* retorna_nome_grafo(Graph a_graph);

/*	Definition: Removes a graph from memory
	Parameters: Graph a_graph - The pointer to the graph you want to destroy
	Return: 0 - a_graph couldn't be destroyed
			1 - a_graph was successfull destroyed*/
int destroi_grafo(Graph a_graph);

/*	Definition: Checks if two vertices on a graph are adjacents
	Parameters: Graph a_graph - The graph to be checked
				int x, y - Identifiers of the vertices to be checked
	Return: 0 - x and y are not adjacent
			1 - x and y are indeed adjacent*/
int adjacente(Graph a_graph, int x, int y);

/*	Definition: Returns all vertices neighbour to x
	Parameters: Graph a_graph - graph to be checked
				int x - Identifier of the vertex to be checked
	Return: Array of the identifiers of the vertices neighbour to x, caller function should deal 
	with memory deallocation of this array*/
int* vizinhos(Graph a_graph, int x);

/*	Definition: Adds a new vertex to a graph
	Parameters: Graph a_graph - graph where the vertex will be added
				int x - Identifier of the vertex to be added
	Return: 0 - Couldn't add vertex
			1 - Vertex added successfully*/
int adiciona_vertice(Graph a_graph, int x);

/*	Definition: Removes a vertex from a graph
	Parameters: Graph a_graph - graph from where the vertex will be removed
				int x - Identifier of the vertex to be removed
	Return: 0 - Couldn't remove vertex
			1 - Vertex removed successfully*/
int remove_vertice(Graph a_graph, int x);

/*	Definition: Adds an edge to a graph
	Parameters:	Graph a_graph - graph where the edge will be added
				int x, y - Identifiers of the vertices linked by the edge
	Return: 0 - Couldn't add edge
			1 - Edge added successfully*/
int adiciona_aresta(Graph a_graph, int x, int y);

/*	Definition: Removes an edge from a graph
	Parameters: Graph a_graph - graph from where the edge will be removed
				int x, y - Identifiers of the vertices linked by the removed edge
	Return: 0 - Couldn't remove edge
			1 - Edge removed successfully*/
int remove_aresta(Graph a_graph, int x, int y);

/*	Definition: Returns the value of a vertex matched by an identifier
	Parameters: Graph a_graph - graph where the vertex is located
				int x - Vertex identifier
	Return: void* v - value on vertex x
			NULL - Couldn't find x on a_graph*/
void* retorna_valor_vertice(Graph a_graph, int x);

/*	Definition: Changes the value stored on a vertex in a graph
	Parameters:	Graph a_graph - graph where the vertex is located
				int x - Vertex identifier
				void* v - new value on x
	Return: void* v - new value on x
			NULL - Couldn't change value of x*/
void* muda_valor_vertice(Graph a_graph, int x, void* v);

/*	Definition: Returns the value of the edge linking two vertices
	Parameters: Graph a_graph - graph where the edge is located
				int x, y - Identifiers of the vertices linked by the edge
	Return: void* e - value on the edge linking x and y
			NULL - couldn't find the edge on a_graph*/
void* retorna_valor_aresta(Graph a_graph, int x, int y);

/*	Definition: Changes the value stored on a edge in a graph
	Parameters:	Graph a_graph - graph where the edge linking x and y is located
				int x, y - Identifiers of the vertices linked by the edge
				void* v - new value of the edge linking x and y
	Return: void* e - new value on the edge linking x and y
			NULL - couldn't change the value of the edge on a_graph*/
void* muda_valor_aresta(Graph a_graph, int x, int y, void* v);

#endif
