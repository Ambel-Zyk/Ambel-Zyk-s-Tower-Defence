#pragma once

#include"Other.h"

using namespace OTHER;

namespace TOWER {

    class Bullet {
        Point _pos;
    public:
        static const char _img = 'o';
        static const int _atk = 3;
        static const int _spd = 2;
        Bullet(Point x) : _pos(x) {}
        Bullet(int x, int y) : _pos(x, y) {}
        Point GetPos(RECT rect) const;
        bool Legal();
        void Move();
        Point GetOriginPoint() const;
    };

    class Tower {
    protected:
        Point _pos;
        int _hp;
    public:
		int _cd;
        int _cost;
		Tower(Point x) : _pos(x) {}
		Tower(int x, int y) : _pos(x, y) {}
        Point GetPos(RECT rect) const;
        Point GetOriginPoint() const;
        void GetAttacked(int damage);
        bool Health() const;
    };

    class Generator : public Tower {
        int _gencd;
    public:
        static const char _img = 'U';
        static const int _cost = 5;
        static const int _gen = 5;
        static const int _spd = 5;
        Generator(Point x) : Tower(x) { _gencd = 0; _hp = 4; }
		Generator(int x, int y) : Tower(x, y) { _gencd = 0; _hp = 4; }
        int Generate();
    };

    class Attacker : public Tower {
        int _atkcd;
    public:
        static const char _img = 'F'; 
        static const int _cost = 10;
        static const int _spd = 1;
        Attacker(Point x) : Tower(x) { _atkcd = 0; _hp = 6; }
        Attacker(int x, int y) : Tower(x, y) { _atkcd = 0; _hp = 6; }
		Bullet Shoot();
    };

    class Defender : public Tower {
	public:
        static const char _img = 'D';
        static const int _cost = 5;
        Defender(Point x) : Tower(x) { _hp = 16; }
        Defender(int x, int y) : Tower(x, y) { _hp = 16; }
	};
}