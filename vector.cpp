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

double Vector::angle(const Vector& second) const {
    return (*this, second) / (this->len() * second.len());
}

Vector Vector::rotated(double degree) {
    double radians = degree * M_PI / 180;

    double oldX   = this->x,      oldY   = this->z;
    double degCos = cos(radians), degSin = sin(radians);

    Vector res = Vector();

    // (sin(a) + cos(a)i)*(x+yi) = (sin(a)*x - cos(a)*y)+(sin(a)*y + cos(a)*x)i
    res.x = degCos * oldX - degSin * oldY;
    res.y = this->y;
    res.z = degCos * oldY + degSin * oldX;

    return res;
}

inline double Vector::len() const {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector operator* (const Vector& a, const Vector& b) {
    return Vector(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vector operator* (const Vector& a, double scalar) {
    return Vector(a.x * scalar, a.y * scalar, a.z * scalar);
}

Vector operator+ (const Vector& a, const Vector& b) {
    return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

void operator+=(Vector& a, const Vector& b) {
    a = a + b;
}

Vector operator- (const Vector& a, const Vector& b) {
    return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector operator/ (const Vector& a, const double scalar) {
    if (scalar == 0) return Vector();
    return Vector(a.x / scalar, a.y / scalar, a.z / scalar);
}

Vector operator! (const Vector& a) {
    return Vector(a.x, a.y, a.z) / a.len();
}

double operator, (const Vector& a, const Vector& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

bool operator!=(const Vector& a, const Vector& b) {
    return !(a.x == b.x && a.y == b.y && a.z == b.z);
}