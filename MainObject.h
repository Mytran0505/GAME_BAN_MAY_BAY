#include"BulletObject.h"
#include<vector>
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

//#define WIDTH_MAIN_OBJECT 77
//#define HEIGHT_MAIN_OBJECT 52

class MainObject :public BaseObject {
private:
	int x_val_;
	int y_val_;
	vector<BulletObject*> p_Bullet_list_;
public:
	MainObject();
	~MainObject();
	void HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2]);
	void HandleMove();
	void SetBulletList(vector<BulletObject*> Bullet_list) { p_Bullet_list_ = Bullet_list; }
	vector<BulletObject*> GetBulletList() const { return p_Bullet_list_; }
	void MakeBullet(SDL_Surface* des);
	void RemoveBullet(const int& idx);
};
#endif // !MAIN_OBJECT_H_
