#include<iostream>
#include "dog.h"
#include"cat.h"
using namespace std;
int main() {
    Dog dog;
    Cat cat;
    cout << dog.barking() << endl;
    cout << cat.barking() << endl;
    return 0;
}