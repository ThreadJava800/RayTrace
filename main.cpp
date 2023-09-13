#include "graphics.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(), "Ray-Casting", sf::Style::Fullscreen);
    window.setPosition(sf::Vector2i(0, 0));

    Vector* lights = new Vector[1];
    lights[0] = Vector(1, 1, 1);
    Sphere sphere  = Sphere(Vector(960, 540, 500), 250, Vector(1, 0, 0));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // close if escape clicked
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                break;
            }
        }

        sphere.visualize(window, lights);
        window.display();
    }
    
    delete[] lights;

    return 0;
}