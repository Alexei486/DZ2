#include <iostream>
#include <string>
#include<set>
#include<vector>
#include <fstream>

unsigned int RSHash(const char* str, unsigned int length)
{
    unsigned int b    = 378551;
    unsigned int a    = 63689;
    unsigned int hash = 0;
    unsigned int i    = 0;
    for (i = 0; i < length; ++str, ++i)
    {
        hash = hash * a + (*str);
        a    = a * b;
    }

    return hash;
}

unsigned int JSHash(const char* str, unsigned int length)
{
    unsigned int hash = 1315423911;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((hash << 5) + (*str) + (hash >> 2));
    }

    return hash;
}

unsigned int PJWHash(const char* str, unsigned int length)
{
    const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
    const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
    const unsigned int HighBits          =
            (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << OneEighth) + (*str);

        if ((test = hash & HighBits) != 0)
        {
            hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return hash;
}

unsigned int ELFHash(const char* str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int x    = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << 4) + (*str);

        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
        }

        hash &= ~x;
    }

    return hash;
}
unsigned int BKDRHash(const char* str, unsigned int length)
{
    unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
    unsigned int hash = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash * seed) + (*str);
    }

    return hash;
}
unsigned int SDBMHash(const char* str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (*str) + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

unsigned int DJBHash(const char* str, unsigned int length)
{
    unsigned int hash = 5381;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) + hash) + (*str);
    }

    return hash;
}

unsigned int DEKHash(const char* str, unsigned int length)
{
    unsigned int hash = length;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
    }

    return hash;
}

unsigned int APHash(const char* str, unsigned int length)
{
    unsigned int hash = 0xAAAAAAAA;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
                (~((hash << 11) + ((*str) ^ (hash >> 5))));
    }

    return hash;
}
int main() {

   // std::string filename = "mass.txt";
    //std::fstream s("mass.txt",s.out);
    std::string path = "mass1.txt";
    std::ofstream fout;



    std::set < int > st;
    std::vector<int> array;
    std::set < int > st2;
    std::vector<int> array2;
    std::set < int > st3;
    std::vector<int> array3;
    std::set < int > st4;
    std::vector<int> array4;
    std::set < int > st5;
    std::vector<int> array5;
    std::set < int > st6;
    std::vector<int> array6;
    std::set < int > st7;
    std::vector<int> array7;
    std::set < int > st8;
    std::vector<int> array8;
    std::set < int > st9;
    std::vector<int> array9;
    std::vector<std::vector<size_t>> stat{9, std::vector<size_t>{}};
    srand(42);
    int RSH,JSH,PJWH,ELFH,BKDRH,SDBMH,DJBH,DEKH,APH;
    for (int i = 0; i < 5000000; ++i)
    {

        char text[6];
        for (int j = 0; j < 6; ++j )
        {
            text[j] = char(rand() % 26 + 0x61);
        }
        int a= RSHash(text,6);
        int b= JSHash(text,6);
        int c= PJWHash(text,6);
        int d= ELFHash(text,6);
        int e= BKDRHash(text,6);
        int f= SDBMHash(text,6);
        int g= DJBHash(text,6);
        int k= DJBHash(text,6);
        int h= APHash(text,6);
        st.insert(a);
        array.push_back(a);
        st2.insert(b);
        array2.push_back(b);
        st3.insert(c);
        array3.push_back(c);
        st4.insert(d);
        array4.push_back(d);
        st5.insert(e);
        array5.push_back(e);
        st6.insert(f);
        array6.push_back(f);
        st7.insert(g);
        array7.push_back(g);
        st8.insert(k);
        array8.push_back(k);
        st9.insert(h);
        array9.push_back(h);
        stat[0].push_back(array.size() - st.size());
        stat[1].push_back(array2.size() - st2.size());
        stat[2].push_back(array3.size() - st3.size());
        stat[3].push_back(array4.size() - st4.size());
        stat[4].push_back(array5.size() - st5.size());
        stat[5].push_back(array6.size() - st6.size());
        stat[6].push_back(array7.size() - st7.size());
        stat[7].push_back(array8.size() - st8.size());
        stat[8].push_back(array9.size() - st9.size());
        /*
         array.size()-st.size()
        std::cout<<array2.size()-st2.size()<<"\n";
        std::cout<<array3.size()-st3.size()<<"\n";
        std::cout<<array4.size()-st4.size()<<"\n";
        std::cout<<array5.size()-st5.size()<<"\n";
        std::cout<<array6.size()-st6.size()<<"\n";
        std::cout<<array7.size()-st7.size()<<"\n";
        std::cout<<array8.size()-st8.size()<<"\n";
        std::cout<<array9.size()-st9.size()<<"\n";
         */
    }
    fout.open(path);
    if(!fout.is_open())
    {
        std::cout<<"error"<<std::endl;
    }
    else
    {
        for(auto const& x : stat) {
            for (auto const &i: x)
                fout << i << "\n";
        }
    }
    fout.close();
}