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

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double x = -50 + i * (100 / double(height));
            double y =  50 + j * (-200 / double(width));

            // if ((x - centerX) * (x - centerX) + (i - centerY) * (i - centerY) <= r2) { 
                // std::cout << width << ' ' << height << '\n';

                Vector    pointOnScreen = Vector(x, 50, y);
                Vector    vectorColor   = diffusiveCoeff(camera, pointOnScreen, lights[0]);
                sf::Color pixelColor    = sf::Color(vectorColor.getX(), vectorColor.getY(), vectorColor.getZ());

                pixels.setPixel(j, i, pixelColor);
            // }
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
    Vector intersectionPoint = intersect(camera, pointVector - camera);
    if (intersectionPoint != Vector())
        return !(light.getColor() * this->color);
    return Vector();
}

Vector Sphere::diffusiveCoeff(const Vector& camera, const Vector& pointVector, const Light& light) {
    Vector intersectionPoint = intersect(camera, pointVector);
    Vector pointToLight      = !(intersectionPoint - this->center);
    Vector lightVector       = !(light.getPosition() - intersectionPoint);

    double degree = pointToLight.angle(lightVector);
    if (degree < 0) degree = 0;

    return Vector(degree, degree, degree) * this->color;
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