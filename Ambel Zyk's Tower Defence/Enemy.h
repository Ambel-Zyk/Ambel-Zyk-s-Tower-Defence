#pragma once

#include"Other.h"

using namespace OTHER;

namespace ENEMY {
	class Enemy {
		int _hp = 10;
		Point _pos;
	public:
		static const char _img = 'A';
		static const int _atk = 3;
		static const int _spd = 1;
		Enemy(Point x) : _pos(x) {}
		Enemy(int x, int y) : _pos(x, y) {}
		Point GetPos(RECT rect) const;
		void Move();
		bool Legal();
		void GetAttacked(int damage);
		Point GetOriginPoint() const;
		bool Health() const;
	};
}