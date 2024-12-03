#include<iostream>
#include "animal/dog.h"
#include"animal/cat.h"
#include"config.h"
using namespace std;
int main() {
    Dog dog;
    Cat cat;
    cout << dog.barking() << endl;
    cout << cat.barking() << endl;
    cout << CMAKE_CXX_STANDARD << endl;
    return 0;
}