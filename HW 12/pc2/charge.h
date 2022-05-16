//
// Created by Алексей Морозов on 16.05.2022.
//

#include "particle.hpp"
#include "functions.hpp"
#include <vector>

#include <SFML/Graphics.hpp>

class Charges
{
public:

    using particle_t = std::shared_ptr < Particle > ;

public:

    //Charges() noexcept = default;

    explicit Charges(const std::vector < particle_t > & particles, const std::size_t n) noexcept :
            m_particles(particles), N(n)
    {
        //set_charges();
    }

    ~Charges() noexcept = default;

public:

    void update() const ;
/*
private:
    void set_charges();
*/
private:

    const std::size_t N;
    std::vector <float> charges
    {10,1,1,1,1,1,1,1,1,10,
     1,1,1,1,1,1,1,10,1,1,
     1,1,1,1,1,1,1,1,1,1,
     1,1,1,-1,-1,-1,-1,-1,1,1,
     1,1,1,-1,5,1,-1,1,1,1,
     1,10,1,-1,-1,-1,-1,1,1,1,
     1,1,1,1,1,1,1,1,1,1,
     1,1,1,1,1,1,1,1,1,1,
     10,1,1,1,10,1,1,1,1,10,
     1,1,1,1,1,1,1,1,1,1
    };
    std::vector < particle_t > m_particles;
};
