#include "Brouns.h"


Brouns::Brouns() :
	window(sf::VideoMode(Xw, Yw), start_window_name)
{
	// Sozdaem okoshechko


	// melkaya setochka
	{
		// sozdaem massiv razmerom s pikselnoe pole na 4 kanala RGBA
		G_Field.resize(Xm * Ym * 4);
		for (int i = 0; i < G_Field.size(); i++)
			G_Field[i] = 0u; // prozrachnost

		G_FieldT.create(Xm, Ym); //  widelenie pamyati na wideokarte po razmery
		G_FieldS.scale(sf::Vector2f(Xw / float(Xm), Yw / float(Ym)));
	}

	// krypnaya setochka
	{
		//  sozdaem massiv razmerom s pikselnoe pole na 4 kanala RGBA
		G_FieldDis.resize(Xm_dis * Xm_dis * 4);
		for (int i = 0; i < G_FieldDis.size(); i++)
			G_FieldDis[i] = 255; // white

		G_FieldDisT.create(Xm_dis, Ym_dis); //widelenie pamyati na wideokarte po razmery
		G_FieldDisS.scale(sf::Vector2f(Xw / float(Xm_dis), Yw / float(Ym_dis)));
	}

	window.setVerticalSyncEnabled(true); //wertikalnaya sinxronizaciya dlya ogrranichenya 60 cps i rownosti

    //
 // karta
   //
	
	particles.resize(particles_num);
	for (int i = 0; i < particles.size(); i++) {
		auto &p = particles[i];
		p.x = mersenne() % Xm;
		p.y = mersenne() % Ym;
	}

	field.resize(Xm);
	for (int x = 0; x < field.size(); x++)
		field[x].resize(Ym);

	for (int x = 0; x < Xm; x++)
		for (int y = 0; y < Ym; y++)
			field[x][y] = 0;

	field_discretizations.resize(Xm_dis);
	for (int x = 0; x < field_discretizations.size(); x++)
		field_discretizations[x].resize(Ym_dis);
};

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

void Brouns::draw() {

	// risuem krypnozernistoe pole
	if (1)
	{
		for (int x = 0; x < Xm_dis; x++)
			for (int y = 0; y < Ym_dis; y++) {
				auto pixel = &G_FieldDis[(x + y * Xm_dis) * 4];
				float v = field_discretizations[x][y] * 2 / static_cast<float>(upper_value);
				v = 2.f - std::max(0.f, std::min(v, 2.f));
				if (v < 1.f) {
					pixel[0] = uint8_t(248.f * (1. - v) + 255.f * v);
					pixel[1] = uint8_t(105.f * (1. - v) + 235.f * v);
					pixel[2] = uint8_t(107.f * (1. - v) + 132.f * v);
				}
				else {
					v -= 1.f;
					pixel[0] = uint8_t(255.f * (1. - v) + 99.f * v);
					pixel[1] = uint8_t(235.f * (1. - v) + 190.f * v);
					pixel[2] = uint8_t(132.f * (1. - v) + 123.f * v);
				}
			}

		G_FieldDisT.update(&G_FieldDis[0]); // zagryzaem na videokarty
		G_FieldDisS.setTexture(G_FieldDisT); // privyazka k videokarte
		window.draw(G_FieldDisS); // risuem sprite(ego mozna ywelichiwat i ymenshat!!! ny i menyat cwet// )
        // na eti pary strok bilo ybito pol dnya chtob yiti ot pikselnoi risowki k optimizacii spritow
	} else
		window.clear(sf::Color(127, 127, 127, 255));

	// melkozernistoe pole
	if (1)
	{
		for (int x = 0; x < Xm; x++)
			for (int y = 0; y < Ym; y++)
				if (field[x][y] > 0) {
					G_Field[(x + y * Xm) * 4 + 3] = 255;
				}
				else {
					G_Field[(x + y * Xm) * 4 + 3] = 0;
				}

		G_FieldT.update(&G_Field[0]); //zagryzaem na videokarty
		G_FieldS.setTexture(G_FieldT); //  privyazka k videokarte
		window.draw(G_FieldS); //risuem sprite(ego mozna ywelichiwat i ymenshat!!! ny i menyat cwet// )
	}

	window.display();
}

void Brouns::compute() {
	//std::for_each(std::begin(Brouns::m_particles), std::end(Brouns::m_particles), [this](auto& particle) {step(particle); });

	// ybiraem chastici s melkozernistogo polya
	for (int i = 0; i < particles.size(); i++) {
		auto &p = particles[i];
		field[p.x][p.y] = 0;
	}
	
	std::for_each(std::begin(Brouns::particles), std::end(Brouns::particles), [this](auto& particle) { chaotic_movement(particle); });

	//rasstawlyaem chastici na melkozernistom pole
	for (int i = 0; i < particles.size(); i++) {
		auto &p = particles[i];
		field[p.x][p.y]++;
	}

	for (int x = 0; x < Xm_dis; x++)
		for (int y = 0; y < Ym_dis; y++)
			field_discretizations[x][y] = 0;

	// rastavlyaem chastici na krypnozernistom pole
	for (int i = 0; i < particles.size(); i++) {
		auto &p = particles[i];
		field_discretizations[static_cast<int>(p.x * (1.f / scale_of_field))][static_cast<int>(p.y * (1.f / scale_of_field))]++;
	}
}

void Brouns::chaotic_movement(Particle& p) {
	p.x = std::max(0, std::min(p.x + int(mersenne() % 5) - 2, Xm - 1));
	p.y = std::max(0, std::min(p.y + int(mersenne() % 5) - 2, Ym - 1));
}
