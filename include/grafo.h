/** @file grafo.h
 *  @brief GRAFO.C header file
 *
 *  Implementa uma biblioteca simples de grafos direcionados
 *  
 *	@author Eduardo Sousa (eduardoforca) Ana Pergentino(AnaPergentino)
 *  @date 4 Jul 2017
**/

#ifndef _GRAFO_H_
#define _GRAFO_H_
#include "lista.h"

/**	
* Graph is defined as a pointer to a struct graph
**/
typedef struct graph *Graph;

/**
*	@brief Directed graph structure
*	@var char* name - user assigned name to the graph, can't be NULL
*	@var List adjList - headers list containing all the vertices on the graph, uses the List structure defined by list.h
**/
struct graph {
	List verticesList;
	char name[100];
};

/**	
*   Edge is defined as a pointer to an edge
*	@brief Edge of a graph, connects two vertices
*	@var void* value - generic value to be stored on the edge
*	@var int start, end - identifiers of the vertices on the start and end of the edge(for a directed graph)
**/
typedef struct edge {
	void* value;
	int start, end;
} *Edge;

/**	
*	Vertex is defined as a pointer to a vertex
*	@brief Vertex of a graph, or a node
*	@var void* value - generic value to be stored on the vertex
*	@var int id - identifier of the vertex(defined by user, must be unique)
* 	@var List adjList - adjacency list containing all the edges connected to this vertex, uses the List structure defined by list.h
**/
typedef struct vertex {
	List adjList;
	void* value;
	int id;

} *Vertex;


/**
*	@brief Creates an empty graph called nome
*	@param char* nome - string containing the name of the graph
*	@return a pointer to the empty graph created by the function 
**/
Graph cria_grafo(char* name);

/**
*	@brief Returns the name of a graph 
*	@param  Graph a_graph - The pointer to the graph from which you want to get the name
*	@return a string containing the name of a_graph
**/
char* retorna_nome_grafo(Graph a_graph);

/**
*	@brief Removes a graph from memory
*	@param  Graph a_graph - The pointer to the graph you want to destroy
*	@retval 0 - a_graph couldn't be destroyed
*	@retval 1 - a_graph was successfull destroyed
**/
int destroi_grafo(Graph a_graph);

/**
*	@brief Checks if two vertices on a graph are adjacentsc
*	@param  Graph a_graph - The graph to be checked
*	@param  int x - Identifiers of the vertices linked by the edge to be checked
*	@param	int y - Identifiers of the vertices linked by the edge to be checked
*	@retval 0 - x and y are not adjacent
*	@retval 1 - x and y are indeed adjacent
**/
int adjacente(Graph a_graph, int x, int y);

/**
*	@brief Returns all vertices neighbour to x
*	@param  Graph a_graph - graph to be checked
*	@param  int x - Identifier of the vertex to be checked
*	@return Array of the identifiers of the vertices neighbour to x, caller function should deal 
*	with memory deallocation of this array
*
**/
int* vizinhos(Graph a_graph, int x);

/**
*	@brief Adds a new vertex to a graph
*	@param  Graph a_graph - graph where the vertex will be added
*	@param  int x - Identifier of the vertex to be added
*	@retval 0 - Couldn't add vertex
*	@retval 1 - Vertex added successfully
**/
int adiciona_vertice(Graph a_graph, int x);

/**
*	@brief Removes a vertex from a graph
*	@param  Graph a_graph - graph from where the vertex will be removed
*	@param  int x - Identifier of the vertex to be removed
*	@retval 0 - Couldn't remove vertex
*	@retval 1 - Vertex removed successfully
**/
int remove_vertice(Graph a_graph, int x);

/**
*	@brief Adds an edge to a graph
*	@param 	Graph a_graph - graph where the edge will be added
*	@param  int x - Identifiers of the vertices linked by the edge
*	@param	int y - Identifiers of the vertices linked by the edge
*	@retval 0 - Couldn't add edge
*	@retval 1 - Edge added successfully
**/
int adiciona_aresta(Graph a_graph, int x, int y);

/**
*	@brief Removes an edge from a graph
*	@param  Graph a_graph - graph from where the edge will be removed
*	@param  int x - Identifiers of the vertices linked by the edge
*	@param	int y - Identifiers of the vertices linked by the edge
*	@retval 0 - Couldn't remove edge
*	@retval 1 - Edge removed successfully
**/
int remove_aresta(Graph a_graph, int x, int y);

/**
*	@brief Returns the value of a vertex matched by an identifier
*	@param  Graph a_graph - graph where the vertex is located
*	@param  int x - Vertex identifier
*	@return void* v - value on vertex x
*	@retval NULL - Couldn't find x on a_graph
**/
void* retorna_valor_vertice(Graph a_graph, int x);

/**
*	@brief Changes the value stored on a vertex in a graph
*	@param 	Graph a_graph - graph where the vertex is located
*	@param  int x - Vertex identifier
*	@param  void* v - new value on x
*	@return void* v - new value on x
*	@retval NULL - Couldn't change value of x
**/
void* muda_valor_vertice(Graph a_graph, int x, void* v);

/**
*	@brief Returns the value of the edge linking two vertices
*	@param  Graph a_graph - graph where the edge is located
*	@param  int x - Identifiers of the vertices linked by the edge
*	@param  int y - Identifiers of the vertices linked by the edge
*	@return void* e - value on the edge linking x and y
*	@retval NULL - couldn't find the edge on a_graph
**/
void* retorna_valor_aresta(Graph a_graph, int x, int y);

/**
*	@brief Changes the value stored on a edge in a graph
*	@param 	Graph a_graph - graph where the edge linking x and y is located
*	@param  int x - Identifiers of the vertices linked by the edge
*	@param	int y - Identifiers of the vertices linked by the edge
*	@param  void* v - new value of the edge linking x and y
*	@return void* e - new value on the edge linking x and y
*	@retval NULL - couldn't change the value of the edge on a_graph
**/
void* muda_valor_aresta(Graph a_graph, int x, int y, void* v);

#endif
