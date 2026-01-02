#pragma once
#include "framework.h"

namespace OTHER {

	class Point {
		int _x;
		int _y;
	public:
		Point() : _x(0), _y(0) {}
		Point(int x, int y) : _x(x), _y(y) {}
		int GetX() const { return _x; }
		int GetY() const { return _y; }
		bool operator==(const Point other) const;
		void Move(int dx, int dy);
		Point Translate(RECT rect) const;
		Point ReTranslate(RECT rect) const;
		bool Legal() const;
	};

}