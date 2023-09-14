#include "graphics.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(), "Ray-Casting", sf::Style::Fullscreen);
    window.setPosition(sf::Vector2i(0, 0));

    Vector camera = Vector(960, 500, 0);

    Light* lights = new Light[1];
    Vector lightPos = Vector(960, 500, 0);
    Vector lightCol = Vector(255, 255, 255);
    lights[0] = Light(lightPos, lightCol);

    Sphere sphere  = Sphere(Vector(960, 500, 300), 400, Vector(255, 0, 0));

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

        sphere.visualize(window, camera, lights);
        window.display();
    }
    
    delete[] lights;

    return 0;
}