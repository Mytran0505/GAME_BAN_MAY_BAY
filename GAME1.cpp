#include"Common_Function.h"
#include"MainObject.h"
#include"ThreatsObject.h"
#include"Explosion.h"
bool Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (g_screen == NULL)
		return false;
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		return false;
	g_sound_bullet[0] = Mix_LoadWAV(g_sound_Sphere);
	g_sound_bullet[1] = Mix_LoadWAV(g_sound_Laser);
	g_sound_exp[0] = Mix_LoadWAV(g_sound_ExpTheat);
	g_sound_exp[1] = Mix_LoadWAV(g_sound_ExpMain);

	if (g_sound_exp[0] == NULL || g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_exp[1] == NULL)
		return false;

	return true;
}
int main(int arc, char*argv[]) {
	bool is_run_screen = true;
	int bkgn_x = 0;
	bool is_quit = false;

	if (Init() == false)
		return 0;
	g_bkground = SDLCommonFunc:: LoadImage(g_name_background);
	if (g_bkground == NULL)
		return 0;

	MainObject plane_object;
	plane_object.SetRect(100, 200);
	/*plane_object.GetRect(100, 200);
	bool ret = planet_object.Loading(g_name_Main);*/
	bool ret = plane_object.Loading(g_name_Main);
	if (!ret)
		return 0;

	ExplosionObject exp_main;
	ret = exp_main.Loading(g_name_Exp);
	exp_main.set_clips();
	if (ret == false)
		return 0;

	

	ThreatObject* p_threats = new ThreatObject[NUM_THREAT];
	for (int t = 0; t < NUM_THREAT; t++) {
		ThreatObject* p_threat = p_threats + t;
		if (p_threats) {
			ret = p_threat->Loading(g_name_threat1);
			if (!ret)
				return 0;
			int rand_y = rand() % 400;
			if (rand_y > SCREEN_HEIGHT - 200)
				rand_y = SCREEN_HEIGHT * 0.3;
			p_threat->SetRect(SCREEN_WIDTH + t * 400, rand_y);
			p_threat->set_x_val(3);
			BulletObject* p_Bullet = new BulletObject();
			p_threat->InitBullet(p_Bullet);
		}
	}

	while (!is_quit) {
		while (SDL_PollEvent(&g_event)) {
			if (g_event.type == SDL_QUIT) {
				is_quit = true;
				break;
			}
			plane_object.HandleInputAction(g_event,g_sound_bullet);
		}
		if (is_run_screen == true) {
			bkgn_x -= 2;
			if (bkgn_x <= -(WIDTH_BACKGROUND - SCREEN_WIDTH))
				is_run_screen = false;
			else
				SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
		}
		else
			SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);

		/*SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
		SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x + SCREEN_WIDTH, 0);
		if (bkgn_x <= -SCREEN_WIDTH)
			bkgn_x = 0;*/
		plane_object.HandleMove();
		plane_object.Show(g_screen);
		plane_object.MakeBullet(g_screen);
		for (int tt = 0; tt < NUM_THREAT; tt++) {
			ThreatObject* p_threat = p_threats + tt;
			if (p_threats) {
				p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(g_screen);
				p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

				bool is_col1 = false;
				vector<BulletObject*> Bullet_arr = p_threat->GetBulletList();
				for (int am = 0; am < Bullet_arr.size(); am++) {
					BulletObject* p_Bullet = Bullet_arr.at(am);
					if (p_Bullet) {
						is_col1 = SDLCommonFunc::CheckCollision(p_Bullet->GetRect(), plane_object.GetRect());
						if (is_col1 == true) {
							p_threat->ResetBullet(p_Bullet);
							break;
						}
					}
				}
		
				bool is_col = SDLCommonFunc::CheckCollision(plane_object.GetRect(), p_threat->GetRect());
				if (is_col1||is_col) {

					for (int ex = 0; ex < 4; ex++) {
						int x_pos = (plane_object.GetRect().x + plane_object.GetRect().w * 0.5) - EXPLOSION_WIDTH * 0.5;
						int y_pos = (plane_object.GetRect().y + plane_object.GetRect().h * 0.5) - EXPLOSION_HEIGHT * 0.5;
						exp_main.set_frame(ex);
						exp_main.SetRect(x_pos, y_pos);
						exp_main.ShowEx(g_screen);
						Mix_PlayChannel(-1, g_sound_exp[1], 0);
						SDL_Delay(200);
						if (SDL_Flip(g_screen) == -1)
							return 0;
					}
					Mix_PlayChannel(-1, g_sound_exp[1], 0);
					//if () {
					delete[] p_threats;
					SDLCommonFunc::CleanUp();
					SDL_Quit();
					return 1;
					//}
				}

				vector<BulletObject*> Bullet_list = plane_object.GetBulletList();
				for (int im = 0; im < Bullet_list.size(); im++) {
					BulletObject* p_Bullet = Bullet_list.at(im);
					if (p_Bullet!=NULL) {
						bool rect_col = SDLCommonFunc::CheckCollision(p_Bullet->GetRect(), p_threat->GetRect());
						if (rect_col) {
							for (int tx = 0; tx < 4; tx++) {
								int x_pos = p_Bullet->GetRect().x - EXPLOSION_WIDTH * 0.5;
								int y_pos = p_Bullet->GetRect().y - EXPLOSION_HEIGHT * 0.5;

								exp_main.set_frame(tx);
								exp_main.SetRect(x_pos, y_pos);
								exp_main.ShowEx(g_screen);

								if (SDL_Flip(g_screen) == -1)
									return 0;

							}
							p_threat->Reset(SCREEN_WIDTH + tt * 400);
							plane_object.RemoveBullet(im);
							Mix_PlayChannel(-1, g_sound_exp[0], 0);
						}

					}
				}
			}	
		}
		if (SDL_Flip(g_screen) == -1)
			return 0;
	}

	delete[] p_threats;
	SDLCommonFunc::CleanUp();
	SDL_Quit();
	return 1;
}