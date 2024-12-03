#include <iostream>
#include <fstream>
#include "json.hpp"
#include "tinyxml2.h"
using namespace std;
using json = nlohmann::json;
using namespace tinyxml2;

//json->xml
XMLElement* json2xmlAssistment(const json& jsonObj, XMLDocument* doc, XMLElement* parent) {

    for (auto it = jsonObj.begin();it != jsonObj.end();it++) {
        if (it.key() == "_text") {
            parent->SetText(it.value().get<string>().c_str());

        } else if (it.key()[0] == '@') {
            parent->SetAttribute(it.key().substr(1).c_str(), it.value().get<string>().c_str());
        } else if (it.value().is_array()) {
            for (auto item : it.value()) {
                XMLElement* child = doc->NewElement(it.key().c_str());
                json2xmlAssistment(item, doc, child);
                parent->LinkEndChild(child);
            }
        } else {
            XMLElement* child = doc->NewElement(it.key().c_str());
            cout << it.key().c_str() << endl;
            json2xmlAssistment(it.value(), doc, child);
            parent->LinkEndChild(child);

        }

    }
    return parent;
}
void json2xml(const char* filename, const json& jsonObj) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.LinkEndChild(root);
    json2xmlAssistment(jsonObj, &doc, root);
    doc.SaveFile(filename);
}

//xml->json
json xml2jsonAssistment(tinyxml2::XMLElement* element) {
    json jsonObj;
    const tinyxml2::XMLAttribute* attr = nullptr;
    attr = element->FirstAttribute();
     //先处理属性
    int i = 0;
    cout << "attr = " << (attr == nullptr);
    while (attr) {
        string name = attr->Name();
        jsonObj["@" + name] = attr->Value();
        attr = attr->Next();
        cout << ++i << endl;
    }
    //处理文本
    const char* text = element->GetText();
    if (text) {
        jsonObj["_text"] = text;
    }

    //处理子节点
    bool hasChildren = false;
    for (auto child = element->FirstChildElement();child != nullptr;child = child->NextSiblingElement()) {
        hasChildren = true;
        string key = child->Value();
        if (jsonObj.find(key) == jsonObj.end()) {
            jsonObj[key] = json::array();
        }
        jsonObj[child->Value()].push_back(xml2jsonAssistment(child));
    }
    if (hasChildren == true) {
        for (auto it = jsonObj.begin();it != jsonObj.end();it++) {
            if (it.value().is_array() && it.value().size() == 1) {
                it.value() = it.value()[0];
            }
        }
    }
    /*for (auto child = element->FirstChildElement();child;child = child->NextSiblingElement()) {
        if (jsonObj[child->Value()].size() == 1) {
            jsonObj[child->Value()] = jsonObj[child->Value()].back();
        }
    }*/

    return jsonObj;
}
json xml2json(const string& filename) {
    json jsonObj;
    tinyxml2::XMLDocument doc;
    doc.LoadFile(filename.c_str());
    if (doc.Error()) {
        cout << "is error" << endl;
        return jsonObj;
    }
    cout << doc.RootElement()->Name() << endl;
   // cout << doc.RootElement()->F
    return xml2jsonAssistment(doc.RootElement());
}
int main() {
    ifstream ifs("test.json");
    json jsonObj;
    ifs >> jsonObj;

    json2xml("test5.xml", jsonObj);
    //jsonObj = xml2json("test5.xml");
    //ofstream ofs("test.json");
    //ofs << jsonObj.dump(4);

    return 0;
}