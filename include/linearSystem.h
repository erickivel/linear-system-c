#ifndef LINEAR_SYSTEM_H
#define LINEAR_SYSTEM_H

struct Matrix {
	double **m;
	int size;
};

struct Solution {
	double *s;
};

struct Matrix* createMatrix();

void fillMatrix(struct Matrix *m);

//struct Solution* solve(struct Matrix* matrix);



#endif
