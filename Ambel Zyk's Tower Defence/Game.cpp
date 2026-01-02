#include <random>
#include "Game.h"

using namespace GAME;

COLORREF Gainsboro = RGB(220, 220, 220);
COLORREF DimGray = RGB(105, 105, 105);
RECT rect;

void Game::DrawPrepage(HDC hdc, RECT* clientRect) {
    int midX = clientRect->left + clientRect->right >> 1;
    int midY = clientRect->top + clientRect->bottom >> 1;

    HBRUSH BKBrush = CreateSolidBrush(DimGray);
    FillRect(hdc, clientRect, BKBrush);
    DeleteObject(BKBrush);

    WCHAR text[50];
    SetTextColor(hdc, Gainsboro);
    SetBkMode(hdc, TRANSPARENT);
	SetTextAlign(hdc, TA_CENTER);

    HFONT hFont = CreateFontA(100, 0, 0, 0,
        FW_BOLD, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Temp"
    );
    HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
    swprintf(text, 50, L"TD塔防");
    TextOut(hdc, midX, midY - 100, text, wcslen(text));

    hFont = CreateFontA(30, 0, 0, 0,
        FW_BOLD, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Temp"
    );
    SelectObject(hdc, hFont);
    swprintf(text, 50, L"按 空格 开始游戏");
    TextOut(hdc, midX, midY + 30, text, wcslen(text));

    SelectObject(hdc, oldFont);
    DeleteObject(hFont);
}

void Game::DrawGame(HDC hdc, RECT* clientRect) {
    int left = clientRect->left;
    int top = clientRect->top;
    int right = clientRect->right;
    int bottom = clientRect->bottom;

    // Draw background
    HBRUSH BKBrush = CreateSolidBrush(DimGray);
    FillRect(hdc, clientRect, BKBrush);
    DeleteObject(BKBrush);

    // Draw fight region frame
    HBRUSH FRBrush = CreateSolidBrush(Gainsboro);
    rect = { left + 100, top + 100, right - 100, bottom - 100 };
    FrameRect(hdc, &rect, FRBrush);
    DeleteObject(FRBrush);

    // Draw fight region mesh
    HPEN meshPen = CreatePen(PS_SOLID, 1, Gainsboro);
    HPEN oldPen = (HPEN)SelectObject(hdc, meshPen);
    int height = (bottom - top - 200) / 5;
    int width = (right - left - 200) / 8;
    for (int i = 1; i < 5; i++) {
        MoveToEx(hdc, left + 100, top + 100 + height * i, NULL);
        LineTo(hdc, right - 100, top + 100 + height * i);
    }
    for (int i = 1; i < 8; i++) {
        MoveToEx(hdc, left + 100 + width * i, top + 100, NULL);
        LineTo(hdc, left + 100 + width * i, bottom - 100);
    }
    SelectObject(hdc, oldPen);
    DeleteObject(meshPen);

    // Draw game information
    WCHAR text[50];
    SetTextColor(hdc, Gainsboro);
    SetBkMode(hdc, TRANSPARENT);
    HFONT hFont = CreateFontA(20, 0, 0, 0,
        FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Temp"
    );
    HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

    // Draw life
    swprintf(text, 50, L"生命: %d", _life);
    TextOut(hdc, 10, 10, text, wcslen(text));

    // Draw money
    swprintf(text, 50, L"金钱: %d", _money);
    TextOut(hdc, 100, 10, text, wcslen(text));

    // Draw score
    swprintf(text, 50, L"分数: %d", _score);
    TextOut(hdc, 10, 50, text, wcslen(text));

	// Draw time
    swprintf(text, 50, L"时间: %d", _time);
	TextOut(hdc, 100, 50, text, wcslen(text));

    // Draw tips
	swprintf(text, 50, L"按1/2/3或U/F/D并点选格子以建塔，按ESC以取消");
    TextOut(hdc, 30, bottom - 70, text, wcslen(text));
    swprintf(text, 50, L"U：金矿   F：炮塔    D：盾墙");
	TextOut(hdc, 30, bottom - 50, text, wcslen(text));

    // Draw cards cd
    hFont = CreateFontA(35, 0, 0, 0,
        FW_BOLD, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Temp"
    );
    SelectObject(hdc, hFont);
    swprintf(text, 50, L"%d", cdG);
	TextOut(hdc, 200, 50, text, wcslen(text));
    swprintf(text, 50, L"%d", cdA);
    TextOut(hdc, 250, 50, text, wcslen(text));
    swprintf(text, 50, L"%d", cdD);
    TextOut(hdc, 300, 50, text, wcslen(text));

    hFont = CreateFontA(35, 0, 0, 0,
        FW_BOLD, TRUE, UsableG ? TRUE : FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Temp"
    );
    SelectObject(hdc, hFont);
    swprintf(text, 50, L"%c", Generator::_img);
	TextOut(hdc, 200, 10, text, wcslen(text));

    hFont = CreateFontA(35, 0, 0, 0,
        FW_BOLD, TRUE, UsableA ? TRUE : FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Temp"
    );
    SelectObject(hdc, hFont);
	swprintf(text, 50, L"%c", Attacker::_img);
	TextOut(hdc, 250, 10, text, wcslen(text));

    hFont = CreateFontA(35, 0, 0, 0,
        FW_BOLD, TRUE, UsableD ? TRUE : FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Temp"
    );
    SelectObject(hdc, hFont);
	swprintf(text, 50, L"%c", Defender::_img);
	TextOut(hdc, 300, 10, text, wcslen(text));

	// Draw towers
    hFont = CreateFontA(35, 0, 0, 0,
        FW_BOLD, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Temp"
    );
    SelectObject(hdc, hFont);
    for (auto const& tower : _generators) {
        Point pos = tower.GetPos(rect);
        swprintf(text, 50, L"%c", tower._img);
        TextOut(hdc, pos.GetX(), pos.GetY(), text, wcslen(text));
    }
    for (auto const& tower : _attackers) {
        Point pos = tower.GetPos(rect);
        swprintf(text, 50, L"%c", tower._img);
        TextOut(hdc, pos.GetX(), pos.GetY(), text, wcslen(text));
    }
    for (auto const& tower : _defenders) {
        Point pos = tower.GetPos(rect);
        swprintf(text, 50, L"%c", tower._img);
        TextOut(hdc, pos.GetX(), pos.GetY(), text, wcslen(text));
    }
	// Draw bullets
    for (auto const& bullet : _bullets) {
        Point pos = bullet.GetPos(rect);
        swprintf(text, 50, L"%c", bullet._img);
        TextOut(hdc, pos.GetX(), pos.GetY(), text, wcslen(text));
	}

	// Draw enemies
    for (auto const& enemy: _enemies){
        Point pos = enemy.GetPos(rect);
        swprintf(text, 50, L"%c", enemy._img);
        TextOut(hdc, pos.GetX(), pos.GetY(), text, wcslen(text));
	}

    SelectObject(hdc, oldFont);
    DeleteObject(hFont);
}

void Game::DrawGameOver(HDC hdc, RECT* clientRect) {
    int left = clientRect->left;
    int top = clientRect->top;
    int right = clientRect->right;
    int bottom = clientRect->bottom;
	int midX = left + right >> 1;
	int midY = top + bottom >> 1;

    HBRUSH FRBrush = CreateSolidBrush(Gainsboro);
    rect = { left + 100, top + 100, right - 100, bottom - 100 };
    FrameRect(hdc, &rect, FRBrush);
    DeleteObject(FRBrush);

    WCHAR text[50];
    SetTextColor(hdc, Gainsboro);
    SetBkMode(hdc, TRANSPARENT);
	SetTextAlign(hdc, TA_CENTER);

    HFONT hFont = CreateFontA(100, 0, 0, 0,
        FW_BOLD, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Temp"
    );
    HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
    swprintf(text, 50, L"游戏结束");
    TextOut(hdc, midX, midY - 100, text, wcslen(text));

    hFont = CreateFontA(30, 0, 0, 0,
        FW_BOLD, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Temp"
    );
    SelectObject(hdc, hFont);
	swprintf(text, 50, L"最终得分: %d", _score * _life);
	TextOut(hdc, midX, midY + 30, text, wcslen(text));

    SelectObject(hdc, oldFont);
    DeleteObject(hFont);
}

void Game::Update() {

    // Update time
    _time++;

    // Update cd;
    if (cdG > 0) cdG--;
    if (cdA > 0) cdA--;
    if (cdD > 0) cdD--;
    if (cdG == 0) UsableG = true;
    if (cdA == 0) UsableA = true;
    if (cdD == 0) UsableD = true;

	// Towers work
    for (auto& generator : _generators) {
        _money += generator.Generate();
    }
    for (auto& tower : _attackers) {
        Bullet bullet = tower.Shoot();
        if (bullet.Legal()) _bullets.push_back(bullet);
    }

    // Update enemies
    for (auto it = _enemies.begin(); it != _enemies.end(); ) {
        Point pos = it->GetOriginPoint();
        
        // get attacked
        for (auto bIt = _bullets.begin(); bIt != _bullets.end();) {
            int x = bIt->GetOriginPoint().GetX();
            int y = bIt->GetOriginPoint().GetY();
            bool hit = false;
            for (int i = 0; i <= Bullet::_spd; i++)
                hit |= (pos.GetX() == x + i && pos.GetY() == y);
            if (hit) {
                it->GetAttacked(Bullet::_atk);
                bIt = _bullets.erase(bIt);
            }
            else ++bIt;
        }

        // check health
        if (!it->Health()) {
            _score++;
            it = _enemies.erase(it);
        }
        else
        {
			// attack tower
            bool existTower = false;
            for (auto& tower : _generators)
                if (tower.GetOriginPoint() == pos) {
					existTower |= true;
                    tower.GetAttacked(Enemy::_atk);
                }
            for (auto& tower : _attackers)
                if (tower.GetOriginPoint() == pos) {
                    existTower |= true;
                    tower.GetAttacked(Enemy::_atk);
                }
            for (auto& tower : _defenders)
                if (tower.GetOriginPoint() == pos) {
                    existTower |= true;
                    tower.GetAttacked(Enemy::_atk);
                }
            if (!existTower) it->Move();

            // reach boundary
            if (!it->Legal()) {
                _life--;
                it = _enemies.erase(it);
            }
            else ++it;
        }
    }
    if (_time % 7 == 0) AddEnemy();

    // Update tower
    for (auto it = _generators.begin(); it != _generators.end(); ) {
        if (!it->Health()) it = _generators.erase(it);
        else ++it;
    }
    for (auto it = _attackers.begin(); it != _attackers.end(); ) {
        if (!it->Health()) it = _attackers.erase(it);
        else ++it;
    }
    for (auto it = _defenders.begin(); it != _defenders.end(); ) {
        if (!it->Health()) it = _defenders.erase(it);
        else ++it;
    }

    // Update bulltes
    for (auto& bullet : _bullets) {
        bullet.Move();
    }

}

void Game::AddGenerator(int x, int y) {
    Point point = Point(x, y).ReTranslate(rect);
    Generator tower = Generator(point);
    if (_money >= tower._cost && UsableG) {
	    _generators.push_back(tower);
		_money -= tower._cost;
        cdG = 3;
        UsableG = false;
    }
}

void Game::AddAttacker(int x, int y) {
    Point point = Point(x, y).ReTranslate(rect);
    Attacker tower = Attacker(point);
    if (_money >= tower._cost && UsableA) {
        _attackers.push_back(tower);
		_money -= tower._cost;
        cdA = 4;
        UsableA = false;
    }
}

void Game::AddDefender(int x, int y) {
    Point point = Point(x, y).ReTranslate(rect);
    Defender tower = Defender(point);
    if (_money >= tower._cost && UsableD) {
        _defenders.push_back(tower);
		_money -= tower._cost;
        cdD = 10;
        UsableD = false;
    }
}

void Game::AddEnemy() {
    int y = rand() % 5;
    _enemies.push_back(Enemy(7, y));
}

bool Game::GameOver() {
    return _life <= 0 || _time >= 180;
}