#ifndef LINEAR_SYSTEM_H
#define LINEAR_SYSTEM_H

struct LinearSystem {
  double **m;
  double *b;
  int size;
};

struct Solution {
  double *s;
};

struct LinearSystem *createLinearSystem(int size);

void readLinearSystem(struct LinearSystem *system);

struct LinearSystem *copyLinearSystem(struct LinearSystem *system);

double *solvePivotingWithMult(struct LinearSystem *system);

double *solvePivotingWithoutMult(struct LinearSystem *system);

double *solveWithoutPivoting(struct LinearSystem *system);

void printSolution(double *solution, int size);

double *calculateResidualVector(struct LinearSystem *system, double *solution);

void printResidualVector(double *residualVector, int size);

void printSystem(struct LinearSystem *sys);

#endif
