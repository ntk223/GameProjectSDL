#ifndef BOSS_OBJECT_H
#define BOSS_OBJECT_H

#include "BaseObject.h"
#include "Enemy.h"
#include "Bullet.h"

#define BOSS_WIDTH 140
#define BOSS_HEIGHT 250 
#define BOSS_SPEED 3
#define BOSS_HP 10

#define MAX_BULLET_BOSS 7



class BossObject : public BaseObject
{
public:
	BossObject();
	~BossObject();
	void SetRect()
	{
		rect_.x = x_val;
		rect_.y = y_val;
		rect_.w = BOSS_WIDTH;
		rect_.h = BOSS_HEIGHT;

	}
	void update();

	void Set_bullets(std::vector<Bullet*>bullets_, int i) { bullets[i] = bullets_; }
	std::vector<Bullet*> Get_bullets(int i) { return bullets[i]; }

	void Init_bullet_(std::vector<Bullet*>& bullets_, int x_val_, int y_val_, int w, int h);
	void Init_bullet();

	void set_HP(int hp) { HP = hp; }
	int get_HP() { return HP; }

	void set_is_alive(bool alive) { is_alive = alive; }
	bool get_is_alive() { return is_alive; }
	void destroy_all_bullet();
	void check_bullet_out();
	void reset_boss();
protected:
	int x_val;
	int y_val;
	int step = BOSS_SPEED;
	int HP = BOSS_HP;
	bool is_alive ;

	Uint32 lastBulletTime;


	std::vector<std::vector<Bullet*>> bullets;

};


#endif // !BOSS_OBJECT_H

