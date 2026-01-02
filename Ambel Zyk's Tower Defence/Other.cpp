#include"Other.h"
#include <cmath>

using namespace OTHER;

bool Point::operator==(const Point other) const {
	return other._x == _x && other._y == _y;
}

void Point::Move(int dx, int dy) {
	_x += dx;
	_y += dy;
}

Point Point::Translate(RECT rect) const {
	int left = rect.left, right = rect.right;
	int bottom = rect.bottom, top = rect.top;
	int width = (right - left) / 8;
	int height = (bottom - top) / 5;
	return Point(
		left + width * (_x + 0.5),
		top + height * (_y + 0.5)
	);
}

Point Point::ReTranslate(RECT rect) const {
	int left = rect.left, right = rect.right;
	int bottom = rect.bottom, top = rect.top;
	int width = (right - left) / 8;
	int height = (bottom - top) / 5;
	return Point(
		floor((_x - left) / width),
		floor((_y - top) / height)
	);
}

bool Point::Legal() const {
	return (_x >= 0 && _x < 8 && _y >= 0 && _y < 5);
}