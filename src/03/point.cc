#include "point.h"
#include <iostream>

Point::Point(long long x, long long y)
  :x{x},y{y}
{}

long long Point::X() const { return x;}
long long Point::Y() const { return y;}

void Point::X(long long const& x) { this->x = x;}
void Point::Y(long long const& y) { this->y = y;}

std::ostream& operator<<(std::ostream & os, Point const& p) {
  os << "(" << p.X()  << ":" << p.Y() << ")";
  return os;
}
