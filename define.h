#pragma once
#include<DxLib.h>
#include <math.h>

int key[256];
void UpdateKey() {
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
}


//定義
int timecnt = 0; //「何秒かに一回」をやるため

int gamemode = 0; //0:OP 1:Game 2:Pause 3:ED

int gamecnt = 0; //ゲームの進行状況

int azukiL32, azukiL24, azukiL16, azukiLB32, azukiLB24, azukiLB16, Cica32, Cica24, Cica16; //FontHandle
int stone_red, stone_yellow, brush, sheet; //GraphHandle

int mX = 0, mY = 0;

int course = 0;			//シュートの方向
int power = 3;			//シュートのパワー
//double speed = 1;		//シュートのスピード
int cnt = 0;			//Game内で経過時間カウント
int stoneMoveTime = 0;	//stoneが動いている時間

double nowStonePos = 0;		//stonePos * power = 進んだ距離

double xBevel = 0, yBevel = 0;

int sX = 180, sY = 540;
bool setFlag = false, moveFlag = false, turnEndFlag = false;

struct stone {
	double x, y, speed;
	bool isYellow;
};

stone stoneInfo[8]{
	{ 804,36 ,0,true },
	{ 516,36 ,0,false },
	{ 804,100,0,true },
	{ 516,100,0,false },
	{ 804,164,0,true },
	{ 516,164,0,false },
	{ 804,228,0,true },
	{ 516,228,0,false }
};

stone stoneDefault[8]{
	{ 804,36 ,0,true },
	{ 516,36 ,0,false },
	{ 804,100,0,true },
	{ 516,100,0,false },
	{ 804,164,0,true },
	{ 516,164,0,false },
	{ 804,228,0,true },
	{ 516,228,0,false }
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
//void MoveYellowStone(int);
//void MoveRedStone(int);
void Shoot(int);			//シュート
void Acceleration(int);		//加減速
void StopLowStone(int);		//ゆっくりすぎるstoneを止める
void StopOverStone(int);	//はみでたstoneを止める
void PhysicStone(int);		//その他物理演算


void DrawInfo();
void DrawMousePos();
void DrawShootLine();
void DrawShootLineRad();
//void MoveStoneD(int);

double Rad(int);