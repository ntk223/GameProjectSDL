#include "Player.h"

Player::Player()
{
    level = 0;
	x_val = 10;
    y_val = (SCREEN_HEIGHT - PLAYER_HEIGHT)/2;
    is_move = false;
    is_speed = false;
    is_slowed = false;

    bullets.push_back(std::vector<Bullet*>());
    bullets.push_back(std::vector<Bullet*>());
    bullets.push_back(std::vector<Bullet*>());
    bullets.push_back(std::vector<Bullet*>());
    bullets.push_back(std::vector<Bullet*>());


	
}
Player::~Player()
{
    Free();
}

void Player::sound()
{
    Mix_Chunk* gunshotSound = Mix_LoadWAV("sound/Gun+Silencer.mp3");
    Mix_VolumeChunk(gunshotSound, MIX_MAX_VOLUME / 4);
    Mix_PlayChannel(-1, gunshotSound, 0);
}
void Player::Init_bullet (std::vector<Bullet*>&bullets_, int x_val_, int y_val_)
{
    
    if (bullets_.size() < 5)
    {
        Bullet* bullet = new Bullet();
        bullet->SetWidthHeight(BULLET_WIDTH, BULLET_HEIGHT);

        bullet->SetRect(this->x_val + PLAYER_WIDTH + x_val_, this->y_val +y_val_ + PLAYER_HEIGHT / 2 - BULLET_HEIGHT / 2, BULLET_WIDTH, BULLET_HEIGHT);
        bullet->set_is_move(true);
   
        bullets_.push_back(bullet);
        
    }
}


void Player ::Handle_input_action(SDL_Event e)
{
    int step;
    if (is_speed) step = 10;
    else step = 0;
    if (is_slowed) step = -10;
    switch (e.type) 
    {
        case SDL_KEYDOWN:
            is_move = true;
            switch (e.key.keysym.sym) 
            {
            case SDLK_w:
                y_speed = -PLAYER_SPEED- step;
                break;
            case SDLK_s:
                y_speed = PLAYER_SPEED + step;
                break;
            case SDLK_a:
                x_speed = -PLAYER_SPEED- step;
                break;
            case SDLK_d:
                x_speed = PLAYER_SPEED + step;
                break;
            //case SDLK_SPACE:
                

            }
            break;
        case SDL_KEYUP:
            is_move = false;
            switch (e.key.keysym.sym)
            {
            case SDLK_w:
                y_speed = 0;
                break;
            case SDLK_s:
                y_speed = 0;
                break;
            case SDLK_a:
                x_speed = 0;
                break;
            case SDLK_d:
                x_speed = 0;
                break;
         

            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            /*switch (e.button.button)
            {
            case SDL_BUTTON_LEFT:
                type = true;
                break;
            case SDL_BUTTON_RIGHT:
                type = true;
                break;
            }*/
            if (level == 0)
            {
                if (bullets[0].size() < 5)
                {
                    Init_bullet(bullets[0], 0, 0);
                    sound();
                }
            }

            else if (level == 1)
            {
                if (bullets[0].size() + bullets[1].size() < 10)
                {
                    Init_bullet(bullets[0], -40, 20);
                    Init_bullet(bullets[1], -40, -20);
                    sound();
                }
            }

            else if (level == 2)
            {
                if (bullets[0].size() + bullets[1].size() + bullets[2].size() < 15)
                {
                    Init_bullet(bullets[0], 0, 0);
                    Init_bullet(bullets[1], -40, 30);
                    Init_bullet(bullets[2], -40, -30);
                    sound();
                }
            }
            else if (level == 3)
            {
                if (bullets[0].size() + bullets[1].size() + bullets[2].size() + bullets[3].size()< 20)
                {
                    Init_bullet(bullets[0], 0, 15);
                    Init_bullet(bullets[1], -40, 40);
                    Init_bullet(bullets[2], -40, -40);
                    Init_bullet(bullets[3], 0, -15);


                    sound();
                }
            }
            else if (level == 4)
            {
                if (bullets[0].size() + bullets[1].size() + bullets[2].size() 
                    + bullets[3].size() + bullets[4].size()< 25)
                {
                    Init_bullet(bullets[0], 0, 0);
                    Init_bullet(bullets[1], -50, 40);
                    Init_bullet(bullets[2], -50, -40);
                    Init_bullet(bullets[3], -20, -20);
                    Init_bullet(bullets[4], -20, 20);


                    sound();
                }
            }

            break;

    }
 }
    

void Player::update() 
{
    if ( x_val+x_speed <= SCREEN_WIDTH - PLAYER_WIDTH && x_val+ x_speed >= 0 ) 
        x_val += x_speed;

    if (y_val +y_speed < SCREEN_HEIGHT - PLAYER_HEIGHT && y_val + y_speed  >= 0 ) 
        y_val += y_speed;
}

bool Player::LoadImg(std::string path, SDL_Renderer* screen)
{	
	bool ret =BaseObject::LoadImg(path, screen);
	return ret;
}


void Player::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
    SDL_Rect renderquad = Player::GetRect();
	SDL_RenderCopy(des, BaseObject::GetObject(), clip, &renderquad);
}

void Player::check_bullet_out()
{
    for (int j = 0; j <= level;j++)
    {
        for (int i = 0; i < bullets[j].size(); i++)
        {
            Bullet* bullet = bullets[j].at(i);
            if (bullet->get_x_val() > SCREEN_WIDTH - BULLET_WIDTH)
            {
                bullet = NULL;
                bullets[j].erase(bullets[j].begin() + i);
            }
        }
    }
}

void Player:: Reset_bullet()
{
    for (int j = 0; j <= MAX_PLAYER_LV; j++)
    {
        for (size_t i = 0; i < bullets[j].size(); ++i) {
            delete bullets[j][i];
        }
        bullets[j].clear();
    }
}

void Player::Reset_player()
{
    x_val = 10;
    y_val = (SCREEN_HEIGHT - PLAYER_HEIGHT) / 2;
    level = 0;
    is_move = false;
    is_speed = false;
    is_slowed = false;
    Reset_bullet();
}
