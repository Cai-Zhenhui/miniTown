#include"miniTown.h"

//=========================================================
//	读取图片

Color loadTexture(double u, double v,Picture *pic) //u ->x v ->y
{
	int y = v * pic->bmpHeight;
	int x = u *pic-> bmpWidth;
	return Color(pic->pBmpBuf[y * pic->bmpWidth * 3 + x * 3 + 2], pic->pBmpBuf[y * pic->bmpWidth * 3 + x * 3 + 1], pic->pBmpBuf[y *pic-> bmpWidth * 3 + x * 3]);
}

//-----------------------------------------------------------------------------------------
//给定一个图像位图数据、宽、高、颜色表指针及每像素所占的位数等信息,将其写到指定文件中
bool readBmp(const char* bmpName,Picture &pic)
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
	pic.bmpWidth = infohead.biWidth;
	pic.bmpHeight = infohead.biHeight;
	pic.biBitCount = infohead.biBitCount;//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
	//showBmpInforHead(infohead);//显示信息头 


	int lineByte = (pic.bmpWidth * pic.biBitCount / 8 + 3) / 4 * 4;//灰度图像有颜色表，且颜色表表项为256
	if (pic.biBitCount == 8)
	{
		//申请颜色表所需要的空间，读颜色表进内存
		pic.pColorTable = new RGBQUAD[256];
		fread(pic.pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	//申请位图数据所需要的空间，读位图数据进内存
	pic.pBmpBuf = new unsigned char[lineByte * pic.bmpHeight];
	fread(pic.pBmpBuf, 1, lineByte * pic.bmpHeight, fp);
	fclose(fp);//关闭文件
	return 1;//读取文件成功
}

