#include "OBB.h"

#include <cmath>
#include <iostream>
#include <limits>

Matrix2D OBB::calcCovMatrix(const std::vector<Vec2> &input_pts) {
  Matrix2D cov_matrix;

  auto n{static_cast<double>(input_pts.size())};
  double x_mean{0.0}, y_mean{0.0};

  for (const auto &point : input_pts) {
    x_mean += point.x;
    y_mean += point.y;
  }
  x_mean = x_mean / n;
  y_mean = y_mean / n;

  for (const auto &point : input_pts) {
    cov_matrix.xy += (point.x - x_mean) * (point.y - y_mean);
    cov_matrix.xx += (point.x - x_mean) * (point.x - x_mean);
    cov_matrix.yy += (point.y - y_mean) * (point.y - y_mean);
  }

  cov_matrix.xy = cov_matrix.xy / n;
  cov_matrix.yx = cov_matrix.xy;
  cov_matrix.xx = cov_matrix.xx / n;
  cov_matrix.yy = cov_matrix.yy / n;

  return cov_matrix;
}

std::tuple<Vec2, Vec2> OBB::calcEigenVec(const Matrix2D &matrix) {
  // https://www.youtube.com/watch?v=e50Bj7jn9IQ
  auto p = (matrix.xx * matrix.yy) - (matrix.xy * matrix.yx);
  auto m = (matrix.xx + matrix.yy) / 2;
  auto eigen_value_x1 = m + std::sqrt(std::pow(m, 2.0) - p);
  auto eigen_value_x2 = m - std::sqrt(std::pow(m, 2.0) - p);

  Matrix2D eigenMatrix1 = matrix;
  Matrix2D eigenMatrix2 = matrix;
  eigenMatrix1.xx = eigenMatrix1.xx - eigen_value_x1;
  eigenMatrix1.yy = eigenMatrix1.yy - eigen_value_x1;

  eigenMatrix2.xx = eigenMatrix2.xx - eigen_value_x2;
  eigenMatrix2.yy = eigenMatrix2.yy - eigen_value_x2;

  Vec2 eigen_vec1{eigenMatrix1.xy * -1, eigenMatrix1.xx};
  Vec2 eigen_vec2{eigenMatrix2.xy, eigenMatrix2.xx * -1};

  eigen_vec1.length();
  eigen_vec2.length();

  return {eigen_vec1, eigen_vec2};
}

std::tuple<Vec2, Vec2> OBB::calcMaxMinExtPts(const std::vector<Vec2> &points,
                                             const Vec2 &eigen_vec) {
  Vec2 min_ext{std::numeric_limits<double>::max(),
               std::numeric_limits<double>::max()},
      max_ext{std::numeric_limits<double>::min(),
              std::numeric_limits<double>::min()},
      tmp{0.0, 0.0};
  double scalar_proj;

  for (const auto &point : points) {
    scalar_proj = eigen_vec.scalar_projection(point);
    tmp.x = scalar_proj * eigen_vec.x / eigen_vec.len;
    tmp.y = scalar_proj * eigen_vec.y / eigen_vec.len;

    min_ext.min(tmp);
    max_ext.max(tmp);
  }

  return {min_ext, max_ext};
}

void OBB::calcOBB() {
  auto matrix = calcCovMatrix(vertices);
  auto [eigen_v1, eigen_v2] = calcEigenVec(matrix);
  auto [pc1_max_pnt, pc1_min_pnt] = calcMaxMinExtPts(vertices, eigen_v1);
  auto [pc2_max_pnt, pc2_min_pnt] = calcMaxMinExtPts(vertices, eigen_v2);
  calcOBBPoints(pc1_max_pnt, pc1_min_pnt, pc2_max_pnt, pc2_min_pnt);
}

void OBB::calcOBBPoints(const Vec2 &pc1_max_pnt, const Vec2 &pc1_min_pnt,
                        const Vec2 &pc2_max_pnt, const Vec2 &pc2_min_pnt) {
  p1 = pc1_max_pnt + pc2_min_pnt;
  p2 = pc1_max_pnt + pc2_max_pnt;
  p3 = pc1_min_pnt + pc2_min_pnt;
  p4 = pc1_min_pnt + pc2_max_pnt;
  got_obb = true;
}

std::tuple<Vec2, Vec2, Vec2, Vec2, bool> OBB::getOBB() const {
  if (!got_obb) {
    std::cerr << "OBB has not been calculated yet!" << std::endl;
    return {p1, p2, p3, p4, false};
  }
  return {p1, p2, p3, p4, true};
}

// void OBB::setVertices(const std::vector<Vec2> &input_pts) {
//  vertices = input_pts;
//}
