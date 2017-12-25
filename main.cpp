#include "DxLib.h"

char Key[256];

int img_back;
int sound;
int color_black,color_white,color_red,color_green,color_blue;
int a = 0,b =  0;
int x, y, mouse;
int i = 0;
int f;
double MAXHP[2] = { 0,0 }, MAXMP[2] = { 0,0 }, HP[2] = { 0,0 }, MP[2] = { 0,0 };
int LV[2] = { 1,1 };
double parHP[2],parMP[2];


void img_load(){
	img_back = LoadGraph("�w�i.png");
}

void sound_load() {
	sound = LoadSoundMem("�`�[��.ogg");
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
	//��������v���C���[�P
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
	//�����܂Ńv���C���[�P

	//��������v���C���[�Q
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
	//�����܂Ńv���C���[�Q
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
}

void set_img(){
	DrawGraph(0,0,img_back,FALSE);
}

void mausu() {

}

void renda(){

	
}




int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	int RefreshTime;

	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;

	SetDrawScreen(DX_SCREEN_BACK);                  //����ʂ��g�p����B

	img_load();
	set_color();
	sound_load();
	sute();
	sute_I();

	while (ProcessMessage() == 0 && GetHitKeyStateAll(Key) == 0) {
		RefreshTime = GetNowCount();               //���̎��Ԃ��擾
		ClearDrawScreen();                         //����ʂ̃f�[�^��S�č폜

		

		set_img();

		renda();

		ver();

		mozi();

		mausu();
		

		ScreenFlip();                             //����ʃf�[�^��\��ʂ֔��f
		

		if (Key[KEY_INPUT_ESCAPE] == 1)    break;//Escape�������ꂽ��I��

		
		while (GetNowCount() - RefreshTime < 17);   //1���̏�����17�~���b�ɂȂ�܂ő҂�
	}

	DxLib_End();
	return 0;
}