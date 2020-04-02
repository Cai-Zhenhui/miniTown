#include"miniTown.h"
using namespace std;



bool IsMoreCloseTo(Object* A, Object* B)
{
	if (A->x + A->pic->Width/2 > B->x)
	{
		if (A->x< B->x + B->pic->Width/2)
		{
			if (A->y + A->pic->Height/2 > B->y)
			{
				if (A->y < B->y + B->pic->Height/2)
				{
					return true;
				}
			}
		}
	}
	return false;
}

//判断两个object是否接触
bool IsCloseTo(Object* A, Object* B)
{
	if (A->x + A->pic->Width > B->x)
	{
		if (A->x < B->x + B->pic->Width)
		{
			if (A->y + A->pic->Height > B->y)
			{
				if (A->y < B->y + B->pic->Height)
				{
					return true;
				}
			}
		}
	}
	return false;
}

//判断该物品是不是rice
bool ObjectIsRice(Object* object)
{
	if (object == NULL)
	{
		return false;
	}
	for (int i = 0; i <= NowRiceSum; i++)
	{
		if (object == &objRice[i])
			return true;
	}

	return false;

}

bool ObjectIsWood(Object* object)
{
	if (object == NULL)
	{
		return false;
	}
	for (int i = 0; i < NowWoodSum; i++)
	{
		if (object == &objWood[i])
		{
			return true;
		}
	}
	return false;
}


//计算两个Object的中心距离
float DistanceAToB(Object* A, Object* B)
{
	float distance;
	distance = sqrt((A->x+A->pic->Width/2 - (B->x+B->pic->Width/2)) * (A->x + A->pic->Width / 2 - (B->x + B->pic->Width / 2)) +
		(A->y+A->pic->Height/2 - (B->y+B->pic->Height/2)) * (A->y + A->pic->Height / 2 - (B->y + B->pic->Height / 2)));
	return distance;
}


//寻找离DrawObject最近的一个房子，找到了把它上锁
//type=0时是普通房子，1是村长房子
House* GetANearEmptyHouse(Object *man,int type)
{
	House* NearEmptyHouse = NULL;
	float MinDistance = 999999;
	for (int i = 0; i < NowHouseSum; i++)
	{
		if (house[i].isUsed == false)
		{
			if ((type == 0 && house[i].isKingHouse == false) || (type == 1 && house[i].isKingHouse == true))
			{
				int nowDistance = DistanceAToB(man, house[i].DrawObject);
				if (nowDistance < MinDistance)
				{
					MinDistance = nowDistance;
					NearEmptyHouse = &house[i];
				}
			}
		}
	}
	if (NearEmptyHouse != NULL)
	{
		NearEmptyHouse->isUsed = true;
	}
	return NearEmptyHouse;
}

//找到一个离DrawObject最近的田，找到了把它上锁
Field* GetANearUnUsedField(Object* man)
{
	Field* NearUnUsedField = NULL;
	float MinDistance = 999999;
	for (int i = 0; i < NowFieldSum; i++)
	{
		if (field[i].isUsed == false)
		{
			int nowDistance = DistanceAToB(man, field[i].DrawObject);
			if (nowDistance < MinDistance)
			{
				MinDistance = nowDistance;
				NearUnUsedField = &field[i];
			}
		}
	}
	if (NearUnUsedField != NULL)
	{
		NearUnUsedField->isUsed = true;
	}
	return NearUnUsedField;
}

void AddUnFinishHouse(int x, int y)
{
	house[NowHouseSum].buildTime = 0;
	house[NowHouseSum].DrawObject = &objHouse[NowHouseSum];
	house[NowHouseSum].DrawObject->pic = &picHouse1;
	house[NowHouseSum].id = NowHouseSum - 1;
	house[NowHouseSum].DrawObject->x = x *  picHouse.Width;
	house[NowHouseSum].DrawObject->y = y * picHouse.Height;
	house[NowHouseSum].FirstBuildMoney = FirstPayHousePrice;
	AddDrawObject(house[NowHouseSum].DrawObject);
	NowHouseSum++;
	
}


void AddFinishHouse(int x, int y,int type)
{
	house[NowHouseSum].buildTime = house[NowHouseSum].RequireBuildTime;
	house[NowHouseSum].DrawObject = &objHouse[NowHouseSum];
	house[NowHouseSum].DrawObject->pic = &picHouse;
	house[NowHouseSum].id = NowHouseSum;
	house[NowHouseSum].DrawObject->x = x * picHouse.Width;
	house[NowHouseSum].DrawObject->y = y * picHouse.Height;
	if (type == 1)
	{
		house[NowHouseSum].isKingHouse = true;
		house[NowHouseSum].DrawObject->pic = &picKingHouse;
	}
	
	AddDrawObject(house[NowHouseSum].DrawObject);
	NowHouseSum++;
}

void AddFarmer(int x,int y,int sex)
{
	objFarmer[NowFarmerSum].pic = &picFarmer;
	objFarmer[NowFarmerSum].x = x * objFarmer[NowFarmerSum].pic->Width;
	objFarmer[NowFarmerSum].y = y * objFarmer[NowFarmerSum].pic->Height;

	farmer[NowFarmerSum].DrawObject = &objFarmer[NowFarmerSum];
	farmer[NowFarmerSum].belongField = GetANearUnUsedField(farmer[NowFarmerSum].DrawObject);
	farmer[NowFarmerSum].belongHouse = GetANearEmptyHouse(farmer[NowFarmerSum].DrawObject);
	farmer[NowFarmerSum].age = 18;
	farmer[NowFarmerSum].money = 10;
	farmer[NowFarmerSum].wantFoodLevel = 1;
	farmer[NowFarmerSum].wantSexLevel = 0;
	farmer[NowFarmerSum].id = NowFarmerSum;
	farmer[NowFarmerSum].Sex = sex;
	

	AddDrawObject(farmer[NowFarmerSum].DrawObject);
	NowFarmerSum++;
}

void AddBuilder(int x, int y,int sex)
{
	objBuilder[NowBuilderSum].pic = &picBuilder;
	objBuilder[NowBuilderSum].x = x*objBuilder[NowBuilderSum].pic->Width;
	objBuilder[NowBuilderSum].y = y*objBuilder[NowBuilderSum].pic->Height;

	builder[NowBuilderSum].DrawObject = &objBuilder[NowBuilderSum];
	builder[NowBuilderSum].belongHouse = GetANearEmptyHouse(builder[NowBuilderSum].DrawObject);
	builder[NowBuilderSum].age = 18;
	builder[NowBuilderSum].money = 10;
	builder[NowBuilderSum].wantFoodLevel = 1;
	builder[NowBuilderSum].wantSexLevel = 0;
	builder[NowBuilderSum].id = NowBuilderSum;
	builder[NowBuilderSum].Sex = sex;

	AddDrawObject(builder[NowBuilderSum].DrawObject);
	NowBuilderSum++;
}

void AddKing(int x, int y,int sex)
{
	objKing.pic = &picKing;
	objKing.x = x * objKing.pic->Width;
	objKing.y = y * objKing.pic->Height;
	king.Sex = sex;

	king.DrawObject = &objKing;
	king.belongHouse = GetANearEmptyHouse(king.DrawObject,1);
	king.belongHouse->isUsed = true;
	king.id = 0;
	king.age = 18;
	king.money = 0;
	king.wantFoodLevel = 1;
	king.wantSexLevel = 1;
	AddDrawObject(king.DrawObject);
}

void AddTree(int x, int y)
{
	objTree[NowTreeSum].pic = &picTree;
	objTree[NowTreeSum].x = x * picTree.Width;
	objTree[NowTreeSum].y = y * picTree.Height;
	tree[NowTreeSum].cutTime = 0;
	tree[NowTreeSum].DrawObject = &objTree[NowTreeSum];
	tree[NowTreeSum].id = NowTreeSum ;
	

	AddDrawObject(&objTree[NowTreeSum]);
	NowTreeSum++;

}

void AddField(int x, int y)
{
	objField[NowFieldSum].pic = &picField;
	objField[NowFieldSum].x = x * picField.Width;
	objField[NowFieldSum].y = y * picField.Height;

	field[NowFieldSum].DrawObject = &objField[NowFieldSum];
	field[NowFieldSum].id = NowFieldSum ;
	field[NowFieldSum].growingTime = 0;
	field[NowFieldSum].isUsed = false;

	AddDrawObject(&objField[NowFieldSum]);
	NowFieldSum++;
}


void ResourceCount()//对村民拥有的资源进行统计
{
	int moneyCount = 0;
	int riceCount = 0;
	int woodCount = 0;
	int FinishHouseCount = 0;
	int UnFinishHouseCount = 0;

	for (int i = 0; i < NowHouseSum; i++)
	{
		if (house[i].isUsed == true)
		{
			riceCount += house[i].StoneRiceSum;
			woodCount += house[i].StoneWoodSum;
		}
	}

	for (int i = 0; i < NowFarmerSum; i++)
	{
		moneyCount += farmer[i].money;
	}
	for (int i = 0; i < NowBuilderSum; i++)
	{
		moneyCount += builder[i].money;
	}
	moneyCount += king.money;

	for (int i = 0; i < NowHouseSum; i++)
	{
		if (house[i].buildTime == house[i].RequireBuildTime)
		{
			FinishHouseCount++;
		}
		else
		{
			UnFinishHouseCount++;
		}
	}

	cout << "==================" << endl;
	cout << "ResourceCount" << endl;
	cout << "DrawObjectSum:" << drawSum << endl;
	cout << "money:" << moneyCount << endl;
	cout << "rice:" << riceCount << endl;
	cout << "wood:" << woodCount << endl;
	cout << "house:" << FinishHouseCount << endl;
	cout << "Unfinish house:" << UnFinishHouseCount << endl;
	
	cout << endl;


	cout << "Farmer:" << endl;
	cout << "id\tsex\tmoney\tage\trice\twFood\twSex" << endl;
	for (int i = 0; i < NowFarmerSum; i++)
	{
		cout << farmer[i].id << "\t" <<((farmer[i].Sex==1)?"man":"woman")<<"\t"<< farmer[i].money << "\t" << farmer[i].age<<"\t"<<farmer[i].belongHouse->StoneRiceSum<<"\t"<<farmer[i].wantFoodLevel<<"\t"<<farmer[i].wantSexLevel << endl;
	}
	cout << "Builder:" << endl;
	cout << "id\tsex\tmoney\tage\trice\tHouse\tWood\twFood\twSex" << endl;
	for (int i = 0; i < NowBuilderSum; i++)
	{
		cout << builder[i].id << "\t"<<((builder[i].Sex==1) ? "man" : "woman")<<"\t" << builder[i].money << "\t" << builder[i].age<<"\t"<<builder[i].belongHouse->StoneRiceSum<<"\t"<<builder[i].OwnHouseCount<<"\t"<<builder[i].belongHouse->StoneWoodSum<<"\t"<<builder[i].wantFoodLevel<<"\t"<<builder[i].wantSexLevel << endl;
	}
	cout << "King:" << endl;
	cout << "sex\tmoney\tage\tHouse\tRice" << endl;
	cout << king.Sex<<"\t"<< king.money << "\t" << king.age << "\t" << king.HaveEmptyHouseSum<<"\t"<<king.belongHouse->StoneRiceSum << endl;
	cout << "==================" << endl;
	
}


void ShowSky()
{
	//白天显示太阳和background
	objSun.x = ((int)runtime % DayTime) * SCREEN_WIDTH / DayTime*2-objSun.pic->Width;
	objMoon.x = (((int)runtime) % DayTime) * SCREEN_WIDTH / DayTime * 2 - SCREEN_WIDTH-objMoon.pic->Width;
	if(((int)runtime/(DayTime/2))%2==1)
	{
		objBackground.pic = &picBackground1;
	}
	else
	{
		objBackground.pic = &picBackground;
	}
}

House* FindKingHouse()
{
	return king.belongHouse;
}

coord GetCoord(Object* object)
{
	int x = (object->x+object->pic->Width/2) / 60;
	int y = (object->y+object->pic->Height/2) / 60;
	return coord(x,y);
}

bool IsCoordUsed(coord Coord)
{

	for (int i = 0; i < NowHouseSum; i++)
	{
		if (house[i].DrawObject->x == Coord.x * house[i].DrawObject->pic->Width && house[i].DrawObject->y == Coord.y * house[i].DrawObject->pic->Height)
		{
			return true;
		}
	}
	for (int i = 0; i < NowFieldSum; i++)
	{
		if (field[i].DrawObject->x == Coord.x * field[i].DrawObject->pic->Width && field[i].DrawObject->y == Coord.y * field[i].DrawObject->pic->Height)
		{
			return true;
		}
	}
	for (int i = 0; i < NowTreeSum; i++)
	{
		if (tree[i].DrawObject->x == Coord.x * tree[i].DrawObject->pic->Width && tree[i].DrawObject->y == Coord.y * tree[i].DrawObject->pic->Height)
		{
			return true;
		}
	}
	return false;
}
