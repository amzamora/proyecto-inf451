#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "graphics.hpp"

float area_triangle(glm::vec2 points[]);
bool is_inside_triangle(glm::vec2 points[], glm::vec2 point);
bool is_inside_quad(glm::vec2 points[], glm::vec2 point);

#endif
