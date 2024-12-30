//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphAllPairsShortestDistances
//

// Student Name : André Silva
// Student Number : 119480
// Student Name : Dinis Oliveira
// Student Number : 119193

/*** COMPLETE THE GraphAllPairsShortestDistancesExecute FUNCTION ***/

#include "GraphAllPairsShortestDistances.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"

struct _GraphAllPairsShortestDistances {
  int** distance;  // The 2D matrix storing the all-pairs shortest distances
                   // It is stored as an array of pointers to 1D rows
                   // Idea: an INDEFINITE distance value is stored as -1
  Graph* graph;
};

// Allocate memory and initialize the distance matrix
// Compute the distances between vertices by running the Bellman-Ford algorithm
GraphAllPairsShortestDistances* GraphAllPairsShortestDistancesExecute(
    Graph* g) {
  assert(g != NULL);

  unsigned int numVertices = GraphGetNumVertices(g);

   // Allocates the memory for the structure
  GraphAllPairsShortestDistances* res =  (GraphAllPairsShortestDistances*)malloc(sizeof(GraphAllPairsShortestDistances));

  res->graph = g;
  // Allocates the memory for the distance matrix
  res->distance = (int**)malloc(numVertices * sizeof(int*));
  // Ensures the memory allocation is succesful
  assert(res->distance != NULL);
  // Loop to alocate the memory for every distance in the matrix
  for (unsigned int i = 0; i < numVertices; i++) {
    res->distance[i] = (int*)malloc(numVertices * sizeof(int));
    // Ensures the memory allocation is succesful
    assert(res->distance[i] != NULL);
  }

  // Computes the shortest distances using Bellman-Ford Algorithm
  for (unsigned int v = 0; v < numVertices; v++) {
    GraphBellmanFordAlg* bfa = GraphBellmanFordAlgExecute(g, v);

    for (unsigned int w = 0; w < numVertices; w++) {
      // Saves the shortest distance in the graph  
      if (GraphBellmanFordAlgReached(bfa, w)) {
        res->distance[v][w] = GraphBellmanFordAlgDistance(bfa, w);
      }else if(v == w){
        res->distance[v][w] = 0;  // Distance to itself is 0
      }else{
        res->distance[v][w] = -1; // INFINITY
      }
    }

    GraphBellmanFordAlgDestroy(&bfa);
  }

  return res;
}

void GraphAllPairsShortestDistancesDestroy(GraphAllPairsShortestDistances** p) {
  assert(*p != NULL);

  GraphAllPairsShortestDistances* aux = *p;
  unsigned int numVertices = GraphGetNumVertices(aux->graph);

  for (unsigned int i = 0; i < numVertices; i++) {
    free(aux->distance[i]);
  }

  free(aux->distance);

  free(*p);
  *p = NULL;
}

// Getting the result

int GraphGetDistanceVW(const GraphAllPairsShortestDistances* p, unsigned int v,
                       unsigned int w) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));
  assert(w < GraphGetNumVertices(p->graph));

  return p->distance[v][w];
}

// DISPLAYING on the console

void GraphAllPairsShortestDistancesPrint(
    const GraphAllPairsShortestDistances* p) {
  assert(p != NULL);

  unsigned int numVertices = GraphGetNumVertices(p->graph);
  printf("Graph distance matrix - %u vertices\n", numVertices);

  for (unsigned int i = 0; i < numVertices; i++) {
    for (unsigned int j = 0; j < numVertices; j++) {
      int distanceIJ = p->distance[i][j];
      if (distanceIJ == -1) {
        // INFINITY - j was not reached from i
        printf(" INF");
      } else {
        printf(" %3d", distanceIJ);
      }
    }
    printf("\n");
  }
}
