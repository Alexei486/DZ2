#include <iostream>
#include <vector>
#include <random>

void print(std::vector <int> p, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        std::cout << i + 1 << ": " << p[i] << std::endl;
    }
    std::cout << std::endl;
}
int is_simple(int n)
{
    for(int i = 2; i <= n/2; i++)
    {
        if ((n % i) == 0)
        {
            return 0;
        }
    }
    return 1;
}
void vect_sqrt (int &n)
{
    n = n * n;
}
void replace_by1 (int &n) {
    n = 1;
}
void replace_by0 (int &n) {
    if (n < 0) {
        n = 0;
    }
}
int main()
{
    std::vector <int> p(10);
    for (int i=0;i<10;++i)
    {
        p[i]=i+1;
    }

    int n1 = p.size();
    print(p,n1);
    std::cout << "how many elements you want to \"cin\"?";
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        std::cout << "Add new element: ";
        std::cin >> x;
        p.push_back(x);
    }
    std::cout << "new p : " << n << std::endl;
    int n2=p.size();
    print(p,n2);

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(p.begin(), p.end(), g);
    std::cout << "change p items places: "<<std::endl;
    print(p,n2);

    for (int i = 0; i < p.size() - 1; i++)
    {
        int n = p[i];
        int count = count_if(p.begin(), p.end(), [n](int kolwo){return kolwo == n;});
        if (count > 1)
        {
            p.erase(remove_if(p.begin() + i + 1, p.end(), [n](int kolwo){return kolwo == n;}));
        }
    }
    std::cout << "p after deleting items: ";
    int n3 = p.size();
    print(p,n3);
    int nechetn = count_if(p.begin(), p.end(), [](int kolwo){return kolwo % 2 != 0;});
    std::cout << "number of odd numbers" << nechetn << std::endl;
    std::cout << "Max item: " << *max_element(p.begin(), p.end()) << std::endl;
    std::cout << "Min item: " << *min_element(p.begin(), p.end()) << std::endl;

    auto it = find_if(p.begin(), p.end(), is_simple);
    std::cout << "simple item: " << *it << std::endl;

    for_each(p.begin(), p.end(), vect_sqrt);
    std::cout << "new p :";
    print(p,n3);

    std::vector <int> p2(p.size());
    std::mt19937 g2(rd());
    std::uniform_int_distribution<> dist_2(0,10);
    int r2 = 0;
    for (size_t i = 0; i < p.size(); i++) {
        p2[i] = dist_2(g2);
    }
    std::cout << "p2 :"<<std::endl;
    int n5=p2.size();
    print(p2,n5);

    int res = accumulate(p2.begin(), p2.end(), 0, [](int sum, int item){return sum += item;});
    std::cout << "p2 summ items: " << res << std::endl;

    std::cout << "How many new first items you want to replace by 1: ";
    int number;
    std::cin >> number;
    for_each(p2.begin(), p2.begin() + number, replace_by1);
    std::cout << "new p2 : "<<std::endl;
    print(p2,n5);

    std::vector <int> p3(p.size());
    for (int i=0;i < p3.size();i++)
    {
        p3[i] = p[i] - p2[i];
    }
    std::cout << "p3 :"<<std::endl;
    int n6=p3.size();
    print(p3,n6);

    for_each(p3.begin(), p3.end(), replace_by0);
    std::cout << "p3 after replacing numbers lower then 0: "<<std::endl;
    int n7=p3.size();
    print(p3,n7);
    p3.erase(remove_if(p3.begin(), p3.end(), [](int number){return number == 0;}), p3.end());
    std::cout << "p3 without 0: "<< std::endl;
    int n8=p3.size();
    print(p3,n8);
    std::cout << std::endl;

    std::sort(p3.begin(), p3.end(), [](int numb_1, int numb_2){return numb_1 > numb_2;});
    std::cout << "p3 after change: "<<std::endl ;
    print(p3,n8);
    std::cout << std::endl;

    std::cout << "p3 top 3 numbers: "<< std::endl;
    print(p3, 3);
    std::cout << std::endl;

    std::cout << "Sorted p and p2" << std::endl;
    sort(p.begin(), p.end());
    sort(p2.begin(), p2.end());
    std::cout << "p after sort: " << std::endl;
    int n9=p.size();
    print(p,n8);
    std::cout << std::endl << "p2 after sort: "<<std::endl;
    int n10=p2.size();
    print(p2,n10);
    std::cout << std::endl;

    std::vector<int> p4(p.size() + p2.size());
    merge(p.begin(), p.end(), p2.begin(), p2.end(), p4.begin());
    std::cout << "p4 : "<< std::endl;
    int n11 = p4.size();
    print(p4,n11);
    std::cout << std::endl;

    std::cout << "where we can place 1: ";
    sort(p4.begin(), p4.end());
    int where = count_if(p4.begin(), p4.end(), [](int number){return number >0 && number < 2;});
    std::cout << where << std::endl;

    std::cout << "all vectors" << std::endl;

    std::cout << "p: "<<std::endl;
    int k = p.size();
    print(p,k);
    std::cout << std::endl << "p2: "<<std::endl;
    int k2 = p2.size();
    print(p2,k2);
    std::cout << std::endl << "p3: "<<std::endl;
    int k3 = p3.size();
    print(p3,k3);
    std::cout << std::endl << "p4: "<<std::endl;
    int k4 = p4.size();
    print(p4,k4);
}
