#include <iostream>
#include <memory>
#include "cat.h"
using namespace std;
int main() {
   // Cat c1("OK");
    //c1.catInfo();

    //raw_pointer
    // Cat* cp1 = new Cat("yy");
    // cp1->catInfo();
    // delete cp1;

    //unique_pointer  自动释放内存
    //三种创建方式
    Cat* cp1 = new Cat("xiaohuang");
    unique_ptr<Cat> ucp1{ cp1 };
    //cp1 还能用，但是不建议，容易应发安全问题，违背了独占指针的初衷
    cp1 = nullptr;//只能置空
    ucp1->catInfo();
    cout << "__--------------------------__" << endl;
    //第二种 new
    unique_ptr<Cat> ucp2{ new Cat("damei") };
    ucp2->catInfo();
    ucp2->setName("jajaja");
    ucp2->catInfo();
    cout << " ----------------------------------" << endl;
    //第三种 推荐的方式
    unique_ptr<Cat> ucp3 = make_unique<Cat>("xiaomimi");
    cout << ucp3->getName() << endl;
    cout << "ucp3 address: " << ucp3.get() << endl;  //get 得到地址
    unique_ptr<int> uip1 = make_unique<int>(100);
    cout << "uip1 = " << *uip1 << " address: " << uip1.get() << endl;

    return 0;
}