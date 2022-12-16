#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

/*bool isSpace(char c)
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
}*/


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
                //cout << "Node" << endl;
                break;
            case T_STRING:
            case T_CHAR:
                //cout << "\"" << *static_cast<string*>(this->data) << "\"" << endl;
                break;
            case T_INT:
                //cout << *static_cast<int*>(this->data) << endl;
                break;
            case T_DOUBLE:
                //cout << *static_cast<double*>(this->data) << endl;
                break;
            case T_LIST:
                break;
            default:break;
        }
    }
} t_data;

typedef map<string, t_data> NODE;

class MyJson {
public:
    MyJson() { };
    MyJson operator[] (string x);

    // #TODO a template val() to return any types in TYPES enum
    string val();
    // #TODO possibility to change the val on run
    void val(string newValue);

    /*friend ostream& operator<<(ostream& stream, MyJson const & self) {
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
        g_currentNode.clear();
        return stream;
    }*/

    static string printJson(const NODE* pc_json = NULL, string pz_tabulation = "\t");
    void print();
    void buildTest();

private:
    NODE mc_json;
};
