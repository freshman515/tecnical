#include<iostream>
#include "dog.h"
#include "cat.h"
#include "config.h.in"
using namespace std;
int main() {
    Dog dog;
    Cat cat;
    cout << dog.barking() << endl;
    cout << cat.barking() << endl;
    cout << "C++ standard: " << CMAKE_CXX_STANDARD << endl;

    return 0;
}