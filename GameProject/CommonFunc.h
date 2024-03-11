#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_


#include <Windows.h>
#include <string>
#include <random>
#include <chrono>
#include <vector>
#include <cmath>


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;


// Screen 
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;


// COLOR
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;


//sound 
static Mix_Music* backgroundMusic;
static Mix_Chunk* gunshotSound ;
static Mix_Chunk* boomSound;
static Mix_Chunk* collectSound;


const int MAX_HP = 3;
#endif
