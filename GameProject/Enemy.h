#ifndef ENEMY_H_
#define ENEMY_H_
#include "BaseObject.h"
#include "Player.h"
#include "Bullet.h"

#define MAX_ENEMY 3

#define ENEMY_WIDTH 40
#define ENEMY_HEIGHT 40
#define ENEMY_SPEED 3
#define ENEMY_HP 1 

#define ENEMY_MEDIUM_WIDTH 60
#define ENEMY_MEDIUM_HEIGHT 60
#define ENEMY_MEDIUM_HP 2 

#define UFO_WIDTH 80
#define UFO_HEIGHT 60
#define UFO_HP 3

#define METEORITE_WIDTH 80
#define METEORITE_HEIGHT 80
#define METEORITE_SPEED 3

#define delayTime 2000

const float AMPLITUDE = 100.0f;
const float FREQUENCY = 0.02f;

class Enemy :public BaseObject
{
public:
	Enemy();
	~Enemy();
	
	void SetRect(const int w , const int h )
	{
		rect_.x = x_val;
		rect_.y = y_val;
		rect_.w = w;
		rect_.h = h;
	}
	int random(int a , int b );
	void respawn();
	void Render(SDL_Renderer* des, const SDL_Rect* clip);


	void respawn_meteorite();
	void update_meteorite();

	void update();

	
	bool Get_is_out() const { return is_out; }

	bool get_is_move() { return is_move; }
	void set_is_move(bool is_move_) { is_move = is_move_; }

	void Set_bullets(std::vector<Bullet*> bullets_) { bullets = bullets_; }
	std::vector<Bullet*> Get_bullets() { return bullets; }

	void Init_bullet();

	void check_bullet_out();

	std::string getType() { return type; }
	void setType(const int n);

	void setSize(std::string size_) { Size = size_; }
	std::string getSize() { return Size; }

	void setHP(int hp_) { hp = hp_; }
	int getHP() { return hp; }

	void setRate_item() { rate_item = random(1, 20); }
	int getRate_item() { return rate_item; }

	int get_oy() { return Oy; }


protected:
	bool is_out;
	float x_val;
	float y_val;

	int Oy;
	bool is_move;
	int enemy_sp = 3;
	Uint32 lastBulletTime;
	std::vector<Bullet*> bullets;

	std::string Size;
	std::string type;

	int hp;
	int rate_item;



};


#endif // !ENEMY_H_
 