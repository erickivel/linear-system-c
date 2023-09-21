// #include <likwid.h>
#include <stdio.h>
#include <sys/time.h>

#include "../include/linearSystem.h"
#include <likwid.h>

int main() {
  // Arrange
  int size;
  scanf("%d", &size);

  struct timeval start1, start2, start3, end1, end2, end3;

  struct LinearSystem *system = createLinearSystem(size);

  readLinearSystem(system);

  struct LinearSystem *copy1 = copyLinearSystem(system);
  struct LinearSystem *copy2 = copyLinearSystem(system);
  struct LinearSystem *copy3 = copyLinearSystem(system);

  LIKWID_MARKER_INIT;

  // Calculate
  LIKWID_MARKER_START("Sol_1");
  gettimeofday(&start1, NULL);
  double *solution1 = solvePivotingWithMult(copy1);
  gettimeofday(&end1, NULL);
  LIKWID_MARKER_STOP("Sol_1");

  LIKWID_MARKER_START("Sol_2");
  gettimeofday(&start2, NULL);
  double *solution2 = solvePivotingWithoutMult(copy2);
  gettimeofday(&end2, NULL);
  LIKWID_MARKER_STOP("Sol_2");

  LIKWID_MARKER_STOP("Sol_3");
  gettimeofday(&start3, NULL);
  double *solution3 = solveWithoutPivoting(copy3);
  gettimeofday(&end3, NULL);
  LIKWID_MARKER_STOP("Sol_3");

  LIKWID_MARKER_CLOSE;

  double *residue1 = calculateResidualVector(system, solution1);
  double *residue2 = calculateResidualVector(system, solution2);
  double *residue3 = calculateResidualVector(system, solution3);

  // Show
  printf("\n");
  printf("Substituição de Gauss com multiplicador:\n");
  printSolution(solution1, size);
  printResidualVector(residue1, size);
  printTime(start1, end1);
  printf("\n");

  printf("Substituição de Gauss sem multiplicador:\n");
  printSolution(solution2, size);
  printResidualVector(residue2, size);
  printTime(start2, end2);
  printf("\n");

  printf("Sem pivoteamento: \n");
  printSolution(solution3, size);
  printResidualVector(residue3, size);
  printTime(start3, end3);
  printf("\n");

  // Free
  freeSystem(system);
  freeSystem(copy1);
  freeSystem(copy2);
  freeSystem(copy3);
  freeDoubleArray(solution1);
  freeDoubleArray(solution2);
  freeDoubleArray(solution3);
  freeDoubleArray(residue1);
  freeDoubleArray(residue2);
  freeDoubleArray(residue3);
}
