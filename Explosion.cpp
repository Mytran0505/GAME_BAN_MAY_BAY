#include "Explosion.h"

ExplosionObject::ExplosionObject() {
	frame_ = 0; 
}

ExplosionObject::~ExplosionObject() {

}


void ExplosionObject::set_clips() {
	clips_[0].x = 0;
	clips_[0].y = 0;
	clips_[0].w = EXPLOSION_WIDTH;
	clips_[0].h = EXPLOSION_HEIGHT;

	clips_[1].x = EXPLOSION_WIDTH;
	clips_[1].y = 0;
	clips_[1].w = EXPLOSION_WIDTH;
	clips_[1].h = EXPLOSION_HEIGHT;

	clips_[2].x = EXPLOSION_WIDTH * 2; 
	clips_[2].y = 0;
	clips_[2].w = EXPLOSION_WIDTH;
	clips_[2].h = EXPLOSION_HEIGHT;

	clips_[3].x = EXPLOSION_WIDTH * 3;
	clips_[3].y = 0; 
	clips_[3].w = EXPLOSION_WIDTH;
	clips_[3].h = EXPLOSION_HEIGHT;
}

void ExplosionObject::ShowEx(SDL_Surface* des) {
	if (frame_ >= 4)
		frame_ = 0;
	SDLCommonFunc::ApplySurfaceClip(this->p_object_, des, &clips_[frame_], rect_.x, rect_.y);
}
