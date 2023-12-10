#include "BoardController.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML Tetris");

	BoardController bc;
	sf::Clock clock;
	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		bc.update(clock.restart().asSeconds());

        window.clear();
		bc.draw(window);
        window.display();
    }
	return 0;

}
