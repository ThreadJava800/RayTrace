#ifndef _GRAPH_h_
#define _GRAPH_h_

#include <SFML/Graphics.hpp>
#include "vector.h"

const sf::Color DEFAULT_COLOR  = sf::Color::Black;
const int       PHONG_CONSTANT =  32;
const int       START_X        = -50;
const int       START_Y        =  50;
const int       START_Z        =  50;
const int       UNIT_X         =  100;
const int       UNIT_Z         = -100;


class Light {
private:
    Vector position;
    Vector color;

public:
    explicit Light();
    explicit Light(Vector& position, Vector& color);

    Vector getPosition();
    void   setPosition(Vector position);
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

    void visualize(sf::RenderWindow& window, const Vector& camera, Light* lights, size_t lightNum);

    Vector intersect(const Vector& camera, const Vector& vector);
    Vector computeColor(const Vector& camera, const Vector& pointVector, Light& light);
};

#define ON_ERROR(expr, errStr, retVal) {                 \
    if (expr) {                                           \
        fprintf(stderr, "FATAL ERROR: %s\n", errStr);      \
        return retVal;                                      \
    }                                                        \
}

#endif