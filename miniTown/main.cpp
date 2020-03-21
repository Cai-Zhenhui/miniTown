#include"miniTown.h"
using namespace std;


Picture picLand;
Picture picHouse;
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


int NowHouseSum = 2;
int NowFieldSum = 1;
int NowTreeSum = 1;
int NowRiceSum = 0;
int NowWoodSum = 0;
Object objHouse[MaxHouseSum];
Object objFarmer;
Object objBuilder;
Object objField[MaxFieldSum];
Object objRice[MaxRiceSum];
Object objTree[MaxTreeSum];
Object objWood[MaxWoodSum];

Object king;

Object objSun;

Farmer farmer;
Builder builder;
Field field[MaxFieldSum];
Tree tree[MaxTreeSum];
House house[2];


float runtime = 0;
float timeScale = 1;
int LastFPS = 0;


void initLoadPic()
{
	readBmp("pic/land.bmp", picLand);
	readBmp("pic/house.bmp", picHouse);
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
	farmer.DrawObject = &objFarmer;
	farmer.belongField = &field[0];
	farmer.belongHouse = &house[0];
	farmer.age = 18;
	farmer.monney = 10;
	farmer.wantFoodLevel = 1;
	farmer.wantSexLevel = 1;
	
	field[0].DrawObject = &objField[0];
	field[0].id = 0;
	field[0].growingTime = 0;

	tree[0].DrawObject = &objTree[0];
	tree[0].id = 0;


	builder.DrawObject = &objBuilder;
	builder.belongHouse = &house[1];
	builder.age = 18;
	builder.money = 10;
	builder.wantFoodLevel = 1;
	builder.wantSexLevel = 1;

	
	
	house[0].DrawObject = &objHouse[0];
	house[0].id = 0;
	house[1].DrawObject = &objHouse[1];
	house[1].id = 1;


	srand(time(NULL));
	for (int i = 0; i < NowHouseSum; i++)
	{
		objHouse[i].pic = &picHouse;
		objHouse[i].x = (rand()%10)*objHouse[i].pic->bmpWidth;
		objHouse[i].y = (rand() % 10) * objHouse[i].pic->bmpHeight;
		
		AddDrawObject(&objHouse[i]);
	}

	for (int i = 0; i < NowFieldSum; i++)
	{
		objField[i].pic = &picField;
		objField[i].x = (rand() % 10) * objHouse[i].pic->bmpWidth;
		objField[i].y = (rand() % 10) * objHouse[i].pic->bmpHeight;
		AddDrawObject(&objField[i]);
	}
	for (int i = 0; i < NowTreeSum; i++)
	{
		objTree[i].pic = &picTree;
		objTree[i].x = (rand() % 10) * objTree[i].pic->bmpWidth;
		objTree[i].y = (rand() % 10) * objTree[i].pic->bmpHeight;
		AddDrawObject(&objTree[i]);
	}

	
	
	objFarmer.x = 300;
	objFarmer.y = 300;
	objFarmer.pic = &picFarmer;
	AddDrawObject(&objFarmer);

	objBuilder.x = 400;
	objBuilder.y = 400;
	objBuilder.pic = &picBuilder;
	AddDrawObject(&objBuilder);

	objSun.pic = &picSun;
	objSun.x = 0;
	objSun.y = 0;
	AddDrawObject(&objSun);
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

		farmer.AI();
		builder.AI();

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
		objFarmer.y--;
	}
	if (screen_keys['S'])
	{
		objFarmer.y++;
	}
	if (screen_keys['A'])
	{
		objFarmer.x--;
	}
	if (screen_keys['D'])
	{
		objFarmer.x++;
	}
}