#ifndef _GRAPH_h_
#define _GRAPH_h_

#include <SFML/Graphics.hpp>
#include "vector.h"

const sf::Color DEFAULT_COLOR  = sf::Color::Black;
const int       PHONG_CONSTANT = 32;

class Light {
private:
    Vector position;
    Vector color;

public:
    explicit Light();
    explicit Light(Vector& position, Vector& color);

    Vector getPosition() const;
    Vector getColor() const;

    ~Light() {};
};

class Sphere {
private:
    const Vector    center;
    const double    radius;
    const Vector    color;

public:
    explicit Sphere();
    explicit Sphere(const Vector& center, const double radius, const Vector& color);

    ~Sphere();

    void visualize(sf::RenderWindow& window, const Vector& camera, Light* lights);

    Vector intersect(const Vector& camera, const Vector& vector);

    Vector ambientCoeff  (const Light& light);
    Vector diffusiveCoeff(const Vector& camera, const Vector& pointVector, const Light& light);
    Vector phongCoeff    (const Vector& camera, const Vector& pointVector, const Light& light);
};

#define ON_ERROR(expr, errStr, retVal) {                 \
    if (expr) {                                           \
        fprintf(stderr, "FATAL ERROR: %s\n", errStr);      \
        return retVal;                                      \
    }                                                        \
}

#endif