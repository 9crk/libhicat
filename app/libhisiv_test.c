#include<stdio.h>
//for video
extern int venc_exit(int n);
extern int venc_init_more(int resolve,int mode,int fps);//resolve: 0/1/2  1280*720/320*240/640*480  mode: 0/1 H264/MJPEG
extern int venc_requestIDR();
extern int venc_getFrame(char* buffer,int *datalen,int *pts,int *type);
extern int venc_snap(char* buff,int xRes,int yRes);
extern int venc_getYUV(int mode,char*buff);//mode=0 Y  mode=1 UV mode = 3 YUV420(SP)
//for audio
extern int aenc_init(int mode);// 0/1 PT_LPCM/AAC/
extern int aenc_getFrame(char* buff);
extern int aenc_exit();
//jpeg to http
extern int libyuvdist_startYuvDistService(int port);
extern int libyuvdist_updateYuv(int iHandle,char* data,int len,int seq,unsigned long timeStamp);
extern int libyuvdist_stopYuvDistService(int iHandle);
extern int libyuvdist_setSettingCallback(int iHandle,int func);//int func(int resX,int resY,int fps)

int main(int argc,char* argv[])
{
#if 1
	int len,ret,pts,type,cnt;
    char data[1000000];
    FILE* fp;
    FILE* fp_snap;
	int hd = libyuvdist_startYuvDistService(8080);
    venc_init_more(1,1,12);
    //fp = fopen("test.jpeg","wb");
    cnt = 0;
    while(1){
        ret = venc_getFrame(data, &len,&pts,&type);
        if(ret>0){
			libyuvdist_updateYuv(hd,data,len,0,0);
			//if(cnt == 50){fwrite(data,len,1,fp);break;}
        	cnt++;
        	printf("len = %d pts=%d type=%d\n",len,pts,type);
		}
    }
	libyuvdist_stopYuvDistService(hd);
    //fclose(fp);
#endif
#if 0	
    int len,ret,pts,type,cnt;
    char data[1000000];
    FILE* fp;
	venc_init_more(0,0);
    fp = fopen("test.h264","wb");
	cnt = 0;
    while(1){
        usleep(10000);
        ret = venc_getFrame(data, &len,&pts,&type);
        if(ret>0)fwrite(data,1,len,fp);
		cnt++;
		if(cnt%50 == 0)venc_requestIDR();
        printf("len = %d pts=%d type=%d\n",len,pts,type);
    }
    fclose(fp);
#endif
#if 0
	int len,ret;
	char data[100000];
	aenc_init(1);//0-PCM  1-AAC
	//FILE*fp = fopen("test.pcm","wb");
	FILE*fp = fopen("test.aac","wb");
	while(1){
		len = aenc_getFrame(data);
		printf("len = %d\n",len);
		if(len <=0)continue;
		fwrite(data,1,len,fp);
	}
	fclose(fp);
	aenc_exit();
#endif
	
}
