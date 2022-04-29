#include <SFML/Graphics.hpp>

#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>
#include "asteroids.h"

int main()
{
    auto w = 1200;
    auto h = 800;

    asteroids::Game game(w, h);
    game.run();
}