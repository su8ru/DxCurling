﻿/*
カーリングっぽいミニゲームっぽいもの

作成：subaru2003
*/

#include <DxLib.h>
#include <stdio.h>
#include <math.h>
#include "define.h"
#include "function.h"
#include "resource.h"

#define font1 "あずきフォントL"
#define font2 "あずきフォントLB"
#define font3 "Cica"

//#define font1 "MyricaM M"
//#define font2 "MyricaM M"
//#define font3 "MyricaM M"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetWindowText("DxCurling");
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetGraphMode(1280, 720, 32);
	DxLib_Init();
	//CreateFontToHandle
	{
		
		azukiL32 = CreateFontToHandle(font1, 32, -1, DX_FONTTYPE_ANTIALIASING_4X4);
		azukiL24 = CreateFontToHandle(font1, 24, -1, DX_FONTTYPE_ANTIALIASING_4X4);
		azukiL16 = CreateFontToHandle(font1, 16, -1, DX_FONTTYPE_ANTIALIASING_4X4);
		azukiLB32 = CreateFontToHandle(font2, 32, -1, DX_FONTTYPE_ANTIALIASING_4X4);
		azukiLB24 = CreateFontToHandle(font2, 24, -1, DX_FONTTYPE_ANTIALIASING_4X4);
		azukiLB16 = CreateFontToHandle(font2, 16, -1, DX_FONTTYPE_ANTIALIASING_4X4);
		Cica32 = CreateFontToHandle(font3, 32, -1, DX_FONTTYPE_ANTIALIASING_4X4);
		Cica24 = CreateFontToHandle(font3, 24, -1, DX_FONTTYPE_ANTIALIASING_4X4);
		Cica16 = CreateFontToHandle(font3, 16, -1, DX_FONTTYPE_ANTIALIASING_4X4);
	}
	//LoadGraph
	{
		stone_red = LoadGraph("./pic/stone_red.png");
		stone_yellow = LoadGraph("./pic/stone_yellow.png");
		brush = LoadGraph("./pic/brush.png");
		sheet = LoadGraph("./pic/sheet.png");
	}
	SetMouseDispFlag(FALSE);
	SetDrawScreen(DX_SCREEN_BACK);
	InitStones();
	gamecnt = 0;
	waitingForInput = true;
	while (!ProcessMessage() && UpdateKey() == 0) {
		ClearDrawScreen();
		//ここに書く
		GetMousePoint(&mX, &mY);
		DrawBox(0, 0, 1280, 720, 0xffffff, TRUE); //白背景
		//DrawMousePos();
		switch (gamemode) {
		case op:
			OP();
			break;

		case game:
			//Control();
			DrawGame();
			//DrawInfo();
			Control();
			
			cnt++;
			break;

		case pause:
			Pause();
			break;

		case ed:
			ED();
			break;

		default:
			Error();
			break;
		}
		if (key[KEY_INPUT_SPACE] && gamemode == ed)	break;
		DrawBrush();
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}
