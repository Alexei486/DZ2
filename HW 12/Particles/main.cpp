#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "system.hpp"

int main(int argc, char ** argv) {
    sf::RenderWindow window(sf::VideoMode(800U, 600U), "PHYSICS");

    sf::Vector2f min_point(0.0f, 0.0f);
    sf::Vector2f max_point(775.0f, 575.0f);

    const auto N = 10U;

    const auto l_neigh = 20.0f;

    const auto C = (min_point + max_point) * 0.5f;

    const auto r = 2.5f;

    const auto charge = 1.f;

    std::vector<System::particle_t> particles;

    for (auto i = 0U; i < N; ++i) {
        for (auto k = 0U; k < N; ++k) {
            auto position = sf::Vector2f(l_neigh * i, l_neigh * k);

            particles.push_back(std::make_shared<Particle>(position, position, sf::Vector2f(0.0f, 0.0f), r, charge));
        }
    }

    System system(min_point, max_point, particles, N);

    sf::Event event;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        for(int i = 0 ; i < 5; i++)
            system.update();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            system.push(sf::Vector2f(0.0f, -5.f));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            system.push(sf::Vector2f(0.0f, 5.f));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            system.push(sf::Vector2f(-5.f, 0.0f));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            system.push(sf::Vector2f(5.f, 0.0f));
        }

        window.clear();

        for (auto i = 0U; i < system.particles().size(); ++i) {
            sf::CircleShape circle(2.0f * r);

            circle.setPosition(system.particle(i)->position() + sf::Vector2f(r, r));

            circle.setFillColor(sf::Color::Red);

            window.draw(circle);
        }

        window.display();
    }

    // system("pause");

    return EXIT_SUCCESS;
}