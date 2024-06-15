//
// Created by matxin on 12/06/24.
//

#ifndef PROYECTOGC_MATH_H
#define PROYECTOGC_MATH_H

#include "models.h"

/**
 * brief Orders the points by their y value. If two points have the same y value,
 * the one with the smallest x value is first.
 * @param p1
 * @param p2
 * @param p3
 */
void order_points(point *p1, point *p2, point *p3);


/**
 * brief Stores the result of matrix * point1 in result
 * @param matrix
 * @param point1
 * @param result
 */
void matrix_by_point(float matrix[4][4], point point1, point result);

#endif //PROYECTOGC_MATH_H
