#include "Tower.h"

using namespace TOWER;

void Bullet::Move() {
	_pos.Move(_spd, 0);
}

Point Bullet::GetPos(RECT rect) const {
	return _pos.Translate(rect);
}

Point Bullet::GetOriginPoint() const {
	return _pos;
}

Point Tower::GetPos(RECT rect) const {
	return _pos.Translate(rect);
}

Point Tower::GetOriginPoint() const {
	return _pos;
}

void Tower::GetAttacked(int damage) {
	_hp -= damage;
	return;
}

bool Tower::Health() const {
	return _hp > 0;
}

int Generator::Generate() {
	if (_gencd == 0) {
		_gencd = _spd;
		return _gen;
	}
	_gencd--;
	return 0;
}

Bullet Attacker::Shoot() {
	if (_atkcd == 0) {
		_atkcd = _spd;
		return Bullet(_pos);
	}
	_atkcd--;
	return Bullet(-1, -1);
}

bool Bullet::Legal() {
	return _pos.Legal();
}