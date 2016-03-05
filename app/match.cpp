#include"cv.h"
#include"highgui.h"
#include"stdio.h"
#include"libhisiv.h"

int main(int argc,char* argv[])
{
	int height,width;
	char data[1000000];
	int len;
	IplImage* model = cvLoadImage(argv[1],0);
	IplImage *img720 = cvCreateImageHeader(cvSize(1280,720), 8, 1);
	IplImage *imgs = cvCreateImage(cvSize(320,240),8,1);

    cvSetImageData(img720,data,1280);

	width = imgs->width - model->width + 1;  
    height = imgs->height - model->height + 1;  
	
	IplImage* result = cvCreateImage(cvSize(width,height),32,1);
	
	CvPoint minLoc, maxLoc;
	double minValue, maxValue;
printf("start compare\n");
	while(1){
	    //1.get image
		len = venc_getYUV(0,data);
		//2.resize it
		cvResize(img720,imgs);
		//3.match
		cvMatchTemplate(imgs, model, result, CV_TM_SQDIFF);
		//4.find high point
		cvMinMaxLoc(result, &minValue, &maxValue, &minLoc, &maxLoc);    
		cvRectangle(imgs,minLoc,cvPoint(minLoc.x+model->width,minLoc.y+model->height),cvScalar(255,255,255,0),8);
		cvSaveImage("hi.jpg",imgs);	
		printf("x:%d y:%d\n",minLoc.x+model->width/2,minLoc.y+model->height/2);
		usleep(1000);
//		cvRectangle(srcResult, minLoc, cvPoint(minLoc.x + img2->width, minLoc.y+ img2->height), cvScalar(0,0,255));
//		cvSaveImage("iiii.jpg",srcResult);
	}
	cvReleaseImage(&result);	
	cvReleaseImage(&model);	
	cvReleaseImageHeader(&img720);	
}
