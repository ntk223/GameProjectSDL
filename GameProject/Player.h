#ifndef PLAYER_H_
#define PLAYER_H_
#include "BaseObject.h"
#include "Bullet.h"


#define PLAYER_WIDTH  120
#define PLAYER_HEIGHT 75
#define PLAYER_SPEED  15

#define PLAYER_SHIED_WIDTH 120 
#define PLAYER_SHIELD_HEIGHT 120

#define MAX_PLAYER_LV 4

class Player :public BaseObject
{
public:
	Player();
	~Player();	
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void SetRect()
	{
		rect_.x = x_val;
		rect_.y = y_val;
		rect_.w = PLAYER_WIDTH;
		rect_.h = PLAYER_HEIGHT;

	}
	int get_x() { return x_val; }
	int get_y() { return y_val; }


	void Handle_input_action(SDL_Event e );
	void update();
	void Render(SDL_Renderer* des, const SDL_Rect* clip);

	void Set_bullets(std::vector<Bullet*>bullets_, int i ) { bullets[i] = bullets_; }
	std::vector<Bullet*> Get_bullets(int i) { return bullets[i]; }

	void Init_bullet(std::vector<Bullet*>& bullets_,int x_val_, int y_val_);
	
	bool get_ismove() { return is_move; }
	void check_bullet_out();
	bool get_type() { return type; }

	void set_level(int level_) { level = level_; }
	int get_level() { return level; }

	void set_shield(bool ret) { is_have_shield = ret;}
	bool get_shield() { return is_have_shield; }

	void set_speed(bool ret) { is_speed = ret; }
	bool get_speed() { return is_speed; }

	void set_slowed(bool ret) { is_slowed = ret; }
	bool get_slowed()  const { return is_slowed; }
	
	void sound();
	void Reset_bullet();
	void Reset_player();
protected:
	bool is_move;
	int x_speed = 0;
	int y_speed = 0; 
	int x_val;
	int y_val;
	std::vector<std::vector<Bullet*>> bullets;

	bool type = 1 ;

	int level = 0;
	bool is_have_shield;
	bool is_speed;
	bool is_slowed;
};


#endif // !

