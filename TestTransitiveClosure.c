//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira, Joao Manuel Rodrigues - Dec 2024
//
// Testing the Transitive Closure algorithm
//

#include <assert.h>

#include "Graph.h"
#include "GraphTransitiveClosure.h"
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

  Graph* tcdig01 = GraphComputeTransitiveClosure(dig01);
  printf("The transitive closure:\n");
  // Displaying in DOT format
  GraphDisplayDOT(tcdig01);
  printf("\n");

  GraphCheckInvariants(tcdig01);

  double elapsedTime1 = cpu_time() - startTime;

  startTime = cpu_time();

  // Reading a directed graph from file
  FILE* file = fopen("DG_2.txt", "r");
  Graph* dig03 = GraphFromFile(file);
  fclose(file);
  // Displaying in DOT format
  GraphDisplayDOT(dig03);
  printf("\n");

  GraphCheckInvariants(dig03);

  Graph* tcdig03 = GraphComputeTransitiveClosure(dig03);
  printf("The transitive closure:\n");
  // Displaying in DOT format
  GraphDisplayDOT(tcdig03);
  printf("\n");

  GraphCheckInvariants(tcdig03);

  double elapsedTime2 = cpu_time() - startTime;

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

    // ComputeTransitiveClosure

    Graph* tcdig03 = GraphComputeTransitiveClosure(dig03);
    printf("The transitive closure:\n");
    // Displaying in DOT format
    GraphDisplayDOT(tcdig03);
    printf("\n");

    elapsedTime4[i] = cpu_time() - startTime;
    GraphDestroy(&dig04);
  }

  /*
  printf("Elapsed time1: %f seconds\n", elapsedTime1);
  printf("Elapsed time2: %f seconds\n", elapsedTime2);

  printf("Elapsed time1: %f miliseconds\n", elapsedTime1*1000);
  printf("Elapsed time2: %f miliseconds\n", elapsedTime2*1000);
  */

  char* graphFile2[] = {"DG_1", "DAG_1", "DAG_2", "DAG_3", "DAG_4"};

  printf("\n\n");
  printf("Elapsed time %-5s v%d-e%-3d: %f seconds\n", "dig01", GraphGetNumVertices(dig01), GraphGetNumEdges(dig01), elapsedTime1);
  printf("Elapsed time %-5s v%d-e%-3d: %f seconds\n", "DG_2", GraphGetNumVertices(dig03), GraphGetNumEdges(dig03), elapsedTime2);

  for (int i = 0; i < 5; i++) 
    printf("Elapsed time %-5s v%d-e%-3d: %f seconds\n", graphFile2[i], vertices4[i], edges4[i], elapsedTime4[i]);

  printf("Elapsed time %-5s v%d-e%-3d: %f milliseconds\n", "dig01", GraphGetNumVertices(dig01), GraphGetNumEdges(dig01), elapsedTime1 * 1000);
  printf("Elapsed time %-5s v%d-e%-3d: %f milliseconds\n", "DG_2", GraphGetNumVertices(dig03), GraphGetNumEdges(dig03), elapsedTime2 * 1000);

  for (int i = 0; i < 5; i++) 
      printf("Elapsed time %-5s v%d-e%-3d: %f milliseconds\n", graphFile2[i], vertices4[i], edges4[i], elapsedTime4[i] * 1000);


  GraphDestroy(&dig01);
  GraphDestroy(&dig03);

  GraphDestroy(&tcdig01);
  GraphDestroy(&tcdig03);

  return 0;
}
