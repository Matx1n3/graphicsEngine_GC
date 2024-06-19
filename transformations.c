//
// Created by matxin on 17/06/24.
//

#include "transformations.h"
#include <math.h>
#include "math.h"
#include "globals.h"

/**
 * @brief Translates the matrix by x, y and z
 * @param matrix
 * @param x
 * @param y
 * @param z
 */
void translate(float matrix[4][4], float x, float y, float z)
{
    matrix[0][3] += x;
    matrix[1][3] += y;
    matrix[2][3] += z;
}

/**
 * @brief Rotates the matrix by angle in the x axis in the local reference system
 * @param matrix
 * @param angle
 */
void rotate_x_local(float matrix[4][4], float angle)
{
    float cos_angle = (float) cos((double)angle);
    float sin_angle = (float) sin((double) angle);

    float aux[4][4] = {
            {1, 0, 0, 0},
            {0, cos_angle, -sin_angle, 0},
            {0, sin_angle, cos_angle, 0},
            {0, 0, 0, 1}
    };

    float result[4][4];
    matrix_by_matrix(matrix, aux, result);

    // Copy the values from result back into matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = result[i][j];
        }
    }
}

/**
 * @brief Rotates the matrix by angle in the y axis in the local reference system
 * @param matrix
 * @param angle
 */
void rotate_y_local(float matrix[4][4], float angle)
{
    float cos_angle = (float) cos((double)angle);
    float sin_angle = (float) sin((double) angle);

    float aux[4][4] = {
            {cos_angle, 0, sin_angle, 0},
            {0, 1, 0, 0},
            {-sin_angle, 0, cos_angle, 0},
            {0, 0, 0, 1}
    };

    float result[4][4];
    matrix_by_matrix(matrix, aux, result);

    // Copy the values from result back into matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = result[i][j];
        }
    }
}

/**
 * @brief Rotates the matrix by angle in the z axis in the local reference system
 * @param matrix
 * @param angle
 */
void rotate_z_local(float matrix[4][4], float angle)
{
    float cos_angle = (float) cos((double)angle);
    float sin_angle = (float) sin((double) angle);

    float aux[4][4] = {
            {cos_angle, -sin_angle, 0, 0},
            {sin_angle, cos_angle, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
    };

    float result[4][4];
    matrix_by_matrix(matrix, aux, result);

    // Copy the values from result back into matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = result[i][j];
        }
    }
}

/**
 * @brief Rotates the matrix by angle in the x axis in the global reference system
 * @param matrix
 * @param angle
 */
void rotate_x_global(float matrix[4][4], float angle)
{
    float cos_angle = (float) cos((double)angle);
    float sin_angle = (float) sin((double) angle);

    float to_center[4][4] = {
        {1, 0, 0, -matrix[0][3]},
        {0, 1, 0, -matrix[1][3]},
        {0, 0, 1, -matrix[2][3]},
        {0, 0, 0, 1}
    };

    float rotation_matrix[4][4] = {
            {1, 0, 0, 0},
            {0, cos_angle, -sin_angle, 0},
            {0, sin_angle, cos_angle, 0},
            {0, 0, 0, 1}
    };

    float back_to_position[4][4] = {
        {1, 0, 0, matrix[0][3]},
        {0, 1, 0, matrix[1][3]},
        {0, 0, 1, matrix[2][3]},
        {0, 0, 0, 1}
    };

    float tmp1_matrix[4][4];
    float tmp2_matrix[4][4];

    matrix_by_matrix(to_center, matrix, tmp1_matrix);
    matrix_by_matrix(rotation_matrix, tmp1_matrix, tmp2_matrix);
    matrix_by_matrix(back_to_position, tmp2_matrix, tmp1_matrix);

    // Copy the values from tmp1_matrix back into matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = tmp1_matrix[i][j];
        }
    }
}

/**
 * @brief Rotates the matrix by angle in the y axis in the global reference system
 * @param matrix
 * @param angle
 */
void rotate_y_global(float matrix[4][4], float angle)
{
    float cos_angle = (float) cos((double)angle);
    float sin_angle = (float) sin((double) angle);

    float to_center[4][4] = {
            {1, 0, 0, -matrix[0][3]},
            {0, 1, 0, -matrix[1][3]},
            {0, 0, 1, -matrix[2][3]},
            {0, 0, 0, 1}
    };

    float rotation_matrix[4][4] = {
            {cos_angle, 0, sin_angle, 0},
            {0, 1, 0, 0},
            {-sin_angle, 0, cos_angle, 0},
            {0, 0, 0, 1}
    };

    float back_to_position[4][4] = {
            {1, 0, 0, matrix[0][3]},
            {0, 1, 0, matrix[1][3]},
            {0, 0, 1, matrix[2][3]},
            {0, 0, 0, 1}
    };

    float tmp1_matrix[4][4];
    float tmp2_matrix[4][4];

    matrix_by_matrix(to_center, matrix, tmp1_matrix);
    matrix_by_matrix(rotation_matrix, tmp1_matrix, tmp2_matrix);
    matrix_by_matrix(back_to_position, tmp2_matrix, tmp1_matrix);

    // Copy the values from tmp1_matrix back into matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = tmp1_matrix[i][j];
        }
    }
}

/**
 * @brief Rotates the matrix by angle in the z axis in the global reference system
 * @param matrix
 * @param angle
 */
void rotate_z_global(float matrix[4][4], float angle)
{
    float cos_angle = (float) cos((double)angle);
    float sin_angle = (float) sin((double) angle);

    float to_center[4][4] = {
            {1, 0, 0, -matrix[0][3]},
            {0, 1, 0, -matrix[1][3]},
            {0, 0, 1, -matrix[2][3]},
            {0, 0, 0, 1}
    };

    float rotation_matrix[4][4] = {
            {cos_angle, -sin_angle, 0, 0},
            {sin_angle, cos_angle, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
    };

    float back_to_position[4][4] = {
            {1, 0, 0, matrix[0][3]},
            {0, 1, 0, matrix[1][3]},
            {0, 0, 1, matrix[2][3]},
            {0, 0, 0, 1}
    };

    float tmp1_matrix[4][4];
    float tmp2_matrix[4][4];

    matrix_by_matrix(to_center, matrix, tmp1_matrix);
    matrix_by_matrix(rotation_matrix, tmp1_matrix, tmp2_matrix);
    matrix_by_matrix(back_to_position, tmp2_matrix, tmp1_matrix);

    // Copy the values from tmp1_matrix back into matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = tmp1_matrix[i][j];
        }
    }
}

/**
 * @brief Transforms the object according to the transformation type, reference system, x, y, z, axis and angle.
 * Acts as wrapper for the other transformation functions
 * @param transformation_type
 * @param reference_system
 * @param x
 * @param y
 * @param z
 * @param axis
 * @param angle
 */
void transform(enum transformation_types transformation_type, enum reference_system_types reference_system, float x, float y, float z, char axis, float angle) {
    switch (transformation_type) {
        case TRANSLATE:
            translate(scene1.objects[scene1.index]->trans_matrix, x, y, z);
            break;
        case ROTATE:
            if (reference_system == LOCAL)
                switch (axis) {
                    case 'x':
                        rotate_x_local(scene1.objects[scene1.index]->trans_matrix, angle);
                        break;
                    case 'y':
                        rotate_y_local(scene1.objects[scene1.index]->trans_matrix, angle);
                        break;
                    case 'z':
                        rotate_z_local(scene1.objects[scene1.index]->trans_matrix, angle);
                        break;
                    default:
                        break;
                }
            else {
                switch (axis) {
                    case 'x':
                        rotate_x_global(scene1.objects[scene1.index]->trans_matrix, angle);
                        break;
                    case 'y':
                        rotate_y_global(scene1.objects[scene1.index]->trans_matrix, angle);
                        break;
                    case 'z':
                        rotate_z_global(scene1.objects[scene1.index]->trans_matrix, angle);
                        break;
                    default:
                        break;
                }
            }
            break;
        case SCALE:
            break;
    }
}
