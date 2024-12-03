#include "json.hpp"
#include <iostream>
#include <fstream>
using namespace std;
using json = nlohmann::json;
int main() {
    string json_str = R"({
        "login": {
            "pwd": "wqq2b4Ild/w=",
            "remember": "yes",
            "user": "Mi/CvL0kLkQ="
        },
        "type_path": {
            "path": "conf/fileType"
        },
        "web_server": {
            "ip": "192.168.1.27",
            "port": "80"
        }
    })";
    json json_obj = json::parse(json_str);
    cout << json_str << endl;
    cout << json_obj << endl;
    ofstream ofs;
    ofs.open("test.json", ios::out);
    string pwd = json_obj["login"]["pwd"];
    cout << "pwd = " << pwd << endl;
    json_obj["web_server"]["port"] = "3306"; //修改值
    ofs << json_obj.dump(4);
    for (auto it = json_obj.begin(); it != json_obj.end(); ++it) {
        std::cout << it.key() << ": " << it.value() << std::endl;
    }
    ofs.close();

}