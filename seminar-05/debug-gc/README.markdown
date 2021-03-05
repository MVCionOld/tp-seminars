# GDB

```GDB``` — переносимый отладчик проекта GNU, который работает на многих UNIX-подобных системах и умеет производить отладку 
многих языков программирования, включая ```С/C++```, ```Free Pascal```, ```FreeBASIC```, ```Ada```, ```Fortran```, 
```Python3```, ```Swift```, ```Rust```.

GDB уже установлен на многих UNIX-подобных системах, лёгок в использовании и поддерживает много языков. 
Работа с ним оказывается очень лёгкой, а также его можно подключить к VSCode и другим редакторам кода (Включая Vim, NeoVim (ясное дело), Emacs, Atom и далее).

Для того чтобы нам пройтись по такому файлу нам нужно собрать его с помощью ```g++``` с использованием флага ```-g``` 
(это действительно важно, без этого флага, программа не будет корректно работать в GDB).

```c++
#include <iostream>

void hello() {
  int x = 5;
  int y = -x;
  std::cout << "Hello, outer World "<< y << "!" << std::endl;
}


int main() {
  std::cout << "Hello, World!" << std::endl;
  hello();
}
```

```shell
g++ -g main.cpp -o main
gdb main
```

Командой ```list``` находим номер строчки вхождения в программу (в нашем случае это функция ```main```).  
Далее пишем её порядковый номер с буквой ```b``` (также можно просто указать имя функции ```b main``` тоже работает).  
Запускаем программу с помощью комманды ```r```.  
Для того, чтобы сделать шаг, нужно нажать ```n``` (от слова next).  
Чтобы зайти в функцию нужно сделать "шаг внутрь" (step-in) или просто клавиша ```s```.  
Чтобы узнать какие переменные (локальные) сейчас инициализированны в программе нужно написать комманду ```info locals```.
Чтобы узнать имя переменной: ```print <varname>```.  
Мы можем также изменить переменную с помощью ```set <varname> = <varvalue>```.  
Также, если нужно, можно посмотреть что в данный момент находится в регистрах: ```info registers```.  
Чтобы посмотреть какие в данный момент есть breakpoints (точки останова) нужно написать ```info breakpoints```.  
Чтобы удалить точку останова ```del <breakpoint_num>```.  
Чтобы прыгнуть к следующей точке останова нужно нажать ```c```.  
Мы можем вызывать функции из программы (локальные) с помощью ```call <function_name>(<args>)```.  
Чтобы продолжить выполнение функции и остановить программу когда она (функция) завершится нужно написать ```finish```
или ```fin```, но нельзя использовать ```fin``` в ```main```.  
Чтобы завершить выполнение программы, нужно написать ```kill```.  
Также можно написать ```help``` в любой момент и получить краткую справку, как пользоваться отладчиком.

# Segfault

### ASAN
```c
#include<stdio.h>

int main() {
    int a[2];
    printf("%d\n", a[100500]); // проезд по памяти
}
```
---
```shell
gcc main.cpp -o main.exe
./main.exe
```
```text
Segmentation fault (core dumped)
```
---
```shell
# компилируем с санитайзером и запускаем как обычно (семинарист рекомендует)
gcc -fsanitize=address main.cpp -o main.exe
./main.exe
```
```text
AddressSanitizer:DEADLYSIGNAL
=================================================================
==13517==ERROR: AddressSanitizer: SEGV on unknown address 0x7ffeeff13110 (pc 0x561a43d9d2e4 bp 0x7ffeefeb0f20 sp 0x7ffeefeb0ea0 T0)
==13517==The signal is caused by a READ memory access.
    #0 0x561a43d9d2e3 in main (/home/mvcion/Desktop/mipt-diht-tp-2021-seminars/seminar-05/debug-gc/src/example-1/main.exe+0x12e3)
    #1 0x7f786199a0b2 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x270b2)
    #2 0x561a43d9d16d in _start (/home/mvcion/Desktop/mipt-diht-tp-2021-seminars/seminar-05/debug-gc/src/example-1/main.exe+0x116d)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (/home/mvcion/Desktop/mipt-diht-tp-2021-seminars/seminar-05/debug-gc/src/example-1/main.exe+0x12e3) in main
==13517==ABORTING
```

### ASAN & GDB
```shell
# комбинируем санитайзер и gdb (если вы хотите больше подробностей)
# по идее это должно находить больше косяков, чем вариант в следующей ячейке
gcc -g -fsanitize=address main.cpp -o main.exe
gdb -ex=r -batch --args ./main.exe
```
```shell
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGSEGV, Segmentation fault.
0x00005555555552c8 in main () at main.cpp:5
5           printf("%d\n", a[100500]); // проезд по памяти
```

### VALGRIND
```shell
# собираем как обычно и запускаем с valgrind
gcc main.cpp -o main.exe
# берем только первые 8 строк выхлопа, а то там много
valgrind --tool=memcheck ./main.exe 2>&1 | head -n 8
```
```text
==14448== Memcheck, a memory error detector
==14448== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==14448== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==14448== Command: ./main.exe
==14448== 
==14448== Invalid read of size 4
==14448==    at 0x109184: main (in /home/mvcion/Desktop/mipt-diht-tp-2021-seminars/seminar-05/debug-gc/src/example-1/main.exe)
==14448==  Address 0x1fff061c50 is not stack'd, malloc'd or (recently) free'd
```

# Memory leaks
```shell
gcc main.cpp -o main.exe
valgrind --tool=memcheck --leak-check=full ./main.exe 2>&1 
```
```text
==15047== Memcheck, a memory error detector
==15047== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==15047== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==15047== Command: ./main.exe
==15047== 
==15047== 
==15047== HEAP SUMMARY:
==15047==     in use at exit: 16 bytes in 1 blocks
==15047==   total heap usage: 1 allocs, 0 frees, 16 bytes allocated
==15047== 
==15047== 16 bytes in 1 blocks are definitely lost in loss record 1 of 1
==15047==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==15047==    by 0x10915A: main (in /home/mvcion/Desktop/mipt-diht-tp-2021-seminars/seminar-05/debug-gc/src/example-2/main.exe)
==15047== 
==15047== LEAK SUMMARY:
==15047==    definitely lost: 16 bytes in 1 blocks
==15047==    indirectly lost: 0 bytes in 0 blocks
==15047==      possibly lost: 0 bytes in 0 blocks
==15047==    still reachable: 0 bytes in 0 blocks
==15047==         suppressed: 0 bytes in 0 blocks
==15047== 
==15047== For lists of detected and suppressed errors, rerun with: -s
==15047== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
---
```shell
gcc -fsanitize=address main.cpp -o main.exe
./main.exe
```
```text

=================================================================
==15102==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x7f701aab5bc8 in malloc (/lib/x86_64-linux-gnu/libasan.so.5+0x10dbc8)
    #1 0x556ffe59d19a in main (/home/mvcion/Desktop/mipt-diht-tp-2021-seminars/seminar-05/debug-gc/src/example-2/main.exe+0x119a)
    #2 0x7f701a7dd0b2 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x270b2)

SUMMARY: AddressSanitizer: 16 byte(s) leaked in 1 allocation(s).
```