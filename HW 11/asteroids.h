#pragma once
#include <SFML/Graphics.hpp>
#include<random>
#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>

namespace asteroids
{
    enum class Parameter {
        player,
        asteroid,
        bullet,
        explosion
    };
    class Animation {
    public:
        Animation() = default;
        explicit Animation(sf::Texture &t, int x, int y, int w, int h, int count,
                           float speed) noexcept: m_frame(0), m_speed(speed) {
            for (auto i = 0U; i < count; i++) {
                m_frames.push_back(sf::IntRect(x + i * w, y, w, h));
            }
            m_sprite.setTexture(t);
            m_sprite.setOrigin(w / 2, h / 2);
            m_sprite.setTextureRect(m_frames[0]);
        }

        void update()
        {
            m_frame += m_speed;
            int n = m_frames.size();
            if (m_frame >= n) {m_frame -= n;}
            if (n>0) m_sprite.setTextureRect( m_frames[static_cast <int> (m_frame)]);
        }

        bool isEnd()
        {
            return m_frame+m_speed>=m_frames.size();
        }
    public:
        sf::Sprite m_sprite;
    private:
        float m_frame, m_speed;
        std::vector < sf::IntRect > m_frames;
    };
    class Entity
    {
    public:
        Entity(): m_life(true) {}

        explicit Entity(Animation &a, float x, float y, float angle = 0.0, float R = 1.0)
        noexcept : m_anim(a), m_x(x), m_y(y), m_angle(angle), m_R(R), m_life(true) {}

        explicit Entity(Animation &a, float x, float y, Parameter name, float angle = 0.0, float R = 1.0)
        noexcept : m_anim(a), m_x(x), m_y(y), m_angle(angle), m_R(R), m_name(name), m_life(true) {}

        explicit Entity(Animation &a, float x, float y, int dx, int dy, Parameter name, float angle = 0.0,
                        float R = 1.0) noexcept : m_anim(a), m_x(x), m_y(y), m_angle(angle), m_R(R), m_dx(dx),m_dy(dy), m_name(name), m_life(true) {}
         void set_place(float x, float y)
         {
             m_x = x;
             m_y = y;
         }
        void set_angle(float angle)
        {
            m_angle = angle;
        }

        virtual void update() = 0;

        void draw(sf::RenderWindow &app) noexcept
        {
            m_anim.m_sprite.setPosition(m_x,m_y);
            m_anim.m_sprite.setRotation(m_angle+90);
            app.draw(m_anim.m_sprite);

            sf::CircleShape circle(m_R);
            circle.setPosition(m_x,m_y);
            circle.setOrigin(m_R,m_R);
        }

        virtual ~Entity() = default;
    public:
        float m_x, m_y, m_dx, m_dy, m_R, m_angle;
        bool m_life;
        Parameter m_name;
        Animation m_anim;
    protected:
        static inline const int W = 1200;
        static inline const int H = 800;
    };
    class Asteroid : public Entity
    {
    public:
        Asteroid(Animation &a, float x, float y, float angle = 0.0, float R = 1.0)
                : m_trash_speed((-1) * asteroid_max_speed, asteroid_max_speed),
                  m_time((std::chrono::system_clock::now().time_since_epoch().count())),
                   Entity(a, x, y, Parameter::asteroid, angle, R)
        {
            m_dx = m_trash_speed(m_time);//peredavat pri sozdanii asteroidov, potomu chto nado vikinut random otsuda
            m_dy = m_trash_speed(m_time);
        }
        void update() noexcept override
        {
            m_x += m_dx;
            m_y += m_dy;

            if (m_x > W) { m_x = 0; }
            if (m_x < 0) { m_x = W; }
            if (m_y > H) { m_y = 0; }
            if (m_y < 0) { m_y = H; }
        }
    private:
        const float asteroid_max_speed = 4.0;
        std::default_random_engine m_time;
        std::uniform_real_distribution <> m_trash_speed;
    };

    class Bullet: public Entity
    {
    public:
        Bullet(Animation &a, float x, float y, float angle = 0.0, float R = 1.0)
        noexcept : Entity(a, x, y, Parameter::bullet, angle, R),m_rand_angle((- 1.0) * d_angle, d_angle),
                   m_time((static_cast <unsigned int> (std::chrono::system_clock::now().time_since_epoch().count())))
        {}
        void  update() noexcept override
        {
            m_dx = std::cos(m_angle * 0.017) * speed;
            m_dy = std::sin(m_angle * 0.017) * speed;
            m_angle += m_rand_angle(m_time);
            //std::mt19937 g2(rd());//vikinut nafig, peredatvat pri sozdanii
            //m_angle += bull_angle(m_time);
            m_x += m_dx;
            m_y += m_dy;

            if (m_x > W || m_x < 0 || m_y > H || m_y < 0)
            {
                m_life = false;
            }
        }
    private:
        const float speed = 6.0;
        const float d_angle = 3.0;
        std::default_random_engine m_time;
        std::uniform_real_distribution <> m_rand_angle;
    };
    class Player : public Entity
    {
    public:
        Player(Animation &a, float x, float y, float angle = 0.0, float R = 1.0): Entity(a, x, y, Parameter::player, angle, R) {}

/*
        //life
        Player()
        {
            life=3;
            health = 100;
            score = 0;
        }
        */
        void update() noexcept override
        {
            if (thrust)
            {
                m_dx += std::cos(m_angle * 0.017) * acceleration;
                m_dy += std::sin(m_angle * 0.017) * acceleration;
            }
            else
            {
                m_dx *= friction;
                m_dy *= friction;
            }
            auto speed = std::sqrt(m_dx * m_dx + m_dy * m_dy);
            if (speed > maxSpeed)
            {
                m_dx *= maxSpeed / speed;
                m_dy *= maxSpeed / speed;
            }
            m_x += m_dx;
            m_y += m_dy;
            if (m_x > W) { m_x = 0; }
            if (m_x < 0) { m_x = W; }
            if (m_y > H) { m_y = 0; }
            if (m_y < 0) { m_y = H; }
        }
    public:
        bool thrust;
        int health;
        int score;
        int life;
    private:
        const float maxSpeed = 150.0;
        const float acceleration = 0.2;
        const float friction = 0.99;
    };
    class Explosion : public Entity
    {
    public:
        Explosion(Animation& anim, float x, float y, float angle = 0.0, float R = 1.0)
                : Entity(anim, x, y, Parameter::explosion, angle, R) {}

        void update()
        {
            m_x += m_dx;
            m_y += m_dy;
        }
    };
    inline bool isCollide(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
    {
        return (b->m_x - a->m_x) * (b->m_x - a->m_x) +
               (b->m_y - a->m_y) * (b->m_y - a->m_y) <
               (a->m_R + b->m_R) * (a->m_R + b->m_R);
    }
    class Game
    {
    public:
        explicit Game(int width, int height) : m_width(width), m_height(height),
                                               app(sf::VideoMode(m_width, m_height), "Asteroids!"),
                                               m_time((static_cast <unsigned int> (std::chrono::system_clock::now().time_since_epoch().count()))),
                                               m_ast_w(0, width), m_ast_h(0, height), m_ast_angle(0.0, 360.0), m_ast_freq(0, m_frequency)
        {};
        ~Game() noexcept = default;
        void create_asteroids(Animation sRock)
        {
            for (auto i = 0U; i < Sum_Asteroids ; i++)
            {
                std::shared_ptr<Asteroid> a = std::make_shared <Asteroid>
                        (Asteroid(sRock, m_ast_w(m_time), m_ast_h(m_time), m_ast_angle(m_time), asteroid_size));
                entities.push_back(a);
            }
        }
        std::shared_ptr<Player> create_player(Animation sPlayer)
        {
            std::shared_ptr<Player> p = std::make_shared <Player>
                    (Player(sPlayer, m_width / 2, m_height / 2, 0, player_size));
            entities.push_back(p);
            return p;
        }
        void check_pressed_keys(sf::Event event, Animation sBullet, std::shared_ptr<Player> p)
        {
            if (event.type == sf::Event::Closed)
            {
                app.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    std::shared_ptr<Bullet> b = std::make_shared <Bullet>
                            (Bullet(sBullet, p->m_x, p->m_y, p->m_angle, bullet_size));
                    entities.push_back(b);
                }
            }
        }
        void rotate_spaceship(std::shared_ptr<Player> p)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { p->m_angle += 3; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { p->m_angle -= 3; }
        }
        void check_collisions(std::shared_ptr<Player> p,
                              Animation sExplosion, Animation sRock_small, Animation sExplosion_ship) {
            for (auto a: entities) {
                for (auto b: entities) {
                    if (isCollide(a, b)) {
                        if (a->m_name == Parameter::asteroid && b->m_name == Parameter::bullet) {
                            a->m_life = false;
                            b->m_life = false;

                            points++;

                            std::shared_ptr<Explosion> e = std::make_shared<Explosion>
                                    (Explosion(sExplosion, a->m_x, a->m_y));
                            entities.push_back(e);

                            for (auto i = 0U; i < Sum_Rock; i++) {
                                if (a->m_R == mini_asteroid_size) {
                                    continue;
                                }
                                std::shared_ptr<Asteroid> e = std::make_shared<Asteroid>
                                        (Asteroid(sRock_small, a->m_x, a->m_y, m_ast_angle(m_time), mini_asteroid_size));

                                entities.push_back(e);
                            }
                        }

                        if (a->m_name == Parameter::player && b->m_name == Parameter::asteroid) {
                            b->m_life = false;
                            if (health>0)
                            {
                                health-=50;
                            }
                            else
                            {
                                lives--;
                                health=100;
                                p->set_place(m_width / 2, m_height / 2);
                            }

                            std::shared_ptr<Explosion> e = std::make_shared<Explosion>
                                    (Explosion(sExplosion_ship, a->m_x, a->m_y));
                            entities.push_back(e);
                            p->m_dx = 0;
                            p->m_dy = 0;
                        }
                    }
                }
            }
        }
        void kill_explosions()
        {
            for (auto e : entities)
            {
                if (e->m_name == Parameter::explosion)
                {
                    if (e->m_anim.isEnd())
                    {
                        e->m_life = 0;
                    }
                }
            }
        }
        void create_new_asteroids(Animation sRock)
        {
            if (m_ast_freq(m_time) == 1)
            {
                std::shared_ptr<Asteroid> a = std::make_shared <Asteroid>
                        (Asteroid(sRock, 0, m_ast_h(m_time), m_ast_angle(m_time), asteroid_size));
                entities.push_back(a);
            }
        }
        void paint(sf::Sprite background)
        {
            app.draw(background);
            for (auto i: entities) {
                i->draw(app);
            }
            text.setString("Lives: " + std::to_string(lives)+ "\nHealth: "+ std::to_string(health) + "\nScore: " + std::to_string(points));
            app.draw(text);
            app.display();
        }
        void run() {
            sf::Font font;//nice
            font.loadFromFile("/Users/alekseimorozov/CLionProjects/untitled21/Chopsic.ttf");//nice

            text.setPosition(0, 0);
            text.setFont(font);
            text.setCharacterSize(24);

            app.setFramerateLimit(60);

            sf::Texture t1, t2, t3, t4, t5, t6, t7;
            t1.loadFromFile("/Users/alekseimorozov/CLionProjects/untitled21/asteroids/images/spaceship.png");
            t2.loadFromFile("/Users/alekseimorozov/CLionProjects/untitled21/asteroids/images/background.jpg");
            t3.loadFromFile("/Users/alekseimorozov/CLionProjects/untitled21/asteroids/images/explosions/type_C.png");
            t4.loadFromFile("/Users/alekseimorozov/CLionProjects/untitled21/asteroids/images/rock.png");
            t5.loadFromFile("/Users/alekseimorozov/CLionProjects/untitled21/asteroids/images/fire_blue.png");
            t6.loadFromFile("/Users/alekseimorozov/CLionProjects/untitled21/asteroids/images/rock_small.png");
            t7.loadFromFile("/Users/alekseimorozov/CLionProjects/untitled21/asteroids/images/explosions/type_B.png");

            t1.setSmooth(true);
            t2.setSmooth(true);

            sf::Sprite background(t2);

            Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5);
            Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
            Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);
            Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
            Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
            Animation sPlayer_go(t1, 40, 40, 40, 40, 1, 0);
            Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);

            create_asteroids(sRock);

            std::shared_ptr<Player> p = create_player(sPlayer);

            while (app.isOpen() && lives > 0)
            {
                sf::Event event;

                while (app.pollEvent(event))
                {
                    check_pressed_keys(event, sBullet, p);
                }

                rotate_spaceship(p);

                p->thrust = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

                check_collisions(p, sExplosion, sRock_small, sExplosion_ship);

                p->m_anim = (p->thrust) ? sPlayer_go : sPlayer;

                kill_explosions();

                create_new_asteroids(sRock);

                std::for_each(std::begin(entities), std::end(entities), [](auto e) {
                    e->update();
                    e->m_anim.update();
                });
                std::erase_if(entities, [](auto e) { return e->m_life == false; });

                paint(background);
            }
            std::cout << "Your result: " << points << " points" << std::endl;
        }
    private:
        const int m_width, m_height;
        const int m_frequency = 150;
        const int Sum_Rock = 2;
        const int Sum_Asteroids  = 15;
        const float asteroid_size = 25.0;
        const float player_size = 20.0;
        const float bullet_size = 10.0;
        const float mini_asteroid_size = 15.0;

        int lives = 3;
        int health = 100;
        int points = 0;

        std::list < std::shared_ptr <Entity> > entities;

        sf::Text text;
        sf::RenderWindow app;
        std::default_random_engine m_time;
        std::uniform_real_distribution <> m_ast_w;
        std::uniform_real_distribution <> m_ast_h;
        std::uniform_real_distribution <> m_ast_angle;
        std::uniform_int_distribution <> m_ast_freq;


    };
}
