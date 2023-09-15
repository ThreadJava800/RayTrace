#include "graphics.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Ray-Casting");
    window.setPosition(sf::Vector2i(0, 0));

                         // x      y
    Vector camera = Vector(0, 0, 0);

    Light* lights = new Light[1];
    Vector lightPos = Vector(50, 0, 0);
    Vector lightCol = Vector(255, 255, 255);
    lights[0] = Light(lightPos, lightCol);

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

        // std::cout << "Start\n";
        sphere.visualize(window, camera, lights);
        window.display();
        // std::cout << "End\n";
    }
    
    delete[] lights;

    return 0;
}