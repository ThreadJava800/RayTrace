#include "graphics.h"

Light::Light() :
    position(Vector()),
    color(Vector())   {}

Light::Light(Vector& position, Vector& color) :
    position(position),
    color(color)      {}

Vector Light::getPosition() {
    return this->position;
}

void Light::setPosition(Vector position) {
    this->position = position;
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

void Sphere::visualize(sf::RenderWindow& window, const Vector& camera, Light* lights, size_t lightNum) {
    ON_ERROR(!lights, "Null pointer exception.",);

    int width  = window.getSize().x;
    int height = window.getSize().y;
    double r2  = this->radius * this->radius;

    sf::Image   pixels;
    sf::Texture pixelTexture;
    sf::Sprite  pixelsSp;

    pixels.create(width, height, DEFAULT_COLOR);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double x = j * (UNIT_X / double(height)) + START_X;
            double z = i * (UNIT_Z / double(width))  + START_Z;
            Vector pointOnScreen = Vector(x, START_Y, z);
            
            Vector vectorColor = Vector();
            for (int i = 0; i < lightNum; i++) {
                vectorColor += computeColor(camera, pointOnScreen, lights[i]) / double(lightNum);
            }

            sf::Color pixelColor = sf::Color(vectorColor.getX(), vectorColor.getY(), vectorColor.getZ());
            pixels.setPixel(j, i, pixelColor);
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

Vector Sphere::computeColor(const Vector& camera, const Vector& pointVector, Light& light) {
    Vector resultVec = Vector();

    Vector intersectionPoint = intersect(camera, pointVector - camera);
    Vector pointToLight      = intersectionPoint - this->center;
    Vector lightVector       = light.getPosition() - intersectionPoint;
    Vector camToIntersect    = intersectionPoint - camera;

    Vector reflect = pointToLight * 2 * (!lightVector, !pointToLight) - lightVector;

    // ambient
    if (intersectionPoint != Vector())
        resultVec += !(light.getColor() * this->color) * 255;

    // diffusive
    double degree = (!pointToLight, !lightVector);
    if (degree < 0) degree = 0;
    resultVec += Vector(degree, degree, degree) * light.getColor();

    // blick
    degree = (!(pointToLight * (-1)), !reflect);
    if (degree < 0) degree = 0;
    degree = pow(degree, PHONG_CONSTANT);
    resultVec += Vector(degree, degree, degree) * light.getColor();

    return resultVec * 0.33;
}