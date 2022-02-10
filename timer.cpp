#include <iostream>
#include <iostream>
#include <chrono>

class Timer
{
public:
    using clock_t = std::chrono::steady_clock;
    using time_point_t = clock_t::time_point;


    Timer(): m_begin(clock_t::now()), m(0){}
    void stop()
    {
        m += std::chrono::duration_cast<std::chrono::microseconds>( clock_t::now() - m_begin).count() ;
    }
    void contine()
    {
        m_begin = clock_t::now();
    }
    ~Timer() noexcept
    {
        std::cout<<m<<std::endl;
        std::cout << std::chrono::duration_cast <std::chrono::microseconds> ( clock_t::now() - m_begin).count() << " microseconds" << std::endl;
    }
private:
    time_point_t m_begin;
    int m;
};


int main()
{
    {
        Timer t;

        auto x = 1.0;
        t.stop();
        for (auto i = 0; i < 1000000000; ++i)
        {
            x += 1.23;
        }
        t.contine();
        for (auto i = 0; i < 1000000000; ++i)
        {
            x += 1.23;
        }
        t.stop();
std::cout << x << std::endl;
    }
    system("pause");
    return EXIT_SUCCESS;
}
