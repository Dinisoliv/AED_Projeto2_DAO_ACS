//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphTransitiveClosure - Transitive Closure of a directed graph
//

// Student Name : André Silva
// Student Number : 119480
// Student Name : Dinis Oliveira
// Student Number : 119193

/*** COMPLETE THE GraphComputeTransitiveClosure FUNCTION ***/

#include "GraphTransitiveClosure.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

// Compute the transitive closure of a directed graph
// Return the computed transitive closure as a directed graph
// Use the Bellman-Ford algorithm
Graph* GraphComputeTransitiveClosure(Graph* g) {
  assert(g != NULL);
  assert(GraphIsDigraph(g));
  assert(GraphIsWeighted(g) == 0);

  //gets the number of vertices
  unsigned int numVertices = GraphGetNumVertices(g);

  //Creates a new Diagraph with the same number of vertices and not weighted
  Graph* transitiveClosure = GraphCreate(numVertices, 1, 0); 

  //iterates trough every vertice
  for(unsigned int i = 0; i < numVertices; i++){
    //executes the Bellman-Ford algorithm 
    GraphBellmanFordAlg* bfa = GraphBellmanFordAlgExecute(g, i);
    //iterates trough every vertice
    for(unsigned int j = 0; j < numVertices; j++){
      if(GraphBellmanFordAlgReached(bfa, j)/*  && j != i se não incluir laços */){
        //Adds the transitive closure edge 
        GraphAddEdge(transitiveClosure, i, j);
      }
    }
    //frees the memory
    GraphBellmanFordAlgDestroy(&bfa); 
  }
  return transitiveClosure;
}
