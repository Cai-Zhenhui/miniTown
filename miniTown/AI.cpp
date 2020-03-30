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
//��һ��ˮ���ظ�һ��ʳ��ˮƽ
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

	//����ȥ����������
	//��һ���0.2��0.8����ȥ�ɻ�
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

			//�п������ķ��Ӿ���ȥ��
			if (this->OwnHouseCount > 0)
			{
				WalkTo(king.DrawObject);
				if (IsMoreCloseTo(this->DrawObject, king.DrawObject))
				{
					this->HouseForMoney();
				}
			}
			//�����Է����Ҽ���û�����ҽ���ûȥ�����
			else if (wantFoodLevel > 0&&this->belongHouse->StoneRiceSum==0
				&&isBuyRiceFinish==false)
			{
				
				if (isTryBuyRice == false)
				{
					//����һ��ˮ���ͻ�ȥ
					if (this->money < RicePrice)
					{
						isTryBuyRice = true;
					}
					//ȥ�峤����ˮ��
					WalkTo(king.belongHouse->DrawObject);
					if (IsMoreCloseTo(this->DrawObject, king.belongHouse->DrawObject))
					{
						BuyRice();
						isTryBuyRice = true;
					}
				}
				else
				{
					//�����߻ؼ�
					WalkTo(this->belongHouse->DrawObject);
					if (IsMoreCloseTo(this->DrawObject, this->belongHouse->DrawObject))
					{
						while(TakeOnThingSum>0&& ObjectIsRice(this->TakeOnThing[this->TakeOnThingSum - 1])==true)
						//�ж�һ�����ϵĶ����ǲ���ˮ��
						{	
							//�ǵĻ�����������ˮ���Ž�����
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
		//����ȥ˯��
		WalkTo(belongHouse->DrawObject);
		//������
		if (IsMoreCloseTo(DrawObject, belongHouse->DrawObject))
		{
			//���˾ͳԷ�
			Eat();
			//Ȼ��˯��
			Sleep();
			if (ObjectIsWood(TakeOnThing[TakeOnThingSum-1]))
			{
				PutWood();
			}
			if (ObjectIsRice(TakeOnThing[TakeOnThingSum - 1]))
			{
				PutRice();
			}
			//˯��ʱ����������״̬
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
	int wantBuyRiceSum = wantFoodLevel + 3; //����Ҫ��ˮ��������
	
	//��������򲻵���ô��ͼ�һ����
	while (this->money < wantBuyRiceSum * RicePrice||king.belongHouse->StoneRiceSum<=wantBuyRiceSum)
	{
		wantBuyRiceSum--;
	}
	//����ͻ�ȥ
	if (wantBuyRiceSum == 0)
	{
		return false;
	}
	else //�����
	{
		for (int i = 0; i < wantBuyRiceSum; i++)
		{
			//����һ��ˮ��������
			this->TakeOnThing[i] = king.belongHouse->StoneRice[king.belongHouse->StoneRiceSum - 1];
			king.belongHouse->StoneRiceSum--;
			king.monney += RicePrice;
			this->TakeOnThingSum++;
			this->money -= RicePrice;
			AddDrawObject(this->TakeOnThing[TakeOnThingSum - 1]);//���������õ�ˮ��
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
	//����ȥ����
	//��һ���0.2��0.8����ȥ�ɻ�
	if (DayTimeNow > 0.2 && DayTimeNow < 0.7)
	{
		if (wantFoodLevel > 0||wantSexLevel>0)
		{
			//�����һ��ˮ������ȥ��
			if (belongHouse->StoneRiceSum > 0)
			{
				//cout << "take On thing sum " << TakeOnThingSum << endl;
				//�ӷ�������һ��ˮ������
				
				if (TakeOnThingSum == 0)
				{
					if (IsMoreCloseTo(DrawObject, belongHouse->DrawObject))
					{
						GetARiceToHand();
					}
					WalkTo(belongHouse->DrawObject);
					
				}

				//����õ�ˮ������ȥ��
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
		//����ȥ˯��
		WalkTo(belongHouse->DrawObject);
		//������
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

//���׸��峤����Ǯ
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


//�ڴ峤��ǰλ������һ���Ƿ��ӵı�ǣ�ľ������ȥ�Ƿ���
bool King::SetUnFinishHouseMark()
{
	if (monney >= FirstPayHousePrice)
	{
		//��õ�ǰλ�õ�����
		coord CoordHere = GetCoord(this->DrawObject);
		//�������������걻���ˣ����˳�
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