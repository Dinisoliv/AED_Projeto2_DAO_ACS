//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphEccentricityMeasures
//

// Student Name : André Silva
// Student Number : 119480
// Student Name : Dinis Oliveira
// Student Number : 119193

/*** COMPLETE THE GraphEccentricityMeasuresCompute FUNCTION ***/
/*** COMPLETE THE GraphGetCentralVertices FUNCTION ***/
/*** COMPLETE THE GraphEccentricityMeasuresPrint FUNCTION ***/

#include "GraphEccentricityMeasures.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "Graph.h"
#include "GraphAllPairsShortestDistances.h"

struct _GraphEccentricityMeasures {
  unsigned int*
      centralVertices;  // centralVertices[0] = number of central vertices
                        // array size is (number of central vertices + 1)
  int* eccentricity;    // the eccentricity value of each vertex
  Graph* graph;         // the graph
  int graphRadius;      // the graph radius
  int graphDiameter;    // the graph diameter
};

// Allocate memory
// Compute the vertex eccentricity values
// Compute graph radius and graph diameter
// Compute the set of central vertices
GraphEccentricityMeasures* GraphEccentricityMeasuresCompute(Graph* g) {
  assert(g != NULL);

  // COMPLETE THE CODE
  // CREATE AUXILIARY (static) FUNCTIONS, IF USEFUL
  // Graph radius --- the smallest vertex eccentricity value
  // Graph diameter --- the largest vertex eccentricity value
  // Do not forget that -1 represents an IDEFINITE value

  // Computing the set of central vertices
  // Allocate the central vertices array : number of central vertices + 1
  // Fill in the central vertices array
  unsigned int numVertices = GraphGetNumVertices(g);

  // Allocates the memory for the structure
  GraphEccentricityMeasures* res = (GraphEccentricityMeasures*)malloc(sizeof(GraphEccentricityMeasures));
  assert(res != NULL);

  res->graph = g;
  // Allocates the memory for the eccentricity of the graph
  res->eccentricity = (int*)malloc(numVertices * sizeof(int));
  assert(res->eccentricity != NULL);

  // Gets the shortest distances of all the pairs
  GraphAllPairsShortestDistances* distances = GraphAllPairsShortestDistancesExecute(g);

  // Inicializes the values
  res->graphRadius = INT_MAX;
  res->graphDiameter = 0;

  // Loops trough every pair to calculate the radius, eccentricity and diameter
  for (unsigned int v = 0; v < numVertices; v++) {
    
    int maxDist = 0;
    //Loops to get the maximum distance between vertices (eccentricity)
    for (unsigned int w = 0; w < numVertices; w++) {

      int dist = GraphGetDistanceVW(distances, v, w);
      if (dist > maxDist) {
        maxDist = dist;
      }
    }
    res->eccentricity[v] = maxDist;

    // Updates the radious and diameter
    if (maxDist < res->graphRadius && maxDist != 0) res->graphRadius = maxDist;
    if (maxDist > res->graphDiameter) res->graphDiameter = maxDist;
  }

  //Handle disconected graphs parts
  if (res->graphRadius == INT_MAX) {
    res->graphRadius = res->graphDiameter;
  }

  // Gets the set of central vertices(set of vertices that have eccentricity == radius)
  unsigned int centralCount = 0;
  for (unsigned int v = 0; v < numVertices; v++) {
    if (res->eccentricity[v] == res->graphRadius) {
      centralCount++;
    }
  }

  // Allocates the memory for the set of central Vertices (+1 because [0] is the number of central vertices)
  res->centralVertices = (unsigned int*)malloc((centralCount + 1) * sizeof(unsigned int));
  assert(res->centralVertices != NULL);

  res->centralVertices[0] = centralCount;
  unsigned int index = 1;
  // Adds every Central Vertice in the graph
  for (unsigned int v = 0; v < numVertices; v++) {
    if (res->eccentricity[v] == res->graphRadius) {
      res->centralVertices[index++] = v;
    }
  }

  // Frees the auxiliary memory
  GraphAllPairsShortestDistancesDestroy(&distances);
  return res;
}

void GraphEccentricityMeasuresDestroy(GraphEccentricityMeasures** p) {
  assert(*p != NULL);

  GraphEccentricityMeasures* aux = *p;

  free(aux->centralVertices);
  free(aux->eccentricity);

  free(*p);
  *p = NULL;
}

// Getting the computed measures

int GraphGetRadius(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  return p->graphRadius;
}

int GraphGetDiameter(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  return p->graphDiameter;
}

int GraphGetVertexEccentricity(const GraphEccentricityMeasures* p,
                               unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));
  assert(p->eccentricity != NULL);

  return p->eccentricity[v];
}

// Getting a copy of the set of central vertices
// centralVertices[0] = number of central vertices in the set
unsigned int* GraphGetCentralVertices(const GraphEccentricityMeasures* p) {
  assert(p != NULL);
  assert(p->centralVertices != NULL);
  // Gets the central count 
  unsigned int centralCount = p->centralVertices[0];
  // Allocates the memory for the set
  unsigned int* cpy = (unsigned int*)malloc((centralCount + 1) * sizeof(unsigned int));
  assert(cpy != NULL);

  for (unsigned int i = 0; i <= centralCount; i++) {
    cpy[i] = p->centralVertices[i];
  }
  
  return cpy;
}

// Print the graph radius and diameter
// Print the vertex eccentricity values
// Print the set of central vertices
void GraphEccentricityMeasuresPrint(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  printf("Graph Radius: %d\n", p->graphRadius);
  printf("Graph Diameter: %d\n", p->graphDiameter);

  printf("Vertex Eccentricities:\n");
  for (unsigned int v = 0; v < GraphGetNumVertices(p->graph); v++) {
    printf("Vertex %u: %d\n", v, p->eccentricity[v]);
  }

  printf("Central Vertices: ");
  unsigned int count = p->centralVertices[0];
  for (unsigned int i = 1; i <= count; i++) {
    printf("%u ", p->centralVertices[i]);
  }
  printf("\n");
}
