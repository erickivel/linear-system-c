#include <likwid.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/linearSystem.h"

int main() {
  int size;
  scanf("%d", &size);

  struct LinearSystem *system = createLinearSystem(size);

  readLinearSystem(system);

  struct LinearSystem *copy = copyLinearSystem(system);
  struct LinearSystem *copy2 = copyLinearSystem(system);
  struct LinearSystem *copy3 = copyLinearSystem(system);

  LIKWID_MARKER_INIT;

  LIKWID_MARKER_START("Solve_1");
  double *solution1 = solvePivotingWithMult(copy);
  LIKWID_MARKER_STOP("Solve_1");

  LIKWID_MARKER_CLOSE;

  // LIKWID_MARKER_START("Solve_2");
  double *solution2 = solvePivotingWithoutMult(copy2);
  // LIKWID_MARKER_STOP("Solve_2");

  // LIKWID_MARKER_START("Solve_3");
  double *solution3 = solveWithoutPivoting(copy3);
  // LIKWID_MARKER_STOP("Solve_3");

  double *residue1 = calculateResidualVector(system, solution1);
  double *residue2 = calculateResidualVector(system, solution2);
  double *residue3 = calculateResidualVector(system, solution3);

  printSolution(solution1, size);
  printResidualVector(residue1, size);
  printSolution(solution2, size);
  printResidualVector(residue2, size);
  printSolution(solution3, size);
  printResidualVector(residue3, size);
}
