#include "bcnr_wrap.h"
#include <opencv/highgui.h>
#include <opencv/cv.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> /*�õ���time����������Ҫ�����ͷ�ļ�*/
#include <fstream>
#include <sstream>
#include <exception>
#include <vector>
#include <io.h>

#include <highgui.h> 
#include <cv.h>

#define showSteps 1

using namespace std;

char * configFile = "config.txt";  //������ɸѡmodel�У�config.txt�������ΪҪɸѡ�������⣬δ���ࡣ---

char* trainSetPosPath = (char *)malloc(200*sizeof(char)); //��ȡconfig�ļ��������--
void readConfig(char* configFile, char* trainSetPosPath){
	fstream f;
	char cstring[1000];
	int readS=0;
	f.open(configFile, fstream::in);
	char param1[200]; strcpy(param1,"");
	char param2[200]; strcpy(param2,"");
	char param3[200]; strcpy(param3,"");

	
	f.getline(cstring, sizeof(cstring));//--��ȡ��һ�У�--
	readS=sscanf (cstring, "%s %s %s", param1,param2, param3);
	strcpy(trainSetPosPath,param3);
}


vector<string> imgNames;
int labelTemp = 0;

void dfsFolder(string folderPath){ //����config.txt��ĸ�Ŀ¼�µ����е��ļ���������Ŀ¼��--// ������Ŀ¼�����־���label����Ŀ¼����ļ�Ϊlabel���ڵ�ѵ����������---
	_finddata_t FileInfo;
	string strfind = folderPath + "\\*";
	long Handle = _findfirst(strfind.c_str(), &FileInfo);
	if (Handle == -1L)
	{
		cerr << "can not match the folder path" << endl;
		exit(-1);
	}
	do{	
		if (FileInfo.attrib & _A_SUBDIR)    	{//�ж��Ƿ�����Ŀ¼--
			//	cout<<FileInfo.name<<" "<<FileInfo.attrib<<endl;	
			if( (strcmp(FileInfo.name,".") != 0 ) &&(strcmp(FileInfo.name,"..") != 0))   		{//���������Ҫ--
				string newPath = folderPath + "\\" + FileInfo.name;
				cout<<FileInfo.name<<" "<<newPath<<endl;
				
				labelTemp = atoi(FileInfo.name);//��Ŀ¼���µ���Ŀ¼���־���label�������û����Ŀ¼����Ϊ��Ŀ¼��
				//	printf("%d\n",labelTemp);
				dfsFolder(newPath);
			}
		}else  {
			string finalName = folderPath + "\\" + FileInfo.name;
			//�����е��ļ���д��һ��txt�ļ�--
			//	cout << FileInfo.name << "\t";
			//	printf("%d\t",label);
			//	cout << folderPath << "\\" << FileInfo.name  << " " <<endl;
			//���ļ����ֺ�label���֣���Ŀ¼���ָ�ֵ��������--
			imgNames.push_back(finalName);
		}
	}while (_findnext(Handle, &FileInfo) == 0);
	_findclose(Handle);

}

void initTrainImage(){
	readConfig(configFile, trainSetPosPath);

	string folderPath = trainSetPosPath;
	dfsFolder(folderPath);

}


void processingTotal(){
	initTrainImage();

	int imgNum = imgNames.size();
	cout<<imgNum<<endl;
	for(int iNum=0;iNum<imgNum;iNum++){

		cout<<endl<<iNum<<endl;
		cout<<imgNames[iNum].c_str()<<endl;
		IplImage * src=cvLoadImage(imgNames[iNum].c_str(),1);  
		if(!src) continue;

		if(showSteps){
			cvNamedWindow("image",1);
			cvShowImage("image",src);

			cvWaitKey(1);
		}
	
		char result[200] ;	
		recognise_from_IplImage(src,result);

		if(result[0] == '\0')  
			continue;
		cout<< result<<endl;

		cvReleaseImage(&src);
		cvWaitKey(0);
	}
}




void main()
{
	 init_all ( "testWeight24.bin",
				 "testWeight16p.bin",
				 "testWeight16.bin","npclass.bin",
				 "cascade.bin" );

	processingTotal();

	release_all ();
}