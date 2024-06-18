//
// Created by matxin on 12/06/24.
//

#ifndef PROYECTOGC_MATH_H
#define PROYECTOGC_MATH_H

#include "models.h"

void order_points(point *p1, point *p2, point *p3);
void matrix_by_point(float matrix[4][4], point point1, point *result);
void matrix_by_matrix(float matrix1[4][4], float matrix2[4][4], float result[4][4]);
void print_matrix(float matrix[4][4]);

#endif //PROYECTOGC_MATH_H
