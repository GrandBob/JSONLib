#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

bool isSpace(char c)
{
    return (c == ' ');
}

string formatStringJson(string& json) {
    string input = json;
    unsigned long firstQuote = input.find("\"");
    unsigned long secondQuote = input.find("\"", firstQuote+1);

    string firstPart="";
    string secondPart="";
    string quotePart="";

    if (firstQuote <= input.size())
    {
        firstPart = input.substr(0,firstQuote-1);
        if (secondQuote <= input.size())
        {
            secondPart = input.substr(secondQuote+1);
            quotePart = input.substr(firstQuote, (secondQuote+1)-firstQuote);
        }
        firstPart.erase(remove_if(firstPart.begin(), firstPart.end(), isSpace),firstPart.end());
        input = firstPart + quotePart + formatStringJson(secondPart);
    }
    else
    {
        input.erase(remove_if(input.begin(), input.end(), isSpace),input.end());
    }
    return input;
}


enum type {
    T_INT = 0,
    T_CHAR,
    T_DOUBLE,
    T_STRING,
    T_NODE,
    T_LIST
};

typedef struct s_data {
    void *data;
    int type;
    void print () {
        switch (this->type) {
            case T_NODE:
                cout << "Node" << endl;
                break;
            case T_STRING:
            case T_CHAR:
                cout << "\"" << *static_cast<string*>(this->data) << "\"" << endl;
                break;
            case T_INT:
                cout << *static_cast<int*>(this->data) << endl;
                break;
            case T_DOUBLE:
                cout << *static_cast<double*>(this->data) << endl;
                break;
            case T_LIST:
                break;
            default:break;
        }
    }
} t_data;

typedef map<string, t_data> NODE;

NODE g_currentNode;

class MyJson {
public:
    MyJson() { };
    MyJson operator[] (string x) {
        try {
            map<string, t_data>::iterator itSearch;
            map<string, t_data>::iterator itEnd;
            if (g_currentNode.empty()) {
                cout << "g_currentNode empty" << endl;
                itSearch = mc_json.find(x);
                itEnd = mc_json.end();
            }
            else {
                cout << "g_currentNode not empty" << endl;
                itSearch = g_currentNode.find(x);
                itEnd = g_currentNode.end();
            }
            if (itSearch != itEnd) {
                if (itSearch->second.type == T_NODE) {
                    cout << "NODE found" << endl;
                    g_currentNode = *static_cast<NODE*>(itSearch->second.data);
                } else {
                    cout << "operator[] g_currentNode.clear()" << endl;
                    g_currentNode.clear();
                    g_currentNode.insert(pair<string, t_data>(itSearch->first, itSearch->second));
                    cout << "Find the value, set it in g_currentNode" << endl;
                }
            } else {
                cout << "WTF" << endl;
                throw std::logic_error( "Undefined key : "+x+"\n" );
            }
        } catch ( const std::exception & e )
        {
            std::cerr << e.what();
        }
        return *this;
    };


    // #TODO a template val() to return any types in TYPES enum
    string val() {
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
        cout << "val() : g_currentNode.clear()" << endl;
        g_currentNode.clear();
        return tmp.str();
    }

    // #TODO possibility to change the val on run
    void val(string newValue) {
        cout << "val mc_json state :" << endl;
        printJson(&mc_json);
        cout << "-------------------" << endl;
        printJson(&g_currentNode);
        cout << "-------------------" << endl;

        stringstream tmp;
        if (g_currentNode.size() == 1) {
            NODE::iterator it = g_currentNode.begin();
            it->second.data = static_cast<void*>(&newValue);
        }
        g_currentNode.clear();
    }


    friend ostream& operator<<(ostream& stream, MyJson const & self) {
        if (g_currentNode.size() > 1) {
            stream << MyJson::printJson(&g_currentNode);
        } else {
            map<string, t_data>::const_iterator it = g_currentNode.begin();
            switch (it->second.type) {
                case T_STRING:
                case T_CHAR:
                    stream << *static_cast<string*>(it->second.data);
                    break;
                case T_INT:
                    stream << *static_cast<int*>(it->second.data);
                    break;
                case T_DOUBLE:
                    stream << *static_cast<double*>(it->second.data);
                    break;
                case T_LIST:
                    break;
                default:break;
            }
        }
        cout << "<< g_currentNode.clear()" << endl;
        g_currentNode.clear();
        return stream;
    }

    NODE mc_json;

    static string printJson(const NODE* pc_json = NULL, string pz_tabulation = "\t");
    void print() {
        if (g_currentNode.empty())
            cout << printJson(&mc_json) << endl;
        else
            cout << printJson(&g_currentNode) << endl;
    }
};

string MyJson::printJson(const NODE* pc_json, string pz_tabulation) {
    stringstream stream;
    stream << "{\n";
    for (NODE::const_iterator it = pc_json->begin(); it != pc_json->end(); it++) {
        stream << pz_tabulation << "\"" << it->first << "\" : ";
        switch (it->second.type) {
            case T_NODE:
                stream << printJson(static_cast<NODE*>(it->second.data), pz_tabulation + "\t");
                break;
            case T_STRING:
            case T_CHAR:
                stream << "\"" << *static_cast<string*>(it->second.data) << "\"" << "\n";
                break;
            case T_INT:
                stream << *static_cast<int*>(it->second.data) << "\n";
                break;
            case T_DOUBLE:
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

int main()
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

    MyJson json;
    t_data data1;
    data1.data = &test2;
    data1.type = T_NODE;
    json.mc_json["1"] = data1;
    json.mc_json["yolo"] = data_double;


    MyJson::printJson(&json.mc_json);
/*
    json.print();
    cout << endl << endl;
    cout << "json[1] : " << json["1"] << endl;
    cout << "json[yolo] : " << json["yolo"] << endl;
    cout << "json[1][2] : " << json["1"]["2"] << endl;
    cout << "json[1][trump] : " << json["1"]["trump"] << endl;
    cout << "json[1][2][3] : " << json["1"]["2"]["3"] << endl;
    cout << "json[1][2][country] : " << json["1"]["2"]["country"] << endl;
    cout << "json[1][2][name] : " << json["1"]["2"]["name"] << endl;
    cout << "json[1][2][town] : " << json["1"]["2"]["town"] << endl;
*/
    //json["1"]["trump"].val("donald");
//    cout << "json[1][trump] : " << json["1"]["trump"] << endl;

    string test = R"({
        toto : "titi",
        tutu : "toto",
        dude : {
            name : "jack",
            age : 12
            city : {
                name : "Plaisir de toto",
                postale : 78370,
                altitude : 21.2422124,
                longitude : 5.123532
            }
        }
    })";

    //int nani = json["1"]["2"]["age"];

    test.erase(remove(test.begin(), test.end(), '\n'), test.end());
    test.erase(remove(test.begin(), test.end(), '\t'), test.end());
    //cout << formatStringJson(test) << endl;

    // MyJson json(test);
    // MyJson
}