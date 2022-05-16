#pragma once

#include <cmath>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "charge.h"
#include "particle.hpp"

class System {
public:
    using particle_t = std::shared_ptr<Particle>;

    explicit System(sf::Vector2f min_point, sf::Vector2f max_point,
                    std::vector<particle_t> & particles, int rib) noexcept :
            m_min_point(min_point), m_max_point(max_point),
            m_particles(particles), m_rib(rib), ch(particles, rib) {}

    ~System() noexcept = default;

    particle_t particle(std::size_t index) const {
        return m_particles.at(index);
    }

    const auto & particles() const noexcept {
        return m_particles;
    }

    void push(sf::Vector2f force) const;

    void update() const;

    Charges ch;
    sf::Vector2f m_min_point;
    sf::Vector2f m_max_point;

    std::vector<particle_t> m_particles;

    int m_rib;
};