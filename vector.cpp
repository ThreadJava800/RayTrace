#include "vector.h"

Vector::Vector() : 
    x(0),
    y(0),
    z(0)      {}

Vector::Vector(double x, double y, double z) :
    x(x),
    y(y),
    z(z)      {}

Vector::~Vector() {
    this->x = NAN;
    this->y = NAN;
    this->z = NAN;
}

double Vector::getX() const {
    return this->x;
}

double Vector::getY() const {
    return this->y;
}

double Vector::getZ() const {
    return this->z;
}

inline double Vector::len() const {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector operator* (const Vector& a, const Vector& b) {
    return Vector(a.x * b.x, a.y * b.y, a.z * b.z);
}