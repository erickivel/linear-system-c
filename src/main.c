#include<stdio.h>

#include"linearSystem.h"

int main() {
	int size;
	scanf("%d", &size);

	struct Matrix* matrix = createMatrix(size);

	readMatrix(matrix);

}
