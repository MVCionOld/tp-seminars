#include <iostream>

#include "HelloWorldClass.h"


int main() {
    HelloWorldClass helloWorldClass;
    helloWorldClass.Set("Hello, world!");
    std::cout << helloWorldClass.Get() << std::endl;
}