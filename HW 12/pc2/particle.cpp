#include "particle.hpp"

void Particle::reset_counters() {
    m_sum_of_movement = sf::Vector2f(0.f, 0.f);
}

void Particle::add_move(sf::Vector2f deltaW) {
    m_sum_of_movement += deltaW * 0.1f;
}

void Particle::move() {
    m_position += m_sum_of_movement ;

    reset_counters();

}
