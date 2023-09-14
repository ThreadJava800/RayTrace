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
                Vector curPoint    = !Vector(i, j, 1);
                Vector vectorColor = diffusiveCoeff(camera, curPoint, lights[0]) * 0.5;

                // std::cout << vectorColor.getX() << ' ' << vectorColor.getY() << ' ' << vectorColor.getZ() << '\n';
    
                sf::Color pixelColor = sf::Color(vectorColor.getX() * 255, vectorColor.getY() * 255, vectorColor.getZ() * 255);
                pixels.setPixel(i, j, pixelColor);
            }
        }
    }
    pixelTexture.loadFromImage(pixels);
    pixelsSp.setTexture(pixelTexture);
    window.draw(pixelsSp);
}

Vector Sphere::intersect(const Vector& camera, const Vector& vector) {
    Vector cam_to_sphere_center = camera - this->center; 
    Vector cam_to_sphere_center_norm = !cam_to_sphere_center;

    Vector AK = (!vector) * sqrt((cam_to_sphere_center, cam_to_sphere_center)) * ((!vector, cam_to_sphere_center_norm));
    Vector OK = cam_to_sphere_center * (-1) + AK;
    
    if ((OK,OK) > (this->radius * this->radius)) 
    {
        return Vector();
    }

    Vector directsqrt = (!vector) * (sqrt (this->radius * this->radius - (OK, OK)));
    Vector AP = AK - directsqrt;
    Vector joint_point_vec = AP + camera;
    
    return joint_point_vec;
}

Vector Sphere::ambientCoeff(const Vector& camera, const Vector& pointVector, const Light& light) {
    Vector intersectionPoint = intersect(camera, !(camera - pointVector));
    if (intersectionPoint != Vector())
        return !(light.getColor() * this->color);
    return Vector();
}

Vector Sphere::diffusiveCoeff(const Vector& camera, const Vector& pointVector, const Light& light) {
    Vector intersectionPoint   = intersect(camera, !(pointVector - camera));

    // std::cout << intersectionPoint.getX() << ' ' << intersectionPoint.getY() << ' ' << intersectionPoint.getZ() << '\n';

    Vector intersectToLight = !(light.getPosition() - intersectionPoint);
    Vector normalVec        = !(intersectionPoint - this->center);

    double coeff =  (intersectionPoint, normalVec);
    if (coeff < 0) coeff = 0;

    return Vector(coeff, coeff, coeff) * !(this->color);
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