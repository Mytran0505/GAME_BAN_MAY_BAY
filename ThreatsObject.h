#include"BulletObject.h"
#include <vector>


#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_

//#define WIDTH_THREAT 80
//#define HEIGHT_THREAT 33
//const int UNDER_LIMIT_THREAT = 200;

class ThreatObject :public BaseObject {
private:
	int x_val_;
	int y_val_;
	vector<BulletObject*> p_Bullet_list_;

public:
	ThreatObject();
	~ThreatObject();
	void HandleMove(const int& x_border, const int& y_border);
	void HandleInputAction(SDL_Event events);
	void set_x_val(const int& val) { x_val_ = val; }
	void set_y_val(const int& val) { y_val_ = val; }
	int get_x_val()const { return x_val_; }
	int get_y_val()const { return y_val_; }
	void SetBulletList(vector<BulletObject*> Bullet_list) { p_Bullet_list_ = Bullet_list; }
	vector<BulletObject*> GetBulletList() const { return p_Bullet_list_; }
	void InitBullet(BulletObject* p_Bullet);
	void MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit);
	void Reset(const int& xborder);
	void ResetBullet(BulletObject* p_Bullet);
};
#endif // !THREATS_OBJECT_H_
