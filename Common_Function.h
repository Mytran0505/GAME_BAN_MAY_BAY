#ifndef COMMON_FUNTION_H_
#define COMMON_FUNTION_H_

#include<iostream>
#include<SDL.h>
#include <string>
#include <SDL_image.h>
#include<SDL_mixer.h>

using namespace std;
#undef main

const int WIDTH_BACKGROUND = 4800;
const int HEIGHT_BACKGROUND = 600;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int SPEED_SCREEN = 2;

const int WIDTH_MAIN_OBJECT = 77;
const int HEIGHT_MAIN_OBJECT = 52;

const int EXPLOSION_WIDTH = 165;
const int EXPLOSION_HEIGHT = 165;

const int NUM_THREAT = 3;
const int WIDTH_THREAT = 80;
const int HEIGHT_THREAT = 33;
const int UNDER_LIMIT_THREAT = 200;

const int WIDTH_LASER = 35;
const int HEIGHT_LASER = 5;
const int WIDTH_SPHERE = 10;
const int HEIGHT_SPHERE = 10;

static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_bkground = NULL;
static SDL_Event g_event;

static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[2];

static char g_name_background[] = "bk5.png";
static char g_name_threat1[] = "af1.png";
static char g_name_Main[] = "plane_fly.png";
static char g_name_Exp[] = "exp_main.png";
static char g_name_Sphere[] = "sphere.png";
static char g_name_Laser[] = "laser.png";

static char g_sound_Sphere[] = "m3.wav";
static char g_sound_Laser[] = "m2.wav";
static char g_sound_ExpTheat[] = "m1.wav";
static char g_sound_ExpMain[] = "m4.wav"; 

namespace SDLCommonFunc {
	SDL_Surface* LoadImage(std::string file_path);
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void CleanUp();
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des,SDL_Rect *clip, int x, int y);

}

#endif // COMMON_FUNTION_H_

