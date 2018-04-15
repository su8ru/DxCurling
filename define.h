#pragma once
#include<DxLib.h>

int key[256];
int UpdateKey() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			key[i]++;     // 加算
		}
		else {              // 押されていなければ
			key[i] = 0;   // 0にする
		}
	}
	return 0;
}


//定義
int timecnt = 0; //「何秒かに一回」をやるため

int gamemode = 0; //0:OP 1:Game 2:Pause 3:ED

int gamecnt = 1; //ゲームの進行状況

int azukiL32, azukiL24, azukiL16, azukiLB32, azukiLB24, azukiLB16, Cica32, Cica24, Cica16; //FontHandle
int stone_red, stone_yellow, brush, sheet; //GraphHandle

int mX = 0, mY = 0, *mXp = &mX, *mYp = &mY;

int course = 0;	//シュートの方向
int power = 3;	//シュートのパワー
double speed = 0;	//シュートのスピード
int cnt = 0;	//Game内で経過時間カウント

double xBevel = 0, yBevel = 0;

int sX = 180, sY = 540;
bool setFlag = false, moveFlag = false;

struct stone {
	double x, y;
};

stone yellowStone[4]{
	{ 804,36 },
	{ 804,100 },
	{ 804,164 },
	{ 804,228 }
};
stone redStone[4]{
	{ 516,36 },
	{ 516,100 },
	{ 516,164 },
	{ 516,228 }
};

stone yellowStoneDefault[4]{
	{ 804,36 },
	{ 804,100 },
	{ 804,164 },
	{ 804,228 }
};
stone redStoneDefault[4]{
	{ 516,36 },
	{ 516,100 },
	{ 516,164 },
	{ 516,228 }
};

void DrawBrush();
void Draw();

void Error();
void OP();
void Pause();
void ED();

void Control();
void DrawControl();
void DrawStone();
void Game();
void DrawGame();

void DrawInfo();
void DrawMousePos();
void DrawShootLine();
void MoveStoneD();