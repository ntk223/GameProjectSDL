#include "Item.h"


Item::Item()
{
	x_val = 0;
	y_val = 0;
	is_move = false;
	is_out = false;

}

Item::~Item()
{

}



void Item::update()
{
	x_val -= 10;
	//y_val = Oy / 2 + AMPLITUDE_ * std::sin(FREQUENCY_ * x_val);
	if (x_val < 0|| y_val< 0 || y_val > SCREEN_HEIGHT - rect_.h)
	{
		is_out = true;
	}
	
}