#include "cat.h"

Cat::Cat(std::string n) :name(n) {
    std::cout << "constructor of Cat : " << n << std::endl;
}
Cat::~Cat() {
    std::cout << "Destructor of Cat : " << name << std::endl;

}