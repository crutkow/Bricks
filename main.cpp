#include <SFML/Graphics.hpp>
#include <memory>

#include "game.hpp"
#include "object_pool.hpp"
#include "controller.hpp"

using namespace std;

int main()
{
    Game game;

    game.start();

    Controller::instance().fillBrickPool(100);

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}