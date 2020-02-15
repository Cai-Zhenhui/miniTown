#pragma once
#pragma once
#include<Windows.h>
#include<iostream>
#include<time.h>
#include<tchar.h>


//用于显示窗体的全局变量
//----------------------------------
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int bits = 24;
extern BYTE buffer[SCREEN_WIDTH * SCREEN_HEIGHT * bits / 8];


//-----------------------------------


extern int runtime;
extern int LastFPS;


class Color
{
public:
	Color(int R, int G, int B) :r(R), g(G), b(B) {};
	Color() :r(255), g(255), b(255) {};
	int r, g, b;
};

class Picture
{
public:
	unsigned char* pBmpBuf;//读入图像数据的指针
	int bmpWidth;//图像的宽
	int bmpHeight;//图像的高
	RGBQUAD* pColorTable;//颜色表指针
	int biBitCount;//图像类型，每像素位数
};

class Object
{
public:
	int x;
	int y;
	int z;
	Picture* pic;
};

class Field
{
public:
	int id;
	float growingTime;
	Object *DrawObject;
};

class House
{
public:
	int id;
	Object *DrawObject;
};

class Rice
{
public:
	int id;
	Object* DrawObject;

};

class Farmer
{
public:
	int id;
	float age;
	int monney;
	Field* belongField;
	House* belongHouse;
	Object*DrawObject;
	int wantFoodLevel;
	int wantSexLevel;
	void AI();
};






void CleanScreen();
void Draw();
extern Object* drawList[1000];
extern int drawSum;

void AddDrawObject(Object* object);
void RemoveDrawObecjt(Object* object);
void DrawPoint(int &x, int &y, const Color &color );
void DrawPoint(int& x, int& y, int& r, int& g, int& b);

int screen_init(int w, int h, const TCHAR* title);
int screen_close(void);
static LRESULT screen_events(HWND hWnd, UINT msg,
	WPARAM wParam, LPARAM lParam);
void MsgGet(void);
void screen_update(void);
void KeyControl();
extern int screen_keys[512];	// 当前键盘按下状态
extern HWND screen_handle;		// 主窗口 HWND

//=========================================================
//	读取图片



bool readBmp(const char* bmpName, Picture& pic);
void DrawRect(int x, int y, int w, int h,Color color);
void DrawBmp(int x, int y, Picture* pic);
Color loadTexture(double u, double v, Picture* pic);
Color loadTexture(int x, int y, Picture* pic);


extern Picture picLand;
extern Picture picHouse;
extern Picture picFarmer;
extern Picture picBuilder;
extern Picture picField;
extern Picture picField1;
extern Picture picField2;
extern Picture picTree;
extern Picture picKing;
extern Picture picRice;