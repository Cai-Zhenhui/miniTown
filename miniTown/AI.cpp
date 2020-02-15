#include"miniTown.h"


void Farmer::AI()
{
	if (DrawObject->x + DrawObject->pic->bmpWidth > belongField->DrawObject->x)
	{
		if (DrawObject->x < belongField->DrawObject->x + belongField->DrawObject->pic->bmpWidth)
		{
			if (DrawObject->y + DrawObject->pic->bmpHeight > belongField->DrawObject->y)
			{
				if (DrawObject->y < belongField->DrawObject->y + belongField->DrawObject->pic->bmpHeight)
				{
					belongField->growingTime += (float)1/(float)LastFPS;
					
				}
			}
		}
	}
	if (belongField->growingTime < 10)
	{
		belongField->DrawObject->pic = &picField;
	}
	else if (belongField->growingTime < 20)
	{
		belongField->DrawObject->pic = &picField1;
	}
	else if (belongField->growingTime < 30)
	{
		belongField->DrawObject->pic = &picField2;
	}
	
	else if (belongField->growingTime > 40)
	{
		belongField->DrawObject->pic = &picRice;

	}
	else if (belongField->growingTime > 50)
	{
		belongField->growingTime = 0;

	}
	
	if (runtime % 30 < 15)
	{
		if (wantFoodLevel > 0)
		{
			if (belongField->DrawObject->x > DrawObject->x)
			{
				DrawObject->x++;
			}
			else if (belongField->DrawObject->x < DrawObject->x)
			{
				DrawObject->x--;
			}
			if (belongField->DrawObject->y > DrawObject->y)
			{
				DrawObject->y++;
			}
			else if (belongField->DrawObject->y < DrawObject->y)
			{
				DrawObject->y--;
			}
		}
	}
	else
	{
		if (belongHouse->DrawObject->x > DrawObject->x)
		{
			DrawObject->x++;
		}
		else if (belongHouse->DrawObject->x < DrawObject->x)
		{
			DrawObject->x--;
		}
		if (belongHouse->DrawObject->y > DrawObject->y)
		{
			DrawObject->y++;
		}
		else if (belongHouse->DrawObject->y < DrawObject->y)
		{
			DrawObject->y--;
		}
	}
	
	
}