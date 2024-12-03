#include "tinyxml2.h"
#include <iostream>
using namespace std;
int main() {
    tinyxml2::XMLDocument doc;
    //prase
    tinyxml2::XMLError eResult = doc.LoadFile("test5.xml");
    if (eResult != tinyxml2::XML_SUCCESS) {
        cerr << "Error load file " << endl;
        return -1;
    }
    tinyxml2::XMLElement* root = doc.RootElement();
    if (root == nullptr) {
        cerr << "no rootElement" << endl;
        return -1;
    }
    cout << "root element = " << root->Name() << endl;
    //遍历
    for (tinyxml2::XMLElement* element = root->FirstChildElement();element != nullptr;element = element->NextSiblingElement()) {
        cout << "Element Name = " << element->Name() << endl;
    }



    return 0;
}