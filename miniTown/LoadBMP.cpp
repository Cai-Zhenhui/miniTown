#include"miniTown.h"

//=========================================================
//	��ȡͼƬ

Color loadTexture(double u, double v,Picture *pic) //u ->x v ->y
{
	int y = v * pic->bmpHeight;
	int x = u *pic-> bmpWidth;
	return Color(pic->pBmpBuf[y * pic->bmpWidth * 3 + x * 3 + 2], pic->pBmpBuf[y * pic->bmpWidth * 3 + x * 3 + 1], pic->pBmpBuf[y *pic-> bmpWidth * 3 + x * 3]);
}

//-----------------------------------------------------------------------------------------
//����һ��ͼ��λͼ���ݡ����ߡ���ɫ��ָ�뼰ÿ������ռ��λ������Ϣ,����д��ָ���ļ���
bool readBmp(const char* bmpName,Picture &pic)
{
	FILE* fp;
	fopen_s(&fp, bmpName, "rb");//�����ƶ���ʽ��ָ����ͼ���ļ�
	if (fp == 0)
		return 0;

	//����λͼ�ļ�ͷ�ṹBITMAPFILEHEADER
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);
	/*
	BITMAPFILEHEADER filehead;
	fread(&filehead, 1, sizeof(BITMAPFILEHEADER), fp);
	showBmpHead(filehead);//��ʾ�ļ�ͷ
*/

//����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���head��
	BITMAPINFOHEADER infohead;
	fread(&infohead, sizeof(BITMAPINFOHEADER), 1, fp); //��ȡͼ����ߡ�ÿ������ռλ������Ϣ
	pic.bmpWidth = infohead.biWidth;
	pic.bmpHeight = infohead.biHeight;
	pic.biBitCount = infohead.biBitCount;//�������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����
	//showBmpInforHead(infohead);//��ʾ��Ϣͷ 


	int lineByte = (pic.bmpWidth * pic.biBitCount / 8 + 3) / 4 * 4;//�Ҷ�ͼ������ɫ������ɫ�����Ϊ256
	if (pic.biBitCount == 8)
	{
		//������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�
		pic.pColorTable = new RGBQUAD[256];
		fread(pic.pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	//����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
	pic.pBmpBuf = new unsigned char[lineByte * pic.bmpHeight];
	fread(pic.pBmpBuf, 1, lineByte * pic.bmpHeight, fp);
	fclose(fp);//�ر��ļ�
	return 1;//��ȡ�ļ��ɹ�
}

