#include <iterator>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include<sstream>
#include <random>
#include <set>

void gen_text(const std::string& file) {
    std::ofstream fout(file);
    if(!fout.is_open())
    {
        std::cout<< "error";
    }
    else
    {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            fout << static_cast<char>('a' + (rand() % 26));
        }
        fout << '\n';
        }
    }
}

int main(int argc, char ** argv)
{
    gen_text("file1.txt");
    int n = 0;
    std::cin >> n;
    std::ifstream fin("file1.txt");
    std::string line;
    std::getline(fin, line);
    size_t line_size = line.size() + 1;
    fin.seekg((n-1) * line_size);
    std::getline(fin, line);
    std::cout << line;
}
