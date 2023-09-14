#include "graphics.h"

Light::Light() :
    position(Vector()),
    color(Vector())   {}

Light::Light(Vector& position, Vector& color) :
    position(position),
    color(color)      {}

Vector Light::getPosition() const {
    return this->position;
}

Vector Light::getColor() const {
    return this->color;
}

Sphere::Sphere() :
    center(Vector()),
    radius(0),
    color(Vector())   {}

Sphere::Sphere(const Vector& center, const double radius, const Vector& color) :
    center(center),
    radius(radius),
    color (color)     {}

Sphere::~Sphere() {}

void Sphere::visualize(sf::RenderWindow& window, const Vector& camera, Light* lights) {
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
                Vector curPoint    = Vector(i, j, sqrt(r2 - (i - centerX) * (i - centerX) - (j - centerY) * (j - centerY)));
                // Vector vectorColor = ambientCoeff(lights[0]);
                Vector vectorColor = phongCoeff(camera, curPoint, lights[0]) * 0.5 + diffusiveCoeff(camera, curPoint, lights[0]) * 0.5;
    
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

Vector Sphere::intersect(const Vector& camera, const Vector& vector) {
    Vector dir = !(vector - camera);
    double b = 2 * ((camera - this->center), dir);
    double c = ((camera - this->center), (camera - this->center)) - this->radius * this->radius;

    double discrim = b * b - 4 * c;
    if(discrim < 0) return Vector();    // black color

    double result = std::min((-b + sqrt(discrim)) / 2, (-b - sqrt(discrim)) / 2);

    return camera + dir * result;
}

Vector Sphere::ambientCoeff(const Vector& camera, const Vector& pointVector, const Light& light) {
    Vector intersectionPoint = intersect(camera, pointVector);

    if (intersectionPoint != Vector())
        return !(light.getColor() * this->color);
    return Vector(0, 0, 0);
}

Vector Sphere::diffusiveCoeff(const Vector& camera, const Vector& pointVector, const Light& light) {
    Vector intersectionPoint = intersect(camera, pointVector);
    Vector pointToLight      = !(intersectionPoint - this->center);
    Vector lightVector       = !(light.getPosition() - intersectionPoint);

    double degree = pointToLight.angle(lightVector);
    if (degree < 0) degree = 0;

    return Vector(degree, degree, degree) * !(this->color);
}

Vector Sphere::phongCoeff(const Vector& camera, const Vector& pointVector, const Light& light) {
    Vector dir                 = !(pointVector - camera);
    Vector intersectionPoint   = intersect(camera, pointVector);

    Vector intersectionToLight = light.getPosition() - intersectionPoint;
    Vector normalVector        = intersectionPoint - this->center;
    Vector cameToIntersection  = intersectionPoint - camera;

    Vector reflected = (intersectionToLight - (normalVector * (!intersectionToLight, !normalVector))) * (-1);

    double coeff = (!(cameToIntersection * (-1)), !reflected);
    if (coeff < 0) coeff = 0;
    coeff = pow(coeff, PHONG_CONSTANT);

    return Vector(coeff, coeff, coeff);
}