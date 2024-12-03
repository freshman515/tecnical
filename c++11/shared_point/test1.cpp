#include <iostream>
#include <memory>
#include "cat.h"
using namespace std;
int main() {
    //常量类型
    //std::shared_ptr pint = make_shared<int>(new int(100));
    std::shared_ptr pint = make_shared<int>(10);
    cout << *pint << " count = " << pint.use_count() << endl;
    //copy
    shared_ptr pint2 = pint;
    cout << "pint 2 values = " << *pint2 << "count = " << pint2.use_count() << endl;
    cout << "pint1 count = " << pint.use_count() << endl;

//这个操作只会把2指针清空，指针1还能继续使用
//如果清空1，那么2就还能用
    pint2 = nullptr;
    cout << "pint1 = " << *pint << " count = " << pint.use_count() << endl;
//一次构造，一次销毁

    return 0;
}