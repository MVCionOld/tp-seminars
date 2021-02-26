#ifndef SEMINAR_04_HELLOWORLDCLASS_H
#define SEMINAR_04_HELLOWORLDCLASS_H

#include <string>


class HelloWorldClass {
public:
    std::string Get() const;
    void Set(const std::string& string);

private:
    std::string string_;
};

#endif //SEMINAR_04_HELLOWORLDCLASS_H
