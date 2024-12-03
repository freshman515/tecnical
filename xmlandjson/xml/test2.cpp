#include "tinyxml2.h"
#include <iostream>
using namespace std;
int main() {
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    tinyxml2::XMLElement* man = doc.NewElement("man");
    //ele->SetAttribute("id", "2");
    //ele->SetText("hello world");
    root->InsertEndChild(man);
    tinyxml2::XMLElement* name = doc.NewElement("name");
    name->SetText("劳大");
    tinyxml2::XMLElement* age = doc.NewElement("age");
    age->SetText("89");
    man->InsertEndChild(name);
    man->InsertEndChild(age);

    doc.SaveFile("test5.xml");
    return 0;
}