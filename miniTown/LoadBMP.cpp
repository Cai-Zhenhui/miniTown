#include"miniTown.h"

//=========================================================
//	��ȡͼƬ
unsigned char* pBmpBuf;//����ͼ�����ݵ�ָ��
int bmpWidth;//ͼ��Ŀ�
int bmpHeight;//ͼ��ĸ�
RGBQUAD* pColorTable;//��ɫ��ָ��
int biBitCount;//ͼ�����ͣ�ÿ����λ��

Color loadTexture(double u, double v) //u ->x v ->y
{
	int y = v * bmpHeight;
	int x = u * bmpWidth;
	return Color(pBmpBuf[y * bmpWidth * 3 + x * 3 + 2], pBmpBuf[y * bmpWidth * 3 + x * 3 + 1], pBmpBuf[y * bmpWidth * 3 + x * 3]);
}

//-----------------------------------------------------------------------------------------
//����һ��ͼ��λͼ���ݡ����ߡ���ɫ��ָ�뼰ÿ������ռ��λ������Ϣ,����д��ָ���ļ���
bool readBmp(const char* bmpName)
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
	bmpWidth = infohead.biWidth;
	bmpHeight = infohead.biHeight;
	biBitCount = infohead.biBitCount;//�������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����
	//showBmpInforHead(infohead);//��ʾ��Ϣͷ 


	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;//�Ҷ�ͼ������ɫ������ɫ�����Ϊ256
	if (biBitCount == 8)
	{
		//������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�
		pColorTable = new RGBQUAD[256];
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	//����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
	pBmpBuf = new unsigned char[lineByte * bmpHeight];
	fread(pBmpBuf, 1, lineByte * bmpHeight, fp);
	fclose(fp);//�ر��ļ�
	return 1;//��ȡ�ļ��ɹ�
}

