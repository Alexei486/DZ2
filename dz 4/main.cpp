#include <iostream>
#include <vector>
#include <random>
int main()
{
    //1)10 chisel
    std::vector <int> p(10);
    std::iota(std::begin(p), std::end(p), 1);
    //2)10 chisel iz cin
    std::copy(std::istream_iterator < int >(std::cin),std::istream_iterator < int >(),std::back_inserter(p));
    //3)meshaem slychainim obrazom
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(p.begin(), p.end(), g);
    //4)ydalenie chisel
    std::sort(std::begin(p), std::end(p));
    auto last = std::unique(std::begin(p), std::end(p));
    p.erase(last, std::end(p));
    //5)nechetn
    auto nechetn = count_if(p.begin(), p.end(), [](int kolwo){return kolwo % 2 != 0;});
    //6)max and min item
    std::cout << "Max item: " << *max_element(p.begin(), p.end()) << std::endl;
    std::cout << "Min item: " << *min_element(p.begin(), p.end()) << std::endl;
    //7)simple item
    auto prime_number = std::find_if(std::begin(p), std::end(p), [](auto element) {for (auto i = 2; i < std::sqrt(element); ++i){if (element % i == 0){return false;}}return element != 1; });
    //8)kwadrati chisel
    std::transform(std::begin(p), std::end(p), std::begin(p), [](int& element) {return element * element; });
    //9)chisel p2
    std::vector <int> p2(p.size());
    std::mt19937 g2(rd());
    std::uniform_int_distribution<> dist_2(0,10);
    std::generate(std::begin(p2), std::end(p2), [&g2, &dist_2]() { return dist_2(g2); });
    //10)sum of p2 items
    auto res = accumulate(p2.begin(), p2.end(), 0, [](int sum, int item){return sum += item;});
    //11) zamena chisel na 1
    std::cout << "How many new first items you want to replace by 1: ";
    int number;
    std::cin >> number;
    std::fill_n(std::begin(p2), number, 1);
    //12)sozdaem p3
    std::vector <int> p3(p.size());
    std::transform(std::begin(p), std::end(p), std::begin(p2),std::begin(p3), [](auto lhs, auto rhs) { return lhs - rhs; });
    //13)zamena otric na 0
    std::replace_if(std::begin(p3), std::end(p3), [](int& element) { return element < 0; }, 0);
    //14)ydalaem 0
    p3.erase(remove_if(p3.begin(), p3.end(), [](int number){return number == 0;}), p3.end());
    //15)poryadok
    std::reverse(std::begin(p3), std::end(p3));
    //16)TOP 3
    std::partial_sort(std::begin(p3), std::next(std::begin(p3), 3), std::end(p3), [](auto lhs, auto rhs) {return lhs > rhs; });
    //17)sort p1 and p2
    sort(p.begin(), p.end());
    sort(p2.begin(), p2.end());
    //18) p4
    std::vector<int> p4(p.size() + p2.size());
    merge(p.begin(), p.end(), p2.begin(), p2.end(), p4.begin());
    //19)diap
    sort(p4.begin(), p4.end());
    auto where = count_if(p4.begin(), p4.end(), [](int number){return number >0 && number < 2;});
    //20)WSE COUT
    std::copy(std::begin(p), std::end(p), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::copy(std::begin(p2), std::end(p2), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::copy(std::begin(p3), std::end(p3), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::copy(std::begin(p4), std::end(p4), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
