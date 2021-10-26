#include "Vec2.h"

#include <algorithm>
#include <cmath>

void Vec2::length() { len = std::sqrt(std::pow(x, 2.0) + std::pow(y, 2.0)); }

void Vec2::max(const Vec2 &v) {
  if (std::max(x, v.x) != x) {
    x = v.x;
    y = v.y;
  }
}

void Vec2::min(const Vec2 &v) {
  if (std::min(x, v.x) != x) {
    x = v.x;
    y = v.y;
  }
}

double Vec2::scalar_projection(const Vec2 &v) const {
  return ((v.x * x) + (v.y * y)) / len;
}

Vec2 Vec2::operator+(const Vec2 &v) const { return Vec2(x + v.x, y + v.y); }

std::ostream &operator<<(std::ostream &output, const Vec2 &v) {
  output << v.x << ", " << v.y;
  return output;
}
