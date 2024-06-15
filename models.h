//
// Created by matxin on 22/05/24.
//

#ifndef PROYECTOGC_MODELS_H
#define PROYECTOGC_MODELS_H

typedef struct point
{
    float x, y, z, u, v;
} point;

typedef struct triangle
{
    point p1,p2,p3;
} triangle;

typedef struct texture
{
    unsigned char *buffer;
    int dimx, dimy;
} texture;

typedef struct object
{
    int num_triangles;
    triangle *triangles;
    int index; //Inicializar a 0 e incrementar si <intro>
    texture *texture;
    float trans_matrix[4][4];
} object;

typedef struct scene
{
    int num_objects;
    object **objects;
    int index; //Inicializar a 0 e incrementar si <intro>
} scene;


#endif //PROYECTOGC_MODELS_H


