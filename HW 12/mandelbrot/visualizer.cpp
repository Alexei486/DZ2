#include "visualizer.hpp"

void Visualizer::initialize() {
    m_image.create(m_calculator.width(), m_calculator.height());

    if (!m_font.loadFromFile("consolas.ttf")) {
        std::cerr << "Font not found\n";
    }

    m_text.setFont(m_font);
    m_text.setCharacterSize(14U);
    m_text.setFillColor(sf::Color::Red);
    m_text.setPosition(10.0f, 10.0f);


    for (auto r = 256/16; r > 1; r--) {
        for (auto g = 256/16; g > 1; g--) {
            for (auto b = 1U; b < 256 / 16 - 1; b++) {
                m_colors.emplace_back(sf::Color(r * 16, g * 16, b * 16));
            }
        }
    }
}

void Visualizer::run()
{
	while (m_window.isOpen()) 
	{
		review();
		update();
		render();
	}
}

void Visualizer::review()
{
    sf::Event event;

    while (m_window.pollEvent(event)) 
	{
        switch (event.type) 
		{
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::KeyPressed:
            m_need_redraw = true;
            handle_key_pressed(event.key.code);
            break;
        default:
            break;
        }
    }
}

void Visualizer::handle_key_pressed(sf::Keyboard::Key code)
{
    const auto offset_x = m_view.width()  / 10.0f;
	const auto offset_y = m_view.height() / 10.0f;

	const auto factor = 2.0f;

    switch (code) 
	{
    case sf::Keyboard::Left:
        m_view.move(sf::Vector2f(-offset_x, 0.0f));
        break;
    case sf::Keyboard::Down:
        m_view.move(sf::Vector2f(0.0f, offset_y));
        break;
    case sf::Keyboard::Right:
        m_view.move(sf::Vector2f(offset_x, 0.0f));
        break;
    case sf::Keyboard::Up:
        m_view.move(sf::Vector2f(0.0f, -offset_y));
        break;
	case sf::Keyboard::A:
        m_view.scale(1.0f / factor);
        break;
    case sf::Keyboard::S:
        m_view.scale(factor);
        break;
    default:
        break;
    }
}

void Visualizer::update()
{    
    if (m_need_redraw) 
	{
		m_calculator.calculate(m_view.center(), m_view.width(), m_view.height());
    }
}

void Visualizer::render()
{
    m_window.clear();

    const auto & field = m_calculator.field();

    if (m_need_redraw)
	{
		for (auto y = 0U; y < m_calculator.height(); ++y)
		{
			for (auto x = 0U; x < m_calculator.width(); ++x)
			{
				const auto iterations = field[y][x];

				if (iterations == 0U || iterations == m_calculator.max_iterations())
				{
					m_image.setPixel(x, y, sf::Color::Black);
				}
				else
				{
					m_image.setPixel(x, y, m_colors[static_cast < std::size_t > (
						(1.0f * iterations / m_calculator.max_iterations()) * m_colors.size())]); // ?
				}
			}
		}

        m_need_redraw = false;
    }

    m_texture.loadFromImage(m_image);
    m_sprite.setTexture(m_texture, true);

    std::stringstream ss;

    ss <<
		"Resolution: " << m_calculator.width() << "x" << m_calculator.height() << "\n" <<
		"Iterations: " << m_calculator.max_iterations() << "\n" <<
		std::fixed << std::setprecision(9) << "\n" <<
		"Center: Re[" << m_view.center().x << "]; Im[" << m_view.center().y << "]\n" <<
		"Window: Re[" << m_view.width()    << "]; Im[" << m_view.height()   << "]";

    m_text.setString(ss.str());

    m_window.draw(m_sprite);
    m_window.draw(m_text);

    m_window.display();
}