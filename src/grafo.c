/* Trabalho 1 de Metodos de Programacao **
** Aluno: Eduardo Sousa da Silva        **
** Matricula: 13/0108405                */

/* GRAFO.C - Implementation of GRAFO.H*/

#define TRUE 1
#define FALSE 0

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

/*ESCOPO PRIVADO DA BIBLIOTECA*/

/*	Definition: Finds a vertex by the identifier
	Parameters: Graph a_graph - the graph to be searched
				int x - identifier of the vertex
	Return: a pointer to the vertex found in the graph*/
Vertex acha_vertice(Graph a_graph, int x) {

	if (a_graph != NULL) {
		for (List n = a_graph->verticesList; n != NULL; n = n->next) {
			if ((((Vertex)(n->value))->id) == x)
				return ((Vertex)(n->value));
		}
	}
	return NULL;
}

/*	Definition: Finds an edge by the identifiers of its vertices
	Parameters: Graph a_graph - the graph to be searched
				int x, y - identifiers of the vertices
	Return: a pointer to the edge found in the graph*/
Edge acha_aresta(Graph a_graph, int x, int y) {

	if (a_graph != NULL) {
		Vertex v = acha_vertice(a_graph, x);
		if(v != NULL){
			for (List n = v->adjList; n != NULL; n = n->next) {
				if ((((Edge)(n->value))->end) == y)
					return ((Edge)(n->value));
			}
		}
	}
	return NULL;
}


/*FIM DO ESCOPO PRIVADO*/


/*ESCOPO PUBLICO DA BIBLIOTECA(ASSIM COMO DEFINIDO EM GRAFO.H)*/


Graph cria_grafo(char* name) {
	
	if (name == NULL)//if an invalid string is passed, the function is terminated
		return NULL;

	Graph a_graph = (Graph)malloc(sizeof(struct graph));
	strcpy(a_graph->name, name);
	a_graph->verticesList = cria_lista();

	return a_graph;
}

char* retorna_nome_grafo(Graph a_graph) {
	if(a_graph != NULL)
		return a_graph->name;
	return NULL;
}
	
int destroi_grafo(Graph a_graph) {
	if (a_graph == NULL)//If the graph is NULL it can't be destroyed
		return FALSE;

	for (List n = a_graph->verticesList; n != NULL; n = n->next) {//removes all the vertices from the graph		
		List adj = ((Vertex)(n->value))->adjList;
		for (List m = adj; m != NULL; m = m->next) { //removes edges from the graph
			free(m->value);
		}
		destroi_lista(adj); //frees adjList
		free((n->value));
	}
	destroi_lista(a_graph->verticesList);
	free(a_graph);

	return TRUE;
}

int adjacente(Graph a_graph, int x, int y) {

	if (a_graph == NULL)
		return FALSE;

	//If there is an edge going from x to y or from y to x, it is adjacent
	if ((acha_aresta(a_graph, x, y) != NULL) || (acha_aresta(a_graph, y, x) != NULL))
		return TRUE;
	return FALSE;
}

int* vizinhos(Graph a_graph, int x) {
	int* neighbours = NULL;
	Vertex v = acha_vertice(a_graph, x);

	if (v != NULL) {

		int count = 0;
		//allocates the array of neighbours
		for (List m = v->adjList; m != NULL; m = m->next) {
			count++;
			int* tmp = (int*)realloc(neighbours, sizeof(int)*count);
			if(tmp != NULL){
				neighbours = tmp; 
			}else{
				free(neighbours);
			}
			neighbours[count - 1] = (((Edge)(m->value))->end);
		}
	}

	return neighbours;
}

int adiciona_vertice(Graph a_graph, int x) {

	if (a_graph == NULL)
		return FALSE;
	if(acha_vertice(a_graph, x) != NULL) //if it already exists a vertice with this identifier
		return FALSE;

	//Creates vertex
	Vertex v = (Vertex)malloc(sizeof(struct vertex));
	v->value = NULL;
	v->id = x;
	v->adjList = cria_lista();

	//adds to graph
	adiciona_no(&(a_graph->verticesList), v);

	return TRUE;
}


int remove_vertice(Graph a_graph, int x) {
	if (a_graph == NULL)
		return FALSE;

	int index = -1, i = 0;
	Vertex v;
	for (List n = a_graph->verticesList; n != NULL; n = n->next, i++) { //iterates over all vertices
		if (((Vertex)(n->value))->id != x) {
			remove_aresta(a_graph, x, ((Vertex)(n->value))->id); //remove all its connections
			remove_aresta(a_graph, ((Vertex)(n->value))->id, x); //remove all its connections
		}
		else {
			index = i; //Finds the index of the vertex to be removed
			remove_aresta(a_graph, x, x); //In case it has a self-directed edge
			v = (Vertex)(n->value);
		}
	}

	if(index == -1) //in case it did not find
		return FALSE;

	destroi_lista(acha_vertice(a_graph, x)->adjList); //frees adjList
	remove_no(&(a_graph->verticesList), index); //removes from the graph
	free(v);

	return TRUE;
}

int adiciona_aresta(Graph a_graph, int x, int y) {
	if (a_graph == NULL)
		return FALSE;
	
	if ((acha_vertice(a_graph, x) == NULL) || (acha_vertice(a_graph, y) == NULL)) // in case one of the vertices doesn't exist
		return FALSE;

	if (acha_aresta(a_graph, x, y) != NULL) // in case the edge already exists
		return FALSE;

	//Creates edge
	Edge e = (Edge)malloc(sizeof(struct edge));
	e->value = NULL;
	e->start = x;
	e->end = y;

	//Adds to graph
	Vertex v = acha_vertice(a_graph, x);
	adiciona_no(&(v->adjList), e);

	return TRUE;
}

int remove_aresta(Graph a_graph, int x, int y) {
	if (a_graph == NULL)
		return FALSE;

	int i = 0;
	Vertex v;

	if((v = acha_vertice(a_graph, x)) != NULL){ //if the vertice x exists
		List xlist = v->adjList;
		for (List n = xlist; n != NULL; n = n->next, i++) { //finds the edge index on adjList
			Edge e = (Edge)(n->value);
			if (e->end == y) {
				if(remove_no(&(v->adjList), i)){ //removes it from the list
					free(e); //free if it was able to remove from list
					return TRUE;
				}else{
					return FALSE;
				}
			}
		}
	}
	return FALSE;
}

void* retorna_valor_vertice(Graph a_graph, int x){
	
	Vertex v;
	if((v = acha_vertice(a_graph, x)) != NULL)
		return v->value;
	return NULL;
}

void* muda_valor_vertice(Graph a_graph, int x, void* v)
{
	Vertex vertex = acha_vertice(a_graph, x);

	if(vertex != NULL)
		return(vertex->value = v);

	return NULL;

}

void* retorna_valor_aresta(Graph a_graph, int x, int y){
	Edge e;
	if((e = acha_aresta(a_graph, x, y)) != NULL)
		return e->value;
	return NULL;
}

void* muda_valor_aresta(Graph a_graph, int x, int y, void* v){
	Edge edge = acha_aresta(a_graph, x, y);

	if(edge != NULL)
		return(edge->value = v);

	return NULL;
}
