#pragma once
#pragma once
#include<Windows.h>
#include<iostream>
#include<time.h>
#include<tchar.h>


//用于显示窗体的全局变量
//----------------------------------
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int bits = 24;
extern BYTE buffer[SCREEN_WIDTH * SCREEN_HEIGHT * bits / 8];


//-----------------------------------

//用于处理排序数据的全局变量
//-----------------------------------
const int DataSum = SCREEN_WIDTH;
extern int DataMax;
extern int DataMin;
extern int data[DataSum];
extern int nowIndex;
//-----------------------------------


class Color
{
public:
	Color(int R, int G, int B) :r(R), g(G), b(B) {};
	Color() :r(255), g(255), b(255) {};
	int r, g, b;
};


void CleanScreen();
void Draw();

void DrawPoint(int x, int y, Color color = Color(255, 255, 255));


int screen_init(int w, int h, const TCHAR* title);
int screen_close(void);
static LRESULT screen_events(HWND hWnd, UINT msg,
	WPARAM wParam, LPARAM lParam);
void MsgGet(void);
void screen_update(void);
void KeyControl();

//=========================================================
//	读取图片
extern unsigned char* pBmpBuf;//读入图像数据的指针
extern int bmpWidth;//图像的宽
extern int bmpHeight;//图像的高
extern RGBQUAD* pColorTable;//颜色表指针
extern int biBitCount;//图像类型，每像素位数
bool readBmp(const char* bmpName);
Color loadTexture(double u, double v);

class Object
{
public:
	int x;
	int y;
};

extern Object Flag;