#ifndef CAT_H__
#define CAT_H__
#include <iostream>
#include <string>
class Cat {
public:
    Cat() = default;
    Cat(std::string n);
    ~Cat();
    //
    void catInfo() const {
        std::cout << "cat info name: " << name << std::endl;
    }
    std::string  getName()const {
        return name;
    }
    void setName(std::string name) {
        this->name = name;
    }
private:
    std::string name = "mimi";

};
#endif