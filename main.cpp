#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "menu.hpp"
#include "game.hpp"

using namespace std;

enum class Screens {
    Menu,
    Game,
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(BOARD_SIZE_X, BOARD_SIZE_Y), "Bricks");
    window.setFramerateLimit(FRAME_RATE);

    sf::Clock clock;

    Screens activeScreen = Screens::Menu;

    vector<std::unique_ptr<Screen>> screens;
    screens.push_back(std::unique_ptr<Screen>(new Menu(window)));
    screens.push_back(std::unique_ptr<Screen>(new Game(window)));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();

        switch (screens[(int)activeScreen]->getState())
        {
        case Screen::State::Starting:
            screens[(int)activeScreen]->start();
            break;
        case Screen::State::Running:
            screens[(int)activeScreen]->update(elapsed);

            window.clear();
            screens[(int)activeScreen]->draw();
            window.display();
            break;
        case Screen::State::Ending:
            screens[(int)activeScreen]->end();
            activeScreen = activeScreen == Screens::Menu ? Screens::Game : Screens::Menu;
            break;
        }
    }

    return 0;
}
