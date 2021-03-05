gcc main.cpp -o main.exe
valgrind --tool=memcheck --leak-check=full ./main.exe 2>&1