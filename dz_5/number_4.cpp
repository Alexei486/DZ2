#include <iostream>
#include <regex>
#include <string>
#include <algorithm>
#include <vector>

#define C_ALL(X) cbegin(X), cend(X)

using namespace std;

int main()
{
    //std::regex pattern(R"(\b(\d){4}.([01]?[0-2]|2[0-2]).([0-5]\d)[\s])");
    std::regex pattern(R"((([01][0-9]|2[0-3])(:[0-5]\d){2}))");
    std::regex pattern_2(R"(((0[1-9]|[12][0-9]|3[01])[\.](0[13-9]|1[012])|(0[1-9]|(([1][0-9])|([2][0-8])))[\.](0[2]))[\.]\d{4})");
    std::string data = "02.07.2002 23:23:09 aa j1:06:59 55:55 2080:03:08 ff 10:06:59 a";

    const vector<smatch> matches{
            sregex_iterator{C_ALL(data), pattern},sregex_iterator{}};

    for (size_t i = 0; i < matches.size(); i++) {
        cout << matches[i].str(0) << endl;
    }
    const vector<smatch> matches2{
            sregex_iterator{C_ALL(data), pattern_2},sregex_iterator{}};

    for (size_t i = 0; i < matches2.size(); i++) {
        cout << matches2[i].str(0) << endl;
    }
}