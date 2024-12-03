#include <iostream>
#include <memory>
#include "cat.h"
using namespace std;
void funcPassByValue(unique_ptr<Cat> c) {
    c->catInfo();
}
void funcPassByRef(unique_ptr<Cat>& c) {
    c->catInfo();
    c->setName("Dag");
    c.reset();
}
//const应用就不能清空reset();
void funcPassByRef2(const unique_ptr<Cat>& c) {
    c->catInfo();
    c->setName("Dag");
    //c.reset();
}
int main() {
    //unique_ptr 不可copy，只可move
    unique_ptr<Cat> c1 = make_unique<Cat>("huamao");
    //pass value     
    funcPassByValue(move(c1));  //用move转移c1的所有权,因为它是不可复制的
    //c1->catInfo();  //此时c1的所有权已经被转移了，不能再使用
    funcPassByValue(make_unique<Cat>()); //默认会使用move

    unique_ptr<Cat> c2 = make_unique<Cat>("lao3");  //用引用的方式传递就不用move
    funcPassByRef2(c2);
    c2->catInfo();
    return 0;
}