#include <iostream>
#include <set>
#include <cstdlib>
#include <vector>
#include<chrono>
#include "timer.hpp"
#include <random>
#include<algorithm>
#define N 1e7

int main() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<int> array0;
    std::iota(std::begin(array0), std::end(array0), 1);
    std::shuffle(std::begin(array0), std::end(array0), g);

    Timer<std::chrono::microseconds> vec_t(false);
    vec_t.stop();
    Timer<std::chrono::microseconds> set_t(false);
    set_t.stop();

    std::vector<int> array;
    std::set < int > st;

    set_t.start();
    for (int count = 0; count < N; count++) {

        st.insert(array0[count]);
    }
    set_t.stop();

    vect_t.start();
    for(int count = 0; count < N; count++)
        array.push_back(array0[count]);
    std::sort(array.begin(),array.end());
    vect_t.stop();

}

//set - 19894 milliseconds
//vector - 1632 milliseconds
