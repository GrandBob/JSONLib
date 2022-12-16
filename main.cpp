#include <iostream>
#include <string>
#include <algorithm>

#include "Json/Base/jsonBase.hpp"

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

int main()
{
    string str = "string";
    jsonData data_string;
    data_string.m_data = &str;
    data_string.m_type = dataType::STRING;

    int i = 12;
    jsonData data_int;
    data_int.m_data = &i;
    data_int.m_type = dataType::INT;

    double d = 12.123;
    jsonData data_double;
    data_double.m_data = &d;
    data_double.m_type = dataType::DOUBLE;

    jsonNode test3;
    test3["3"] = data_int;
    test3["name"] = data_string;
    test3["town"] = data_string;
    test3["country"] = data_string;

    jsonNode test2;
    jsonData data2;
    data2.m_data = &test3;
    data2.m_type = dataType::NODE;
    test2["trump"] = data_string;
    test2["2"] = data2;

    jsonData data1;
    data1.m_data = &test2;
    data1.m_type = dataType::NODE;

    jsonNode yolo;
    yolo["1"] = data1;
    yolo["yolo"] = data_double;

    JsonBase json(yolo);
    json.print();

    cout << endl << endl;
    cout << "json[1] : " << json["1"] << endl;
    //cout << "json[yolo] : " << json["yolo"] << endl;
    //cout << "json[1][2] : " << json["1"]["2"] << endl;
    //cout << "json[1][trump] : " << json["1"]["trump"] << endl;
    //cout << "json[1][2][3] : " << json["1"]["2"]["3"] << endl;
    //cout << "json[1][2][country] : " << json["1"]["2"]["country"] << endl;
    //cout << "json[1][2][name] : " << json["1"]["2"]["name"] << endl;
    //cout << "json[1][2][town] : " << json["1"]["2"]["town"] << endl;

    //json["1"]["trump"].val("donald");
//    cout << "json[1][trump] : " << json["1"]["trump"] << endl;

    string test = R"({
        "dude" : {
            "firstname" : "Pierre",
            "lastname" : "Paul-Jack",
            "age" : 12,
            "city" : {
                "name" : "Plaisir",
                "postale" : 78370,
                "altitude" : 21.2422124,
                "longitude" : 5.123532
            }
        },
        "family" : [
            "Pascaline",
            "Gerald",
            "Bertrand",
            "Celestine",
            "Rorberto"
        ]
    })";

    //int nani = json["1"]["2"]["age"];

    //test.erase(remove(test.begin(), test.end(), '\n'), test.end());
    //test.erase(remove(test.begin(), test.end(), '\t'), test.end());
    //cout << formatStringJson(test) << endl;

    // MyJson json(test);
    // MyJson
}