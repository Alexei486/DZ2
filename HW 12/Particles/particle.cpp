#include "particle.hpp"

void Particle::reset_counters() {
    m_count_of_members = 0.f;
    m_sum_of_movement = sf::Vector2f(0.f, 0.f);
}

void Particle::add_move(sf::Vector2f delta) {
    m_sum_of_movement += delta * 0.1f;
    m_count_of_members++;
}

void Particle::move() {
    m_position += m_sum_of_movement / m_count_of_members;
    reset_counters();
}

void Particle::move(float dt) {
    const auto current_position = m_position;

    m_position += ((m_position - m_previous_position) * dt + m_acceleration * dt * dt);

    m_previous_position = current_position;
}