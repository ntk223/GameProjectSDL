#ifndef BULLET_H
#define BULLET_H
#include "BaseObject.h"

#define BULLET_HEIGHT 10
#define BULLET_WIDTH 30
#define BULLET_SPEED 25
#define BULLET_DMG 1

#define BULLET_HEIGHT_ENEMY 15
#define BULLET_WIDTH_ENEMY 15

#define BULLET_HEIGHT_LASER 10
#define BULLET_WIDTH_LASER 800

#define ICE_BULLET_WIDTH 25
#define ICE_BULLET_HEIGHT 25

#define BULLET_SPEED_ENEMY 10



#define MAX_BULLET_ENEMY 3

class Bullet : public BaseObject
{
public:
	Bullet();
	~Bullet();

	void update();

	void update_enemy();

	bool get_is_move() { return is_move; }
	void set_is_move(bool is_move_) { is_move = is_move_; }

	void SetWidthHeight(const int &width,const int &height) 
	{
		rect_.w = width;
		rect_.h = height;
	}


	void reset(int x, int y)
	{
		x_val = x;
		y_val = y;
		is_move = false;
	}

	int get_x_val() const { return rect_.x; }
	void set_is_loaded(bool res) { is_loaded = res; }
	bool get_is_loaded() { return is_loaded; }
	// enemy
protected:
	int x_val;
	int y_val;
	bool is_move;
	bool is_loaded;


};


#endif // !BULLET_H


