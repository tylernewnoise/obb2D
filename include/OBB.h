#ifndef OBB_H_
#define OBB_H_

#include <tuple>
#include <vector>

#include "Vec2.h"

/**
 * Simple representation of a 2x2 matrix.
 */
struct Matrix2D {
  double xx{};
  double xy{};
  double yx{};
  double yy{};
};

/**
 * This class calculates and holds an oriented bounding box (OBB) from a given
 * set of points in 2D space.
 */
class OBB {
 public:
  /**
   * Constructor.
   *
   * @param input_pts A std::vector of Vec2 for which the OBB should be
   * calculated.
   */
  explicit OBB(std::vector<Vec2> input_pts)
      : vertices{std::move(input_pts)}, got_obb{false} {};

  /**
   * Calculates the OBB.
   */
  void calcOBB();

  /**
   * Return the OBB.
   *
   * @return A std::tuple with all four vertices of the OBB.
   */
  [[nodiscard]] std::tuple<Vec2, Vec2, Vec2, Vec2, bool> getOBB() const;

  // void setVertices(const std::vector<Vec2> &input_pts);

 private:
  std::vector<Vec2> vertices;
  bool got_obb;
  Vec2 p1;
  Vec2 p2;
  Vec2 p3;
  Vec2 p4;

  //! Computes the Covariance matrix from all points.
  static Matrix2D calcCovMatrix(const std::vector<Vec2> &input_pts);

  //! Calculate the Eigenvectors of the Covariance matrix.
  static std::tuple<Vec2, Vec2> calcEigenVec(const Matrix2D &matrix);

  //! Calculate the maximum and minimum of the extents of the OBB.
  static std::tuple<Vec2, Vec2> calcMaxMinExtPts(
      const std::vector<Vec2> &points, const Vec2 &eigen_vec);

  //! Calculates and sets the four points for the OBB.
  void calcOBBPoints(const Vec2 &pc1_max_pnt, const Vec2 &pc1_min_pnt,
                     const Vec2 &pc2_max_pnt, const Vec2 &pc2_min_pnt);
};
#endif  // OBB_H_
