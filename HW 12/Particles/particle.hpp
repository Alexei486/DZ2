#pragma once

#include <SFML/Graphics.hpp>

class Particle {
public:
    Particle() noexcept = default;

    explicit Particle(sf::Vector2f position, sf::Vector2f previous_position,
                      sf::Vector2f acceleration, float radius, float charge) noexcept :
            m_position(position), m_previous_position(previous_position),
            m_acceleration(acceleration), m_radius(radius), m_charge(charge) {
    }

    ~Particle() noexcept = default;

    const auto position() const noexcept {
        return m_position;
    }

    const auto charge() const noexcept {
        return m_charge;
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

    void move(float dt);

    void reset_counters();

private:

    sf::Vector2f m_position;
    sf::Vector2f m_previous_position;
    sf::Vector2f m_acceleration;

    float m_radius;
    float m_charge;

    sf::Vector2f m_sum_of_movement;
    float m_count_of_members;
};