#pragma once
#include<DxLib.h>
#include <math.h>

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


/*
すぎちゃんのれっきょがたこうざ

enum mode{
    TITLE,GAME,PAUSE,ED
};
mode Mode=TITLE;
わかりやすいでしょ?

-- メモ --
structみたいな感じ
 */


//定義
int timecnt = 0; //「何秒かに一回」をやるため

enum Mode {
	op, game, pause, ed
};

Mode gamemode = op;	//op, game, pause, ed

int gamecnt = 0; //ゲームの進行状況

int azukiL32, azukiL24, azukiL16, azukiLB32, azukiLB24, azukiLB16, Cica32, Cica24, Cica16; //FontHandle
int stone_red, stone_yellow, brush, sheet; //GraphHandle

int mX = 0, mY = 0;

int angle = 0;			//シュートの方向
double power = 3.0;			//シュートのパワー
double speed = 1;		//シュートのスピード
int cnt = 0;			//Game内で経過時間カウント

bool waitingForInput;

double nowStonePos = 0;		//stonePos * power = 進んだ距離

double xBevel = 0, yBevel = 0;

int sX = 180, sY = 540;
bool placed = false, moveFlag = false, turnEndFlag = false;

struct stone {
	double x, y, vx=0,vy=0;
	bool isYellow;
};

stone stones[8];

/*stone stoneDefault[8]{
	{ 804,36 ,0,true },
	{ 516,36 ,0,false },
	{ 804,100,0,true },
	{ 516,100,0,false },
	{ 804,164,0,true },
	{ 516,164,0,false },
	{ 804,228,0,true },
	{ 516,228,0,false }
};*/

void InitStones();

void DrawBrush();
//void Draw();

void Error();
void OP();
void Pause();
void ED();

void Control();
void DrawStone();
void DrawGame();
//void MoveYellowStone(int);
//void MoveRedStone(int);
void AddForce(int,double,double);	//ストーンに力を加える
void StopOverStone();	//はみでたstoneを止める
void StopSlowStone();

void PhysicStone();		//その他物理演算

bool isMovingAnyStones();

void DrawInfo();
void DrawMousePos();
void DrawShootLine();
void DrawShootLineRad();
//void MoveStoneD(int);

double Rad(int);
