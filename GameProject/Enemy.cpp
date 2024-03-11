#include "Enemy.h"



Enemy::Enemy()
{

	respawn();
	lastBulletTime = SDL_GetTicks();
}

Enemy::~Enemy()
{

}

int Enemy::random(int a, int b)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> distribution(a, b);
	int random_number = distribution(generator);
	return random_number;
}
void Enemy::respawn() 
{
	x_val = random(SCREEN_WIDTH  , SCREEN_WIDTH + 1000 );
	y_val = random(0,  SCREEN_HEIGHT + 400);
	Oy = y_val;
}

void Enemy::update()
{
	if ( Size == "s")
	{	
		if (y_val > SCREEN_HEIGHT - ENEMY_HEIGHT) y_val= SCREEN_HEIGHT - ENEMY_HEIGHT;
		x_val -= ENEMY_SPEED;
		y_val += enemy_sp;
		if (y_val <= 0 || y_val >= SCREEN_HEIGHT - ENEMY_HEIGHT)
		{
			enemy_sp = -enemy_sp;
		}
		if (x_val < 0)
		{
			is_out = true;
		}
	}
	else
	{
		x_val -= 3.0f;
		y_val = Oy / 2 + AMPLITUDE * std::sin(FREQUENCY * x_val);
		if (x_val < 0)
		{
			is_out = true;
		}
		if (y_val< 0 || y_val > SCREEN_HEIGHT - ENEMY_HEIGHT)
		{
			respawn();
		}
	}
}



void Enemy::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
	SDL_Rect renderquad = { x_val , y_val , rect_.w ,rect_.h };
	SDL_RenderCopy(des, BaseObject::GetObject(), clip, &renderquad);
}

void Enemy::Init_bullet()
{
	int t = 0, x = 0 ;
	if (Size == "m")
	{
		t = 3000;
		x = 100;
	}
	else if (Size == "ufo")
	{
		t = -1000;
	}
	if (this->x_val < SCREEN_WIDTH  - x)
	{
		Uint32 currentTime = SDL_GetTicks();
		if (bullets.size() < MAX_BULLET_ENEMY && currentTime - lastBulletTime >= delayTime + t)
		{
			Bullet* bullet = new Bullet();
			if (Size == "m") {

				bullet->SetWidthHeight(this->x_val - 50, BULLET_HEIGHT_LASER);
				bullet->SetRect(50, this->y_val + ENEMY_HEIGHT / 2 - BULLET_HEIGHT_LASER / 2,
					this->x_val - 50, BULLET_HEIGHT_LASER);
			}
			else if (Size == "ufo")
			{
				bullet->SetWidthHeight(ICE_BULLET_WIDTH, ICE_BULLET_HEIGHT);

				bullet->SetRect(this->x_val, this->y_val + ENEMY_HEIGHT / 2 - ICE_BULLET_HEIGHT / 2,
					ICE_BULLET_WIDTH, ICE_BULLET_HEIGHT);
			}
			else {
				bullet->SetWidthHeight(BULLET_WIDTH_ENEMY, BULLET_HEIGHT_ENEMY);

				bullet->SetRect(this->x_val, this->y_val + ENEMY_HEIGHT / 2 - BULLET_HEIGHT_ENEMY / 2,
					BULLET_WIDTH_ENEMY, BULLET_HEIGHT_ENEMY);

			}
			bullet->set_is_move(true);

			bullets.push_back(bullet);
			lastBulletTime = currentTime;
		}
	}
}

void Enemy::check_bullet_out()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		Bullet* bullet = bullets.at(i);
		if (bullet->get_x_val() < 0)
		{
			bullet = NULL;
			bullets.erase(bullets.begin() + i);
		}
	}
}

void Enemy::setType(const int n)
{
	int t = random(1, n);
	type = std::to_string(t);
}



//
void Enemy::respawn_meteorite()
{
	x_val = random(SCREEN_WIDTH, SCREEN_WIDTH + 1000);
	y_val = random(0, SCREEN_HEIGHT - METEORITE_HEIGHT);

}
void Enemy::update_meteorite()
{
	x_val -= METEORITE_SPEED;
	if (x_val < 0)
	{
		is_out = true;
		//respawn();
	}
}








