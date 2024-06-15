//
// Created by matxin on 12/06/24.
//

#include "math.h"

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

void matrix_by_point(float matrix[4][4], point point1, point result)
{
    result.x = matrix[0][0] * point1.x + matrix[0][1] * point1.y + matrix[0][2] * point1.z + matrix[0][3] * point1.u;
    result.y = matrix[1][0] * point1.x + matrix[1][1] * point1.y + matrix[1][2] * point1.z + matrix[1][3] * point1.u;
    result.z = matrix[2][0] * point1.x + matrix[2][1] * point1.y + matrix[2][2] * point1.z + matrix[2][3] * point1.u;
    result.u = point1.u;
    result.v = point1.v;
}
