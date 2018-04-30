#pragma once
#include<DxLib.h>
#include <math.h>

int key[256];
int UpdateKey() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			key[i]++;	 // 加算
		}
		else {			  // 押されていなければ
			key[i] = 0;   // 0にする
		}
	}
	return 0;
}


//定義
int timecnt = 0; //「何秒かに一回」をやるため

enum Mode {
	op, game, pause, ed
};
Mode gamemode = op;	//op, game, pause, ed

int gamecnt = 0; //ゲームの進行状況

int azukiL32, azukiL24, azukiL16, azukiLB32, azukiLB24, azukiLB16, Cica32, Cica24, Cica16; //FontHandle
int stone_red, stone_yellow, brush, sheet, infoFrame; //GraphHandle

int mX = 0, mY = 0;		//mousePos

int angle = 0;			//シュートのアングル[°]
double power = 3.0;		//シュートのパワー
int cnt = 0;			//Game内で経過時間カウント

bool waitingForInput;

double nowStonePos = 0;		//stonePos * power = 進んだ距離

double xBevel = 0, yBevel = 0;

int sX = 180, sY = 540;
bool placed = false, moveFlag = false, turnEndFlag = false;

int rank[8] = {};	//stones[i].distance の昇順に stoneId を格納
int score = 0;
bool winnerIsYellow = true;

struct stone {
	double x, y, vx = 0, vy = 0, distance = 0;
	bool isYellow, enabled;
};
stone stones[8];


void InitStones();

void DrawBrush();
void Error();

void OP();
void Pause();
void ED();

void Control();
void DrawStone();
void DrawGame();
void ControlDescription();
void StopOverStone();
void StopSlowStone();
void PhysicStone();
void DistanceFromGoal();
void DecideRank();
void CalculateRank();
void DrawRankData();
void DrawDistanceData();
bool isMovingAnyStones();

void DrawInfo();
void DrawMousePos();
void DrawShootLineRad();

double Rad(int);
void   AddForce(int, double, double);
double Distance(double, double);