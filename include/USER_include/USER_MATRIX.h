/*
 * USER_MATRIX.h
 *
 *  Created on: 2018. 5. 27.
 *      Author: mulik
 */

#ifndef USER_MATRIX_H_
#define USER_MATRIX_H_

#include "USER_TOP_HEADER.h"

typedef struct {
	int col;
	int row;
	double** var;
} matrix;

extern matrix* matrix_new( int row, int col );
extern void matrix_free( matrix* m );

extern matrix* matrix_multiple( matrix* a, matrix* b );
extern matrix* matrix_inv( matrix* m );

extern matrix* matrix_transpose( matrix* m );

extern void matrix_init( matrix* m, double* src );
extern void matrix_extract( double* dst, matrix* m );

extern void matrix_load_identity( matrix* m );

#endif /* USER_MATRIX_H_ */
