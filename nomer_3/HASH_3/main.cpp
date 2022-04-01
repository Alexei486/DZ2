#include <iostream>
#include <string>
#include <random>
#include<set>
#include<vector>
#include "hash_functions.hpp"
#include <fstream>

std::set < std::string > make_random_words(std::size_t N, std::size_t length) // length = 10 - good enough
{
    std::uniform_int_distribution <> letter(97, 122);
    std::default_random_engine e(static_cast < std::size_t > (
                                         std::chrono::system_clock::now().time_since_epoch().count()));

    std::set < std::string > words;

    for (std::string s(length, '_'); std::size(words) < N; words.insert(s))
        for (auto & c : s)
            c = letter(e);

    return words;
}
int main() {
    auto s = make_random_words(1e6, 10);
    std::set < int > hash_RS{};
    std::set < int > hash_JS{};
    std::set < int > hash_PJW{};
    std::set < int > hash_ELF{};
    std::set < int > hash_BKDR{};
    std::set < int > hash_SDBM{};
    std::set < int > hash_DJB{};
    std::set < int > hash_DEK{};
    std::set < int > hash_AP{};
    std::string filename = "mass.txt";
    //std::fstream s("mass.txt",s.out);
    std::string path = "mass1.txt";
    std::ofstream fout;

    auto RSH = 0;
    auto JSH = 0;
    auto PJW = 0;
    auto ELF = 0;
    auto BKDR = 0;
    auto SDBM = 0;
    auto DJB = 0;
    auto DEK = 0;
    auto AP = 0;

    auto n = 0;
    fout.open(path);
    for (auto i : s) {
        n++;
        RSH += 1 - hash_RS.insert(RSHash(i, i.size())).second;
        JSH += 1 - hash_JS.insert(JSHash(i, i.size())).second;
        PJW += 1 - hash_PJW.insert(PJWHash(i, i.size())).second;
        ELF += 1 - hash_ELF.insert(ELFHash(i, i.size())).second;
        BKDR += 1 - hash_BKDR.insert(BKDRHash(i, i.size())).second;
        SDBM += 1 - hash_SDBM.insert(SDBMHash(i, i.size())).second;
        DJB += 1 - hash_DJB.insert(DJBHash(i, i.size())).second;
        DEK += 1 - hash_DEK.insert(DEKHash(i, i.size())).second;
        AP += 1 - hash_AP.insert(APHash(i, i.size())).second;


        {
            fout << n << "," << RSH << "," << JSH << "," << PJW << "," << ELF << "," << BKDR << "," << SDBM << ","
                 << DJB << "," << DEK << "," << AP << "\n";
        }
    }
}

