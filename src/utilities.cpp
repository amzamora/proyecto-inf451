#include "utilities.hpp"

float area_triangle(glm::vec2 points[]) {
	float a = glm::distance(points[0], points[1]);
	float b = glm::distance(points[0], points[2]);
	float c = glm::distance(points[1], points[2]);
	float s = (a + b + c) / 2.0f;
	return sqrt(s*(s - a)*(s - b)*(s - c));
}

bool is_inside_triangle(glm::vec2 points[], glm::vec2 point) {
	float area = area_triangle(points);

	glm::vec2 triangle1[] = {point, points[1], points[2]};
	float area1 = area_triangle(triangle1);

	glm::vec2 triangle2[] = {points[0], point, points[2]};
	float area2 = area_triangle(triangle2);

	glm::vec2 triangle3[] = {points[0], points[1], point};
	float area3 = area_triangle(triangle3);

	if (fabs(area - (area1 + area2 + area3)) < 1e-1) {
		return true;
	}
	else {
		return false;
	}
}

bool is_inside_quad(glm::vec2 points[], glm::vec2 point) {
	int concave_point = 0;
	for (int i = 0; i < 4; i++) {
		glm::vec2 triangle[] = {points[(i + 1) % 4], points[(i + 2) % 4], points[(i + 3) % 4]};
		if (is_inside_triangle(triangle, points[i])) {
			concave_point = i;
		}
	}

	glm::vec2 triangle1[] = {points[concave_point], points[(concave_point + 1) % 4], points[(concave_point + 2) % 4]};
	glm::vec2 triangle2[] = {points[(concave_point + 2) % 4], points[(concave_point + 3) % 4], points[(concave_point + 4) % 4]};
	return is_inside_triangle(triangle1, point) || is_inside_triangle(triangle2, point);
}
