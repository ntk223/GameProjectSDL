#include "BossObject.h"


BossObject::BossObject()
{
	x_val = SCREEN_WIDTH - BOSS_WITDH;
	y_val = ( SCREEN_HEIGHT - BOSS_HEIGHT)/2 ;


    bullets.push_back(std::vector<Bullet*>());
    bullets.push_back(std::vector<Bullet*>());
    bullets.push_back(std::vector<Bullet*>());
    bullets.push_back(std::vector<Bullet*>());
    bullets.push_back(std::vector<Bullet*>());
}

BossObject::~BossObject()
{
	Free();
}
void BossObject::update()
{
    y_val += step;

    if (y_val <= 0 || y_val + BOSS_HEIGHT >= SCREEN_HEIGHT)
    {
        step = -step;
    }

}

void BossObject::Init_bullet(std::vector<Bullet*>& bullets_, int x_val_, int y_val_)
{

    if (bullets_.size() < 5)
    {
        Bullet* bullet = new Bullet();
        bullet->SetWidthHeight(BULLET_WIDTH, BULLET_HEIGHT);

        bullet->SetRect(this->x_val + PLAYER_WIDTH + x_val_, this->y_val + y_val_ + PLAYER_HEIGHT / 2 - BULLET_HEIGHT / 2, BULLET_WIDTH, BULLET_HEIGHT);
        bullet->set_is_move(true);

        bullets_.push_back(bullet);

    }
}





