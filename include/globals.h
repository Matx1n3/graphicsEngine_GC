//
// Created by matxin on 22/05/24.
//

#ifndef PROYECTOGC_GLOBALS_H
#define PROYECTOGC_GLOBALS_H

#include "models.h"

#define MAXLINE 200
#define MAXFILENAME 100
#define EPSILON 0.00001

/** If 1, fill the triangles, if 0, only draw the lines.*/
extern int fill_triangles; //lineak

/** If a set of triangles is treated as an object, this option allows to draw all the triangles at once */
extern int treat_as_obj; //objektuak

/** If (treat_as_obj == 1) If 0, draw the selected object. If 1, draw all the triangles of all the objects loaded.
 * If (treat_as_obj == 0) If 1, do not erase previous triangles, if 0, erase (only triangle index).*/
extern int draw_all_objs; //denak

/** Default color for empty triangles */
extern float default_color_empty_triangles[3];

/** Scene to be drawn */
extern struct scene scene1;

/** Texture to be used */
extern struct texture texture1;

/** Transformation to be applied */
enum transformation_types {TRANSLATE, ROTATE, SCALE};
extern enum transformation_types actual_transformation_type;

/** Reference system to be used */
enum reference_system_types {LOCAL, GLOBAL};
extern enum reference_system_types actual_reference_system;

#endif //PROYECTOGC_GLOBALS_H
