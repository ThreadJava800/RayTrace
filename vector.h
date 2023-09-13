#ifndef _VEC_h_
#define _VEC_h_

#include <cmath>
#include <iostream>

class Vector {
private:
    double x, y, z;

public:
    explicit Vector();
    explicit Vector(double x, double y, double z);

    ~Vector();

    double getX() const;
    double getY() const;
    double getZ() const;

    inline double len() const;

    // cos of angle between two vectors (this and second)
    double angle(const Vector& second) const;

    friend Vector operator* (const Vector& a, const Vector& b);
    friend Vector operator+ (const Vector& a, const Vector& b);
    friend Vector operator- (const Vector& a, const Vector& b);
    friend Vector operator/ (const Vector& a, const double scalar);
    friend Vector operator! (const Vector& a);                      // normalized
    friend double operator, (const Vector& a, const Vector& b); 
};

#endif