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