#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"libhisiv.h"
int main(int argc,char* argv[])
{

	char data[1280*720];
	int len;
	int i;
	len = venc_getYUV(0,data);
	int x,y;
	int result[10];
	
	for(i=0;i<10;i++){
		result[i] = 0;
	}
	for(i=0;i<10;i++){
		for(y=635;y<(635+10);y++){
			for(x=i*72;x<(i+1)*72;x++){
				result[i]+=data[y*1280+x];
			}
		}
		result[i] = result[i]/(72*10);
	}
	for(i=0;i<10;i++){
		result[i] = 0;
		printf("result = %d\n",result[i]);
	}
}
