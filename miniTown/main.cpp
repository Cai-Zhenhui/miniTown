#include"miniTown.h"
using namespace std;

Object Flag;

int main()
{
	Flag.x = 100;
	Flag.y = 100;

	const char* title = _T("miniTown");
	if (screen_init(SCREEN_WIDTH, SCREEN_HEIGHT, title))
	{
		return -1;
	}
	
	cout << "miniTown" << endl;
	readBmp("1~1.bmp");
	while (1)
	{
		KeyControl();
		MsgGet();
		Draw();
		
		Sleep(1);
	}

	return 0;
}




