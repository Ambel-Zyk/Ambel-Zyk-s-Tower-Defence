#pragma once
#include <vector>
#include "Tower.h"
#include "Enemy.h"
#include "framework.h"

using namespace TOWER;
using namespace ENEMY;

namespace GAME
{
	class Game {
		int _time;
		int _life;
		int _money;
		int _score;
		bool UsableG, UsableA, UsableD;
		int cdG, cdA, cdD;
		std::vector<Generator> _generators;
		std::vector<Attacker> _attackers;
		std::vector<Defender> _defenders;
		std::vector<Enemy> _enemies;
		std::vector<Bullet> _bullets;
	public:
		int state;
		bool PreGenerator;
		bool PreAttacker;
		bool PreDefender;
		Game() : _life(10), _money(10), _score(0), _time(0),
			cdG(0), cdA(0), cdD(0), UsableG(1), UsableA(1), UsableD(1),
			PreGenerator(0), PreAttacker(0), PreDefender(0) {}
		void DrawPrepage(HDC hdc, RECT* clientRect);
		void DrawGame(HDC hdc, RECT* clientRect);
		void DrawGameOver(HDC hdc, RECT* clientRect);
		void AddGenerator(int x, int y);
		void AddAttacker(int x, int y);
		void AddDefender(int x, int y);
		void AddEnemy();
		void Update();
		bool GameOver();
	};
}