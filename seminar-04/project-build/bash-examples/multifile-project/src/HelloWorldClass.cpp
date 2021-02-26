#include "HelloWorldClass.h"


void HelloWorldClass::Set(const std::string& string) {
    string_ = string;
}

std::string HelloWorldClass::Get() const {
    return string_;
}
