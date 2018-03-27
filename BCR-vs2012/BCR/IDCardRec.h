#ifndef _IDCARDREC_H
#define _IDCARDREC_H

#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> /*�õ���time����������Ҫ�����ͷ�ļ�*/
#include <fstream>
#include <sstream>
#include <exception>
#include <vector>
//#include <sys/io.h>
#include <direct.h>

#include <opencv/highgui.h>
#include <opencv/cv.h>

#include "jiaoZheng.h"
#include "ln_convnet.hpp"

#include "IntImage.h"
#include "SimpleClassifier.h"
#include "AdaBoostClassifier.h"
#include "CascadeClassifier.h"
#include "Global.h"

#include "BankCard.h"

#define showSteps 0
#define saveFlag 0



//typedef unsigned char uchar;

int charWidth = 36;
int charHeight = 54;

const int ROIHEIGHT = 46;

struct  recCharAndP
{
	float recP;//ʶ��ĸ���
	char recChar;
};

struct imageIpl //��ֵ�������ͼ�����򣬴�λ�ú�roiͼ������
{
	IplImage * roiImage;
	int positionX;
};

struct resultPos //��ʶ������roiͼ��������ԭͼ�е�λ��
{
	recCharAndP recCharP;
	int recPosition;
};

struct resultFinal //��ʶ������roiͼ��������ԭͼ�е�λ��
{
	string recString;
	float recPFinal;//ʶ��ĸ���
};

//====================��ʼ������====================//
LightNet::ConvNet *cnn;
LightNet::ConvNet *cnnPlane;
BankCard *BC;

extern "C"
{
void init();
string processingOne(IplImage * src);
resultFinal processingOneT(IplImage *src);
resultFinal processingOneP(IplImage *src);
}
//char *vifLine(vector<cv::Vec4i> lineT,vector<cv::Vec4i> lineB,vector<cv::Vec4i> lineL,vector<cv::Vec4i> lineR);
/*
LARGE_INTEGER m_liPerfFreq;
LARGE_INTEGER m_liPerfStart;
LARGE_INTEGER liPerfNow;
double dfTim;
void getStartTime()
{
	QueryPerformanceFrequency(&m_liPerfFreq);
	QueryPerformanceCounter(&m_liPerfStart);
}

void getEndTime()
{
	QueryPerformanceCounter(&liPerfNow);
	dfTim=( ((liPerfNow.QuadPart - m_liPerfStart.QuadPart) * 1000.0f)/m_liPerfFreq.QuadPart);
}
*/



//char * configFile = "/storage/sdcard0/bcnr/config.txt";
//char* trainSetPosPath = (char *)malloc(200*sizeof(char));


#endif
