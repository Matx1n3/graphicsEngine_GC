#include <stdio.h>
#include <stdlib.h>
#include "models.h"
#include "globals.h"

int load_ppm(char *file, texture *texture1)
{
    //int load_ppm(char *file, unsigned char **bufferptr, int *dimxptr, int *dimyptr)
    char line[40];
    int luz,zbkia;
    FILE *obj_file;
    int fd;

    if ((obj_file = fopen(file, "r")) == NULL)
    {
        texture1->dimx = 0;
        texture1->dimy = 0;
        texture1->buffer = (unsigned char *)0;
        return(-1);
    }

    luz =fscanf(obj_file, "%[^\n]\n", line);
    if ( luz > 1)
    {
        if ((line[0]== 'P')&&(line[1]=='6'))
            printf("correct format\n");
        else
        {
            texture1->dimx = 0;
            texture1->dimy = 0;
            texture1->buffer = (unsigned char*)0;
            printf("format must be of type P6\n");
            return(-1);
        }
    }
    /* fitxategi neurria irakurtzera */
    luz =fscanf(obj_file, "%[^\n]\n", line);
    if (luz>0)
    {
        luz = sscanf(line,"%d %d", &texture1->dimx, &texture1->dimy);
        if (luz == 2)
            printf("Dimensions read: %d,%d\n", texture1->dimx,texture1->dimy);
        else
        {
            texture1->dimx = 0;
            texture1->dimy = 0;
            texture1->buffer = (unsigned char*)0;
            printf("Trouble reading dimensions\n");
            return(-1);
        }
    }

    luz =fscanf(obj_file, "%[^\n]\n", line);
    if (luz>0)
    {
        luz = sscanf(line,"%d",&zbkia);
        if (luz == 1)
            printf("Maximum read color number: %d\n",zbkia);
        else
        {
            texture1->dimx = 0;
            texture1->dimy = 0;
            texture1->buffer = (unsigned char*)0;
            printf("Problems reading the color representation\n");
            return(-1);
        }
    }
    luz=(texture1->dimx)*(texture1->dimy)*3;
    texture1->buffer = (unsigned char *)malloc(luz);
    zbkia=fread(texture1->buffer,1,luz,obj_file);

    if (zbkia != luz)
    {
        texture1->dimx = 0;
        texture1->dimy = 0;
        free(texture1->buffer);
        texture1->buffer = (void*)0;
        printf("Error filling the buffer... number = %d, light =%d\n",zbkia,luz);
        return(-1);
    }
    else
    {
        printf("Buffer correctly read\n");
        return(1);
    }
}

int load_object(char *file, scene *scene1, texture *texture2)
{
    FILE *obj_file;
    char line[MAXLINE];

    if ((obj_file = fopen(file, "r")) == NULL)
    {
        //*hkopptr= 0;
        printf("Error opening file %s\n",file);
        return(-1);
    }
    int num_triangles = 0;
    while (fscanf(obj_file, "\n%[^\n]", line) > 0)
    {
        if (line[0] == 't')
        {
            num_triangles++;
        }
    }

    fclose(obj_file);
    scene1->num_objects++;

    triangle *triangles = (triangle *)malloc(num_triangles * sizeof (triangle));

    obj_file = fopen(file, "r");
    int i = 0;
    while (fscanf(obj_file, "\n%[^\n]", line) > 0)
    {
        if (line[0] == 't')  // triangulo!
        {
            sscanf(line + 2, "%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f", &triangles[i].p1.x, &triangles[i].p1.y, &triangles[i].p1.z,
                   &triangles[i].p1.u, &triangles[i].p1.v,
                   &triangles[i].p2.x, &triangles[i].p2.y, &triangles[i].p2.z,
                   &triangles[i].p2.u, &triangles[i].p2.v,
                   &triangles[i].p3.x, &triangles[i].p3.y, &triangles[i].p3.z,
                   &triangles[i].p3.u, &triangles[i].p3.v);
            i++;
        }
    }
    fclose(obj_file);


    scene1->objects = (object **)realloc(scene1->objects, scene1->num_objects * sizeof (object *));
    if (scene1->objects == NULL)
    {
        printf("Error reallocating memory\n");
        return(-1);
    }

    scene1->objects[scene1->num_objects - 1] = (object *)malloc(sizeof(object));
    if (scene1->objects[scene1->num_objects - 1] == NULL) {
        printf("Error allocating memory\n");
        return(-1);
    }

    // Set the number of triangles and the triangles. Index is set to 0
    scene1->objects[scene1->num_objects - 1]->num_triangles = num_triangles;
    scene1->objects[scene1->num_objects - 1]->triangles = triangles;
    scene1->objects[scene1->num_objects - 1]->index = 0;

    /**
    // Allocate memory for the texture
    scene1->objects[scene1->num_objects - 1]->texture = (texture *)malloc(sizeof(texture));

    if (scene1->objects[scene1->num_objects - 1]->texture == NULL) {
        printf("Error allocating memory for texture\n");
        return(-1);
    }
     */

    // Set the texture
    scene1->objects[scene1->num_objects - 1]->texture = texture2;

    // Set the transformation matrix to the identity matrix
    scene1->objects[scene1->num_objects - 1]->trans_matrix[0][0] = 1;
    scene1->objects[scene1->num_objects - 1]->trans_matrix[0][1] = 0;
    scene1->objects[scene1->num_objects - 1]->trans_matrix[0][2] = 0;
    scene1->objects[scene1->num_objects - 1]->trans_matrix[0][3] = 0;

    scene1->objects[scene1->num_objects - 1]->trans_matrix[1][0] = 0;
    scene1->objects[scene1->num_objects - 1]->trans_matrix[1][1] = 1;
    scene1->objects[scene1->num_objects - 1]->trans_matrix[1][2] = 0;
    scene1->objects[scene1->num_objects - 1]->trans_matrix[1][3] = 0;

    scene1->objects[scene1->num_objects - 1]->trans_matrix[2][0] = 0;
    scene1->objects[scene1->num_objects - 1]->trans_matrix[2][1] = 0;
    scene1->objects[scene1->num_objects - 1]->trans_matrix[2][2] = 1;
    scene1->objects[scene1->num_objects - 1]->trans_matrix[2][3] = 0;

    scene1->objects[scene1->num_objects - 1]->trans_matrix[3][0] = 0;
    scene1->objects[scene1->num_objects - 1]->trans_matrix[3][1] = 0;
    scene1->objects[scene1->num_objects - 1]->trans_matrix[3][2] = 0;
    scene1->objects[scene1->num_objects - 1]->trans_matrix[3][3] = 1;

    return(1);
}


