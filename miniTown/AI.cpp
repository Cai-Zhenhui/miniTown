#include"miniTown.h"
using namespace std;
int RicePrice=3;
int HousePrice=10;

void AILoop()
{
	for (int i = 0; i < NowBuilderSum; i++)
	{
		builder[i].AI();
	}
	for (int i = 0; i < NowFarmerSum; i++)
	{
		farmer[i].AI();
	}
	king.AI();
}

void Farmer::GrowRice()
{
	if (DrawObject->x + DrawObject->pic->Width > belongField->DrawObject->x)
	{
		if (DrawObject->x < belongField->DrawObject->x + belongField->DrawObject->pic->Width)
		{
			if (DrawObject->y + DrawObject->pic->Height > belongField->DrawObject->y)
			{
				if (DrawObject->y < belongField->DrawObject->y + belongField->DrawObject->pic->Height)
				{
					if (LastFPS != 0)
					{
						if (clkClick)
						{
							belongField->growingTime += timeScale;
						}
						if (DebugShowGrowTimeFlag)
						{
							std::cout << "Farmer No." << this->id << " grow time " << this->belongField->growingTime << std::endl;

						}

					}
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
		TakeOnThing->x = this->DrawObject->x;
		TakeOnThing->y = this->DrawObject->y;
		//TakeOnThing->WalkTo(object);
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

House* Builder::FindAUnFinishHouse()
{
	int minDistance = 99999999;
	House* ClossestHouse = NULL;
	for (int i = 0; i < NowHouseSum; i++)
	{
		if (house[i].buildTime < house[i].RequireBuildTime)
		{
			int nowDistance = DistanceAToB(this->DrawObject, house[i].DrawObject);
			if (nowDistance < minDistance)
			{
				minDistance = nowDistance;
				ClossestHouse = &house[i];
			}
		}
		
	}
	return ClossestHouse;
}

void Builder::CutTree()
{
	if (DrawObject->x + DrawObject->pic->Width > AimTree->DrawObject->x)
	{
		if (DrawObject->x < AimTree->DrawObject->x + AimTree->DrawObject->pic->Width)
		{
			if (DrawObject->y + DrawObject->pic->Height > AimTree->DrawObject->y)
			{
				if (DrawObject->y < AimTree->DrawObject->y + AimTree->DrawObject->pic->Height)
				{
					if (LastFPS != 0)
					{
						if (clkClick == true)
						{
							AimTree->cutTime += timeScale;
						}
						
					}
					if (DebugShowGrowTimeFlag)
					{
						std::cout << "Builder No." << this->id << " cut tree take time " << this->AimTree->cutTime << std::endl;

					}
					//std::cout << AimTree->cutTime << std::endl;
				}
			}
		}
	}

	if (AimTree->cutTime > 15)
	{
		AimTree->AddWood();
		AimTree->cutTime = 0;
		this->TakeOnThing = &objWood[NowWoodSum - 1];
		std::cout << "Builder No." << this->id << " take wood!" << std:: endl;
		
	}
}


void Builder::BuildHouse()
{
	
	if (IsCloseTo(this->DrawObject, AimUnFinishHouse->DrawObject) == true)
	{
		if (clkClick)
		{
			AimUnFinishHouse->buildTime += timeScale;
		}
		//std::cout << AimUnFinishHouse->buildTime << std::endl;
	}
	
	if (AimUnFinishHouse->buildTime > house->RequireBuildTime)
	{
		AimUnFinishHouse->buildTime = AimUnFinishHouse->RequireBuildTime;
		AimUnFinishHouse->DrawObject->pic = &picHouse;
		AimUnFinishHouse = NULL;
		OwnHouseCount++;
		belongHouse->StoneWoodSum -= 3;
	}
}

void Builder::AI()
{
	//白天去砍树或种田
	if ((int)runtime % DayTime < DayTime/2)
	{
		if (wantFoodLevel > 0)
		{
			
			if (AimTree == NULL)
			{
				AimTree = FindATree();
			}
			if (AimUnFinishHouse == NULL)
			{
				AimUnFinishHouse = FindAUnFinishHouse();
			}

			//有可以卖的房子就拿去卖
			if (this->OwnHouseCount > 0)
			{
				WalkTo(king.DrawObject);
				if (IsCloseTo(this->DrawObject, king.DrawObject))
				{
					this->HouseForMoney();
				}
			}

			else if (belongHouse->StoneWoodSum >= 3&&AimUnFinishHouse!=NULL)
			{

				WalkTo(AimUnFinishHouse->DrawObject);
				BuildHouse();

			}
			else
			{
				if (AimTree != NULL)
				{
					WalkTo(AimTree->DrawObject);
					CutTree();
				}
				
			}
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
	std::cout << "Wood In House No." <<belongHouse->id<<" Sum " << belongHouse->StoneWoodSum << std::endl;
	RemoveDrawObecjt(TakeOnThing);
	TakeOnThing = NULL;
}

bool Builder::HouseForMoney()
{
	if (king.monney >= HousePrice&&this->OwnHouseCount>0)
	{
		this->money += HousePrice;
		this->OwnHouseCount--;
		king.HaveEmptyHouseSum++;
		king.monney -= HousePrice;
		cout << "Sell house for " << HousePrice << endl;
		return true;
	}
	else
	{
		return false;
	}
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
	House* kingHouse = FindKingHouse();
	//白天去种田
	if ((int)runtime % DayTime < DayTime/2)
	{
		if (wantFoodLevel > 0)
		{
			//如果有一个水稻就拿去卖
			if (belongHouse->StoneRiceSum > 0)
			{
				
				TakeOnThing = belongHouse->StoneRice[belongHouse->StoneRiceSum - 1];
				AddDrawObject(TakeOnThing);
				WalkTo(kingHouse->DrawObject);
				if (IsCloseTo(DrawObject, kingHouse->DrawObject))
				{
					SellRiceForMoney();
				}
			}
			else
			{
				WalkTo(belongField->DrawObject);

				GrowRice();
			}

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
	
	if (DebugShowGrowTimeFlag)
	{
		std::cout << "Rice In House No." << belongHouse->id << " Sum " << belongHouse->StoneRiceSum << std::endl;
	}
	RemoveDrawObecjt(TakeOnThing);
	TakeOnThing = NULL;
}

//卖米给村长，换钱
bool Farmer::SellRiceForMoney()
{
	if (king.monney >= RicePrice)
	{
		this->monney += RicePrice;
		RemoveDrawObecjt(TakeOnThing);
		TakeOnThing = NULL;

		king.monney -= RicePrice;
		king.belongHouse->StoneRice[king.belongHouse->StoneRiceSum] = this->belongHouse->StoneRice[this->belongHouse->StoneRiceSum-1];
		king.belongHouse->StoneRiceSum++;
		this->belongHouse->StoneRiceSum--;
		cout << "Sell rice for " << RicePrice << endl;

		return true;
	}
	else
	{
		return false;
	}
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
	//std::cout << "Add Rice Called!" << std::endl;
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

void King::AI()
{

}

void King::MakeMoney(int Sum)
{
	this->monney += Sum;
}

void King::DestoryMoney(int Sum)
{
	this->monney -= Sum;
	if (this->monney < 0)
	{
		this->monney = 0;
	}
}

void King::SetRicePrice(int Price)
{
	RicePrice = Price;
}

void King::SetHousePrice(int Price)
{
	HousePrice = Price;
}