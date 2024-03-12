#include "CommonFunc.h"
#include "BaseObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "TextObject.h"
#include "Item.h"
#include "BossObject.h"


//time
Uint32 startTime;
Uint32 currentTime;
Uint32 elapsedTime;

Uint32 respawnTime;
Uint32 start_respawnTime;

Uint32 respawnUFOTime;
Uint32 start_respawnUFOTime;

Uint32 start_speedTime;
Uint32 current_speedTime;
Uint32 elapsed_speedTime;


Uint32 start_slowedTime;
Uint32 current_slowedTime;
Uint32 elapsed_slowedTime;



//bg
BaseObject g_background;
BaseObject g_background2;
BaseObject g_background3;
BaseObject g_background4;

const int map_sp = 1;


///pause

BaseObject pause_icon;
BaseObject pause_menu;
TextObject resume;
TextObject main_menu;
TextObject replay;
bool on_pause_menu = false;


//enenmy
std::vector<Enemy*>s_enemies;
std::vector<Enemy*>meteorites;
std::vector<Enemy*>m_enemies;
std::vector<Enemy*>ufo_enemies;

BossObject* Boss_enemy = new BossObject();


//game_play
Item* hp_item;
Item* upgrade_item;
Item* shield_item;
Item* speed_item;

Player g_player;

std::vector<BaseObject*> HP;

BaseObject shield_player;
int score_ = 0;
TextObject score;
bool gameoverDisplayed = false;
TextObject gameover;
TextObject reset_text;

//menu
BaseObject howto;
BaseObject g_menu;
TextObject playgame;
TextObject how_to_play;
TextObject name_game;
bool on_menu = true;
bool on_howto_menu = false;
 //INIT
bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
    {
        return false;
    }

    if (TTF_Init() < 0)
    {
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    // kich thuoc cua so man hinh
    g_window = SDL_CreateWindow("GameProject", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);


    if (g_window == NULL) success = false;
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED); //  man hinh
    }

    if (g_screen == NULL) success = false;
    else
    {
        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);

        int imgflag = IMG_INIT_PNG;
        if (!(IMG_Init(imgflag) && imgflag)) success = false;

    }
    return success;
}

void InitSound()
{
    backgroundMusic = Mix_LoadMUS("sound/background.mp3");
    gunshotSound = Mix_LoadWAV("sound/Gun+Silencer.mp3");
    boomSound= Mix_LoadWAV("sound/boom.wav");
    collectSound = Mix_LoadWAV("sound/collect.mp3");

}

// load text
void Text_playgame()
{
    playgame.SetText("PLAY GAME");
    playgame.LoadText("font/Games.ttf", g_screen);
    playgame.SetRect(SCREEN_WIDTH / 2 - 150, 250, 300, 60);
}
void Text_howtoplay()
{
    how_to_play.SetText("HOW TO PLAY?");
    how_to_play.LoadText("font/Games.ttf", g_screen);
    how_to_play.SetRect(SCREEN_WIDTH / 2 - 175, 350, 350, 60);
}
void Text_name_game()
{
    name_game.SetText("SPACE WAR");
    name_game.LoadText("font/Games.ttf", g_screen);
    name_game.SetRect(SCREEN_WIDTH / 2 - 250, 50, 500, 100);
}

void Text_score()
{
    score.SetText("Score: " + std::to_string(score_));
    score.LoadText("font/Games.ttf", g_screen);
    score.SetRect(SCREEN_WIDTH / 2- 115, 10, 230, 30);
}
void Text_gameover()
{
    gameover.SetText("GAME OVER!");
    gameover.LoadText("font/Games.ttf", g_screen);
    gameover.SetRect(SCREEN_WIDTH / 2 - 200, 250, 400, 100);
}
void Text_reset()
{
    reset_text.SetText("Press 'R' to Replay Game!");
    reset_text.LoadText("font/Games.ttf", g_screen);
    reset_text.SetRect(SCREEN_WIDTH / 2 - 150, 370, 300, 20);
}

void Text_pause()
{
    resume.SetText("RESUME");
    resume.LoadText("font/Games.ttf", g_screen);
    resume.SetRect(SCREEN_WIDTH / 2 - 125, 200, 250 , 50);

    replay.SetText("REPLAY");
    replay.LoadText("font/Games.ttf", g_screen);
    replay.SetRect(SCREEN_WIDTH / 2 - 125, 290, 250, 50);

    main_menu.SetText("MAIN MENU");
    main_menu.LoadText("font/Games.ttf", g_screen);
    main_menu.SetRect(SCREEN_WIDTH / 2 - 150, 380, 300, 50);
}

//load img
void Load_pause_icon()
{
    pause_icon.SetRect(SCREEN_WIDTH - 50 - 10, 10, 50, 50);
    pause_icon.LoadImg("img/pause_icon.png", g_screen);
}

void Load_pause_menu()
{
    pause_menu.SetRect(220, 125, SCREEN_WIDTH - 440, SCREEN_HEIGHT - 250);
    pause_menu.LoadImg("img/pause_menu.png", g_screen);
}

bool Loadhowto_menu()
{
    howto.SetRect(220, 125, SCREEN_WIDTH-440, SCREEN_HEIGHT-250);
    bool ret =howto.LoadImg("img/howto.png", g_screen);
    return ret;
}
bool Load_Menu()
{
    g_menu.SetRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    bool ret = g_menu.LoadImg("img/menu.png", g_screen);
    return ret;

}
bool LoadBackground()
{
    g_background.SetRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    bool ret = g_background.LoadImg("img/paralax_space1.png", g_screen);
    return ret;
}


bool LoadBackground_2()
{
    g_background2.SetRect(SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    bool ret = g_background2.LoadImg("img/paralax_space2.png", g_screen);
    return ret;
}
bool LoadBackground_3()
{
    g_background3.SetRect(2*SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    bool ret = g_background3.LoadImg("img/paralax_space3.png", g_screen);
    return ret;
}
bool LoadBackground_4()
{
    g_background4.SetRect(3 * SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    bool ret = g_background4.LoadImg("img/paralax_space4.png", g_screen);
    return ret;
}


//player
void LoadPLayer()
{
    if (g_player.get_ismove()) bool ret = g_player.LoadImg("img/player1.png", g_screen);
    else bool ret = g_player.LoadImg("img/player.png", g_screen);
}

void Init_hp()
{
    int x = 10;
    while (HP.size() < MAX_HP)
    {
        BaseObject* hp = new BaseObject;
        hp->LoadImg("img/hp.png", g_screen);
        hp->SetRect(x, 10, 31, 30);
        HP.push_back(hp);
        x += 40;
    }
}

// item
void Init_speeditem()
{
    speed_item = new Item();
    bool ret = speed_item->LoadImg("img/speed_item.png", g_screen);
}
void Init_hpitem()
{
    hp_item = new Item();
    bool ret = hp_item->LoadImg("img/hp.png", g_screen);
}

void Init_upgrade_item()
{
    upgrade_item = new Item();
    bool ret = upgrade_item->LoadImg("img/upgrade_item.png", g_screen);
}

void Init_shield_item()
{
    shield_item = new Item();
    bool ret = shield_item->LoadImg("img/shield.png", g_screen);
}

void Init_shield()
{
    bool ret = shield_player.LoadImg("img/shield.png", g_screen);
}

void Render_item(Item* &item)
{
    if (item != NULL)
    {
        item->Render(g_screen, NULL);
        if (item->get_isout())
        {
            item = new Item();
        }
    }

}

//enemy 
void respawn_item(Enemy* enemy )
{
    if (enemy->getRate_item() == 1)
    {
        if (!hp_item->get_ismove())
        {
            Init_hpitem();
            hp_item->set_ismove(true);
            hp_item->set_xy(enemy->GetRect().x, enemy->GetRect().y);
        }
    }
    else if (enemy->getRate_item() == 2)
    {
        if (!upgrade_item->get_ismove()) 
        {
            Init_upgrade_item();
            upgrade_item->set_ismove(true);
            upgrade_item->set_xy(enemy->GetRect().x, enemy->GetRect().y);
        }
    }
    else if (enemy->getRate_item() == 3)
    {
        if (!shield_item->get_ismove())
        {
            Init_shield_item();
            shield_item->set_ismove(true);
            shield_item->set_xy(enemy->GetRect().x, enemy->GetRect().y);
        }
    }
    else if (enemy->getRate_item() == 4)
    {
        if (!speed_item->get_ismove())
        {
            Init_speeditem();
            speed_item->set_ismove(true);
            speed_item->set_xy(enemy->GetRect().x, enemy->GetRect().y);
        }
    }

}
void remove_enemy(int idx, std::vector<Enemy*>& enemies)
{
    if (idx < enemies.size())
    {
        Enemy* enemy = enemies.at(idx);
        enemy = NULL;
        enemies.erase(enemies.begin() + idx);
    }
}

void update_enemy(std::vector<Enemy*>& enemies, const int w , const int h)
{
    for (int en = 0; en < enemies.size(); en++)
    {
        Enemy* enemy = enemies.at(en);
        if (enemy != NULL)
        {
            enemy->SetRect(w, h);
            enemy->update();
            for (int bl = 0; bl < enemy->Get_bullets().size(); bl++)
            {
                std::vector <Bullet*> bullets = enemy->Get_bullets();
                Bullet* bullet = bullets.at(bl);
                if (!bullet->get_is_loaded())
                {
                    if (enemy->getSize() == "m") bullet->set_is_loaded(bullet->LoadImg("img/enemy/laser.png", g_screen));
                    else if (enemy->getSize() == "ufo") bullet->set_is_loaded(bullet->LoadImg("img/enemy/ice_bullet.png", g_screen));

                    else bullet->set_is_loaded(bullet->LoadImg("img/enemy/bullet_enemy.png", g_screen));
                }
                if (bullet != NULL)
                {

                    if (bullet->get_is_move())
                    {
                        bullet->update_enemy(   );
                    }
                    enemy->check_bullet_out();
                }
            }
        }
    }
}

void render_enemy(std::vector<Enemy*>& enemies)
{
    for (int en = 0; en < enemies.size(); en++)
    {
        Enemy* enemy = enemies.at(en);
        if (enemy != NULL)
        {
            enemy->Render(g_screen, NULL);
            for (int bl = 0; bl < enemy->Get_bullets().size(); bl++)
            {
                std::vector <Bullet*> bullets = enemy->Get_bullets();
                Bullet* bullet = bullets.at(bl);
                if (bullet != NULL)
                {
                    if (bullet->get_is_move())
                    {
                        bullet->Render(g_screen, NULL);
                    }
                }
            }
            if (enemy->Get_is_out())
            {
                remove_enemy(en, enemies);;
                HP.pop_back();
            }

        }
    }
}
void Init_meteorite()
{
    while (meteorites.size() < 3)
    {
        
        Enemy* meteorite = new Enemy();
        meteorite->respawn_meteorite();
       // meteorite->SetRect(METEORITE_WIDTH, METEORITE_HEIGHT);
        bool  ret = meteorite->LoadImg("img/enemy/meteorite.png", g_screen);
        meteorites.push_back(meteorite);

    }
}
void InitEnemy()
{
    while ( s_enemies.size() < MAX_ENEMY)
    {
        Enemy* enemy = new Enemy();
        enemy->setSize("s");
        enemy->setRate_item();
        enemy->setHP(ENEMY_HP);
        enemy->setType(5);
        bool ret = enemy->LoadImg("img/enemy/enemy"+enemy->getType() + ".png", g_screen);
        
        s_enemies.push_back(enemy);
    }
}

void InitEnemy_M()
{
    while (m_enemies.size() < MAX_ENEMY)
    {
        Enemy* enemy = new Enemy();
        enemy->setRate_item();

        enemy->setHP(ENEMY_MEDIUM_HP);
        enemy->setSize("m");
        enemy->setType(4);
        bool ret = enemy->LoadImg("img/enemy/enemy_m" + enemy->getType() + ".png", g_screen);

        m_enemies.push_back(enemy);
    }
}
void InitEnemy_UFO()
{
    while (ufo_enemies.size() < MAX_ENEMY)
    {
        Enemy* enemy = new Enemy();
        enemy->setRate_item();

        enemy->setHP(UFO_HP);
        enemy->setSize("ufo");
        enemy->setType(4);
        bool ret = enemy->LoadImg("img/enemy/ufo.png", g_screen);

        ufo_enemies.push_back(enemy);
    }
}

void InitEnemy_Bullet(std::vector<Enemy*>& enemies)
{
    for (int en = 0; en < enemies.size(); en++)
    {
        Enemy* enemy = enemies.at(en);
        enemy->Init_bullet();
    }
}



//////////



void Init_boss()
{
    Boss_enemy->LoadImg("img/boss1.png", g_screen);
    //Boss_enemy->Init_bullet();
}
void remove_meteorite(int idx)
{
    if (idx < meteorites.size())
    {
        Enemy* meteorite = meteorites.at(idx);
        meteorite = NULL;
        meteorites.erase(meteorites.begin() + idx);
    }
}
// va cham
bool checkCollision(SDL_Rect a, SDL_Rect b) {
    // Xác định các biên của hai hình chữ nhật
    int leftA = a.x;
    int rightA = a.x + a.w;
    int topA = a.y;
    int bottomA = a.y + a.h;

    int leftB = b.x;
    int rightB = b.x + b.w;
    int topB = b.y;
    int bottomB = b.y + b.h;

    // Kiểm tra va chạm theo hướng ngang và hướng dọc
    if (rightA >= leftB && leftA <= rightB && bottomA >= topB && topA <= bottomB) {
        return true; // Có va chạm
    }

    return false; // Không có va chạm
}

void Collision_p_e(std::vector<Enemy*>&enemies)
{
    for (int en = 0; en < enemies.size(); en++)
    {
        Enemy* enemy = enemies.at(en);
        std::vector<Bullet*> bullets_enemy = enemy->Get_bullets();
        for (int bl = 0; bl < enemy->Get_bullets().size(); bl++)
        {
            Bullet* bullet = bullets_enemy.at(bl);
            bool check2 = checkCollision(g_player.GetRect(), bullet->GetRect());
            if (check2)
            {
                Mix_PlayChannel(-1, boomSound, 0);
                bullet = NULL;
                bullets_enemy.erase(bullets_enemy.begin() + bl);
                enemy->Set_bullets(bullets_enemy);

                if (!g_player.get_shield())
                {
                    if (enemy->getSize() == "ufo")
                    {
                        g_player.set_slowed(true);
                        start_slowedTime = SDL_GetTicks();
                    }

                    if (HP.size() > 0) HP.pop_back();
                    if (g_player.get_level() > 0)
                    {
                        g_player.set_level(g_player.get_level() - 1);
                        g_player.Reset_bullet();
                    }

                }
            }
        }

        bool check3 = checkCollision(g_player.GetRect(), enemy->GetRect());
        if (check3)
        {
            Mix_PlayChannel(-1, boomSound, 0);
            remove_enemy(en, enemies);
            en--;

            if (!g_player.get_shield())
            {
                if (HP.size() > 0) HP.pop_back();
                if (g_player.get_level() > 0)
                {
                    g_player.set_level(g_player.get_level() - 1);
                    g_player.Reset_bullet();

                }

            }
        }

        if (en == -1) en++;

        // bullet player - enemy
        for (int i = 0; i <= g_player.get_level(); i++)
        {
            std::vector<Bullet*> bullets = g_player.Get_bullets(i);
            for (int bl = 0; bl < bullets.size(); bl++)
            {
                Bullet* bullet = bullets.at(bl);
                bool check4 = checkCollision(bullet->GetRect(), enemy->GetRect());
                if (check4)
                {
                    enemy->setHP(enemy->getHP() - BULLET_DMG);
                    bullet = NULL;
                    bullets.erase(bullets.begin() + bl);
                    g_player.Set_bullets(bullets, i);
                }
                if (enemy->getHP() <= 0)
                {
                    score_++;
                    respawn_item(enemy);
                    remove_enemy(en, enemies);  
                }
            }
        }
    }
}

void checkCollision_play() 
{
    bool check6 = checkCollision(g_player.GetRect(), speed_item->GetRect());
    if (check6)
    {
        start_speedTime = SDL_GetTicks();
        Mix_PlayChannel(-1, collectSound, 0);
        g_player.set_speed(true);
        speed_item = new Item();
    }
    bool check5 = checkCollision(g_player.GetRect(), shield_item->GetRect());
    if (check5)
    {
        startTime = SDL_GetTicks();
        Mix_PlayChannel(-1, collectSound, 0);
        g_player.set_shield(true);
        shield_item = new Item();
    }
    bool check = checkCollision(g_player.GetRect(), upgrade_item->GetRect());
    if (check)
    {
        Mix_PlayChannel(-1, collectSound, 0);
        g_player.Reset_bullet();
        if (g_player.get_level() < MAX_PLAYER_LV)g_player.set_level(g_player.get_level() + 1);
        upgrade_item = new Item();

    }
    bool check1 = checkCollision(g_player.GetRect(), hp_item->GetRect());
    if (check1)
    {
        BaseObject* hp = new BaseObject;
        hp->LoadImg("img/hp.png", g_screen);
        hp->SetRect(HP.back()->GetRect().x + 40, 10, 31, 30);
        HP.push_back(hp);
        Mix_PlayChannel(-1, collectSound, 0);
        hp_item = new Item();

    }

    // collision enemy
    for (int mt = 0; mt < meteorites.size(); mt++)
    {
        Enemy* meteorite = meteorites.at(mt);
        bool check = checkCollision(meteorite->GetRect(), g_player.GetRect());
        if (check)
        {
            remove_meteorite(mt);
            if (!g_player.get_shield())
            {

                HP.pop_back();
                if (g_player.get_level() > 0) 
                {
                    g_player.set_level(g_player.get_level() - 1);
                    g_player.Reset_bullet();
                }
            }

            Mix_PlayChannel(-1, boomSound, 0);

        }
    }
    Collision_p_e(s_enemies);
    Collision_p_e(m_enemies);
    Collision_p_e(ufo_enemies);


}



// close
void close_menu()
{
    g_menu.Free();
    playgame.Free();
    how_to_play.Free();
    name_game.Free();
}

void close()
{
    for (int j = 0; j <= MAX_PLAYER_LV; j++)
    {
        for (int i = 0; i < g_player.Get_bullets(j).size(); i++)
        {
            std::vector <Bullet*> bullets = g_player.Get_bullets(j);
            Bullet* bullet = bullets.at(i);
            if (bullet != NULL)
            {
                bullet->Free();
            }
        }
    }
    g_player.Free();
    g_background.Free();
    for (int en = 0; en< s_enemies.size(); en++)
    {
        Enemy* enemy = s_enemies.at(en);
        if (enemy != NULL)
        {
            enemy->Free();
        }
    }
    for (int en = 0; en < m_enemies.size(); en++)
    {
        Enemy* enemy = m_enemies.at(en);
        if (enemy != NULL)
        {
            enemy->Free();
        }
    }
    for (int en = 0; en < ufo_enemies.size(); en++)
    {
        Enemy* enemy = ufo_enemies.at(en);
        if (enemy != NULL)
        {
            enemy->Free();
        }
    }
    score.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;
    Mix_FreeMusic(backgroundMusic);
    Mix_FreeChunk(gunshotSound);
    Mix_FreeChunk(boomSound);

    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void reset()
{
    g_player.Reset_player();

    for (int en = 0; en < s_enemies.size(); en++)
    {
        delete s_enemies[en];
    }
    s_enemies.clear();
    for (int en = 0; en < m_enemies.size(); en++)
    {
        delete m_enemies[en];
    }
    m_enemies.clear();
    for (int en = 0; en < ufo_enemies.size(); en++)
    {
        delete ufo_enemies[en];
    }
    ufo_enemies.clear();
    for (int hp_ = 0; hp_ < HP.size(); hp_++)
    {
        delete HP[hp_];
    }
    HP.clear();
    for (int mt = 0; mt < meteorites.size(); mt++)
    {
        delete meteorites[mt];
    }
    meteorites.clear();
    Init_hp();
    Init_hpitem();
    Init_upgrade_item();
    Init_shield_item();
    Init_speeditem();

    gameoverDisplayed = false;
    on_pause_menu = false;
    on_howto_menu = false;

    start_respawnTime = SDL_GetTicks();
    start_respawnUFOTime = SDL_GetTicks();
    respawnTime = 0;
    respawnUFOTime = 0;


    score_ = 0;
    g_background.SetRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    g_background2.SetRect(SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    g_background3.SetRect(2 * SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    g_background4.SetRect(3 * SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

}

// MAIN
int main(int argc, char* argv[]){
    if (InitData() == false) return -1;
    if (LoadBackground() == false) return -1;
    if (LoadBackground_2() == false) return -1;
    if (LoadBackground_3() == false) return -1;
    if (LoadBackground_4() == false) return -1;

    if (Load_Menu() == false) return -1;
    if (Loadhowto_menu() == false) return -1;

    Load_pause_icon();
    Load_pause_menu();

    Init_hp();
    InitSound();
    Mix_PlayMusic(backgroundMusic, -1);

    Text_gameover();
    Text_reset();
    Init_hpitem();
    Init_upgrade_item();
    Init_shield_item();
    Init_speeditem();

    Init_shield();

    Text_name_game();

    Init_boss();


    bool is_quit = false; 
    bool isPaused = true;
    int mouseX, mouseY;
    SDL_Rect mouse;

    while (!is_quit)
    {

        //event 
        while (SDL_PollEvent(&g_event))
        {
            
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            if (on_menu)
            {
                Text_playgame();
                Text_howtoplay();
                if (g_event.type == SDL_MOUSEMOTION)
                {

                    SDL_GetMouseState(&mouseX, &mouseY);
                    SDL_Rect mouse = { mouseX , mouseY , 1 , 1 };
                    bool check = checkCollision(playgame.GetRect(), mouse);
                    bool check2 = checkCollision(how_to_play.GetRect(), mouse);                  

                    if (check) playgame.SetColor_R();
                    else playgame.SetColor_W();

                    if (check2)  how_to_play.SetColor_R();
                    else how_to_play.SetColor_W();

                }
                else if (g_event.type == SDL_MOUSEBUTTONDOWN )
                {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    SDL_Rect mouse = { mouseX , mouseY , 1 , 1 };
                    SDL_Rect quit_howto = { 220 + SCREEN_WIDTH - 440 - 70, 125 + 55, 25, 25 };

                    bool check = checkCollision(playgame.GetRect(), mouse);
                    bool check2 = checkCollision(how_to_play.GetRect(), mouse);
                    bool check3 = checkCollision(quit_howto, mouse);

                    if (check && !on_howto_menu)
                    {
                        start_respawnTime = SDL_GetTicks();
                        start_respawnUFOTime = SDL_GetTicks();
                        isPaused = false;
                        on_menu = false;
                        SDL_RenderClear(g_screen);

                        g_background.Render(g_screen, NULL);
                        SDL_RenderPresent(g_screen);
                        SDL_Delay(250);

                    }
                    if (check2)
                    {
                        on_howto_menu = true;
                    }
                    if (check3)
                    {
                        on_howto_menu = false;
                    }

                }
            }
            

            else
            {

                if (g_event.type == SDL_MOUSEBUTTONDOWN && !on_pause_menu && !gameoverDisplayed)
                {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    SDL_Rect mouse = { mouseX , mouseY , 1 , 1 };
                    bool check = checkCollision(pause_icon.GetRect(), mouse);
                    if (check)
                    {
                        isPaused = true;
                        on_pause_menu = true;
                    }

                }
                if (on_pause_menu)
                {
                    Text_pause();

                    if (g_event.type == SDL_MOUSEMOTION && isPaused)
                    {

                        SDL_GetMouseState(&mouseX, &mouseY);
                        SDL_Rect mouse = { mouseX , mouseY , 1 , 1 };
                        bool check2 = checkCollision(resume.GetRect(), mouse);
                        bool check4 = checkCollision(replay.GetRect(), mouse);

                        bool check3 = checkCollision(main_menu.GetRect(), mouse);


                        if (check2) resume.SetColor_R();
                        else resume.SetColor_W();

                        if (check3)  main_menu.SetColor_R();
                        else main_menu.SetColor_W();

                        if (check4) replay.SetColor_R();
                        else replay.SetColor_W();

                    }
                    if (g_event.type == SDL_MOUSEBUTTONDOWN && !gameoverDisplayed)
                    {
                        SDL_GetMouseState(&mouseX, &mouseY);
                        SDL_Rect mouse = { mouseX , mouseY , 1 , 1 };
                        bool check2 = checkCollision(resume.GetRect(), mouse);
                        bool check3 = checkCollision(main_menu.GetRect(), mouse);
                        bool check4 = checkCollision(replay.GetRect(), mouse);

                        if (check2)
                        {
                            isPaused = false;
                            on_pause_menu = false;
                        }
                        if (check3)
                        {
                            on_menu = true;
                            reset();
                        }
                        if (check4)
                        {
                            isPaused = false;
                            reset();
                        }

                    }
                }
                else
                {

                    g_player.Handle_input_action(g_event);
                    if (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_r)
                    {
                        isPaused = false;
                        reset();
                    }
                }
            }
        }

        if (on_menu)
        {
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
            SDL_RenderClear(g_screen);

            g_menu.Render(g_screen, NULL);
            name_game.Render(g_screen, NULL);
            playgame.Render(g_screen, NULL);
            how_to_play.Render(g_screen, NULL);
            if (on_howto_menu)
            {
                howto.Render(g_screen, NULL);
            }

            SDL_RenderPresent(g_screen);
            SDL_Delay(16);

        }

        //update 
        else {
            if (!isPaused)
            {
                

                Init_meteorite();
                respawnTime = SDL_GetTicks();
                respawnUFOTime = SDL_GetTicks();
                if (respawnTime - start_respawnTime > 15000)
                {
                    InitEnemy_M();
                    InitEnemy_Bullet(m_enemies);
                }
                if (respawnUFOTime - start_respawnUFOTime > 25000)
                {
                    InitEnemy_UFO();
                    InitEnemy_Bullet(ufo_enemies);
                }
                

                InitEnemy();
                InitEnemy_Bullet(s_enemies);


                Text_score();
                LoadPLayer();

                // item 
                if (speed_item != NULL)
                {
                    speed_item->SetRect(SPEED_WIDTH, SPEED_HEIGHT);
                    speed_item->update();
                }
                if (hp_item != NULL)
                {
                    hp_item->SetRect(HP_WIDTH, HP_HEIGHT);
                    hp_item->update();
                }
                if (upgrade_item != NULL)
                {
                    upgrade_item->SetRect(UPGRADE_WIDTH, UPGRADE_HEIGHT);
                    upgrade_item->update();
                }
                if (shield_item != NULL)
                {
                    shield_item->SetRect(SHIELD_WIDTH, SHIELD_HEIGHT);
                    shield_item->update();
                }
                if (g_player.get_shield())
                {
                    shield_player.SetRect(g_player.GetRect().x, g_player.GetRect().y + PLAYER_HEIGHT/2- PLAYER_SHIELD_HEIGHT/2,
                                           PLAYER_SHIED_WIDTH, PLAYER_SHIELD_HEIGHT);
                }

                currentTime = SDL_GetTicks();
                elapsedTime = currentTime - startTime;
                if (elapsedTime > 5000) g_player.set_shield(false);

                current_speedTime = SDL_GetTicks();
                elapsed_speedTime = current_speedTime - start_speedTime;
                if (elapsed_speedTime > 5000) g_player.set_speed(false);

                current_slowedTime = SDL_GetTicks();
                elapsed_slowedTime = current_slowedTime - start_slowedTime;
                if (elapsed_slowedTime > 5000) g_player.set_slowed(false);

                for (int i = 0; i <= g_player.get_level(); i++)
                {
                    for (int bl = 0; bl < g_player.Get_bullets(i).size(); bl++)
                    {
                        std::vector <Bullet*> bullets = g_player.Get_bullets(i);
                        Bullet* bullet = bullets.at(bl);

                        if (!bullet->get_is_loaded())
                        {
                            if (g_player.get_type()) bullet->set_is_loaded(bullet->LoadImg("img/bullet.png", g_screen));

                            else bullet->set_is_loaded(bullet->LoadImg("img/bullet2.png", g_screen));
                        }
                        if (bullet != NULL)
                        {
                            if (bullet->get_is_move())
                            {
                                bullet->update();
                            }
                        }
                    }
                }

                g_player.check_bullet_out();
                g_player.SetRect();
                g_player.update();

                //enemy
                //boss
                Boss_enemy->update();
                Boss_enemy->SetRect(BOSS_WITDH, BOSS_HEIGHT);
                for (int i = 0; i < MAX_BULLET_BOSS; i++)
                {
                    for (int bl = 0; bl < Boss_enemy->Get_bullets(i).size(); bl++)
                    {
                        std::vector <Bullet*> bullets = Boss_enemy->Get_bullets(i);
                        Bullet* bullet = bullets.at(bl);
                        
                        if ( i == 0 || i == 3 || i == 4) bullet->set_is_loaded(bullet->LoadImg("img/enemy/laser.png", g_screen));
                        else bullet->set_is_loaded(bullet->LoadImg("img/enemy/ice_bullet.png", g_screen));

                        if (bullet != NULL)
                        {
                            if (bullet->get_is_move())
                            {
                                bullet->update_enemy();
                            }
                        }
                    }
                }

                for (int mt = 0;mt < meteorites.size(); mt++)
                {
                    Enemy* meteorite = meteorites.at(mt);
                    meteorite->SetRect(METEORITE_WIDTH, METEORITE_HEIGHT);
                    meteorite->update_meteorite();
                    
                }
                update_enemy(s_enemies, ENEMY_WIDTH, ENEMY_HEIGHT);
                update_enemy(m_enemies, ENEMY_MEDIUM_WIDTH, ENEMY_MEDIUM_HEIGHT);
                update_enemy(ufo_enemies, UFO_WIDTH, UFO_HEIGHT);


                g_background.SetRect(g_background.GetRect().x- map_sp, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                g_background2.SetRect(g_background2.GetRect().x - map_sp, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                g_background3.SetRect(g_background3.GetRect().x - map_sp, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                g_background4.SetRect(g_background4.GetRect().x - map_sp, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

                if (g_background4.GetRect().x <= 0)
                {
                    g_background.SetRect(SCREEN_WIDTH + g_background4.GetRect().x, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                }

                if (g_background3.GetRect().x <= 0)
                {
                    g_background4.SetRect(SCREEN_WIDTH + g_background3.GetRect().x, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                }
                                                                            
                if (g_background2.GetRect().x <= 0)
                {
                    g_background3.SetRect(SCREEN_WIDTH + g_background2.GetRect().x, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                }
                if (g_background.GetRect().x <= 0) 
                {
                    g_background2.SetRect(g_background.GetRect().x + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                }
                                                                   



                //render 
                SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
                SDL_RenderClear(g_screen);
                g_background.Render(g_screen, NULL);
                g_background2.Render(g_screen, NULL);
                g_background3.Render(g_screen, NULL);
                g_background4.Render(g_screen, NULL);



                pause_icon.Render(g_screen, NULL);
                
                g_player.Render(g_screen, NULL);
                for (int i = 0; i <= g_player.get_level(); i++)
                {
                    for (int bl = 0; bl < g_player.Get_bullets(i).size(); bl++)
                    {
                        std::vector <Bullet*> bullets = g_player.Get_bullets(i);
                        Bullet* bullet = bullets.at(bl);
                        if (bullet != NULL)
                        {
                            if (bullet->get_is_move())
                            {
                                bullet->Render(g_screen, NULL);
                            }
                        }
                    }
                }
                if (g_player.get_shield())
                {
                    shield_player.Render(g_screen, NULL);
                }

                // item
                Render_item(hp_item);
                Render_item(upgrade_item);
                Render_item(shield_item);
                Render_item(speed_item);


                // render enemy
                Boss_enemy->Render(g_screen, NULL);
                for (int i = 0; i < MAX_BULLET_BOSS; i++)
                {
                    for (int bl = 0; bl < Boss_enemy->Get_bullets(i).size(); bl++)
                    {
                        std::vector <Bullet*> bullets = Boss_enemy->Get_bullets(i);
                        Bullet* bullet = bullets.at(bl);
                        if (bullet != NULL)
                        {
                            if (bullet->get_is_move())
                            {
                                bullet->Render(g_screen, NULL);
                            }
                        }
                    }
                }
                Boss_enemy->check_bullet_out();
                Boss_enemy->Init_bullet();
                for (int mt = 0;mt < meteorites.size(); mt++)
                {
                    Enemy* meteorite = meteorites.at(mt);
                    meteorite->Render(g_screen, NULL);
                    if (meteorite->Get_is_out())
                    {
                        remove_meteorite(mt);
                    }
                }
                render_enemy(s_enemies);
                render_enemy(m_enemies);
                render_enemy(ufo_enemies);
                

                for (int hp_ = 0; hp_ < HP.size(); hp_++)
                {
                    HP[hp_]->Render(g_screen, NULL);
                }

                score.Render(g_screen, NULL);

                if (HP.size() == 0)
                {
                    if (!gameoverDisplayed)
                    {
                        gameoverDisplayed = true;
                    }
                    else
                    {
                        reset_text.Render(g_screen, NULL);
                        gameover.Render(g_screen, NULL);
                        isPaused = true;
                    }
                }
                checkCollision_play();

                SDL_RenderPresent(g_screen);
                SDL_Delay(16);
            }
            else if (isPaused && !gameoverDisplayed)
            {

                pause_menu.Render(g_screen, NULL);
                replay.Render(g_screen, NULL);
                resume.Render(g_screen, NULL);
                main_menu.Render(g_screen, NULL);
                SDL_RenderPresent(g_screen);
            }
        }
    }

    close();
    return 0;
}















