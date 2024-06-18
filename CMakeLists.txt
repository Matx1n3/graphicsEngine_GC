cmake_minimum_required(VERSION 3.28)
project(proyectoGC C)

set(CMAKE_C_STANDARD 11)

# Añadir las bibliotecas GLUT y OpenGL
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

# Incluir las cabeceras de GLUT y OpenGL
include_directories(${GLUT_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})

# Link libraries
set(LIBS ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

# Agregar los archivos fuente al ejecutable
add_executable(proyectoGC
        main.c
        loader.c
        models.h
        loader.h
        display.h
        display.c
        input.c
        input.h
        globals.c
        globals.h
        math.c
        math.h
        transformations.c
        transformations.h
)

# Enlazar el ejecutable con las bibliotecas GLUT y OpenGL
target_link_libraries(proyectoGC ${GLUT_LIBRARY} ${OPENGL_LIBRARIES})
