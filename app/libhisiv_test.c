#include<stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include<stdlib.h>

extern int venc_exit(int n);
extern int venc_init_more(int resolve,int mode,int fps);//resolve: 0/1/2  1280*720/320*240/640*480  mode: 0/1 H264/MJPEG
extern int venc_rotate(int dir);//0/2   0/180 degree 
extern int venc_requestIDR();
extern int venc_getFrame(char* buffer,int *datalen,int *pts,int *type);
extern int venc_getYUV(int mode,char*buff);//mode=0 Y  mode=1 UV mode = 3 YUV420(SP)
extern int aenc_init(int mode);// 0/1 PT_LPCM/AAC/
extern int aenc_getFrame(char* buff);
extern int aenc_exit();

extern int libyuvdist_startYuvDistService(int port);
extern int libyuvdist_updateYuv(int iHandle,char* data,int len,int seq,unsigned long timeStamp);
extern int libyuvdist_stopYuvDistService(int iHandle);
extern int libyuvdist_setSettingCallback(int iHandle,int func);//int func(int resX,int resY,int fps)

int gSave=0;
char fifo_buf[1000];
void snapService(void*arg)
{
	int fd,len;
	mode_t mode = 0666;
	system("rm /dev/snapctl");
	usleep(1000);
	while(1){
		if(gSave == 0){
			if ((fd = open("/dev/snapctl", O_RDONLY)) < 0){
				printf("open fifo failed!\n");
				if ((mkfifo("/dev/snapctl", mode)) < 0){
					printf("failed to mkfifo!\n");
					return;
				}
			}
			memset(fifo_buf,0,1000);
			len = read(fd, fifo_buf, 1000);
			if(len > 0){
				fifo_buf[len-1] = 0;
				gSave = 1;
			}
			close(fd);
		}else{
			usleep(100000);
		}
	}
}
int main(int argc,char* argv[])
{
//test for jpeg
#if 1
	int len,ret,pts,type,cnt;
    char data[1000000];
    FILE* fp;
	int fps = 25;	
	int resolution = 0;
	int hd = libyuvdist_startYuvDistService(8080);
	if(argc > 1){
		resolution = atoi(argv[1]);
		if(resolution<0 || resolution>2)resolution = 0;
		printf("resolution = %d\n",resolution);
	}
	if(argc > 2){
		fps = atoi(argv[2]);
		printf("fps = %d\n",fps);
		if(fps<0 || fps>25)fps=25;
	}
    venc_init_more(resolution,1,fps);
	
	pthread_t pid;
	pthread_create(&pid,NULL,snapService,NULL);
    cnt = 0;
    while(1){
        usleep(10000);
        ret = venc_getFrame(data, &len,&pts,&type);
        if(ret>0){
			if(gSave){
				fp = fopen(fifo_buf,"wb");
				fwrite(data,1,len,fp);
				fclose(fp);
				gSave = 0;
			}
			libyuvdist_updateYuv(hd,data,len,0,0);
        	cnt++;
        	//printf("len = %d pts=%d\n",len,pts);
		}
    }
	libyuvdist_stopYuvDistService(hd);
#endif
//test for h264
#if 0	
    int len,ret,pts,type,cnt;
    char data[1000000];
    FILE* fp;
	venc_init_more(0,0);
    fp = fopen("zhou.h264","wb");
	cnt = 0;
    while(1){
        usleep(10000);
        ret = venc_getFrame(data, &len,&pts,&type);
        if(ret>0)fwrite(data,1,len,fp);
		cnt++;
		if(cnt%50 == 0)venc_requestIDR();
        //printf("len = %d pts=%d type=%d\n",len,pts,type);
    }
    fclose(fp);
#endif
//test for audio
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
