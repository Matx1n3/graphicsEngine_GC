#include <stdio.h>
#include <GL/glut.h>
#include "globals.h"
#include "loader.h"
#include "display.h"
#include "input.h"
#include "models.h"


int main(int argc, char *argv[]) {
    int retval;

    printf("Press <ESC> to finish\n");
    glutInit(&argc,argv);
    glutInitDisplayMode ( GLUT_RGB|GLUT_DEPTH );
    glutInitWindowSize ( 500, 500 );
    glutInitWindowPosition ( 100, 100 );
    glutCreateWindow( "KBG/GO praktika" );

    glutDisplayFunc( draw);
    glutKeyboardFunc( keyboard);

    retval = load_ppm("testura.ppm", &texture1);

    if (retval !=1)
    {
        printf("Couldn't find file testura.ppm\n");
        exit(-1);
    }

    glClearColor( 0.0f, 0.0f, 0.7f, 1.0f );
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    if (argc>1) load_object(argv[1], &scene1, &texture1);
    else load_object("objects/adibideak.txt", &scene1, &texture1);

    glClear( GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT );
    glutMainLoop();

    return 0;
}
