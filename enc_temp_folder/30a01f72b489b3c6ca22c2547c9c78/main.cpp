#include"miniTown.h"
using namespace std;


Picture picLand;
Picture picHouse;
Picture picHouse1;
Picture picFarmer;
Picture picBuilder;
Picture picField;
Picture picField1;
Picture picField2;
Picture picTree;
Picture picKing;
Picture picRice;
Picture picWood;
Picture picSun;


int NowHouseSum = 0;
int NowFieldSum = 0;
int NowTreeSum = 0;
int NowRiceSum = 0;
int NowWoodSum = 0;
int NowFarmerSum = 0;
int NowBuilderSum = 0;
Object objHouse[MaxHouseSum];
Object objFarmer[MaxFarmerSum];
Object objBuilder[MaxBuilderSum];
Object objField[MaxFieldSum];
Object objRice[MaxRiceSum];
Object objTree[MaxTreeSum];
Object objWood[MaxWoodSum];



Object king;

Object objSun;

Farmer farmer[MaxFarmerSum];
Builder builder[MaxBuilderSum];
Field field[MaxFieldSum];
Tree tree[MaxTreeSum];
House house[MaxHouseSum];


float runtime = 0;
float timeScale = 1;
int LastFPS = 0;


void initLoadPic()
{
	readBmp("pic/land.bmp", picLand);
	readBmp("pic/house.bmp", picHouse);
	readBmp("pic/house1.bmp", picHouse1);
	readBmp("pic/farmer.bmp", picFarmer);
	readBmp("pic/builder.bmp", picBuilder);
	readBmp("pic/field.bmp", picField);
	readBmp("pic/tree.bmp", picTree);
	readBmp("pic/king.bmp", picKing);
	readBmp("pic/field1.bmp", picField1);
	readBmp("pic/field2.bmp", picField2);
	readBmp("pic/rice.bmp", picRice);
	readBmp("pic/wood.bmp", picWood);
	readBmp("pic/sun.bmp", picSun);
	cout << "Load Pic OK!" << endl;
}

void initObject()
{
	
	AddField(0, 1);
	AddField(0, 4);
	AddTree(0, 0);
	
	AddFinishHouse(1, 1);
	AddFinishHouse(1, 2);
	
	srand(time(NULL));

	AddFarmer(2, 3);
	AddBuilder(4, 4);

	objSun.pic = &picSun;
	objSun.x = 0;
	objSun.y = 0;
	AddDrawObject(&objSun);

	AddUnFinishHouse(5, 5);
	/*
	builder.x = 400;
	builder.y = 400;
	builder.pic = &picBuilder;
	AddDrawObject(&builder);

	king.x = 500;
	king.y = 500;
	king.pic = &picKing;
	AddDrawObject(&king);
	*/
}

int main()
{

	const char* title = _T("miniTown");
	if (screen_init(SCREEN_WIDTH, SCREEN_HEIGHT, title))
	{
		return -1;
	}
	
	
	cout << "miniTown" << endl;

	initLoadPic();
	initObject();

	int frame = 0;
	time_t start, stop;
	start = time(NULL);
	
	//cout << "Time scale?";

	//cin >> timeScale;
	timeScale = 2;
	
	while (1)
	{
		KeyControl();
		MsgGet();
		Draw();
		
		Sleep(1);

		farmer[0].AI();
		builder[0].AI();
		

		frame++;
		stop = time(NULL);
		if (stop - start >= 1)
		{
			runtime+=timeScale;
			objSun.x = ((int)runtime % DayTime)*SCREEN_WIDTH/DayTime;
			
			start = stop;
			char title[200];
			sprintf_s(title, "FPS %d ", frame);
			SetWindowText(screen_handle, title);
			LastFPS = frame;
			frame = 0;
			//cout << "run time:" << runtime << endl;

		}

	}

	return 0;
}




void KeyControl()
{
	if (screen_keys[VK_ESCAPE])
	{
		exit(1);		//Õý³£½áÊø
	}
	if (screen_keys['W'])
	{
		objFarmer[0].y--;
	}
	if (screen_keys['S'])
	{
		objFarmer[0].y++;
	}
	if (screen_keys['A'])
	{
		objFarmer[0].x--;
	}
	if (screen_keys['D'])
	{
		objFarmer[0].x++;
	}
}