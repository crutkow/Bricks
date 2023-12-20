#include <SFML/Graphics.hpp>
#include <memory>

#include "game.hpp"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(BOARD_SIZE_X, BOARD_SIZE_Y), "SFML works!");
    window.setFramerateLimit(60);

    sf::Clock clock;

    Game game(window);

    game.start();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();
        game.update(elapsed);

        window.clear();
        game.draw();
        window.display();
    }

    return 0;
}