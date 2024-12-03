#include <iostream>
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;
int main() {
    const char* xmlData = R"(
        <root>
            <man>
                <name>劳大</name>
                <age>89</age>
            </man>
        </root>
    )";
    XMLDocument doc;
    doc.Parse(xmlData);
    XMLElement* root = doc.RootElement();
    //查找man
    XMLElement* man = root->FirstChildElement("man");
    //查找name age
    XMLElement* name = man->FirstChildElement("name");
    XMLElement* age = man->FirstChildElement("age");
    cout << "name = " << name->GetText();
    cout << "age = " << age->GetText();

    return 0;

}