#include <iostream>
#include <regex>
#include <string>
#include <vector>
#define C_ALL(X) cbegin(X), cend(X)
int main()
{
    std::regex pattern("((\\w+)(\\.\\w+))*(@)((\\w+\\.)+(\\w+))");
    std::string data = "morozov.aleksei@phystech.edu freezz.79@mail.ru nikomy1404@phystech.edu cewcwe 31424 dog2@gmail.com";

    const std::vector<std::smatch> matches{std::sregex_iterator{C_ALL(data), pattern},std::sregex_iterator{}};

    for (int i = 0; i < matches.size(); i++)
    {
        std::string domain = matches[i].str();

        std::cout << domain.substr(domain.find("@")) << std::endl;
    }

}
