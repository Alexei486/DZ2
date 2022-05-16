#include "charge.h"
void Charges::update() const
{
    for (auto i = 0U; i < std::size(m_particles); ++i)
    {

        for (auto i1 = i + 1; i1 < std::size(m_particles); ++i1) {
            auto p2 = *m_particles[i1];
            auto delta_pos = m_particles[i]->position() - p2.position();
            {
                auto action = charges[i] /((delta_pos.x * delta_pos.x + delta_pos.y * delta_pos.y)*(delta_pos.x * delta_pos.x + delta_pos.y * delta_pos.y)) * 10000.f;
                auto norm_delta_pos = norm(delta_pos);
                m_particles[i]->add_move(norm_delta_pos * action);
                m_particles[i1]->add_move(norm_delta_pos * -action);
            }
        }
    }
}

