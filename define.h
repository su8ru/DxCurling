#pragma once
#include<DxLib.h>
#include <math.h>

int key[256];
void UpdateKey() {
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
}


//��`
int timecnt = 0; //�u���b���Ɉ��v����邽��

int gamemode = 0; //0:OP 1:Game 2:Pause 3:ED

int gamecnt = 0; //�Q�[���̐i�s��

int azukiL32, azukiL24, azukiL16, azukiLB32, azukiLB24, azukiLB16, Cica32, Cica24, Cica16; //FontHandle
int stone_red, stone_yellow, brush, sheet; //GraphHandle

int mX = 0, mY = 0;

int course = 0;			//�V���[�g�̕���
int power = 3;			//�V���[�g�̃p���[
//double speed = 1;		//�V���[�g�̃X�s�[�h
int cnt = 0;			//Game���Ōo�ߎ��ԃJ�E���g
int stoneMoveTime = 0;	//stone�������Ă��鎞��

double nowStonePos = 0;		//stonePos * power = �i�񂾋���

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
void Shoot(int);			//�V���[�g
void Acceleration(int);		//������
void StopLowStone(int);		//������肷����stone���~�߂�
void StopOverStone(int);	//�݂͂ł�stone���~�߂�
void PhysicStone(int);		//���̑��������Z


void DrawInfo();
void DrawMousePos();
void DrawShootLine();
void DrawShootLineRad();
//void MoveStoneD(int);

double Rad(int);