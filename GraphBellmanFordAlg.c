//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphBellmanFord - Bellman-Ford Algorithm
//

// Student Name : Dinis Oliveira
// Student Number : 119193
// Student Name : André Silva
// Student Number : 119480

/*** COMPLETE THE GraphBellmanFordAlgExecute FUNCTION ***/

#include "GraphBellmanFordAlg.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "Graph.h"
#include "IntegersStack.h"
#include "instrumentation.h"

struct _GraphBellmanFordAlg {
  unsigned int* marked;  // To mark vertices when reached for the first time
  int* distance;  // The number of edges on the path from the start vertex
                  // distance[i]=-1, if no path found from the start vertex to i
  int* predecessor;  // The predecessor vertex in the shortest path
                     // predecessor[i]=-1, if no predecessor exists
  Graph* graph;
  unsigned int startVertex;  // The root of the shortest-paths tree
};

GraphBellmanFordAlg* GraphBellmanFordAlgExecute(Graph* g,
                                                unsigned int startVertex) {
  assert(g != NULL);
  assert(startVertex < GraphGetNumVertices(g));
  assert(GraphIsWeighted(g) == 0);

  GraphBellmanFordAlg* result =
      (GraphBellmanFordAlg*)malloc(sizeof(struct _GraphBellmanFordAlg));
  assert(result != NULL);

  // Given graph and start vertex for the shortest-paths
  result->graph = g;
  result->startVertex = startVertex;

  unsigned int numVertices = GraphGetNumVertices(g);

  // CREATE AND INITIALIZE
  // result->marked
  // result->distance
  // result->predecessor

  // Mark all vertices as not yet visited, i.e., ZERO
  
  // No vertex has (yet) a (valid) predecessor
  
  // No vertex has (yet) a (valid) distance to the start vertex
  
  // THE ALGORTIHM TO BUILD THE SHORTEST-PATHS TREE

  // Step 1
  // Create arrays
  result->distance = (int*)malloc(numVertices * sizeof(int));
  result->predecessor = (int*)malloc(numVertices * sizeof(int));
  result->marked = (unsigned int*)malloc(numVertices * sizeof(unsigned int));
  // Check if the memory allocation was successful
  if (result->distance == NULL || result->predecessor == NULL || result->marked == NULL)
  {
    free(result->distance);
    free(result->predecessor);
    free(result->marked);
    free(result);
    return NULL;
  }
  // Initialize the arrays
  for (unsigned i = 0; i < numVertices; i++)
  {
    result->distance[i] = INT_MAX;
    result->predecessor[i] = -1;
    result->marked[i] = 0;
  }
  result->distance[startVertex] = 0;

  // Step 2
  // Relax all edges V-1 times
  for (unsigned int i = 1; i < numVertices-1; i++)
  {
    int relaxed = 0;  // Flag - bool
    for (unsigned int v = 0; v < numVertices; v++)
    {
      unsigned int* adjList = GraphGetAdjacentsTo(g, v);
      if (adjList == NULL)
      {
        continue;
      }

      // Relax edges from vertex v to its adjacent vertices
      for (unsigned int j = 1; j <= adjList[0]; j++) {
        unsigned int w = adjList[j];  // Adjacent vertex
        if (result->distance[v] != INT_MAX && result->distance[v] + 1 < result->distance[w]) {
          result->distance[w] = result->distance[v] + 1;
          result->predecessor[w] = v;
          result->marked[w] = 1;
          relaxed = 1;
        }
      }      
      free(adjList);
    }
    if (!relaxed)
      break;
  }
  /*
  // Step 3 - simple
  // Check for negative cycles
  for (unsigned int v = 0; v < numVertices; v++) {
    unsigned int* adjList = GraphGetAdjacentsTo(g, v);
    for (unsigned int i = 1; i < adjList[0]; i++) {
      unsigned int w = adjList[i];
      if (result->distance[v] != INT_MAX && result->distance[v] + 1 < result->distance[w]) {
        free(result->distance);
        free(result->predecessor);
        free(result->marked);
        free(result);
        free(adjList);
        return NULL;
      }
    }
    free(adjList);
  }
  */

  // Step 3 
  // Check for negative cycles
  /*
  for (unsigned int v = 0; v < numVertices; v++) {
    int* adjList = GraphGetAdjacentsTo(g, v);

    int vertexDegree = GraphIsDigraph(result->graph) ? GraphGetVertexOutDegree(g, v) : GraphGetVertexDegree(g, v);
    for (unsigned int i = 0; i < vertexDegree; i++) {
    unsigned int w = adjList[i];
      if (result->distance[v] != INT_MAX && result->distance[v] + 1 < result->distance[w]) {
        result->predecessor[w] = v;

        for (unsigned int j = 0; j < numVertices; j++)
        {
          result->marked[j] = 0;
        }

        result->marked[w] = 1;
        while (result->marked[v] == 0)
        {
          result->marked[v] = 1;
          v = result->predecessor[v];
        }

        int cycleStart = v;
        int* ncycle = (int*)malloc(numVertices * sizeof(int));

        if (ncycle == NULL)
        {
          free(result->distance);
          free(result->predecessor);
          free(result->marked);
          free(result);
          free(adjList);
          return NULL;
        }
        
        int cycleLength = 0;
        ncycle[cycleLength++] = v;
        w = result->predecessor[v];
        while (w != cycleStart)
        {
          ncycle[cycleLength++] = w;
          w = result->predecessor[w];  
        }
        ncycle[cycleLength++] = cycleStart;

        printf("Graph contains a negative-weight cycle: ");
        for (int k = cycleLength - 1; k >= 0; k--)
        {
          printf("%d ", ncycle[k]);
        }
        free(ncycle);
        free(result->distance);
        free(result->predecessor);
        free(result->marked);
        free(result);
        free(adjList);
        return NULL;
      }
    }
  }
  */
  
  // Step 3: Detect and Print Negative Cycles
  for (unsigned int v = 0; v < numVertices; v++) {
    unsigned* adjList = GraphGetAdjacentsTo(g, v);
    
    for (unsigned int i = 1; i < adjList[0]; i++) {
      unsigned int w = adjList[i];
      if (result->distance[v] != INT_MAX && result->distance[v] + 1 < result->distance[w]) {
        printf("Negative cycle detected starting from vertex %u.\n", w);

        // Trace the negative cycle
        unsigned int x = w;
        for (unsigned int j = 0; j < numVertices; j++) x = result->predecessor[x]; // Step into the cycle
        
        unsigned int cycleStart = x;
        printf("Cycle: ");
        do {
          printf("%u -> ", x);
          x = result->predecessor[x];
        } while (x != cycleStart);
        printf("%u\n", cycleStart);

        // Clean up memory
        free(adjList);
        free(result->distance);
        free(result->predecessor);
        free(result->marked);
        free(result);
        return NULL;
      }
    }
    free(adjList);
  }

  return result;
}

void GraphBellmanFordAlgDestroy(GraphBellmanFordAlg** p) {
  assert(*p != NULL);

  GraphBellmanFordAlg* aux = *p;

  free(aux->marked);
  free(aux->predecessor);
  free(aux->distance);

  free(*p);
  *p = NULL;
}

// Getting the paths information

int GraphBellmanFordAlgReached(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->marked[v];
}

int GraphBellmanFordAlgDistance(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->distance[v];
}
Stack* GraphBellmanFordAlgPathTo(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack* s = StackCreate(GraphGetNumVertices(p->graph));

  if (p->marked[v] == 0) {
    return s;
  }

  // Store the path
  for (unsigned int current = v; current != p->startVertex;
       current = p->predecessor[current]) {
    StackPush(s, current);
  }

  StackPush(s, p->startVertex);

  return s;
}

// DISPLAYING on the console

void GraphBellmanFordAlgShowPath(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack* s = GraphBellmanFordAlgPathTo(p, v);

  while (StackIsEmpty(s) == 0) {
    printf("%d", StackPop(s));
  }

  StackDestroy(&s);
}

// Display the Shortest-Paths Tree in DOT format
void GraphBellmanFordAlgDisplayDOT(const GraphBellmanFordAlg* p) {
  assert(p != NULL);

  Graph* original_graph = p->graph;
  unsigned int num_vertices = GraphGetNumVertices(original_graph);

  // The paths tree is a digraph, with no edge weights
  Graph* paths_tree = GraphCreate(num_vertices, 1, 0);

  // Use the predecessors array to add the tree edges
  for (unsigned int w = 0; w < num_vertices; w++) {
    // Vertex w has a predecessor vertex v?
    int v = p->predecessor[w];
    if (v != -1) {
      GraphAddEdge(paths_tree, (unsigned int)v, w);
    }
  }

  // Display the tree in the DOT format
  GraphDisplayDOT(paths_tree);

  // Housekeeping
  GraphDestroy(&paths_tree);
}
