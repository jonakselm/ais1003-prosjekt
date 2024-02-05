#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "android-specifics.hpp"
#include "include/Board/BoardController.hpp"

int main(int argc, char* argv[])
{
    sf::VideoMode screen(sf::VideoMode::getDesktopMode());

    sf::RenderWindow window(screen, "");
    window.setFramerateLimit(30);

    sf::Texture texture;
    if (!texture.loadFromFile("image.png"))
        return EXIT_FAILURE;

    sf::Sprite image(texture);
    image.setPosition(sf::Vector2f(screen.size) / 2.f);
    image.setOrigin(sf::Vector2f(texture.getSize()) / 2.f);

    sf::Font font;
    if (!font.loadFromFile("tuffy.ttf"))
        return EXIT_FAILURE;

    sf::Text text(font, "Tap anywhere to move the logo.", 64);
    text.setFillColor(sf::Color::Black);
    text.setPosition({10, 10});

    sf::View view = window.getDefaultView();

    sf::Color background = sf::Color::Black;

    // We shouldn't try drawing to the screen while in background
    // so we'll have to track that. You can do minor background
    // work, but keep battery life in mind.
    bool active = true;

    BoardController bc(sf::Vector2i(screen.size.x, screen.size.y));
    sf::Clock clock;

    while (window.isOpen())
    {
        for (sf::Event event; active ? window.pollEvent(event) : window.waitEvent(event);)
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Key::Escape)
                        window.close();
                    break;
                case sf::Event::Resized:
                    view.setSize(sf::Vector2f(event.size.width, event.size.height));
                    view.setCenter(sf::Vector2f(event.size.width, event.size.height) / 2.f);
                    window.setView(view);
                    break;
                case sf::Event::LostFocus:
                    background = sf::Color::Black;
                    break;
                case sf::Event::GainedFocus:
                    background = sf::Color::White;
                    break;

                // On Android MouseLeft/MouseEntered are (for now) triggered,
                // whenever the app loses or gains focus.
                case sf::Event::MouseLeft:
                    active = false;
                    break;
                case sf::Event::MouseEntered:
                    active = true;
                    break;
                case sf::Event::TouchBegan:
                    if (event.touch.finger == 0)
                    {
                        image.setPosition({static_cast<float>(event.touch.x), static_cast<float>(event.touch.y)});
#if defined(USE_JNI)
                        vibrate(sf::milliseconds(10));
#endif
                    }
                    break;
                default:
                    break;
            }
        }
        if (active)
            bc.update(clock.restart().asSeconds());

        if (active)
        {
            window.clear(sf::Color::Black);
            bc.draw(window);
            window.display();
        }
        else
        {
            sf::sleep(sf::milliseconds(100));
        }
    }
}
