#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "menu.hpp"
#include "game.hpp"

using namespace std;

enum class Screens : uint {
    Menu = 0,
    Game = 1,
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(BOARD_SIZE_X, BOARD_SIZE_Y), "Bricks");
    window.setFramerateLimit(FRAME_RATE);

    sf::Clock clock;
    bool isWaiting = false;

    Screens activeScreen = Screens::Menu;

    vector<std::unique_ptr<Screen>> screens;
    screens.push_back(std::unique_ptr<Screen>(new Menu(window)));
    screens.push_back(std::unique_ptr<Screen>(new Game(window)));

    int currentLevel = 1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (isWaiting) {
            if (clock.getElapsedTime().asSeconds() >= 0.6f) {
                clock.restart();
                isWaiting = false;
            }
            else {
                continue;
            }
        }
        sf::Time elapsed = clock.restart();

        switch (screens[(int)activeScreen]->getState())
        {
        case Screen::States::Starting:
            screens[(int)activeScreen]->start(currentLevel);
            isWaiting = true;
            break;
        case Screen::States::Running:
            screens[(int)activeScreen]->update(elapsed);

            window.clear();
            screens[(int)activeScreen]->draw();
            window.display();
            break;
        case Screen::States::Ending:
            screens[(int)activeScreen]->end();
            switch (activeScreen)
            {
            case Screens::Menu:
                if (screens[(int)activeScreen]->getAction() == Screen::Actions::Quit) window.close();
                else if (screens[(int)activeScreen]->getAction() == Screen::Actions::Play) activeScreen = Screens::Game;
                break;
            case Screens::Game:
                if (screens[(int)activeScreen]->getAction() == Screen::Actions::Loose) activeScreen = Screens::Menu;
                else if (screens[(int)activeScreen]->getAction() == Screen::Actions::Win) {
                    currentLevel++;
                    if (currentLevel > LEVEL_COUNT) {
                        activeScreen = Screens::Menu;
                        currentLevel = 0;
                    }
                }
                break;
            default:
                activeScreen = Screens::Menu;
                break;
            }
        }
    }

    return 0;
}
