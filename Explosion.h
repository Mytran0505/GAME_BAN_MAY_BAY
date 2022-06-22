#include"BaseObject.h"
#include"Common_Function.h"

#ifndef EXPLOSION_H_ 
#define EXPLOSION_H_

//const int EXPLOSION_HEIGHT =165;
//const int EXPLOSION_HEIGHT = 165;

class ExplosionObject : public BaseObject {
private:
	int frame_;
	SDL_Rect clips_[4];
public:
	ExplosionObject();
	~ExplosionObject();
	void set_clips();
	void set_frame(const int& fr) { frame_ = fr; }
	//void move();
	void ShowEx(SDL_Surface* des);
};
#endif