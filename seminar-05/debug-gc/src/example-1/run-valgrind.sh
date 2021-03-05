gcc main.cpp -o main.exe
valgrind --tool=memcheck ./main.exe 2>&1 | head -n 8