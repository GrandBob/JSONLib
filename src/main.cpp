#include "MyJsonLib/MyJson.hpp"

using namespace std;

int main()
{
    MyJson json;
    json.buildTest();
    json.print();
/*
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
/*
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
*/
    //int nani = json["1"]["2"]["age"];

    //test.erase(remove(test.begin(), test.end(), '\n'), test.end());
    //test.erase(remove(test.begin(), test.end(), '\t'), test.end());
    //cout << formatStringJson(test) << endl;

    // MyJson json(test);
    // MyJson
}