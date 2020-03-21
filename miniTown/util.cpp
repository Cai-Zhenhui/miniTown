#include"miniTown.h"


//�ж�����object�Ƿ�Ӵ�
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

//�жϸ���Ʒ�ǲ���rice
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


//��������Object�����ľ���
float DistanceAToB(Object* A, Object* B)
{
	float distance;
	distance = sqrt((A->x+A->pic->bmpWidth/2 - (B->x+B->pic->bmpWidth/2)) * (A->x + A->pic->bmpWidth / 2 - (B->x + B->pic->bmpWidth / 2)) +
		(A->y+A->pic->bmpHeight/2 - (B->y+B->pic->bmpHeight/2)) * (A->y + A->pic->bmpHeight / 2 - (B->y + B->pic->bmpHeight / 2)));
	return distance;
}