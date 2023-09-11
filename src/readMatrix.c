#include<stdio.h>
#include<stdlib.h>

#include"linearSystem.h"

struct Matrix* createMatrix(int size) {
	struct Matrix *matrix = malloc(sizeof(struct Matrix));

	matrix->m = malloc(sizeof(double) * size+1);

	for(int i = 0; i <= size; i++){
		matrix->m[i] = malloc(sizeof(double) * size+1);
	}

	return matrix;
}

void readMatrix(struct Matrix* matrix) {
	int matrixSize = matrix->size;

	for(int i = 0; i <= matrixSize; i++){
		for(int j = 0; j <= matrixSize; j++){
			scanf("%lf", &matrix->m[i][j]);
		}	
	}
}
