//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira, Joao Manuel Rodrigues - Dec 2024
//
// Testing the Bellman-Ford algorithm
//

#include <assert.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

int main(void) {
  
  // Instrumentation
  InstrCalibrate();

  double startTime;

  InstrReset();
  startTime = cpu_time();

  // What kind of graph is dig01?
  Graph* dig01 = GraphCreate(6, 1, 0);
  GraphAddEdge(dig01, 1, 2);
  GraphAddEdge(dig01, 1, 4);
  GraphAddEdge(dig01, 3, 4);
  printf("The graph:\n");
  // Displaying in DOT format
  GraphDisplayDOT(dig01);
  printf("\n");

  GraphCheckInvariants(dig01);

  // Bellman-Ford Algorithm

  // Consider each vertex as a start vertex
  for (unsigned int i = 0; i < 6; i++) {
    GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(dig01, i);

    printf("The shortest path tree rooted at %u\n", i);
    GraphBellmanFordAlgDisplayDOT(BF_result);
    printf("\n");

    GraphBellmanFordAlgDestroy(&BF_result);
  }

  double elapsedTime1 = cpu_time() - startTime;

  startTime = cpu_time();

  // What kind of graph is g01?
  Graph* g01 = GraphCreate(6, 0, 0);
  GraphAddEdge(g01, 0, 5);
  GraphAddEdge(g01, 2, 4);
  GraphAddEdge(g01, 2, 3);
  GraphAddEdge(g01, 1, 2);
  GraphAddEdge(g01, 0, 1);
  GraphAddEdge(g01, 3, 4);
  GraphAddEdge(g01, 3, 5);
  GraphAddEdge(g01, 0, 2);
  printf("The graph:\n");
  // Displaying in DOT format
  GraphDisplayDOT(g01);
  printf("\n");

  GraphCheckInvariants(g01);

  // Bellman-Ford Algorithm

  // Consider each vertex as a start vertex
  for (unsigned int i = 0; i < 6; i++) {
    GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(g01, i);

    printf("The shortest path tree rooted at %u\n", i);
    GraphBellmanFordAlgDisplayDOT(BF_result);
    printf("\n");

    GraphBellmanFordAlgDestroy(&BF_result);
  }

  double elapsedTime2 = cpu_time() - startTime;

  startTime = cpu_time();

  // Reading a directed graph from file
  FILE* file = fopen("DG_2.txt", "r");
  Graph* dig03 = GraphFromFile(file);
  fclose(file);
  // Displaying in DOT format
  GraphDisplayDOT(dig03);
  printf("\n");

  GraphCheckInvariants(dig03);

  // Bellman-Ford Algorithm

  // Consider each vertex as a start vertex
  for (unsigned int i = 0; i < GraphGetNumVertices(dig03); i++) {
    GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(dig03, i);

    printf("The shortest path tree rooted at %u\n", i);
    GraphBellmanFordAlgDisplayDOT(BF_result);
    printf("\n");

    GraphBellmanFordAlgDestroy(&BF_result);
  }

  double elapsedTime3 = cpu_time() - startTime;

  char* graphFile[] = {"DG_1.txt", "DAG_1.txt", "DAG_2.txt", "DAG_3.txt", "DAG_4.txt"};
  double elapsedTime4[5];
  int vertices4[5];
  int edges4[5];

  for (int i = 0; i < 5; i++)
  {
    startTime = cpu_time();

    // Reading a directed graph from file
    FILE* file = fopen(graphFile[i], "r");
    if (file == NULL) {
    perror("Error opening file");
    return 1; // Ou retorne o erro desejado
    }
    Graph* dig04 = GraphFromFile(file);
    fclose(file);

    vertices4[i] = GraphGetNumVertices(dig04);
    edges4[i] = GraphGetNumEdges(dig04);
    // Displaying in DOT format
    GraphDisplayDOT(dig04);
    printf("\n");

    GraphCheckInvariants(dig04);

    // Bellman-Ford Algorithm

    // Consider each vertex as a start vertex
    for (unsigned int j = 0; j < GraphGetNumVertices(dig04); j++) {
      GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(dig04, j);

      printf("The shortest path tree rooted at %u\n", j);
      GraphBellmanFordAlgDisplayDOT(BF_result);
      printf("\n");

      GraphBellmanFordAlgDestroy(&BF_result);
    }

    elapsedTime4[i] = cpu_time() - startTime;
    GraphDestroy(&dig04);
  }

  /*
  printf("Elapsed time1: %f seconds\n", elapsedTime1);
  printf("Elapsed time2: %f seconds\n", elapsedTime2);
  printf("Elapsed time3: %f seconds\n", elapsedTime3);

  for (int i = 0; i < 5; i++)
    printf("Elapsed time4[%d]: %f seconds\n", i, elapsedTime4[i]);
  
  printf("Elapsed time1: %f miliseconds\n", elapsedTime1*1000);
  printf("Elapsed time2: %f miliseconds\n", elapsedTime2*1000);
  printf("Elapsed time3: %f miliseconds\n", elapsedTime3*1000);

  for (int i = 0; i < 5; i++)
    printf("Elapsed time4[%d]: %f miliseconds\n", i, elapsedTime4[i]*1000);

  */
  char* graphFile2[] = {"DG_1", "DAG_1", "DAG_2", "DAG_3", "DAG_4"};

  printf("\nElapsed time %-5s v%d-e%-3d: %f seconds\n", "dig01", GraphGetNumVertices(dig01), GraphGetNumEdges(dig01), elapsedTime1);
  printf("Elapsed time %-5s v%d-e%-3d: %f seconds\n", "g01", GraphGetNumVertices(g01), GraphGetNumEdges(g01), elapsedTime2);
  printf("Elapsed time %-5s v%d-e%-3d: %f seconds\n", "DG_2", GraphGetNumVertices(dig03), GraphGetNumEdges(dig03), elapsedTime3);

  for (int i = 0; i < 5; i++) 
    printf("Elapsed time %-5s v%d-e%-3d: %f seconds\n", graphFile2[i], vertices4[i], edges4[i], elapsedTime4[i]);

  printf("Elapsed time %-5s v%d-e%-3d: %f milliseconds\n", "dig01", GraphGetNumVertices(dig01), GraphGetNumEdges(dig01), elapsedTime1 * 1000);
  printf("Elapsed time %-5s v%d-e%-3d: %f milliseconds\n", "g01", GraphGetNumVertices(g01), GraphGetNumEdges(g01), elapsedTime2 * 1000);
  printf("Elapsed time %-5s v%d-e%-3d: %f milliseconds\n", "DG_2", GraphGetNumVertices(dig03), GraphGetNumEdges(dig03), elapsedTime3 * 1000);

  for (int i = 0; i < 5; i++) 
      printf("Elapsed time %-5s v%d-e%-3d: %f milliseconds\n", graphFile2[i], vertices4[i], edges4[i], elapsedTime4[i] * 1000);


  GraphDestroy(&g01);
  GraphDestroy(&dig01);
  GraphDestroy(&dig03);

  return 0;
}
