#include <iostream>
#include <locale>
#include <iomanip>

int main()
{
    long double change,money;
    std::cout << "Enter the money in USD: ";

    std::cin >> money;
    money *= 100;
    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << "USD: " << std::put_money(money) << std::endl;

    std::cout << "Enter the USD-RUB exchange rate: " << std::endl;
    std::cin >> change;
    money = money * change;

    std::cout.imbue(std::locale("ru_RU.UTF-8"));
    std::cout << std::showbase<< "Amount entered in RUB: " << std::put_money(money) << std::endl;

}