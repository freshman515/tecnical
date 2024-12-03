#include <iostream>
#include <cstring>  // 为了演示使用动态内存

class MyClass {
private:
    char* data;  // 动态分配的资源

public:
    // 默认构造函数
    MyClass(const char* str = "") {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
        std::cout << "Default Constructor\n";
    }

    // 拷贝构造函数
    MyClass(const MyClass& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
        std::cout << "Copy Constructor\n";
    }

    // 移动构造函数
    MyClass(MyClass&& other) noexcept : data(other.data) {
        other.data = nullptr;  // 将原对象的资源置空，避免析构时释放已转移的资源
        std::cout << "Move Constructor\n";
    }

    // 析构函数
    ~MyClass() {
        delete[] data;
        std::cout << "Destructor\n";
    }

    // 打印数据
    void print() const {
        std::cout << "Data: " << data << "\n";
    }
};

int main() {
    MyClass obj1("Hello");
    obj1.print();  // 输出 Data: Hello

    MyClass obj2 = std::move(obj1);  // 使用移动构造函数
    obj2.print();  // 输出 Data: Hello
    obj1.print();  // 输出 Data: (空)，因为 obj1 的数据已经被移动

    return 0;
}