#include"miniTown.h"
using namespace std;


Picture picLand;
Picture picHouse;
Picture picFarmer;
Picture picBuilder;
Picture picField;
Picture picTree;
Picture picKing;

const int MaxHouseSum = 10 * 10;
const int MaxFieldSum = 10 * 10;
const int MaxTreeSum = 10 * 10;
int NowHouseSum = 0;
int NowFieldSum = 0;
int NowTreeSum = 0;
Object House[MaxHouseSum];
Object Farmer;
Object Builder;
Object Field[MaxFieldSum];
Object Tree[MaxTreeSum];
Object King;

void initLoadPic()
{
	readBmp("pic/land.bmp", picLand);
	readBmp("pic/house.bmp", picHouse);
	readBmp("pic/farmer.bmp", picFarmer);
	readBmp("pic/builder.bmp", picBuilder);
	readBmp("pic/field.bmp", picField);
	readBmp("pic/tree.bmp", picTree);
	readBmp("pic/king.bmp", picKing);
}

void initObject()
{

	srand(time(NULL));
	for (int i = 0; i < NowHouseSum; i++)
	{
		House[i].pic = &picHouse;
		House[i].x = (rand()%10)*House[i].pic->bmpWidth;
		House[i].y = (rand() % 10) * House[i].pic->bmpHeight;
		
		AddDrawObject(&House[i]);
	}

	for (int i = 0; i < NowFieldSum; i++)
	{
		Field[i].pic = &picField;
		Field[i].x = (rand() % 10) * House[i].pic->bmpWidth;
		Field[i].y = (rand() % 10) * House[i].pic->bmpHeight;
		AddDrawObject(&Field[i]);
	}
	for (int i = 0; i < NowTreeSum; i++)
	{
		Tree[i].pic = &picTree;
		Tree[i].x = (rand() % 10) * Tree[i].pic->bmpWidth;
		Tree[i].y = (rand() % 10) * Tree[i].pic->bmpHeight;
		AddDrawObject(&Tree[i]);
	}

	
	
	Farmer.x = 300;
	Farmer.y = 300;
	Farmer.pic = &picFarmer;
	AddDrawObject(&Farmer);

	Builder.x = 400;
	Builder.y = 400;
	Builder.pic = &picBuilder;
	AddDrawObject(&Builder);

	King.x = 500;
	King.y = 500;
	King.pic = &picKing;
	AddDrawObject(&King);


	
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
	int runtime = 0;


	while (1)
	{
		KeyControl();
		MsgGet();
		Draw();
		
		Sleep(1);

		frame++;
		stop = time(NULL);
		if (stop - start >= 1)
		{
			runtime++;
			start = stop;
			char title[200];
			sprintf_s(title, "FPS %d ", frame);
			SetWindowText(screen_handle, title);
			frame = 0;
			cout << "run time:" << runtime << endl;
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
		Farmer.y--;
	}
	if (screen_keys['S'])
	{
		Farmer.y++;
	}
	if (screen_keys['A'])
	{
		Farmer.x--;
	}
	if (screen_keys['D'])
	{
		Farmer.x++;
	}
}