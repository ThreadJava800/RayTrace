#include "graphics.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Ray-Casting");
    window.setPosition(sf::Vector2i(0, 0));

    Vector camera = Vector(0, 0, 0);

    Light* lights = new Light[2];
    Vector lightPos = Vector(100, 0, 0);
    Vector lightCol = Vector(255, 255, 255);
    lights[0] = Light(lightPos, lightCol);

    Vector lightPos2 = Vector(-50, 0, -50);
    Vector lightCol2 = Vector(0, 0, 255);
    lights[1] = Light(lightPos2, lightCol2);

    Sphere sphere  = Sphere(Vector(0, 150, 0), 50, Vector(255, 0, 0));

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

        lights[1].setPosition(lights[1].getPosition().rotated(50));

        sphere.visualize(window, camera, lights, 2);
        window.display();
    }
    
    delete[] lights;

    return 0;
}