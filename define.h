#pragma once
#include<DxLib.h>
#include <math.h>

int key[256];
int UpdateKey() {
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			key[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			key[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}


//��`
int timecnt = 0; //�u���b���Ɉ��v����邽��

int gamemode = 0; //0:OP 1:Game 2:Pause 3:ED

int gamecnt = 1; //�Q�[���̐i�s��

int azukiL32, azukiL24, azukiL16, azukiLB32, azukiLB24, azukiLB16, Cica32, Cica24, Cica16; //FontHandle
int stone_red, stone_yellow, brush, sheet; //GraphHandle

int mX = 0, mY = 0, *mXp = &mX, *mYp = &mY;

int course = 0;			//�V���[�g�̕���
int power = 3;			//�V���[�g�̃p���[
double speed = 1;		//�V���[�g�̃X�s�[�h
int cnt = 0;			//Game���Ōo�ߎ��ԃJ�E���g
int stoneMoveTime = 0;	//stone�������Ă��鎞��

double nowStonePos = 0;		//stonePos * power = �i�񂾋���

double xBevel = 0, yBevel = 0;

int sX = 180, sY = 540;
bool setFlag = false, moveFlag = false;

struct stone {
	double x, y, speed;
};

stone yellowStone[4]{
	{ 804,36 ,0 },
	{ 804,100,0 },
	{ 804,164,0 },
	{ 804,228,0 }
};
stone redStone[4]{
	{ 516,36 ,0 },
	{ 516,100,0 },
	{ 516,164,0 },
	{ 516,228,0 }
};

stone yellowStoneDefault[4]{
	{ 804,36 ,0 },
	{ 804,100,0 },
	{ 804,164,0 },
	{ 804,228,0 }
};
stone redStoneDefault[4]{
	{ 516,36 ,0 },
	{ 516,100,0 },
	{ 516,164,0 },
	{ 516,228,0 }
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
void DrawShootLineRad();
void MoveStoneD();

double Rad(int);