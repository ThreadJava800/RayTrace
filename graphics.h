#ifndef _GRAPH_h_
#define _GRAPH_h_

#include <SFML/Graphics.hpp>
#include "vector.h"

const sf::Color DEFAULT_COLOR = sf::Color::Black;

class Sphere {
private:
    const Vector    center;
    const double    radius;
    const Vector    color;

public:
    explicit Sphere();
    explicit Sphere(const Vector& center, const double radius, const Vector& color);

    ~Sphere();

    void visualize(sf::RenderWindow& window, Vector* lights);

    Vector ambientCoeff  (const Vector& light);
    double diffusiveCoeff(const Vector& light);
    double phongCoeff    (const Vector& light);
};

#define ON_ERROR(expr, errStr, retVal) {                 \
    if (expr) {                                           \
        fprintf(stderr, "FATAL ERROR: %s\n", errStr);      \
        return retVal;                                      \
    }                                                        \
}

#endif