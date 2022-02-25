#include <iostream>
#include <set>
#include <cstdlib>
#include <vector>
#include<chrono>
#include "timer.hpp"
#include<algorithm>

int main() {
    Timer<std::chrono::microseconds> t(false);
    srand(4541);
    std::set < int > st;

    for (int count = 0; count < 100; ++count) {

        st.insert(rand());
    }

    t.start();
    std::vector<int> array;
    for(auto i : st)
        array.push_back(i);

    std::sort(array.begin(),array.end());
    t.stop();
    t.elapsed();
}
//set -40,42,43,41,42,43
//vector - 17,18,45,21,19,31,21
