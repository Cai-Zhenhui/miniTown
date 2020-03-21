#include"miniTown.h"

void Farmer::GrowRice()
{
	if (DrawObject->x + DrawObject->pic->bmpWidth > belongField->DrawObject->x)
	{
		if (DrawObject->x < belongField->DrawObject->x + belongField->DrawObject->pic->bmpWidth)
		{
			if (DrawObject->y + DrawObject->pic->bmpHeight > belongField->DrawObject->y)
			{
				if (DrawObject->y < belongField->DrawObject->y + belongField->DrawObject->pic->bmpHeight)
				{
					belongField->growingTime += (float)1 / (float)LastFPS * timeScale;
				}
			}
		}
	}
	if (belongField->growingTime < 5)
	{
		belongField->DrawObject->pic = &picField;
	}
	else if (belongField->growingTime < 10)
	{
		belongField->DrawObject->pic = &picField1;
	}
	else if (belongField->growingTime < 20)
	{
		belongField->DrawObject->pic = &picField2;
	}
	else if (belongField->growingTime < 30)
	{
		belongField->AddRice();
		belongField->growingTime = 0;
		TakeOnThing= &objRice[NowRiceSum-1];
	}
}

void Farmer::WalkTo(Object* object)
{
	DrawObject->WalkTo(object);
	if (TakeOnThing != NULL)
	{
		TakeOnThing->WalkTo(object);
	}
}

void Builder::WalkTo(Object* object)
{
	DrawObject->WalkTo(object);
	if (TakeOnThing != NULL)
	{
		TakeOnThing->WalkTo(object);
	}
}

Tree* Builder::FindATree()
{
	int minDistance=99999999;
	Tree* ClosesetTree = NULL;
	for (int i = 0; i < NowTreeSum; i++)
	{
		int nowDistance= DistanceAToB(this->DrawObject, tree[i].DrawObject);
		if (nowDistance < minDistance)
		{
			minDistance = nowDistance;
			ClosesetTree = &tree[i];
		}
	}
	return ClosesetTree;
}

void Builder::CutTree()
{
	if (DrawObject->x + DrawObject->pic->bmpWidth > AimTree->DrawObject->x)
	{
		if (DrawObject->x < AimTree->DrawObject->x + AimTree->DrawObject->pic->bmpWidth)
		{
			if (DrawObject->y + DrawObject->pic->bmpHeight > AimTree->DrawObject->y)
			{
				if (DrawObject->y < AimTree->DrawObject->y + AimTree->DrawObject->pic->bmpHeight)
				{
					AimTree->cutTime += (float)1 / (float)LastFPS * timeScale;
				}
			}
		}
	}

	if (AimTree->cutTime > 15)
	{
		AimTree->AddWood();
		AimTree->cutTime = 0;
		this->TakeOnThing = &objWood[NowWoodSum - 1];
	}
}

void Builder::AI()
{
	//白天去种田
	
	if ((int)runtime % DayTime < DayTime/2)
	{
		if (wantFoodLevel > 0)
		{
			if (AimTree == NULL)
			{
				AimTree = FindATree();
			}
			WalkTo(AimTree->DrawObject);
			CutTree();
		}
	}
	else
	{
		//晚上去睡觉
		WalkTo(belongHouse->DrawObject);
		if (IsCloseTo(DrawObject, belongHouse->DrawObject))
		{
			if (ObjectIsWood(TakeOnThing))
			{
				PutWood();
			}
		}
	}

}

void Builder::PutWood()
{
	belongHouse->StoneWood[belongHouse->StoneWoodSum] = TakeOnThing;
	belongHouse->StoneWoodSum++;
	std::cout << "Wood In House Sum " << belongHouse->StoneWoodSum << std::endl;
	RemoveDrawObecjt(TakeOnThing);
	TakeOnThing = NULL;
}

void Object::WalkTo(Object* object)
{

	if (object->x >x)
	{
		x += timeScale;

	}
	else if (object->x < x)
	{
		x -= timeScale;
	}
	if (object->y > y)
	{
		y += timeScale;
	}
	else if (object->y < y)
	{
		y -= timeScale;
	}
}






void Farmer::AI()
{
	//白天去种田
	if ((int)runtime % DayTime < DayTime/2)
	{
		if (wantFoodLevel > 0)
		{
			
			WalkTo(belongField->DrawObject);
			GrowRice();
		}
	}
	else
	{
		//晚上去睡觉
		WalkTo(belongHouse->DrawObject);
		if (IsCloseTo(DrawObject, belongHouse->DrawObject))
		{
			if (ObjectIsRice(TakeOnThing))
			{
				PutRice();
			}
		}
	}
	
	
}

void Farmer::PutRice()
{
	belongHouse->StoneRice[belongHouse->StoneRiceSum] = TakeOnThing;
	belongHouse->StoneRiceSum++;
	std::cout << "Rice In House Sum " << belongHouse->StoneRiceSum <<std:: endl;
	RemoveDrawObecjt(TakeOnThing);
	TakeOnThing = NULL;
}

void Field::AI()
{

}

void Field::AddRice()
{
	Object* newObjRice = &objRice[NowRiceSum];
	newObjRice->x = this->DrawObject->x;
	newObjRice->y = this->DrawObject->y;
	newObjRice->z = 0;
	newObjRice->pic = &picRice;
	NowRiceSum++;

	AddDrawObject(newObjRice);
}

void Tree::AddWood()
{
	Object* newObjWood = &objWood[NowWoodSum];
	newObjWood->x = this->DrawObject->x;
	newObjWood->y = this->DrawObject->y;
	newObjWood->z = 0;
	newObjWood->pic = &picWood;
	NowWoodSum++;
	AddDrawObject(newObjWood);
}