#ifndef ITEM_H
#define ITEM_H
#include "BaseObject.h"

#define HP_WIDTH 25 
#define HP_HEIGHT 25 

#define SHIELD_WIDTH 30
#define SHIELD_HEIGHT 30

#define UPGRADE_WIDTH 25
#define UPGRADE_HEIGHT 32

#define SPEED_WIDTH 32
#define SPEED_HEIGHT 25
#define ITEM_SPEED 5

const float AMPLITUDE_ = 100.0f;
const float FREQUENCY_ = 0.02f;

class Item : public BaseObject
{
public:
	Item();
	~Item();

	//int random(int a, int b);
	//void respawn();
	void update();
	void SetRect(const int w , const int h)
	{
		rect_.x = x_val;
		rect_.y = y_val;
		rect_.w = w;
		rect_.h =h;
	}
	void set_xy( const int x , const int y ) 
	{
		x_val = x;
		y_val = y;
	}
	bool get_isout() { return is_out; }
	void set_ismove(bool bool_) { is_move = bool_; }
	bool get_ismove() { return is_move; }
protected:
	int sp = ITEM_SPEED;
	bool is_move;
	bool is_out;

	int x_val;
	int y_val;



};
#endif // !ITEM_H

