#include "system.hpp"

void System::push(const sf::Vector2f force) const {
    for (auto i = 0U; i < std::size(m_particles); ++i) {
        m_particles[i]->reset_counters();
        m_particles[i]->add_move(force);
        m_particles[i]->move();
    }
}

void System::update() const {
    for (auto i = 0U; i < std::size(m_particles); ++i) {
        m_particles[i]->move();
    }

    for (auto i = 0U; i < std::size(m_particles); ++i)
        m_particles[i]->reset_counters();
    ch.update();

    for (auto i = 0U; i < std::size(m_particles); ++i)
        m_particles[i]->move();
}