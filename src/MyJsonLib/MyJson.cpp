#include "MyJson.hpp"

NODE g_currentNode;

void MyJson::print() {
        //if (g_currentNode.empty())
        cout << printJson(&mc_json) << endl;
        //else
        //    cout << printJson(&g_currentNode) << endl;
    }

string MyJson::printJson(const NODE* pc_json, string pz_tabulation) {
    stringstream stream;
    stream << "{\n";
    for (NODE::const_iterator it = pc_json->begin(); it != pc_json->end(); it++) {
        stream << pz_tabulation << "\"" << it->first << "\" : ";
        cout << pz_tabulation << "\"" << it->first << "\" : " << endl;
        switch (it->second.type) {
            case T_NODE:
                cout << "NODE" << endl;
                stream << printJson(static_cast<NODE*>(it->second.data), pz_tabulation + "\t");
                break;
            case T_STRING:
            case T_CHAR:
                cout << "str" << endl;
                stream << "\"" << *static_cast<string*>(it->second.data) << "\"" << "\n";
                break;
            case T_INT:
                cout << "int" << endl;
                stream << *static_cast<int*>(it->second.data) << "\n";
                break;
            case T_DOUBLE:
                cout << "double" << endl;
                stream << *static_cast<double*>(it->second.data) << "\n";
                break;
            case T_LIST:
                break;
            default:break;
        }
    }
    stream << pz_tabulation.substr(0, pz_tabulation.size()-1) << "}\n";
    return stream.str();
}

MyJson MyJson::operator[] (string x) {
    try {
        map<string, t_data>::iterator itSearch;
        map<string, t_data>::iterator itEnd;
        if (g_currentNode.empty()) {
            itSearch = mc_json.find(x);
            itEnd = mc_json.end();
        }
        else {
            itSearch = g_currentNode.find(x);
            itEnd = g_currentNode.end();
        }
        if (itSearch != itEnd) {
            if (itSearch->second.type == T_NODE) {
                g_currentNode = *static_cast<NODE*>(itSearch->second.data);
            } else {
                g_currentNode.clear();
                g_currentNode.insert(pair<string, t_data>(itSearch->first, itSearch->second));
            }
        } else {
            throw std::logic_error( "Undefined key : "+x+"\n" );
        }
    } catch ( const std::exception & e )
    {
        std::cerr << e.what();
    }
    return *this;
};

string MyJson::val() {
    stringstream tmp;
    if (g_currentNode.size() > 1) {
        tmp << MyJson::printJson(&g_currentNode);
    }
    else {
        NODE::const_iterator it = g_currentNode.begin();
        switch (it->second.type) {
            case T_STRING:
            case T_CHAR:
                tmp << *static_cast<string*>(it->second.data);
                break;
            case T_INT:
                tmp << *static_cast<int*>(it->second.data);
                break;
            case T_DOUBLE:
                tmp << *static_cast<double*>(it->second.data);
                break;
            case T_LIST:
                break;
            default:break;
        }
    }
    g_currentNode.clear();
    return tmp.str();
}

void MyJson::val(string newValue) {
    //printJson(&mc_json);
    //printJson(&g_currentNode);

    stringstream tmp;
    if (g_currentNode.size() == 1) {
        NODE::iterator it = g_currentNode.begin();
        it->second.data = static_cast<void*>(&newValue);
    }
    g_currentNode.clear();
}

/* ONLY FOR TESTING */
void MyJson::buildTest()
{
    string str = "string";
    t_data data_string;
    data_string.data = &str;
    data_string.type = T_STRING;

    int i = 12;
    t_data data_int;
    data_int.data = &i;
    data_int.type = T_INT;

    double d = 12.123;
    t_data data_double;
    data_double.data = &d;
    data_double.type = T_DOUBLE;

    NODE test3;
    test3["3"] = data_int;
    test3["name"] = data_string;
    test3["town"] = data_string;
    test3["country"] = data_string;

    NODE test2;
    t_data data2;
    data2.data = &test3;
    data2.type = T_NODE;
    test2["trump"] = data_string;
    test2["2"] = data2;

    t_data data1;
    data1.data = &test2;
    data1.type = T_NODE;
    //this->mc_json["1"] = data1;
    this->mc_json["yolo"] = data_double;

}