#include"miniTown.h"
using namespace std;
int RicePrice=3;
int HousePrice=10;
int FirstPayHousePrice = 10;
int FieldProduceRiceSum = 5;

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
		for (int i = 0; i < FieldProduceRiceSum; i++)
		{
			belongField->AddRice();		
			TakeOnThing[TakeOnThingSum] = &objRice[NowRiceSum - 1];
			TakeOnThingSum++;
		}
		belongField->growingTime = 0;

	}
}

void Farmer::WalkTo(Object* object)
{
	DrawObject->WalkTo(object);

	for (int i = 0; i < TakeOnThingSum; i++)
	{
		if (TakeOnThing[i] != NULL)
		{
			TakeOnThing[i]->x = this->DrawObject->x;
			TakeOnThing[i]->y = this->DrawObject->y;
		}
	}
}
//吃一个水稻回复一个食欲水平
void Farmer::Eat()
{
	if (wantFoodLevel > 0&&belongHouse->StoneRiceSum>0)
	{
		belongHouse->StoneRiceSum--;
		wantFoodLevel--;
	}
}

void Farmer::Sleep()
{
	if (clkClick)
	{
		if (DaySum > LastDaySum)
		{
			wantFoodLevel++;
			cout << "want food level update " << wantFoodLevel << endl;
			LastDaySum = DaySum;
		}
		
	}

}

void Builder::WalkTo(Object* object)
{
	DrawObject->WalkTo(object);
	for (int i = 0; i < TakeOnThingSum; i++)
	{
		if (TakeOnThing[i] != NULL)
		{
			TakeOnThing[i]->x = this->DrawObject->x;
			TakeOnThing[i]->y = this->DrawObject->y;
		}
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
		this->TakeOnThing[this->TakeOnThingSum] = &objWood[NowWoodSum - 1];
		this->TakeOnThingSum++;
		std::cout << "Builder No." << this->id << " take wood!" << std:: endl;
		
	}
}


void Builder::BuildHouse()
{
	
	if (IsMoreCloseTo(this->DrawObject, AimUnFinishHouse->DrawObject) == true)
	{
		if (clkClick)
		{
			if (AimUnFinishHouse->FirstBuildMonney > 0)
			{
				this->money += AimUnFinishHouse->FirstBuildMonney;
				AimUnFinishHouse->FirstBuildMonney = 0;
			}
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

void Builder::Eat()
{
	if (wantFoodLevel > 0 && belongHouse->StoneRiceSum > 0)
	{
		belongHouse->StoneRiceSum--;
		wantFoodLevel--;
	}
}

void Builder::Sleep()
{
	if (clkClick)
	{
		if (DaySum > LastDaySum)
		{
			wantFoodLevel++;
			cout << "want food level update " << wantFoodLevel << endl;
			LastDaySum = DaySum;
			ResourceCount();
		}

	}
}

void Builder::AI()
{

	//白天去砍树或种田
	//在一天的0.2到0.8部分去干活
	if (DayTimeNow >0.2 &&DayTimeNow<0.7)
	{
		if (wantFoodLevel > 0||wantSexLevel>0)
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
				if (IsMoreCloseTo(this->DrawObject, king.DrawObject))
				{
					this->HouseForMoney();
				}
			}
			//如果想吃饭并且家里没饭并且今天没去买过则
			else if (wantFoodLevel > 0&&this->belongHouse->StoneRiceSum==0
				&&isBuyRiceFinish==false)
			{
				
				if (isTryBuyRice == false)
				{
					//买不起一个水稻就回去
					if (this->money < RicePrice)
					{
						isTryBuyRice = true;
					}
					//去村长家买水稻
					WalkTo(king.belongHouse->DrawObject);
					if (IsMoreCloseTo(this->DrawObject, king.belongHouse->DrawObject))
					{
						BuyRice();
						isTryBuyRice = true;
					}
				}
				else
				{
					//买完走回家
					WalkTo(this->belongHouse->DrawObject);
					if (IsMoreCloseTo(this->DrawObject, this->belongHouse->DrawObject))
					{
						while(TakeOnThingSum>0&& ObjectIsRice(this->TakeOnThing[this->TakeOnThingSum - 1])==true)
						//判断一下手上的东西是不是水稻
						{	
							//是的话把手里所有水稻放进家里
							PutRice();
							
							
						}
						isBuyRiceFinish = true;
					}

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
		//到家了
		if (IsMoreCloseTo(DrawObject, belongHouse->DrawObject))
		{
			//饿了就吃饭
			Eat();
			//然后睡觉
			Sleep();
			if (ObjectIsWood(TakeOnThing[TakeOnThingSum-1]))
			{
				PutWood();
			}
			if (ObjectIsRice(TakeOnThing[TakeOnThingSum - 1]))
			{
				PutRice();
			}
			//睡觉时重置这两个状态
			isTryBuyRice = false;
			isBuyRiceFinish = false;
		}
	}

}

void Builder::PutWood()
{
	belongHouse->StoneWood[belongHouse->StoneWoodSum] = TakeOnThing[TakeOnThingSum-1];
	belongHouse->StoneWoodSum++;
	std::cout << "Wood In House No." <<belongHouse->id<<" Sum " << belongHouse->StoneWoodSum << std::endl;
	RemoveDrawObecjt(TakeOnThing[TakeOnThingSum-1]);
	TakeOnThing[TakeOnThingSum-1] = NULL;
	TakeOnThingSum--;
}

bool Builder::BuyRice()
{
	int wantBuyRiceSum = wantFoodLevel + 3; //现在要买水稻的数量
	
	//买不起或者买不到那么多就减一尝试
	while (this->money < wantBuyRiceSum * RicePrice||king.belongHouse->StoneRiceSum<=wantBuyRiceSum)
	{
		wantBuyRiceSum--;
	}
	//买不起就回去
	if (wantBuyRiceSum == 0)
	{
		return false;
	}
	else //买得起
	{
		for (int i = 0; i < wantBuyRiceSum; i++)
		{
			//拿起一个水稻到手上
			this->TakeOnThing[i] = king.belongHouse->StoneRice[king.belongHouse->StoneRiceSum - 1];
			king.belongHouse->StoneRiceSum--;
			king.monney += RicePrice;
			this->TakeOnThingSum++;
			this->money -= RicePrice;
			AddDrawObject(this->TakeOnThing[TakeOnThingSum - 1]);//画上手里拿的水稻
		}
	}


}

bool Builder::PutRice()
{
	if (TakeOnThingSum == 0)
	{
		return false;
	}
	belongHouse->StoneRice[belongHouse->StoneRiceSum] = TakeOnThing[TakeOnThingSum - 1];

	belongHouse->StoneRiceSum++;

	if (DebugShowGrowTimeFlag)
	{
		std::cout << "Rice In House No." << belongHouse->id << " Sum " << belongHouse->StoneRiceSum << std::endl;
	}
	RemoveDrawObecjt(TakeOnThing[TakeOnThingSum - 1]);
	TakeOnThing[TakeOnThingSum - 1] = NULL;
	TakeOnThingSum--;
	return true;
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
	//在一天的0.2到0.8部分去干活
	if (DayTimeNow > 0.2 && DayTimeNow < 0.7)
	{
		if (wantFoodLevel > 0||wantSexLevel>0)
		{
			//如果有一个水稻就拿去卖
			if (belongHouse->StoneRiceSum > 0)
			{
				//cout << "take On thing sum " << TakeOnThingSum << endl;
				//从房子里拿一个水稻来卖
				
				if (TakeOnThingSum == 0)
				{
					if (IsMoreCloseTo(DrawObject, belongHouse->DrawObject))
					{
						GetARiceToHand();
					}
					WalkTo(belongHouse->DrawObject);
					
				}

				//如果拿到水稻就拿去卖
				if (TakeOnThingSum > 0)
				{
					AddDrawObject(TakeOnThing[TakeOnThingSum - 1]);
					WalkTo(kingHouse->DrawObject);
					if (IsMoreCloseTo(DrawObject, kingHouse->DrawObject))
					{
						SellRiceForMoney();
					}
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
		//到家了
		if (IsMoreCloseTo(DrawObject, belongHouse->DrawObject))
		{
			
			while (TakeOnThingSum > 0)
			{
				if (ObjectIsRice(TakeOnThing[TakeOnThingSum-1]))
				{
					PutRice();
				}
			}
			
			Eat();
			Sleep();

		}
	}
}

void Farmer::PutRice()
{
	belongHouse->StoneRice[belongHouse->StoneRiceSum] = TakeOnThing[TakeOnThingSum-1];
	
	belongHouse->StoneRiceSum++;
	
	if (DebugShowGrowTimeFlag)
	{
		std::cout << "Rice In House No." << belongHouse->id << " Sum " << belongHouse->StoneRiceSum << std::endl;
	}
	RemoveDrawObecjt(TakeOnThing[TakeOnThingSum-1]);
	TakeOnThing[TakeOnThingSum-1] = NULL;
	TakeOnThingSum--;
	
}

void Farmer::GetARiceToHand()
{
	TakeOnThing[TakeOnThingSum] = belongHouse->StoneRice[belongHouse->StoneRiceSum - 1];
	TakeOnThingSum++;
}

void Farmer::GetAllRiceToHand()
{
	for (int i = 0; i < belongHouse->StoneRiceSum; i++)
	{
		TakeOnThing[TakeOnThingSum] = belongHouse->StoneRice[i];
		TakeOnThingSum++;
	}
	//belongHouse->StoneRiceSum = 0;
}

//卖米给村长，换钱
bool Farmer::SellRiceForMoney()
{
	if (king.monney >= RicePrice&&TakeOnThingSum>0)
	{
		this->monney += RicePrice;
		RemoveDrawObecjt(TakeOnThing[TakeOnThingSum-1]);
		TakeOnThing[TakeOnThingSum-1] = NULL;
		TakeOnThingSum--;

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


//在村长当前位置设置一个盖房子的标记，木匠随后会去盖房子
bool King::SetUnFinishHouseMark()
{
	if (monney >= FirstPayHousePrice)
	{
		//获得当前位置的坐标
		coord CoordHere = GetCoord(this->DrawObject);
		//如果现在这个坐标被用了，则退出
		if (IsCoordUsed(CoordHere))
		{
			return false;
		}

		AddUnFinishHouse(CoordHere.x, CoordHere.y);
		monney -= FirstPayHousePrice;
		return true;
	}
	else
	{
		return false;
	}

}