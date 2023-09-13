#include "graphics.h"

Sphere::Sphere() :
    center(Vector()),
    radius(0),
    color(Vector())   {}

Sphere::Sphere(const Vector& center, const double radius, const Vector& color) :
    center(center),
    radius(radius),
    color (color)     {}

Sphere::~Sphere() {}

void Sphere::visualize(sf::RenderWindow& window, Vector* lights) {
    ON_ERROR(!lights, "Null pointer exception.",);

    int width  = window.getSize().x;
    int height = window.getSize().y;
    double r2  = this->radius * this->radius;

    double centerX = this->center.getX();
    double centerY = this->center.getY();

    sf::Image   pixels;
    sf::Texture pixelTexture;
    sf::Sprite  pixelsSp;

    pixels.create(width, height, DEFAULT_COLOR);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if ((i - centerX) * (i - centerX) + (j - centerY) * (j - centerY) <= r2) {
                // TODO: clean up
                Vector curPoint = !Vector(i, j, sqrt(r2 - (i - centerX) * (i - centerX) - (j - centerY) * (j - centerY)));
                Vector vectorColor   = diffusiveCoeff(curPoint, lights[0]) + ambientCoeff(lights[0]);
                // TODO: make 0 if outside range
                sf::Color pixelColor = sf::Color(vectorColor.getX() * 255, vectorColor.getY() * 255, vectorColor.getZ() * 255);
                // std::cout << "For: " << i << ',' << j << ": " << vectorColor.getX() << ' ' << vectorColor.getY() << ' ' << vectorColor.getZ() << '\n';
                pixels.setPixel(i, j, pixelColor);
            }
        }
    }
    pixelTexture.loadFromImage(pixels);
    pixelsSp.setTexture(pixelTexture);
    window.draw(pixelsSp);
}

Vector Sphere::ambientCoeff(const Vector& light) {
    return light * (this->color);
}

Vector Sphere::diffusiveCoeff(const Vector& pointVector, const Vector& light) {
    Vector pointToLight = light - pointVector;
    double degree = pointVector.angle(pointToLight);

    return Vector(degree, degree, degree);
}