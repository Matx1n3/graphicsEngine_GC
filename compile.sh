mkdir -p bin
gcc -o bin/your_executable src/*.c -lGL -lglut -lGLU -lm
./bin/your_executable