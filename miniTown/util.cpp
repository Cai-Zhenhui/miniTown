#include"miniTown.h"


//判断两个object是否接触
bool IsCloseTo(Object* A, Object* B)
{
	if (A->x + A->pic->bmpWidth > B->x)
	{
		if (A->x < B->x + B->pic->bmpWidth)
		{
			if (A->y + A->pic->bmpHeight > B->y)
			{
				if (A->y < B->y + B->pic->bmpHeight)
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
	distance = sqrt((A->x+A->pic->bmpWidth/2 - (B->x+B->pic->bmpWidth/2)) * (A->x + A->pic->bmpWidth / 2 - (B->x + B->pic->bmpWidth / 2)) +
		(A->y+A->pic->bmpHeight/2 - (B->y+B->pic->bmpHeight/2)) * (A->y + A->pic->bmpHeight / 2 - (B->y + B->pic->bmpHeight / 2)));
	return distance;
}

House* findANearEmptyHouse(Object *man)
{
	House* NearEmptyHouse = NULL;
	float MinDistance = 999999;
	for (int i = 0; i < NowHouseSum; i++)
	{
		if (house[i].isUsed == false)
		{
			int nowDistance = DistanceAToB(man, house[i].DrawObject);
			if (nowDistance < MinDistance)
			{
				MinDistance = nowDistance;
				NearEmptyHouse = &house[i];
			}
		}
	}
	return NearEmptyHouse;
}

Field* findANearUnUsedField(Object* man)
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
	return NearUnUsedField;
}

void AddUnFinishHouse(int x, int y)
{
	house[NowHouseSum].buildTime = 0;
	house[NowHouseSum].DrawObject = &objHouse[NowHouseSum];
	house[NowHouseSum].DrawObject->pic = &picHouse1;
	house[NowHouseSum].id = NowHouseSum - 1;
	house[NowHouseSum].DrawObject->x = x *  picHouse.bmpWidth;
	house[NowHouseSum].DrawObject->y = y * picHouse.bmpHeight;
	AddDrawObject(house[NowHouseSum].DrawObject);
	NowHouseSum++;
	
}


void AddFinishHouse(int x, int y)
{
	house[NowHouseSum].buildTime = house[NowHouseSum].RequireBuildTime;
	house[NowHouseSum].DrawObject = &objHouse[NowHouseSum];
	house[NowHouseSum].DrawObject->pic = &picHouse;
	house[NowHouseSum].id = NowHouseSum;
	house[NowHouseSum].DrawObject->x = x * picHouse.bmpWidth;
	house[NowHouseSum].DrawObject->y = y * picHouse.bmpHeight;
	AddDrawObject(house[NowHouseSum].DrawObject);
	NowHouseSum++;
}

void AddFarmer(int x,int y)
{
	objFarmer[NowFarmerSum].pic = &picFarmer;
	objFarmer[NowFarmerSum].x = x * objFarmer[NowFarmerSum].pic->bmpWidth;
	objFarmer[NowFarmerSum].y = y * objFarmer[NowFarmerSum].pic->bmpHeight;

	farmer[NowFarmerSum].DrawObject = &objFarmer[NowFarmerSum];
	farmer[NowFarmerSum].belongField = findANearUnUsedField(farmer[NowFarmerSum].DrawObject);
	farmer[NowFarmerSum].belongHouse = findANearEmptyHouse(farmer[NowFarmerSum].DrawObject);
	farmer[NowFarmerSum].belongHouse->isUsed = true;
	farmer[NowFarmerSum].belongField->isUsed = true;
	farmer[NowFarmerSum].age = 18;
	farmer[NowFarmerSum].monney = 10;
	farmer[NowFarmerSum].wantFoodLevel = 1;
	farmer[NowFarmerSum].wantSexLevel = 1;
	

	AddDrawObject(farmer[NowFarmerSum].DrawObject);
	NowFarmerSum++;
}

void AddBuilder(int x, int y)
{
	objBuilder[NowBuilderSum].pic = &picBuilder;
	objBuilder[NowBuilderSum].x = x*objBuilder[NowBuilderSum].pic->bmpWidth;
	objBuilder[NowBuilderSum].y = y*objBuilder[NowBuilderSum].pic->bmpHeight;

	builder[NowBuilderSum].DrawObject = &objBuilder[NowBuilderSum];
	builder[NowBuilderSum].belongHouse = findANearEmptyHouse(builder[NowBuilderSum].DrawObject);
	builder[NowBuilderSum].belongHouse->isUsed = true;
	builder[NowBuilderSum].age = 18;
	builder[NowBuilderSum].money = 10;
	builder[NowBuilderSum].wantFoodLevel = 1;
	builder[NowBuilderSum].wantSexLevel = 1;

	AddDrawObject(builder[NowBuilderSum].DrawObject);
	NowBuilderSum++;
}

void AddTree(int x, int y)
{
	objTree[NowTreeSum].pic = &picTree;
	objTree[NowTreeSum].x = x * picTree.bmpWidth;
	objTree[NowTreeSum].y = y * picTree.bmpHeight;

	tree[NowTreeSum].DrawObject = &objTree[NowTreeSum];
	tree[NowTreeSum].id = NowTreeSum ;

	AddDrawObject(&objTree[NowTreeSum]);
	NowTreeSum++;

}

void AddField(int x, int y)
{
	objField[NowFieldSum].pic = &picField;
	objField[NowFieldSum].x = x * picField.bmpWidth;
	objField[NowFieldSum].y = y * picField.bmpHeight;

	field[NowFieldSum].DrawObject = &objField[NowFieldSum];
	field[NowFieldSum].id = NowFieldSum ;
	field[NowFieldSum].growingTime = 0;

	AddDrawObject(&objField[NowFieldSum]);
	NowFieldSum++;

}