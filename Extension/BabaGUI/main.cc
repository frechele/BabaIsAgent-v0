// Copyright(c) 2019 Junyeong Park

#include <SFML/Graphics.hpp>

#include <spdlog/spdlog.h>

int main(int argc, char** argv)
{
    spdlog::info("BabaIsYou GUI");

    sf::RenderWindow window(sf::VideoMode(680, 480), "Baba Is You",
                            sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                spdlog::info("Window closed");
                window.close();
            }
        }

        window.clear();

        window.display();
    }
}
