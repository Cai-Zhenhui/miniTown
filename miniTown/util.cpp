#include"miniTown.h"

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

bool ObjectIsRice(Object* object)
{
	for (int i = 0; i <= NowRiceSum; i++)
	{
		if (object == &objRice[i])
			return true;
	}

	return false;

}