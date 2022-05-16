#pragma once

#include <SFML/Graphics.hpp>

class Particle {
public:
    Particle() noexcept = default;

    explicit Particle(sf::Vector2f position, float radius, float charge) noexcept :
            m_position(position), m_radius(radius) {
    }

    ~Particle() noexcept = default;

    const auto position() const noexcept {
        return m_position;
    }

    const auto radius() const noexcept {
        return m_radius;
    }

    void set_x(float x) noexcept {
        m_position.x = x;
    }

    void set_y(float y) noexcept {
        m_position.y = y;
    }

    void add_move(sf::Vector2f delta);

    void move();

    void reset_counters();

private:

    sf::Vector2f m_position;

    float m_radius;
    sf::Vector2f m_sum_of_movement;
};