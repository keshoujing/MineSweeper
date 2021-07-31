#include <SFML/Graphics.hpp>
#include "displayManager.h"

int main()
{
    sf::Mouse mouse;

    displayManager::gameBefore();

    sf::RenderWindow window(sf::VideoMode(toolClass::getWidth(), toolClass::getHeight()), "Minesweeper");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.mouseButton.button == mouse.Left && event.type == event.MouseButtonPressed){
                MouseController::leftClicked(window, mouse);
                //MouseController::setPosition(window, mouse);

            } else if (event.mouseButton.button == mouse.Right && event.type == event.MouseButtonPressed){
                MouseController::rightClicked(window, mouse);
                //MouseController::setPosition(window, mouse);
            }
        }


        window.clear(sf::Color::White);

        displayManager::gameStart(window);

        displayManager::gameProcessing();


        window.display();
    }

    toolClass::clearTexture();

    return 0;
}