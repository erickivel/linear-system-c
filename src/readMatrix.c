#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/linearSystem.h"

struct LinearSystem *createLinearSystem(int size) {
  struct LinearSystem *system = malloc(sizeof(struct LinearSystem));

  system->size = size;
  system->b = malloc(sizeof(double) * size);
  system->m = malloc(sizeof(double) * size);

  for (int i = 0; i < size; i++) {
    system->m[i] = malloc(sizeof(double) * size);
  }

  return system;
}

void readLinearSystem(struct LinearSystem *system) {
  int size = system->size;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j <= size; j++) {
      if (j == size) {
        scanf("%lf", &system->b[i]);
      } else {
        scanf("%lf", &system->m[i][j]);
      }
    }
  }
}

struct LinearSystem *copyLinearSystem(struct LinearSystem *system) {
  int size = system->size;

  struct LinearSystem *systemCopy = createLinearSystem(size);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      systemCopy->m[i][j] = system->m[i][j];
    }
  }

  for (int i = 0; i < size; i++) {
    systemCopy->b[i] = system->b[i];
  }

  return systemCopy;
}

void retrossubs(struct LinearSystem *system, double *solution) {
  int size = system->size;

  for (int i = size - 1; i >= 0; i--) {
    solution[i] = system->b[i];
    for (int j = i + 1; j < size; j++)
      solution[i] -= system->m[i][j] * solution[j];
    solution[i] /= system->m[i][i];
  }
}

int encontraMax(double **A, int col, int size) {
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

void eliminacaoGauss(struct LinearSystem *system) {
  int size = system->size;

  for (int i = 0; i < size; ++i) {
    int rowPivot = encontraMax(system->m, i, system->size);
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

  eliminacaoGauss(system);
  retrossubs(system, solution);

  return solution;
}

void eliminacaoGaussPartialPivoting(struct LinearSystem *system) {
  int size = system->size;

  for (int i = 0; i < size; i++) {
    int rowPivot = encontraMax(system->m, i, system->size);
    if (i != rowPivot) {
      swapRow(system, i, rowPivot);
    }
    for (int k = i + 1; k < size; k++) {

      // double m = system->m[k][i] / system->m[i][i];
      // system->m[k][i] = 0.0;
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

  eliminacaoGaussPartialPivoting(system);
  retrossubs(system, solution);

  return solution;
}

void thirdMethod(struct LinearSystem *system) {
  int size = system->size;

  // Diagonal
  for (int i = 0; i < size; i++) {
    // Linha Pivo
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

  thirdMethod(system);
  retrossubs(system, solution);

  return solution;
}

double *calculateResidualVector(struct LinearSystem *system, double *solution) {
  double *residue = malloc(sizeof(double) * system->size);

  for (int i = 0; i < system->size; i++) {
    double res = 0;
    for (int j = 0; j < system->size; j++) {
      res += system->m[i][j] * solution[j];
    }
    residue[i] = res - system->b[i];
  }

  return residue;
}

void printResidualVector(double *residualVector, int size) {
  printf("Resíduo = [ ");
  for (int i = 0; i < size; i++) {
    printf("%lf ", residualVector[i]);
  }
  printf("]\n");
}

void printSolution(double *solution, int size) {
  printf("X = [ ");
  for (int i = 0; i < size; i++) {
    printf("%lf ", solution[i]);
  }
  printf("]\n");
}

void printSystem(struct LinearSystem *sys) {
  int matrixSize = sys->size;
  for (int i = 0; i < matrixSize; i++) {
    for (int j = 0; j < matrixSize; j++) {
      printf("%lf ", sys->m[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  for (int i = 0; i < matrixSize; i++) {
    printf("%lf ", sys->b[i]);
  }
  printf("\n");
}
