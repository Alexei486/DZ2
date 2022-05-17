#include "brouns.h"

Brouns::Brouns() {
    // melkaya setochka
    createGrid(Xm, Ym, 0u, G_Field, G_FieldT, G_FieldS);

    // krypnaya setochka
    createGrid(Xm_dis, Ym_dis, 255u, G_FieldDis, G_FieldDisT, G_FieldDisS);

    window.setVerticalSyncEnabled(true); //wertikalnaya sinxronizaciya dlya ogrranichenya 60 cps i rownosti

    // karta
    std::uniform_int_distribution<> distX(0, Xm - 1);
    std::uniform_int_distribution<> distY(0, Ym - 1);
    const int particlesNum = 200000; // stoka chastichek
    m_particles.reserve(particlesNum);
    std::generate_n(std::back_inserter(m_particles), particlesNum, [this, &distX, &distY]() {
        return sf::Vector2i(distX(mersenne), distY(mersenne));
    });
}

void Brouns::run() {
    // zapysk okna and functions, wse po typoi klaseke
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        compute();
        draw();
    }
}

void
Brouns::createGrid(int x, int y, uint8_t color, std::vector<uint8_t> &field, sf::Texture &fieldTexture,
                   sf::Sprite &fieldSprite) {
    field.resize(x * y * 4);
    std::fill(std::begin(field), std::end(field), color);
    fieldTexture.create(x, y); //  widelenie pamyati na wideokarte po razmery
    fieldSprite.scale(
            {static_cast<float>(Xw) / static_cast<float>(x), static_cast<float>(Yw) / static_cast<float>(y)});
}

void Brouns::draw() {

    // risuem krypnozernistoe pole
    const int upper_value = 250;
    for (int x = 0; x < Xm_dis; x++)
        for (int y = 0; y < Ym_dis; y++) {
            auto pixel = &G_FieldDis[(x + y * Xm_dis) * 4];
            float v = static_cast<float>(m_fieldDiscretizations[x][y]) * 2.0f / static_cast<float>(upper_value);
            v = 2.f - std::max(0.f, std::min(v, 2.f));
            if (v < 1.f) {
                pixel[0] = uint8_t(248.f * (1. - v) + 255.f * v);
                pixel[1] = uint8_t(105.f * (1. - v) + 235.f * v);
                pixel[2] = uint8_t(107.f * (1. - v) + 132.f * v);
            } else {
                v -= 1.f;
                pixel[0] = uint8_t(255.f * (1. - v) + 99.f * v);
                pixel[1] = uint8_t(235.f * (1. - v) + 190.f * v);
                pixel[2] = uint8_t(132.f * (1. - v) + 123.f * v);
            }
        }

    G_FieldDisT.update(&G_FieldDis[0]); // zagryzaem na videokarty
    G_FieldDisS.setTexture(G_FieldDisT); // zagryzaem na videokarty
    window.draw(G_FieldDisS); // risuem sprite(ego mozna ywelichiwat i ymenshat!!! ny i menyat cwet// )
    // na eti pary strok bilo ybito pol dnya chtob yiti ot pikselnoi risowki k optimizacii spritow
//        window.clear(sf::Color(127, 127, 127, 255));

    // melkozernistoe pole
    for (int x = 0; x < Xm; x++)
        for (int y = 0; y < Ym; y++)
            if (m_field[x][y] > 0) {
                G_Field[(x + y * Xm) * 4 + 3] = 255;
            } else {
                G_Field[(x + y * Xm) * 4 + 3] = 0;
            }

    G_FieldT.update(&G_Field[0]); //zagryzaem na videokarty
    G_FieldS.setTexture(G_FieldT); // zagryzaem na videokarty
    window.draw(G_FieldS); //risuem sprite(ego mozna ywelichiwat i ymenshat!!! ny i menyat cwet// )

    window.display();
}

void Brouns::compute() {
    //std::for_each(std::begin(Brouns::m_particles), std::end(Brouns::m_particles), [this](auto& particle) {step(particle); });

    // ybiraem chastici s melkozernistogo polya
    for (const auto &p: m_particles) {
        m_field[p.x][p.y] = 0;
    }

    std::for_each(std::begin(Brouns::m_particles), std::end(Brouns::m_particles),
                  [this](auto &particle) { chaotic_movement(particle); });

    //rasstawlyaem chastici na melkozernistom pole
    for (const auto &p: m_particles) {
        m_field[p.x][p.y]++;
    }

    for (int x = 0; x < Xm_dis; x++)
        for (int y = 0; y < Ym_dis; y++)
            m_fieldDiscretizations[x][y] = 0;

    // rastavlyaem chastici na krypnozernistom pole
    for (const auto &p: m_particles) {
        m_fieldDiscretizations[static_cast<int>(static_cast<float>(p.x) * (1.f / fieldScale))]
        [static_cast<int>(static_cast<float>(p.y) * (1.f / fieldScale))]++;
    }
}

void Brouns::chaotic_movement(sf::Vector2i &p) {
    std::uniform_int_distribution<> dist(0, 4);
    p.x = std::max(0, std::min(p.x + dist(mersenne) - 2, Xm - 1));
    p.y = std::max(0, std::min(p.y + dist(mersenne) - 2, Ym - 1));
}
