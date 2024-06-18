//
// Created by matxin on 22/05/24.
//

#include "globals.h"
#include <stddef.h>

int fill_triangles = 0;
int treat_as_obj = 0;
int draw_all_objs = 1;

float default_color_empty_triangles[3] = {1, 1, 1};

struct scene scene1 = {
        .num_objects = 0,
        .objects = NULL,
        .index = 0
};

struct texture texture1 = {
        .buffer = NULL,
        .dimx = 0,
        .dimy = 0
};

enum transformation_types actual_transformation_type = TRANSLATE;

enum reference_system_types actual_reference_system = LOCAL;

