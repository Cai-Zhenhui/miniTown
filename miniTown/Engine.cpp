#include"miniTown.h"

Object* drawList[MaxDrawObjectSum];
int drawSum=0;

BYTE buffer[SCREEN_WIDTH * SCREEN_HEIGHT * bits / 8];
HWND screen_handle = NULL;		// 主窗口 HWND

void AddDrawObject(Object* object)
{
	bool findFlag = false;
	for (int i = 0; i < drawSum; i++)
	{
		if (drawList[i] == object)
		{
			findFlag = true;
		}
	}
	if (!findFlag)
	{
		drawList[drawSum] = object;
		drawSum++;
	}
}

void RemoveDrawObecjt(Object* object)
{
	int findIndex = -1;
	for (int i = 0; i < drawSum; i++)
	{
		if (drawList[i] == object)
		{
			findIndex = i;
			break;
		}
	}
	if (findIndex != -1)
	{
		for (int i = findIndex; i < drawSum-1; i++)
		{
			drawList[i] = drawList[i + 1];
		}
		drawSum--;
	}
}

void DrawPoint(int &x, int &y, const Color &color)
{
	if (x <= 0 || x >= SCREEN_WIDTH)return;
	if (y <= 0 || y >= SCREEN_HEIGHT)return;

	buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 1] = color.r;
	buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 2] = color.g;
	buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 3] = color.b;
}

void DrawPoint(int& x, int& y, int &r,int &g,int &b)
{
	if (x <= 0 || x >= SCREEN_WIDTH)return;
	if (y <= 0 || y >= SCREEN_HEIGHT)return;

	buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 1] = r;
	buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 2] = g;
	buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 3] = b;
}


void CleanScreen()
{
	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{

			buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 1] = 0;
			buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 2] = 0;
			buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 3] = 0;
		}
	}
}
void DrawRect(int x, int y, int w, int h, Color color)
{
	for (int i = y; i < y + h; i++)
	{
		for (int j = x; j < x + w; j++)
		{
			DrawPoint(j, i, color);
		}
	}
	
}
void DrawBmp(int x, int y,Picture *pic)
{
	int bufHeight;
	int bufWidth;
	int DrawX;
	int DrawY;
	int DrawR;
	int DrawG;
	int DrawB;

	for (int i = 0; i < pic->Height; i++)
	{
		bufHeight = i * pic->Width * 3;
		for (int j = 0; j < pic->Width; j++)
		{
			bufWidth = j * 3;
			DrawR = pic->pBmpBuf[bufHeight + bufWidth + 2];
			DrawG = pic->pBmpBuf[bufHeight + bufWidth + 1];
			DrawB = pic->pBmpBuf[bufHeight + bufWidth];
			
			if (DrawR != 255 || DrawG != 255 || DrawB != 255)
			{
				DrawX = x + j;
				DrawY = y + pic->Height - i;
				DrawPoint(DrawX, DrawY, DrawR, DrawG, DrawB);
			}
		}
	}

}



void Draw()
{
	CleanScreen();
	Color ColorLand = Color(192, 224, 0);
	DrawRect(0, 0, 600, 600, ColorLand);
	for (int i = 0; i < drawSum; i++)
	{
		Object* drawNowObject = drawList[i];
		DrawBmp(drawNowObject->x, drawNowObject->y, drawNowObject->pic);

	}

	screen_update();
}

int screen_w, screen_h, screen_exit = 0;
int screen_mx = 0, screen_my = 0, screen_mb = 0;
int screen_keys[512];	// 当前键盘按下状态

static HDC screen_dc = NULL;			// 配套的 HDC
static HBITMAP screen_hb = NULL;		// DIB
static HBITMAP screen_ob = NULL;		// 老的 BITMAP
static BITMAPINFO binfo;				//BITMAPINFO结构体
unsigned char* screen_fb = NULL;		// frame buffer
long screen_pitch = 0;

int screen_init(int w, int h, const TCHAR* title);	// 屏幕初始化
int screen_close(void);								// 关闭屏幕

void MsgGet(void);							// 处理消息
void screen_update(void);							// 显示 FrameBuffer

// win32 event handler
static LRESULT screen_events(HWND, UINT, WPARAM, LPARAM);

#ifdef _MSC_VER
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#endif

// 初始化窗口并设置标题
int screen_init(int w, int h, const TCHAR* title) {
	WNDCLASS wc = { CS_BYTEALIGNCLIENT, (WNDPROC)screen_events, 0, 0, 0,
		NULL, NULL, NULL, NULL, _T("SCREEN3.1415926") };
	BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB,
		w * h * 4, 0, 0, 0, 0 } };
	RECT rect = { 0, 0, w, h };
	int wx, wy, sx, sy;
	LPVOID ptr;
	HDC hDC;

	screen_close();

	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	if (!RegisterClass(&wc)) return -1;

	screen_handle = CreateWindow(_T("SCREEN3.1415926"), title,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);
	if (screen_handle == NULL) return -2;

	screen_exit = 0;
	hDC = GetDC(screen_handle);
	screen_dc = CreateCompatibleDC(hDC);
	ReleaseDC(screen_handle, hDC);

	screen_hb = CreateDIBSection(screen_dc, &bi, DIB_RGB_COLORS, &ptr, 0, 0);
	if (screen_hb == NULL) return -3;

	screen_ob = (HBITMAP)SelectObject(screen_dc, screen_hb);
	screen_fb = (unsigned char*)ptr;
	screen_w = w;
	screen_h = h;
	screen_pitch = w * 4;

	AdjustWindowRect(&rect, GetWindowLong(screen_handle, GWL_STYLE), 0);
	wx = rect.right - rect.left;
	wy = rect.bottom - rect.top;
	sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
	sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
	if (sy < 0) sy = 0;
	SetWindowPos(screen_handle, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
	SetForegroundWindow(screen_handle);

	ShowWindow(screen_handle, SW_NORMAL);
	MsgGet();

	memset(screen_keys, 0, sizeof(int) * 512);
	memset(screen_fb, 0, w * h * 4);

	ZeroMemory(&binfo, sizeof(BITMAPINFO));
	binfo.bmiHeader.biBitCount = 24;
	binfo.bmiHeader.biCompression = BI_RGB;
	binfo.bmiHeader.biHeight = -SCREEN_HEIGHT;
	binfo.bmiHeader.biPlanes = 1;
	binfo.bmiHeader.biSizeImage = 0;
	binfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	binfo.bmiHeader.biWidth = SCREEN_WIDTH;


	return 0;
}

int screen_close(void) {
	if (screen_dc) {
		if (screen_ob) {
			SelectObject(screen_dc, screen_ob);
			screen_ob = NULL;
		}
		DeleteDC(screen_dc);
		screen_dc = NULL;
	}
	if (screen_hb) {
		DeleteObject(screen_hb);
		screen_hb = NULL;
	}
	if (screen_handle) {
		CloseWindow(screen_handle);
		screen_handle = NULL;
	}
	return 0;
}

static LRESULT screen_events(HWND hWnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CLOSE: screen_exit = 1; break;
	case WM_KEYDOWN: screen_keys[wParam & 511] = 1; break;
	case WM_KEYUP: screen_keys[wParam & 511] = 0; break;
	default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

void MsgGet(void) {
	MSG msg;
	while (1) {
		if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) break;
		if (!GetMessage(&msg, NULL, 0, 0)) break;
		DispatchMessage(&msg);
	}
}

void screen_update(void) {
	HDC hDC = GetDC(screen_handle);
	SetDIBits(screen_dc, screen_hb, 0, SCREEN_HEIGHT, buffer, (BITMAPINFO*)&binfo, DIB_RGB_COLORS);

	BitBlt(hDC, 0, 0, screen_w, screen_h, screen_dc, 0, 0, SRCCOPY);

	ReleaseDC(screen_handle, hDC);
	MsgGet();
}



//=========================================================
//	读取图片

Color loadTexture(double u, double v, Picture* pic) //u ->x v ->y
{
	int y = v * pic->Height;
	int x = u * pic->Width;
	return Color(pic->pBmpBuf[y * pic->Width * 3 + x * 3 + 2], pic->pBmpBuf[y * pic->Width * 3 + x * 3 + 1], pic->pBmpBuf[y * pic->Width * 3 + x * 3]);
}

Color loadTexture(int x, int y, Picture* pic)
{
	return Color(pic->pBmpBuf[y * pic->Width * 3 + x * 3 + 2], pic->pBmpBuf[y * pic->Width * 3 + x * 3 + 1], pic->pBmpBuf[y * pic->Width * 3 + x * 3]);

}

//-----------------------------------------------------------------------------------------
//给定一个图像位图数据、宽、高、颜色表指针及每像素所占的位数等信息,将其写到指定文件中
bool readBmp(const char* bmpName, Picture& pic)
{
	FILE* fp;
	fopen_s(&fp, bmpName, "rb");//二进制读方式打开指定的图像文件
	if (fp == 0)
		return 0;

	//跳过位图文件头结构BITMAPFILEHEADER
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);
	/*
	BITMAPFILEHEADER filehead;
	fread(&filehead, 1, sizeof(BITMAPFILEHEADER), fp);
	showBmpHead(filehead);//显示文件头
*/

//定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中
	BITMAPINFOHEADER infohead;
	fread(&infohead, sizeof(BITMAPINFOHEADER), 1, fp); //获取图像宽、高、每像素所占位数等信息
	pic.Width = infohead.biWidth;
	pic.Height = infohead.biHeight;
	pic.biBitCount = infohead.biBitCount;//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
	//showBmpInforHead(infohead);//显示信息头 


	int lineByte = (pic.Width * pic.biBitCount / 8 + 3) / 4 * 4;//灰度图像有颜色表，且颜色表表项为256
	if (pic.biBitCount == 8)
	{
		//申请颜色表所需要的空间，读颜色表进内存
		pic.pColorTable = new RGBQUAD[256];
		fread(pic.pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	//申请位图数据所需要的空间，读位图数据进内存
	pic.pBmpBuf = new unsigned char[lineByte * pic.Height];
	fread(pic.pBmpBuf, 1, lineByte * pic.Height, fp);
	fclose(fp);//关闭文件
	return 1;//读取文件成功
}

