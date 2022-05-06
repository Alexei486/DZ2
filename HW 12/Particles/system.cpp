#include "system.hpp"

void System::initialize() {
    const auto size = std::size(m_particles);

    for (auto i = 0U; i < size; ++i) {
        if ((i + 1) % m_rib != 0) {
            m_links.push_back(Link(particle(i), particle(i + 1), 0.7f));
        }
        if (i + m_rib < size) {
            m_links.push_back(Link(particle(i), particle(i + m_rib), 0.7f));
        }
        if ((i + 1 + m_rib < size) and ((i + 1 + m_rib) % m_rib) != 0) {
            m_links.push_back(Link(particle(i), particle(i + 1 + m_rib), 0.7f));
        }
        if ((i - 1 + m_rib < size) and ((i - 1 + m_rib) % m_rib != 0)) {
            m_links.push_back(Link(particle(i), particle(i - 1 + m_rib), 0.7f));
        }
    }
}

void System::push(const sf::Vector2f force) const {
    for (auto i = 0U; i < std::size(m_particles); ++i) {
        m_particles[i]->reset_counters();
        m_particles[i]->add_move(force);
        m_particles[i]->move();
    }
}

void System::update() const {
    for (auto i = 0U; i < std::size(m_particles); ++i) {
        m_particles[i]->move(0.25f);

        if (m_particles[i]->position().y + m_particles[i]->radius() > m_max_point.y) {
            m_particles[i]->set_y(m_max_point.y - m_particles[i]->radius());
        }

        if (m_particles[i]->position().y - m_particles[i]->radius() < m_min_point.y) {
            m_particles[i]->set_y(m_min_point.y + m_particles[i]->radius());
        }

        if (m_particles[i]->position().x + m_particles[i]->radius() > m_max_point.x) {
            m_particles[i]->set_x(m_max_point.x - m_particles[i]->radius());
        }

        if (m_particles[i]->position().x - m_particles[i]->radius() < m_min_point.x) {
            m_particles[i]->set_x(m_min_point.x + m_particles[i]->radius());
        }

        m_particles[i]->reset_counters();
    }

    for (auto i = 0U; i < std::size(m_links); ++i) {
        m_links[i].compute();
    }

    for (auto i = 0U; i < std::size(m_particles); ++i) {
        m_particles[i]->move();
    }

    for (auto i = 0U; i < std::size(m_particles); ++i)
        m_particles[i]->reset_counters();

    // ���� �������
    for (auto i = 0U; i < std::size(m_particles); ++i) {

        for (auto i1 = i + 1; i1 < std::size(m_particles); ++i1) {
            auto p2 = *m_particles[i1];
            auto delta_pos = m_particles[i]->position() - p2.position();
            {
                auto q1 = m_particles[i]->charge();
                auto q2 = m_particles[i1]->charge();
                auto action = m_particles[i]->charge() * m_particles[i1]->charge() /((delta_pos.x * delta_pos.x + delta_pos.y * delta_pos.y)*(delta_pos.x * delta_pos.x + delta_pos.y * delta_pos.y)) * 10000.f;
                auto norm_delta_pos = norm(delta_pos);
                m_particles[i]->add_move(norm_delta_pos * action);
                m_particles[i1]->add_move(norm_delta_pos * -action);
            }
        }
    }

    for (auto i = 0U; i < std::size(m_particles); ++i)
        m_particles[i]->move();

}