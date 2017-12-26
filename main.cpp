#include "DxLib.h"

char Key[256];

int img_back;
int img_Hshikaku[2], img_Rshikaku[2];
int sound;
int color_black,color_white,color_red,color_green,color_blue;
int a = 0,b =  0;
int x, y, mouse;
int i = 0, OldMouseOshita = 0, NewMouseOshita;
int f;
double MAXHP[2] = { 0,0 }, MAXMP[2] = { 0,0 }, HP[2] = { 0,0 }, MP[2] = { 0,0 };
int LV[2] = { 1,1 };
double parHP[2],parMP[2];


void img_load(){
	img_back = LoadGraph("画像/背景.png");
	img_Hshikaku[0] = LoadGraph("画像/高温四角（前）.png");
	img_Hshikaku[1] = LoadGraph("画像/高温四角（後）.png");
	img_Rshikaku[0] = LoadGraph("画像/低温四角（前）.png");
	img_Rshikaku[1] = LoadGraph("画像/低温四角（後）.png");
}

void sound_load() {
	sound = LoadSoundMem("チーン.ogg");
}

void set_color(){
	color_black = GetColor(0, 0, 0);
	color_white = GetColor(255, 255, 255);
	color_red = GetColor(255, 0, 0);
	color_green = GetColor(0, 255, 0);
	color_blue = GetColor(0, 0, 255);
}

void sute() {
	MAXHP[0] = LV[0] * 100;
	MAXMP[0] = LV[0] * 10;
	MAXHP[1] = LV[1] * 100;
	MAXMP[1] = LV[1] * 10;
}

void sute_I(){
	HP[0] = MAXHP[0];
	MP[0] = MAXMP[0];
	HP[1] = MAXHP[1];
	MP[1] = MAXMP[1];
}

void ver() {
	//ここからプレイヤー１
	parHP[0] = HP[0] / MAXHP[0];
	if (HP[0] < 0) {
		HP[0] = 0;
	}
	if (parHP[0] < 0.1) {
		parHP[0] = 0.1;
	}
	DrawBox(20, 20, 200 * parHP[0], 35, color_green, TRUE);

	parMP[0] = MP[0] / MAXMP[0];
	if (MP[0] < 0) {
		MP[0] = 0;
	}
	if (parMP[0] < 0.1) {
		parMP[0] = 0.1;
	}
	DrawBox(20, 40, 200 * parMP[0], 55, color_blue, TRUE);
	//ここまでプレイヤー１

	//ここからプレイヤー２
	parHP[1] = HP[1] / MAXHP[1];
	if (HP[1] < 0 ) {
		HP[1] = 0;
	}
	
	DrawBox(620, 20, 620 - (200 * parHP[1]) , 35, color_green, TRUE);
	parMP[1] = MP[1] / MAXMP[1];
	if (MP[1] < 0) {
		MP[1] = 0;
	}
	DrawBox(620, 40, 620 - (200 * parMP[1]), 55, color_blue, TRUE);
	//ここまでプレイヤー２
}

void mozi(){
	DrawBox(19,19,201,36,color_black,FALSE);
	DrawFormatString(20, 20, color_black, "HP");
	DrawBox(19, 39, 201, 56, color_black, FALSE);
	DrawFormatString(20, 40, color_black, "MP");

	DrawBox(419, 19, 621, 36, color_black, FALSE);
	DrawFormatString(603, 20, color_black, "HP");
	DrawBox(419, 39, 621, 56, color_black, FALSE);
	DrawFormatString(603, 40, color_black, "MP");

	DrawBox(0, 350, 640, 480, color_black, FALSE);

	DrawFormatString(10, 360, color_black, "攻撃");
	DrawBox(9, 359, 43, 375, color_black, FALSE);
}

void set_img(){
	DrawGraph(0,0,img_back,FALSE);
	DrawRotaGraph(100, 250, 0.6, 0.0, img_Hshikaku[1], TRUE);
	DrawRotaGraph(500, 150, 0.6, 0.0, img_Rshikaku[0], TRUE);
}

void mausu() {
	NewMouseOshita = (GetMouseInput() & MOUSE_INPUT_LEFT);
	GetMousePoint(&x, &y);
	if (x <= 43 && x >= 9 && y <= 375 && y >= 359) {
		if (OldMouseOshita == 0 && NewMouseOshita == 1) {
			HP[1] = HP[1] - 1.0;
		}
		OldMouseOshita = NewMouseOshita;
	}

}

void renda(){

	
}




int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	int RefreshTime;

	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;

	SetDrawScreen(DX_SCREEN_BACK);                  //裏画面を使用する。

	img_load();
	set_color();
	sound_load();
	sute();
	sute_I();

	while (ProcessMessage() == 0 && GetHitKeyStateAll(Key) == 0) {
		RefreshTime = GetNowCount();               //今の時間を取得
		ClearDrawScreen();                         //裏画面のデータを全て削除

		

		set_img();

		renda();

		ver();

		mozi();

		mausu();
		

		ScreenFlip();                             //裏画面データを表画面へ反映
		

		if (Key[KEY_INPUT_ESCAPE] == 1)    break;//Escapeが押されたら終了

		
		while (GetNowCount() - RefreshTime < 17);   //1周の処理が17ミリ秒になるまで待つ
	}

	DxLib_End();
	return 0;
}