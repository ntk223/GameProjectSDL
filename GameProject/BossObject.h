#ifndef BOSS_OBJECT_H
#define BOSS_OBJECT_H

#include "BaseObject.h"
#include "Enemy.h"
#include "Bullet.h"

#define BOSS_WITDH 140
#define BOSS_HEIGHT 250 
#define BOSS_SPEED 3
#define BOSS_HP 100 

#define MAX_BULLET_BOSS 7



class BossObject : public BaseObject
{
public:
	BossObject();
	~BossObject();
	void SetRect(const int w, const int h)
	{
		rect_.x = x_val;
		rect_.y = y_val;
		rect_.w = w;
		rect_.h = h;
	}
	void update();

	void Set_bullets(std::vector<Bullet*>bullets_, int i) { bullets[i] = bullets_; }
	std::vector<Bullet*> Get_bullets(int i) { return bullets[i]; }

	void Init_bullet_(std::vector<Bullet*>& bullets_, int x_val_, int y_val_, int w, int h);
	void Init_bullet();

	void check_bullet_out();

protected:
	int x_val;
	int y_val;
	int step = BOSS_SPEED;


	Uint32 lastBulletTime;


	std::vector<std::vector<Bullet*>> bullets;

};


#endif // !BOSS_OBJECT_H

