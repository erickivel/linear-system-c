#include <math.h>
#include <stdlib.h>

#include "../include/linearSystem.h"

void substitution(struct LinearSystem *system, double *solution) {
  int size = system->size;

  for (int i = size - 1; i >= 0; i--) {
    solution[i] = system->b[i];
    for (int j = i + 1; j < size; j++)
      solution[i] -= system->m[i][j] * solution[j];
    solution[i] /= system->m[i][i];
  }
}

int findMax(double **A, int col, int size) {
  int row = col;

  for (int i = col; i < size; i++) {
    if (fabs(A[i][col]) > fabs(A[row][col])) {
      row = i;
    }
  }

  return row;
}

void swapRow(struct LinearSystem *system, int rowA, int rowB) {
  double **A = system->m;
  double *B = system->b;

  for (int i = 0; i < system->size; i++) {
    double aux = A[rowA][i];
    A[rowA][i] = A[rowB][i];
    A[rowB][i] = aux;
  }

  double aux = B[rowA];
  B[rowA] = B[rowB];
  B[rowB] = aux;
}

void gaussElimination(struct LinearSystem *system) {
  int size = system->size;

  for (int i = 0; i < size; ++i) {
    int rowPivot = findMax(system->m, i, system->size);
    if (i != rowPivot) {
      swapRow(system, i, rowPivot);
    }
    for (int k = i + 1; k < size; k++) {
      double m = system->m[k][i] / system->m[i][i];
      system->m[k][i] = 0.0;
      for (int j = i + 1; j < size; j++) {
        system->m[k][j] -= system->m[i][j] * m;
      }
      system->b[k] -= system->b[i] * m;
    }
  }
}

double *solvePivotingWithMult(struct LinearSystem *system) {
  int size = system->size;
  double *solution = malloc(sizeof(double) * size);

  gaussElimination(system);
  substitution(system, solution);

  return solution;
}

void gaussEliminationPartialPivoting(struct LinearSystem *system) {
  int size = system->size;

  for (int i = 0; i < size; i++) {
    int rowPivot = findMax(system->m, i, system->size);
    if (i != rowPivot) {
      swapRow(system, i, rowPivot);
    }
    for (int k = i + 1; k < size; k++) {
      for (int j = i + 1; j < size; j++) {
        system->m[k][j] = system->m[k][j] * system->m[i][i] -
                          system->m[i][j] * system->m[k][i];
      }
      system->b[k] =
          system->b[k] * system->m[i][i] - system->b[i] * system->m[k][i];
    }
  }
}

double *solvePivotingWithoutMult(struct LinearSystem *system) {
  int size = system->size;
  double *solution = malloc(sizeof(double) * size);

  gaussEliminationPartialPivoting(system);
  substitution(system, solution);

  return solution;
}

void withoutPivoting(struct LinearSystem *system) {
  int size = system->size;
  // Diagonal
  for (int i = 0; i < size; i++) {
    // Pivot row
    double d = system->m[i][i];
    for (int j = i; j < size; j++) {
      system->m[i][j] /= d;
    }
    system->b[i] /= d;

    for (int k = i + 1; k < size; k++) {
      double m = system->m[k][i];
      system->m[k][i] = 0.0;
      for (int j = i + 1; j < size; j++) {
        system->m[k][j] -= system->m[i][j] * m;
      }
      system->b[k] -= system->b[i] * m;
    }
  }
}

double *solveWithoutPivoting(struct LinearSystem *system) {
  int size = system->size;
  double *solution = malloc(sizeof(double) * size);

  withoutPivoting(system);
  substitution(system, solution);

  return solution;
}
