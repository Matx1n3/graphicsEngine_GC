//
// Created by matxin on 22/05/24.
//

#include "display.h"
#include <GL/glut.h>
#include "globals.h"
#include "models.h"
#include "math.h"
#include <stdio.h>

/**
 * @brief Returns the color of the texture in the given coordinates
 * @param texture1
 * @param u
 * @param v
 * @return pointer to the color rgb
 */
unsigned char* color_texture(texture *texture1, float u, float v)
{
    int x = (int) (u * (float) texture1->dimx);
    int y = (int) (v * (float) texture1->dimy);
    return &texture1->buffer[(y * texture1->dimx + x) * 3];

}

/**
 * @brief Draws a colored horizontal line in the screen
 * @param y
 * @param x1
 * @param z1
 * @param u1
 * @param v1
 * @param x2
 * @param z2
 * @param u2
 * @param v2
 */
void draw_line_z(float y, float x1, float z1, float u1, float v1, float x2, float z2, float u2, float v2)
{

    //Calculate increase in u and v for each iteration
    float denominator = x2 - x1;
    if (denominator < EPSILON) denominator = 1;
    float du = (u2 - u1) / denominator;
    float dv = (v2 - v1) / denominator;

    float x, z, u, v;

    for (x = x1, u = u1, v = v1; x <= x2; x++, u += du, v += dv)
    {
        unsigned char* colorv = color_texture(scene1.objects[scene1.index]->texture, u, v);
        glColor3ub(colorv[0], colorv[1], colorv[2]);
        glVertex3f(x, y, 0);
    }

    glEnd();
}

/**
 * @brief draws a triangle in the screen
 * @param triangle1
 * @param texture1
 * @param trans_matrix
 */
void draw_triangle(triangle *triangle1, float trans_matrix[4][4])
{
    // Get the points of the triangle
    point p1 = triangle1->p1;
    point p2 = triangle1->p2;
    point p3 = triangle1->p3;

    // Get the points of the triangle that must be drawn
    matrix_by_point(trans_matrix, triangle1->p1, p1);
    matrix_by_point(trans_matrix, triangle1->p2, p2);
    matrix_by_point(trans_matrix, triangle1->p3, p3);

    // If triangle doesn't have to be filled, draw just the lines
    if (!fill_triangles)
    {
        glBegin(GL_POLYGON);
        glColor3f(default_color_empty_triangles[0],default_color_empty_triangles[1], default_color_empty_triangles[2]);
        glVertex3d(p1.x, p1.y, p1.z);
        glVertex3d(p2.x, p2.y, p2.z);
        glVertex3d(p3.x, p3.y, p3.z);
        glEnd();
        return;
    }

    // Order the points by y
    order_points(&p1, &p2, &p3);

    // Create p5 and p6, which will be the points intersecting p1p2 and p1p4 at the current y
    point p5, p6;
    p5 = p1;
    if (p2.y == p1.y) p6 = p2;
    else p6 = p1;


    // Calculate the slopes and increments for each point
    float dx_p1p2 = (p2.x - p1.x) / (p2.y - p1.y);
    float dz_p1p2 = (p2.z - p1.z) / (p2.y - p1.y);
    float du_p1p2 = (p2.u - p1.u) / (p2.y - p1.y);
    float dv_p1p2 = (p2.v - p1.v) / (p2.y - p1.y);

    float dx_p1p3 = (p3.x - p1.x) / (p3.y - p1.y);
    float dz_p1p3 = (p3.z - p1.z) / (p3.y - p1.y);
    float du_p1p3 = (p3.u - p1.u) / (p3.y - p1.y);
    float dv_p1p3 = (p3.v - p1.v) / (p3.y - p1.y);

    float dx_p2p3 = (p3.x - p2.x) / (p3.y - p2.y);
    float dz_p2p3 = (p3.z - p2.z) / (p3.y - p2.y);
    float du_p2p3 = (p3.u - p2.u) / (p3.y - p2.y);
    float dv_p2p3 = (p3.v - p2.v) / (p3.y - p2.y);

    // Draw the upper part of the triangle
    // if p1.y == p2.y, it will just skip this
    for (float y = p1.y; y > p2.y; y--)
    {
        draw_line_z(y, p5.x, 0, p5.u, p5.v, p6.x, 0, p6.u, p6.v);
        p5.x -= dx_p1p2;
        p5.z -= dz_p1p2;
        p5.u -= du_p1p2;
        p5.v -= dv_p1p2;

        p6.x -= dx_p1p3;
        p6.z -= dz_p1p3;
        p6.u -= du_p1p3;
        p6.v -= dv_p1p3;
    }

    // Draw the lower part of the triangle
    // if p1.y == p2.y, the slopes will be p1p3 and p2p3, else it'll be the other way around
    if (p1.y != p2.y) {
        for (float y = p2.y; y >= p3.y; y--) {
            draw_line_z(y, p5.x, 0, p5.u, p5.v, p6.x, 0, p6.u, p6.v);
            p5.x -= dx_p2p3;
            p5.z -= dz_p2p3;
            p5.u -= du_p2p3;
            p5.v -= dv_p2p3;

            p6.x -= dx_p1p3;
            p6.z -= dz_p1p3;
            p6.u -= du_p1p3;
            p6.v -= dv_p1p3;
        }
    }
    else {
        for (float y = p2.y; y >= p3.y; y--) {
            draw_line_z(y, p5.x, 0, p5.u, p5.v, p6.x, 0, p6.u, p6.v);
            p5.x -= dx_p1p3;
            p5.z -= dz_p1p3;
            p5.u -= du_p1p3;
            p5.v -= dv_p1p3;

            p6.x -= dx_p2p3;
            p6.z -= dz_p2p3;
            p6.u -= du_p2p3;
            p6.v -= dv_p2p3;
        }
    }

    glEnd();
}

/**
 * @brief Draws the scene. This function is called by glutDisplayFunc every time the screen must be drawn.
 */
void draw(void)
{

    // If there are no objects, return
    if (scene1.num_objects == 0) return;

    if (treat_as_obj == 1) glClear( GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT );
    else {if (draw_all_objs == 0) glClear( GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT );}

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-500.0, 500.0, -500.0, 500.0,-500.0, 500.0);


    if (treat_as_obj == 1) {
        if (draw_all_objs == 1) {
            for (int i = 0; i < scene1.num_objects; i++) {
                for (int j = 0; j < scene1.objects[i]->num_triangles; j++) {
                    draw_triangle(&(scene1.objects[i]->triangles[j]), scene1.objects[i]->trans_matrix);
                }
            }
        }
        else {
            for (int j = 0; j < scene1.objects[scene1.index]->num_triangles; j++) {
                draw_triangle(&(scene1.objects[scene1.index]->triangles[j]), scene1.objects[scene1.index]->trans_matrix);
            }
        }
    }
    else {
        draw_triangle(&(scene1.objects[scene1.index]->triangles[scene1.objects[scene1.index]->index]), scene1.objects[scene1.index]->trans_matrix);
    }
    glFlush();
}