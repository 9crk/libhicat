#ifndef _LIBHISIV_H_
#define _LIBHISIV_H_

#ifdef __cplusplus 
extern "C" { 
#endif
int venc_exit(int n);//0 by default
int venc_init(int resolve);//0:720P 1:QVGA(320*240) 2:VGA(640*480)
int venc_requestIDR();//request IDR frame
int venc_getFrame(char* buffer,int *datalen);//get a h264 frame
//mode=0:get Y  mode=1:get UV mode=2:get YUV
//YUV420
int venc_getYUV(int mode,char*buff);
int venc_rotate(int dir);
#ifdef __cplusplus 
}
#endif
#endif
