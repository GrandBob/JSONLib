#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

enum dataType {
    INT = 0,
    CHAR,
    DOUBLE,
    STRING,
    NODE,
    LIST
};

typedef struct s_data {
    void *m_data;
    enum dataType m_type;
    void print () {
        switch (this->m_type) {
            case dataType::NODE:
                cout << "Node" << endl;
                break;
            case dataType::STRING:
            case dataType::CHAR:
                cout << "\"" << *static_cast<string*>(this->m_data) << "\"" << endl;
                break;
            case dataType::INT:
                cout << *static_cast<int*>(this->m_data) << endl;
                break;
            case dataType::DOUBLE:
                cout << *static_cast<double*>(this->m_data) << endl;
                break;
            case dataType::LIST:
                break;
            default:break;
        }
    }
} jsonData;

typedef map<string, jsonData> jsonNode;

class JsonBase {
public:
    JsonBase(jsonNode json) {
        mc_base = json;
        mc_current = nullptr;
    };
    JsonBase operator[] (string x) {
        try {
            jsonNode::iterator itSearch;
            jsonNode::iterator itEnd;
            if (mc_current != nullptr  && mc_current->empty()) {
                itSearch = mc_current->find(x);
                itEnd = mc_current->end();
            } else {
                itSearch = mc_base.find(x);
                itEnd = mc_base.end();
            }
             
            if (itSearch != itEnd) {
                mc_current = &*itSearch;
            } else {
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
        if (mc_current->size() > 1) {
            tmp << JsonBase::printJson(mc_current);
        }
        else {
            jsonNode::const_iterator it = mc_current->begin();
            switch (it->second.m_type) {
                case dataType::STRING:
                case dataType::CHAR:
                    tmp << *static_cast<string*>(it->second.m_data);
                    break;
                case dataType::INT:
                    tmp << *static_cast<int*>(it->second.m_data);
                    break;
                case dataType::DOUBLE:
                    tmp << *static_cast<double*>(it->second.m_data);
                    break;
                case dataType::LIST:
                    break;
                default:break;
            }
        }
        mc_current->clear();
        return tmp.str();
    }

    // #TODO possibility to change the val on run
    void val(string newValue) {
        printJson(&mc_base);
        cout << "-------------------" << endl;
        printJson(mc_current);
        cout << "-------------------" << endl;

        stringstream tmp;
        if (mc_current->size() == 1) {
            jsonNode::iterator it = mc_current->begin();
            it->second.m_data = static_cast<void*>(&newValue);
        }
        mc_current->clear();
    }


    friend ostream& operator<<(ostream& stream, JsonBase const & self) {
        if (self.mc_current != nullptr) {
            if (self.mc_current->size() > 1) {
                stream << JsonBase::printJson(self.mc_current);
            } else {
                jsonNode::const_iterator it = self.mc_current->begin();
                switch (it->second.m_type) {
                    case dataType::STRING:
                    case dataType::CHAR:
                        stream << *static_cast<string*>(it->second.m_data);
                        break;
                    case dataType::INT:
                        stream << *static_cast<int*>(it->second.m_data);
                        break;
                    case dataType::DOUBLE:
                        stream << *static_cast<double*>(it->second.m_data);
                        break;
                    case dataType::LIST:
                        break;
                    default:break;
                }
            }
            //cout << "<< mc_current->clear()" << endl;
            self.mc_current->clear();
        }
        return stream;
    }

    jsonNode mc_base;
    jsonNode *mc_current;

    static string printJson(const jsonNode* pc_json = nullptr, string pz_tabulation = "\t");
    void print() {
        if (mc_current != nullptr && !mc_current->empty())
            cout << printJson(mc_current) << endl;
        else
            cout << printJson(&mc_base) << endl;
    }
};

string JsonBase::printJson(const jsonNode* pc_json, string pz_tabulation) {
    stringstream stream;
    stream << "{\n";
    for (jsonNode::const_iterator it = pc_json->begin(); it != pc_json->end(); it++) {
        stream << pz_tabulation << "\"" << it->first << "\" : ";
        switch (it->second.m_type) {
            case dataType::NODE:
                stream << printJson(static_cast<jsonNode*>(it->second.m_data), pz_tabulation + "\t");
                break;
            case dataType::STRING:
            case dataType::CHAR:
                stream << "\"" << *static_cast<string*>(it->second.m_data) << "\"" << "\n";
                break;
            case dataType::INT:
                stream << *static_cast<int*>(it->second.m_data) << "\n";
                break;
            case dataType::DOUBLE:
                stream << *static_cast<double*>(it->second.m_data) << "\n";
                break;
            case dataType::LIST:
                break;
            default:break;
        }
    }
    stream << pz_tabulation.substr(0, pz_tabulation.size()-1) << "}\n";
    return stream.str();
}