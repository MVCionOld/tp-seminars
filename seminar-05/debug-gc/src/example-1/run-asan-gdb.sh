gcc -g -fsanitize=address main.cpp -o main.exe
gdb -ex=r -batch --args ./main.exe