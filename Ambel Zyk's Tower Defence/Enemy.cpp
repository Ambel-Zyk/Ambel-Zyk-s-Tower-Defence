#include "Enemy.h"

using namespace ENEMY;

Point Enemy::GetPos(RECT rect) const {
	return _pos.Translate(rect);
}

void Enemy::Move() {
	_pos.Move(-_spd, 0);
}

bool Enemy::Legal() {
	return _pos.Legal();
}

void Enemy::GetAttacked(int damage) {
	_hp -= damage;
}

Point Enemy::GetOriginPoint() const {
	return _pos;
}

bool Enemy::Health() const {
	return _hp > 0;
}