#include "Bullet.h"

Bullet::Bullet()
{
	x_val = 0;
	y_val = 0;
	is_move = false;
	
}

Bullet::~Bullet()
{
	Free();
}


void Bullet::update()
{
	rect_.x += BULLET_SPEED;
}
void Bullet::update_enemy()
{
	rect_.x -= BULLET_SPEED_ENEMY;
	//rect_.y = enemy->get_oy() + sqrt(rect_.x);
	

}

