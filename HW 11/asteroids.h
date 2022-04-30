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
        sf::Sprite m_sprite;

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
    private:
        float m_frame, m_speed;
        std::vector < sf::IntRect > m_frames;
    };
    class Entity
    {
    public:
        Entity() noexcept : m_life(true) {}

        explicit Entity(Animation &a, float x, float y, float angle = 0.0, float R = 1.0)
        noexcept : m_anim(a), m_x(x), m_y(y), m_angle(angle), m_R(R), m_life(true) {}

        explicit Entity(Animation &a, float x, float y, Parameter name, float angle = 0.0, float R = 1.0)
        noexcept : m_anim(a), m_x(x), m_y(y), m_angle(angle), m_R(R), m_name(name), m_life(true) {}

        explicit Entity(Animation &a, float x, float y, int dx, int dy, Parameter name, float angle = 0.0,
                        float R = 1.0) noexcept : m_anim(a), m_x(x), m_y(y), m_angle(angle), m_R(R), m_dx(dx),m_dy(dy), m_name(name), m_life(true) {}
        void setSettings(Animation &a,int x,int y,float angle=0,int radius=1) noexcept
        {
            m_anim = a;
            m_x=x;
            m_y=y;
            m_angle = angle;
            m_R = radius;
        }

        virtual void update(){};

        void draw(sf::RenderWindow &app) noexcept
        {
            m_anim.m_sprite.setPosition(m_x,m_y);
            m_anim.m_sprite.setRotation(m_angle+90);
            app.draw(m_anim.m_sprite);

            sf::CircleShape circle(m_R);
            circle.setPosition(m_x,m_y);
            circle.setOrigin(m_R,m_R);
            //app.draw(circle);
        }

        virtual ~Entity() = default;
    public:
        float m_x, m_y, m_dx, m_dy, m_R, m_angle;
        bool m_life;
        Parameter m_name;
        Animation m_anim;
    protected:
        const int W = 1200;
        const int H = 800;
    };
    class Asteroid : public Entity
    {
    public:
        Asteroid(Animation &a, float x, float y, float angle = 0.0, float R = 1.0)
        noexcept : m_trash_speed(-4,4),
                Entity(a, x, y, Parameter::asteroid, angle, R)
        {
            std::random_device rd;
            std::mt19937 g(rd());
            m_dx = m_trash_speed(g);
            m_dy = m_trash_speed(g);
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
        std::uniform_int_distribution <> m_trash_speed;
    };

    class Bullet: public Entity
            {
    public:
        Bullet(Animation &a, float x, float y, float angle = 0.0, float R = 1.0)
        noexcept : Entity(a, x, y, Parameter::bullet, angle, R),
        bull_angle(-4,4)
        {}
        void  update() noexcept override
        {
            m_dx = std::cos(m_angle * 0.017) * 6;
            m_dy = std::sin(m_angle * 0.017) * 6;
            std::random_device rd;
            std::mt19937 g2(rd());
            m_angle += bull_angle(g2);
            m_x += m_dx;
            m_y += m_dy;

            if (m_x > W || m_x < 0 || m_y > H || m_y < 0)
            {
                m_life = false;
            }
        }
    private:
        std::uniform_int_distribution <> bull_angle;
    };
    class Player : public Entity
    {
    public:
        Player(Animation &a, float x, float y, float angle = 0.0, float R = 1.0)
        noexcept : Entity(a, x, y, Parameter::player, angle, R) {}


        //life
        Player()
        {
            life=3;
            health = 100;
            score = 0;
        }
    void update() noexcept override
    {
    if (thrust)
    {
        m_dx += std::cos(m_angle * 0.017) * 0.2;
        m_dy += std::sin(m_angle * 0.017) * 0.2;
    }
    else
    {
        m_dx *= 0.99;
        m_dy *= 0.99;
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
};
    inline bool isCollide(Entity* a, Entity* b)
    {
        return (b->m_x - a->m_x) * (b->m_x - a->m_x) +
               (b->m_y - a->m_y) * (b->m_y - a->m_y) <
               (a->m_R + b->m_R) * (a->m_R + b->m_R);
    }
    class Game
            {
    public:
        explicit Game(int width, int height) noexcept : m_width(width), m_height(height), m_frequency(150),
        m_rand((static_cast <unsigned int> (std::chrono::system_clock::now().time_since_epoch().count()))),
        m_w(0, width), m_h(0, height), m_angle(0, 360), m_freq(0, m_frequency)
        {};
        void run() {
            sf::RenderWindow app(sf::VideoMode(m_width, m_height), "Asteroids!");
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

            std::list<Entity *> entities;

            for (auto i = 0U; i < 15; i++) {
                Asteroid *a = new Asteroid(sRock, m_w(m_rand), m_h(m_rand), m_angle(m_rand), 25);
                entities.push_back(a);
            }

            Player *p = new Player(sPlayer, 200, 200, 0, 20);
            entities.push_back(p);

            //life

            sf::Font font;//øðèôò
            font.loadFromFile("/Users/alekseimorozov/CLionProjects/untitled21/Chopsic.ttf");
            sf::Text text("", font, 18);
            sf::Text death("", font, 72);

            while (app.isOpen()) {
                sf::Event event;

                while (app.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        app.close();
                    }
                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Space) {
                            Bullet *b = new Bullet(sBullet, p->m_x, p->m_y, p->m_angle, 10);
                            entities.push_back(b);
                        }
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { p->m_angle += 3; }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { p->m_angle -= 3; }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { p->thrust = true; }
                else { p->thrust = false; }
                //life
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && p->life == 0) {
                    p->score = 0;
                    p->life = 3;
                    p->health = 100;
                    p->setSettings(sPlayer, 200, 200, 0, 20);
                    entities.push_back(p);
                }

                for (auto a: entities) {
                    for (auto b: entities) {
                        if (a->m_name == Parameter::asteroid && b->m_name == Parameter::bullet) {
                            if (isCollide(a, b)) {
                                a->m_life = false;
                                b->m_life = false;

                                //life
                                if (a->m_R== 25)
                                    p->score++;
                                else
                                    p->score += 10;

                                Entity *e = new Entity(sExplosion, a->m_x, a->m_y, Parameter::explosion);
                                entities.push_back(e);

                                for (auto i = 0U; i < 2; i++) {
                                    if (a->m_R == 15) {
                                        continue;
                                    }
                                    Entity *e = new Asteroid(sRock_small, a->m_x, a->m_y, m_angle(m_rand), 15);
                                    entities.push_back(e);
                                }
                            }
                        }

                        if (a->m_name == Parameter::player && b->m_name == Parameter::asteroid) {
                            if (isCollide(a, b)) {
                                b->m_life = false;

                                Entity *e = new Entity(sExplosion_ship, a->m_x, a->m_y, Parameter::explosion);
                                entities.push_back(e);

                                //life
                                if (p->health > b->m_R)
                                    p->health -= b->m_R;
                                else {
                                    if (p->life > 1) {
                                        p->life -= 1;
                                        p->health = 100;

                                        p->setSettings(sPlayer, m_width / 2, m_height / 2, 0, 20);
                                        p->m_dx = 0;
                                        p->m_dy = 0;
                                    } else {
                                        p->life = 0;
                                        p->health = 0;
                                        p->thrust = false;
                                    }
                                }
                                //p->m_dx = 0;
                                //p->m_dy = 0;
                            }
                        }
                    }
                }
                if (p->thrust) {
                    p->m_anim = sPlayer_go;
                } else {
                    p->m_anim = sPlayer;
                }
                for (auto e: entities) {
                    if (e->m_name == Parameter::explosion) {
                        if (e->m_anim.isEnd()) {
                            e->m_life = 0;
                        }
                    }
                }
                if (m_freq(m_rand) == 0) {
                    Asteroid *a = new Asteroid(sRock, 0, m_h(m_rand), m_angle(m_rand), 25);
                    entities.push_back(a);
                }
                std::for_each(std::begin(entities), std::end(entities), [](auto e) {
                    e->update();
                    e->m_anim.update();
                });
                std::erase_if(entities, [](auto e) { return e->m_life == false; });


                app.draw(background);
                for (auto i: entities) {
                    i->draw(app);
                }
                text.setString("Score:");
                text.setPosition(15, 10);
                app.draw(text);

                text.setString("Lives: ");
                text.setPosition(15, 35);
                app.draw(text);

                text.setString("Health: ");
                text.setPosition(15, 60);
                app.draw(text);

                text.setString(std::to_string(p->score));
                text.setPosition(105, 10);
                app.draw(text);

                text.setString(std::to_string(p->life));
                text.setPosition(96, 35);
                app.draw(text);

                text.setString(std::to_string(p->health) + "%");
                text.setPosition(116, 60);
                app.draw(text);

                if (p->life == 0)
                {
                    death.setString("Dorabotaite");
                    death.setPosition(m_width / 2 - 300, m_height / 2);
                    app.draw(death);

                    text.setString("Press \"F\" to pay respect");
                    text.setPosition(m_width / 2 - 150, m_height / 2 + 100);
                    app.draw(text);
                }
                app.display();
            }
        }
    private:
        const int m_width, m_height, m_frequency;
        std::default_random_engine m_rand;
        std::uniform_int_distribution <> m_angle;
        std::uniform_int_distribution <> m_freq;
        std::uniform_int_distribution <> m_w;
        std::uniform_int_distribution <> m_h;

    };
}
