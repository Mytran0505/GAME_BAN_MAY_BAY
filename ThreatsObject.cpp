#include"ThreatsObject.h"



ThreatObject::ThreatObject() {
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT * 0.5;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;
	x_val_ = 0;
	y_val_ = 0;
}

ThreatObject::~ThreatObject() {
	if (p_Bullet_list_.size() > 0) {
		for (int i = 0; i < p_Bullet_list_.size(); i++) {
			BulletObject* p_Bullet = p_Bullet_list_.at(i);
			if (p_Bullet != NULL) {
				delete p_Bullet;
				p_Bullet = NULL;
			}
		}
		p_Bullet_list_.clear();
	}
}


void ThreatObject::InitBullet(BulletObject* p_Bullet) {
	if (p_Bullet) {
		bool rect = p_Bullet->Loading(g_name_Sphere);
		if (rect) {
			p_Bullet->Set_is_move(true);
			p_Bullet->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_Bullet->Set_type(BulletObject::SPHERE);
			p_Bullet->SetRect(rect_.x, rect_.y + rect_.h * 0.5);
			p_Bullet->set_x_val(5);
			p_Bullet_list_.push_back(p_Bullet);
		}
	}
}


void ThreatObject::HandleMove(const int& x_border, const int& y_border) {
	rect_.x -= x_val_;
	if (rect_.x < 0) {
		rect_.x = SCREEN_WIDTH;
		int rand_y = rand() % 400;
		if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
			rand_y = SCREEN_HEIGHT * 0.3;
		rect_.y = rand_y;
	}
}

void ThreatObject::HandleInputAction(SDL_Event events) {

}

void ThreatObject::MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit) {
	for (int i = 0; i < p_Bullet_list_.size(); i++) {
		BulletObject* p_Bullet = p_Bullet_list_.at(i);
		if(p_Bullet)
			if (p_Bullet->Get_is_move()) {
				p_Bullet->Show(des);
				p_Bullet->HandleMoveRightToLeft();
			}
			else {
				p_Bullet->Set_is_move(true);
				p_Bullet->SetRect(rect_.x, rect_.y + rect_.h * 0.5);
			}
	}
}

void ThreatObject::Reset(const int& xborder) {
	rect_.x = xborder;
	int rand_y = rand() % 400;
	if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
		rand_y = SCREEN_HEIGHT * 0.3;
	rect_.y = rand_y;
	for (int i = 0; i < p_Bullet_list_.size(); i++) {
		BulletObject* p_Bullet = p_Bullet_list_.at(i);
		if (p_Bullet) {
			ResetBullet(p_Bullet);
		}
	}
}

void ThreatObject::ResetBullet(BulletObject* p_Bullet) {
	p_Bullet->SetRect(rect_.x, rect_.y + rect_.h * 0.5);
	
}