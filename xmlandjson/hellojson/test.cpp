#include <iostream>
#include <fstream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

int createJsonFile() {
    json j;
    j["pi"] = 3.14;
    j["happy"] = true;
    j["name"] = "xmf";
    j["nothing"] = nullptr;
    string str = j.dump(4);   //会以格式化的形式转换
    cout << str << endl;
    cout << j << endl;
    //写入文件中
    ofstream ofs;
    ofs.open("./test.json", ios::out);
    ofs << str;

    return 0;
}
int readJsonFile() {
    ifstream ifs;
    ifs.open("test.json");
    json j;
    ifs >> j;

    json::const_iterator pi = j.find("pi");
    if (pi != j.end()) {
        cout << pi.value().get<double>() << endl;
    }

    ifs.close();
    return 0;
}
int main() {
    cout << "hello nlohmannjson" << endl;
    //createJsonFile();
    readJsonFile();

    return 0;
}