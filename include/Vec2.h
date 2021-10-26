#ifndef VEC2_H_
#define VEC2_H_

#include <ostream>

/**
 * This class implements a simple vector (or point) with two fields.
 */
class Vec2 {
 public:
  double len{};
  double x{};
  double y{};

  /**
   * Constructors.
   *
   * @param x x-value of the vector.
   * @param y y-value of the vector.
   */
  Vec2(const double &x, const double &y) : len{0.0}, x{x}, y{y} {};
  Vec2() : len{0.0}, x{0.0}, y{0.0} {};

  /**
   * Calculates the length of the vector. Comes in handy for the projection
   * stuff.
   */
  void length();

  /**
   * Tests if another Vec2 is bigger.
   * @param v The Vec2 for comparison.
   */
  void max(const Vec2 &v);

  /**
   * Tests if another Vec2 is smaller.
   * @param v The Vec2 for comparison.
   */
  void min(const Vec2 &v);

  /**
   * Calculates the scalar_projection from a given Vec2 on to this one.
   * @param v The Vec2 to be projected.
   * @return The scalar projection.
   */
  [[nodiscard]] double scalar_projection(const Vec2 &v) const;

  /**
   * Overloads + for addition of two Vec2.
   * @param v The Vec2 to be added to this one.
   * @return The resulting Vec2.
   */
  Vec2 operator+(const Vec2 &v) const;

  /**
   * Overloads << for simpler output.
   * @param output ostream object.
   * @param v The Vec2 which needs to be printed.
   * @return Reference to ostream.
   */
  friend std::ostream &operator<<(std::ostream &output, const Vec2 &v);
};

#endif  // VEC2_H_
