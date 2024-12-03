#include <iostream>
#include <fstream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
void praseJson() {
    std::string json_str = R"({
    "name": "Alice",
        "age" : 24,
        "is_student" : false,
        "skills" : ["C++", "Python", "JavaScript"]
    })";

    json json_obj = json::parse(json_str);
    string name = json_obj["name"];
    int age = json_obj["age"];
    bool is_student = json_obj["is_student"];
    cout << name << " " << age << " " << is_student << endl;
    cout << "skills:";
    vector<string> skills = json_obj["skills"];

    for (const auto& skills : skills) {
        cout << skills << " ";
    }
    cout << endl;
}
void createJson() {
    json jsonObj1;
    json jsonObj2;
    jsonObj1["name"] = "xmf";
    jsonObj1["gender"] = "famale";
    jsonObj1["skills"] = { "java","c++","python","go" };
    jsonObj2["xmf"] = jsonObj1;
    string jsonStr = jsonObj2.dump(4);
    ofstream ofs;
    ofs.open("test.json", ios::out);
    ofs << jsonStr;
    ofs.close();


}
int main() {
    createJson();
    //string name = jsonObj["name"];
    //int age = jsonObj["age"];
    //cout << name << " " << age << endl;
    return 0;
}