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