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

	if (object->x >DrawObject->x)
	{
		DrawObject->x += timeScale;

	}
	else if (object->x < DrawObject->x)
	{
		DrawObject->x -= timeScale;
	}
	if (object->y > DrawObject->y)
	{
		DrawObject->y += timeScale;
	}
	else if (object->y < DrawObject->y)
	{
		DrawObject->y -= timeScale;
	}
	if (TakeOnThing != NULL)
	{
		TakeOnThing->x = DrawObject->x;
		TakeOnThing->y = DrawObject->y;
		TakeOnThing->z = DrawObject->z;
	}
}






void Farmer::AI()
{
	//白天去种田
	if ((int)runtime % 30 < 15)
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