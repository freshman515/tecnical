#include<iostream>
#include "animal/dog.h"
#include"animal/cat.h"
using namespace std;
int main() {
    Dog dog;
    Cat cat;
    cout << dog.barking() << endl;
    cout << cat.barking() << endl;
    return 0;
}