#include<iostream>
#include<functional>
void changeInt(int x) {
    x = 20;
}
int main() {
    int y = 10;
    changeInt(std::ref(y));
    std::cout << y << std::endl;
    return 0;
}