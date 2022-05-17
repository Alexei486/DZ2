#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

class Brouns {
public:
    Brouns();

    void run();

private:
    void draw();

    void chaotic_movement(sf::Vector2i &particle);

    void compute();

    void createGrid(int x, int y, uint8_t color, std::vector<uint8_t> &field, sf::Texture &fieldTexture,
                    sf::Sprite &fieldSprite);

private:
    std::mt19937 mersenne{std::random_device()()};

    // okno
    const int Xw = 700; // razmer po x
    const int Yw = 700; // razmer po y

    sf::Texture G_FieldDisT; // SFML Textures // spasibo habr za idey optimizacii so spraitami a ne popikselno
    sf::Sprite G_FieldDisS; // sprite - ta ze tekstura, proshe menyat
    std::vector<uint8_t> G_FieldDis; // mesto gde hrany dannie o pykselyax

    sf::Texture G_FieldT; // SFML Textures // spasibo habr za idey optimizacii so spraitami a ne popikselno
    sf::Sprite G_FieldS;// sprite - ta ze tekstura, proshe menyat
    std::vector<uint8_t> G_Field; // mesto gde hrany dannie o pykselyax

//	std::string start_window_name = "Broun movement";
    sf::RenderWindow window{sf::VideoMode(Xw, Yw), "Broun movement"};

    // parametry and dannie
    const float scale = 1.; //  bolshie pikseli dlya podscheta teploty
    const float fieldScale = 20.; //

    const int Xm = static_cast<int>(static_cast<float>(Xw) / scale); // melkozernistoe pole po pykselyam dlya tochek
    const int Ym = static_cast<int>(static_cast<float>(Yw) / scale);

    const int Xm_dis = static_cast<int>(static_cast<float>(Xw) / scale / fieldScale); // krypnozernistoe pole
    const int Ym_dis = static_cast<int>(static_cast<float>(Yw) / scale /
                                        fieldScale); // eto otwechayet za plotnost po syti

    std::vector<sf::Vector2i> m_particles;
    std::vector<std::vector<int>> m_field{static_cast<size_t>(Xm), std::vector<int>(Ym, 0)};
    std::vector<std::vector<int>> m_fieldDiscretizations{static_cast<size_t>(Xm_dis), std::vector<int>(Ym_dis, 0)};
};
