//
// Created by matxin on 12/06/24.
//

#include <stdio.h>
#include "../include/math.h"

/**
 * @brief Orders the points by their y value. If two points have the same y value,
 * the one with the smallest x value is first.
 * @param p1
 * @param p2
 * @param p3
 */
void order_points(point *p1, point *p2, point *p3)
{
    point aux;
    if (p1->y < p2->y)
    {
        aux = *p1;
        *p1 = *p2;
        *p2 = aux;
    }
    if (p1->y < p3->y)
    {
        aux = *p1;
        *p1 = *p3;
        *p3 = aux;
    }

    if (p2->y < p3->y)
    {
        aux = *p2;
        *p2 = *p3;
        *p3 = aux;
    }
    if (p1->y == p2->y && p1->x > p2->x)
    {
        aux = *p1;
        *p1 = *p2;
        *p2 = aux;
    }
    if (p1->y == p3->y && p1->x > p3->x)
    {
        aux = *p1;
        *p1 = *p3;
        *p3 = aux;
    }
    if (p2->y == p3->y && p2->x > p3->x)
    {
        aux = *p2;
        *p2 = *p3;
        *p3 = aux;
    }
}

/**
 * @brief Stores the result of matrix * point1 in result
 * @param matrix
 * @param point1
 * @param result
 */
void matrix_by_point(float matrix[4][4], point point1, point *result)
{
    result->x = matrix[0][0] * point1.x + matrix[0][1] * point1.y + matrix[0][2] * point1.z + matrix[0][3];
    result->y = matrix[1][0] * point1.x + matrix[1][1] * point1.y + matrix[1][2] * point1.z + matrix[1][3];
    result->z = matrix[2][0] * point1.x + matrix[2][1] * point1.y + matrix[2][2] * point1.z + matrix[2][3];
    result->u = point1.u;
    result->v = point1.v;
}

/**
 * @brief Stores the result of matrix1 * matrix2 in result
 * @param matrix1
 * @param matrix2
 * @param result
 */
void matrix_by_matrix(float matrix1[4][4], float matrix2[4][4], float result[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

/**
 * @brief Prints the matrix
 * @param matrix
 */
void print_matrix(float matrix[4][4]) {
    for (int i = 0; i < 4; i++) {
        printf("[");
        for (int j = 0; j < 4; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("]\n");
    }
}