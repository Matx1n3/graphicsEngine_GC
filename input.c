//
// Created by matxin on 22/05/24.
//

#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "input.h"
#include "globals.h"
#include "loader.h"


// This function will be called whenever the user pushes one key
void keyboard (unsigned char key, int x, int y)
{
    // The screen must be drawn to show the new triangle
    switch (key) {
        case 27: //esc
            printf("Exiting...\n");
            exit(0);
            break;
        case 9: //tab
            scene1.index = (scene1.index + 1) % scene1.num_objects;
            scene1.objects[scene1.index]->index = 0;
            break;
        case 13: //intro
            scene1.objects[scene1.index]->index = (scene1.objects[scene1.index]->index + 1) % scene1.objects[scene1.index]->num_triangles;
            break;
        case'f':
            printf("Load new object from file: \n");
            char filename[MAXFILENAME];
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = '\0';
            load_object(filename, &scene1, &texture1);
            break;
        case 'l':
            if (fill_triangles) fill_triangles = 0;
            else fill_triangles = 1;
            break;
        case 'o':
            if (treat_as_obj) treat_as_obj = 0;
            else treat_as_obj = 1;
            break;
        case 'd':
            if (draw_all_objs) draw_all_objs = 0;
            else draw_all_objs = 1;
            break;
        default:
            break;
    }
    glutPostRedisplay();
    printf("--------------------\n");
    printf("Pressed key: %c %i \n", key, key); // No funciona bien con <intro> ??
    printf("Current state: fill_triangles = %d, treat_as_obj = %d, draw_all_objs = %d\n", fill_triangles, treat_as_obj, draw_all_objs);
    printf("Current object: %d, current triangle: %d\n", scene1.index, scene1.objects[scene1.index]->index);
    printf("--------------------\n");
}