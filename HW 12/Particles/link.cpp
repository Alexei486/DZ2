#include "link.hpp"

void Link::compute() const {
    const auto delta = m_particle_2->position() - m_particle_1->position();
    const auto action = (norm(delta) * (length(delta) - m_distance) * m_stiffness) * 10.f;

    m_particle_1->add_move(action);
    m_particle_2->add_move(action * -1.0f);
}