#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"libhisiv.h"
#include"cv.h"
#include"highgui.h"
int main(int argc,char* argv[])
{

	char data[1280*720];
	int len;
	int i;
	IplImage *img = cvCreateImageHeader(cvSize(1280,720), 8, 1);
	len = venc_getYUV(0,data);
	printf("len = %08x\n",len);
	for(int i=0;i<20;i++){printf("%d ",data[i]);}
	cvSetImageData(img,data,1280);
	cvSaveImage("myImage.jpg",img);
	cvReleaseImageHeader(&img);
}
