#include <algorithm>
#include <array>
#include <thread>
#include <vector>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>


class Brouns {
public:
	Brouns();
	~Brouns() noexcept = default;

	void run();

private:
	struct ivec2 {
		ivec2() {};
		ivec2(int coord) : x(coord), y(coord) {};
		ivec2(int coord_1, int coord_2) : x(coord_1), y(coord_2) {};
		int x = 0, y = 0;
	};

	const ivec2 Direction[4] = {ivec2(0, 1), ivec2(1, 0), ivec2(0, -1), ivec2(-1, 0)};

	struct Particle : ivec2 {
	};

	void draw();
	void chaotic_movement(Particle& particle);
	void compute();

private:
	std::mt19937 mersenne;

	// okno
	const int Xw = 700; // razmer po x
	const int Yw = 700; // razmer po y

	sf::Texture G_FieldDisT; // SFML Textures // spasibo habr za idey optimizacii so spraitami a ne popikselno
	sf::Sprite G_FieldDisS; // sprite - ta ze tekstura, proshe menyat
	std::vector<uint8_t> G_FieldDis; // mesto gde hrany dannie o pykselyax

	sf::Texture G_FieldT; // SFML Textures // spasibo habr za idey optimizacii so spraitami a ne popikselno
	sf::Sprite G_FieldS;// sprite - ta ze tekstura, proshe menyat
	std::vector<uint8_t> G_Field; // mesto gde hrany dannie o pykselyax

	std::string start_window_name = "Broun movement";
	sf::RenderWindow window;

	// parametry and dannie
	const float scale = 2.; //  bolshie pikseli dlya podscheta teploty
	const float scale_of_field = 10.; //

	const int particles_num = 5000; // stoka chastichek
	const int upper_value = 10;

	const int Xm = int(Xw / scale); // melkozernistoe pole po pykselyam dlya tochek
	const int Ym = int(Yw / scale);

	const int Xm_dis = int(Xw / scale / scale_of_field); // krypnozernistoe pole
	const int Ym_dis = int(Yw / scale / scale_of_field); // eto otwechayet za plotnost po syti

	std::vector<Particle> particles;
	std::vector<std::vector<int>> field;
	std::vector<std::vector<int>> field_discretizations;
};
