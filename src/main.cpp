#include <OBB.h>
#include <Vec2.h>

#include <iomanip>
#include <iostream>
#include <regex>

/**
 * Validates if a given std::string is in the format of a double.
 * Source for the regex: https://stackoverflow.com/a/56502134
 *
 * @param candidate A std::string representing a double value.
 * @return True if the format is correct, false otherwise.
 */
static bool validateDouble(const std::string &candidate);

/**
 * Reads line by line from stdin to create a list of 2d vertices.
 *
 * @return A std::tuple with the read vertices and a return value. If the
 * reading process fails, the value is set to false, true otherwise.
 */
[[nodiscard]] static std::tuple<std::vector<Vec2>, bool> readVertices();

/**
 * Program main entry point.
 */
int main() {
  auto [vertices, ret] = readVertices();
  if (!ret) {
    std::cerr << "WRONG INPUT!" << std::endl;
    return EXIT_FAILURE;
  }

  // heap...
  // std::unique_ptr<OBB> obb{std::make_unique<OBB>(vertices)};

  // stack...
  OBB obb(vertices);
  obb.calcOBB();
  auto [p1, p2, p3, p4, retObb] = obb.getOBB();

  if (retObb) {
    std::cout << "OBB: " << std::endl;
    std::cout << std::fixed << std::setprecision(2) << p1 << "\n"
              << p2 << "\n"
              << p3 << "\n"
              << p4 << std::endl;
  }

  return 0;
}

static bool validateDouble(const std::string &candidate) {
  const std::regex dbl(
      R"(^([+-]?(?:[[:d:]]+\.?|[[:d:]]*\.[[:d:]]+))(?:[Ee][+-]?[[:d:]]+)?$)");
  return std::regex_match(candidate, dbl);
}

std::tuple<std::vector<Vec2>, bool> static readVertices() {
  std::string input_line;
  std::string x_input;
  std::string y_input;
  std::size_t pos_y;
  double retVal{true};
  std::vector<Vec2> vertices;

  while (std::getline(std::cin, input_line)) {
    // Run through line and check if there are two doubles.
    if (input_line.empty()) {
      retVal = false;
      break;
    }

    // Get the first double, the x coordinate.
    pos_y = input_line.find(' ');
    if (pos_y == std::string::npos) {
      retVal = false;
      break;
    }
    x_input = input_line.substr(0, pos_y);

    // Get the second double, the y coordinate.
    y_input = input_line.substr(++pos_y, input_line.length());

    if (!validateDouble(y_input) || !validateDouble(x_input)) {
      retVal = false;
      break;
    }

    Vec2 point{std::stod(x_input), std::stod(y_input)};
    vertices.push_back(point);
  }

  return {vertices, retVal};
}
