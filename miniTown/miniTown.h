//
//
//  miniTown
//
//
//=============================================================================


#pragma once
#pragma once
#include<Windows.h>
#include<iostream>
#include<time.h>
#include<tchar.h>


//----------------------------------
//调试使用的全局变量
const bool DebugShowGrowTimeFlag = false;  //输出田和树木的生长、砍伐时间

//-----------------------------------


//======================================================
// 游戏引擎部分

//用于显示窗体的全局变量
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int bits = 24;
extern BYTE buffer[SCREEN_WIDTH * SCREEN_HEIGHT * bits / 8];

class coord //以60*60为单位标记坐标
{
public:
	coord(int X, int Y) :x(X), y(Y) {};
	coord() :x(0), y(0) {};
	int x, y;
};

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
	int Width;//图像的宽
	int Height;//图像的高
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
	void WalkTo(Object* object);
};

void CleanScreen();
void Draw();
extern Object* drawList[1000];
extern int drawSum;

void AddDrawObject(Object* object);
void RemoveDrawObecjt(Object* object);
void DrawPoint(int& x, int& y, const Color& color);
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


//	读取图片
bool readBmp(const char* bmpName, Picture& pic);
void DrawRect(int x, int y, int w, int h, Color color);
void DrawBmp(int x, int y, Picture* pic);
Color loadTexture(double u, double v, Picture* pic);
Color loadTexture(int x, int y, Picture* pic);


extern float runtime;
extern int LastFPS;
extern float timeScale;



const int MaxHouseSum = 10 * 10;
const int MaxFieldSum = 10 * 10;
const int MaxFarmerSum = 10 * 10;
const int MaxBuilderSum = 10 * 10;
const int MaxTreeSum = 10 * 10;
const int MaxRiceSum = 10 * 10;
const int MaxWoodSum = 10 * 10;

extern int RicePrice;
extern int HousePrice;
extern int FirstPayHousePrice; //盖房子预先给木匠的定金

class Field
{
public:
	int id;
	bool isUsed = false;
	float growingTime;
	Object *DrawObject;
	void AddRice();
	void AI();
};

class Rice
{
public:
	int id;
	Object* DrawObject;

};

class House
{
public:
	int id;
	float buildTime=0;
	const int RequireBuildTime = 30;
	int FirstBuildMonney = 0; //盖房子预付给木匠的钱
	bool isKingHouse = false;
	bool isUsed = false;
	Object *DrawObject;
	Object* StoneRice[MaxRiceSum];
	Object* StoneWood[MaxWoodSum];
	int StoneRiceSum;
	int StoneWoodSum;

	
};

class Tree
{
public:
	int id;
	Object* DrawObject;
	float cutTime = 0;
	void AddWood();
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
	Object* TakeOnThing;
	void WalkTo(Object* object);
	void GrowRice();
	void AI();
	void PutRice();
	bool SellRiceForMoney();

	
};

class Builder
{
public:
	int id;
	float age;
	int money;
	House* belongHouse;
	Tree* AimTree=NULL;
	House* AimUnFinishHouse = NULL;
	int OwnHouseCount = 0;   //拥有的还没卖出去的房子数量
	int wantFoodLevel;
	int wantSexLevel;
	int buildTime = 0;
	Object* DrawObject;
	Object* TakeOnThing;
	void WalkTo(Object* object);
	void BuildHouse();
	void CutTree();
	Tree* FindATree();
	House* FindAUnFinishHouse();
	void AI();
	void PutWood();

	bool HouseForMoney();
};

class King
{
public:
	int id;
	float age;
	int monney;
	House* belongHouse;
	Object* DrawObject;
	int wantFoodLevel;
	int wantSexLevel;
	Object* TakeOnThing;
	int HaveEmptyHouseSum=0;
	void WalkTo(Object* object);
	
	void AI();
	void MakeMoney(int Sum);
	void DestoryMoney(int Sum);
	void SetRicePrice(int Price);
	void SetHousePrice(int Price);
	bool SetUnFinishHouseMark();  //在村长当前位置设置一个盖房子的记号（木匠随后会取盖房子）需要村长花一部分钱

};



const int DayTime = 30;

extern Picture picLand;
extern Picture picHouse;
extern Picture picHouse1;
extern Picture picFarmer;
extern Picture picBuilder;
extern Picture picField;
extern Picture picField1;
extern Picture picField2;
extern Picture picTree;
extern Picture picKing;
extern Picture picRice;
extern Picture picWood;
extern Picture picSun;
extern Picture picBackground;
extern Picture picBackground1;
extern Picture picMoon;
extern Picture picKingHouse;

extern int NowHouseSum;
extern int NowFieldSum;
extern int NowTreeSum;
extern int NowRiceSum;
extern int NowWoodSum;
extern int NowFarmerSum;
extern int NowBuilderSum;

extern Object objHouse[MaxHouseSum];
extern Object objFarmer[MaxFarmerSum];
extern Object objBuilder[MaxBuilderSum];
extern Object objField[MaxFieldSum];
extern Object objRice[MaxRiceSum];
extern Object objTree[MaxTreeSum];
extern Object objWood[MaxWoodSum];
extern Object objKing;
extern Object objSun;
extern Object objMoon;
extern Object objBackground;

extern Field field[MaxFieldSum];
extern Tree tree[MaxTreeSum];
extern House house[MaxHouseSum];
extern Farmer farmer[MaxFarmerSum];
extern Builder builder[MaxBuilderSum];
extern King king;


//--------------------------------
// AI
void AILoop();



//--------------------------------
//游戏机制

extern bool clkClick;
void AddUnFinishHouse(int x, int y);
void AddFinishHouse(int x, int y,int type=0);
void AddFarmer(int x,int y);
void AddBuilder(int x,int y);
void AddTree(int x,int y);
void AddField(int x, int y);
void AddKing(int x, int y);
bool ObjectIsRice(Object* object);
bool ObjectIsWood(Object* object);


void ShowSky();

void ResourceCount();//对村民拥有的资源进行统计

bool IsCloseTo(Object* A, Object* B);  //判断两个Object是否靠近
float DistanceAToB(Object* A, Object* B);
House* GetANearEmptyHouse(Object* man,int type=0); 
Field* GetANearUnUsedField(Object* man);
House* FindKingHouse();
coord GetCoord(Object* object); //获取最接近的坐标
bool IsCoordUsed(coord Coord);