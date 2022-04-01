#pragma once
#include <string>

unsigned int RSHash(const std::string& str, unsigned int length)
{
    unsigned int b    = 378551;
    unsigned int a    = 63689;
    unsigned int hash = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++i)
    {
        hash = (str)[i] + hash * a;
        a    = a * b;
    }

    return hash;
}



unsigned int JSHash(const std::string& str, unsigned int length)
{
    unsigned int hash = 1315423911;
    unsigned int i    = 0;

    for (i = 0; i < length; ++i)
    {
        hash ^= ((hash << 5) + (str)[i] + (hash >> 2));
    }

    return hash;
}



unsigned int PJWHash(const std::string& str, unsigned int length)
{
    const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
    const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
    const unsigned int HighBits          =
            (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++i)
    {
        hash = (hash << OneEighth) + (str)[i];
        if ((test = hash & HighBits) != 0)
        {
            hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return hash;
}



unsigned int ELFHash(const std::string& str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int x    = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++i)
    {
        hash = (hash << 4) + (str)[i];

        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
        }

        hash &= ~x;
    }

    return hash;
}



unsigned int BKDRHash(const std::string& str, unsigned int length)
{
    unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
    unsigned int hash = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++i)
    {
        hash = (hash * seed) + (str)[i];
    }

    return hash;
}



unsigned int SDBMHash(const std::string& str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++i)
    {
        hash = (str)[i] + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}



unsigned int DJBHash(const std::string& str, unsigned int length)
{
    unsigned int hash = 5381;
    unsigned int i    = 0;

    for (i = 0; i < length; ++i)
    {
        hash = ((hash << 5) + hash) + (str)[i];
    }

    return hash;
}



unsigned int DEKHash(const std::string& str, unsigned int length)
{
    unsigned int hash = length;
    unsigned int i    = 0;

    for (i = 0; i < length; ++i)
    {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (str)[i];
    }

    return hash;
}



unsigned int APHash(const std::string& str, unsigned int length)
{
    unsigned int hash = 0xAAAAAAAA;
    unsigned int i    = 0;

    for (i = 0; i < length; ++i)
    {
        hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (str)[i] * (hash >> 3)) :
                (~((hash << 11) + ((str)[i] ^ (hash >> 5))));
    }

    return hash;
}
