#SDK:
	linux
	file system
	Hisiv stuff
	download address: http://pan.baidu.com/s/1c1qOQ6O  verifycode: kspc
#How to burn the firmware to flash
	you must have a hicat board with a uboot already burned.
	then connect the UART0 on the ARM9 Hisiv chip. and then use the command as below[recomendly using Hyper Terminal to finish this]:
	>>loady 0x82000000
	then send file on Hyper Terminal with xmodern protocal. choose the uImage file under https://github.com/9crk/libhisiv/opt/
	>>sf probe 0
	>>sf erase 0x100000 0x300000
	>>sf write 0x82000000 0x100000 0x300000
	>>loady 0x82000000
	then send the rootfs file to the board.
	>>sf erase 0x400000 0xC00000
	>>sf write 0x82000000 0x400000 0x500000
	>>setenv bootargs 'mem=32M console=ttyAMA0,115200 root=/dev/mtdblock2 rootfstype=jffs2 mtdparts=hi_sfc:1M(boot),3M(kernel),12M(rootfs)'
	>>setenv bootcmd 'sf probe 0;sf read 0x82000000 0x100000 0x300000;bootm 0x82000000'	
	>>saveenv
	then reboot the board or execute 'reset' command.
#How to use opencv Demo
	clone this repo
	then install the compiler
	compile the apps under 'app' dir with './build.sh'
	copy the app dir to the board
	copy the opt/opencvlib dir to the board at /www/mmc/opencv/opencvlib
	cd app
	source env.sh
	execute './capture' to capture an image named 'myImage.jpg'
	execute './match model.jpg' to find the object model.jpg in the camera.
	then you can browser the result hi.jpg on http://192.168.1.1/mmc/opencv/app/hi.jpg

#About rtspserver and libhisiv.a
	rtspserver have two demo:
		one is modified from live555 project.[live555MediaServer]
			source code is in https://bitbucket.org/zhouhua/hicat_rtspserver
			play Address:[rtsp://192.168.1.1/hicat.264]
		one is a http-rtp based program. with only binary file provided.[http-rtpServer]
			play Address:[http://192.168.1.1/cgi-bin/video.sdp] but must with zwebs running first.
		you can rename any of it as 'rtspserver',then it will be run in the next boot. or run /hicat/launch.sh restart to restart all services.
	libhisiv.a contains all the camera function.as below:
		extern int venc_exit(int n);//0 
		extern int venc_init(int resolve);//0:720P 1:QVGA 2:VGA
		extern int venc_requestIDR();
		extern int venc_getFrame(char* buffer,int *datalen);//get h264 frame data.
		extern int venc_rotate(int dir);//0:no rotate 2:180 digree rotate.
		extern int venc_getYUV(int mode,char*buff);//get YUV data.
#How to install software pack
[old way before 20160417]
	unpack the hicat2016xxxx.tar
	cp hicat2016xxxx /
	cd /hicat
	./launch.sh install
	then the board will reboot.
[new way for sd upgrade after 20160418]
	1.execute 'lrz' command to send libhicat/opt/hi_sd.sh into the board[any where]
    2.format the sd card with fat32 format in default param. or use mkfs.vfat on Linux OS
	3.then execute 'chmod +x hi_sd.sh && ./hi_sd.sh',the board will reboot

#How to upgrade
	1.Formating the SD card with vfat or fat32 mode.
	2.then copy the hicat2016xxxx.tar package to the SD card.
	3.press the reset button[RST_PBC]
	4.connect the power supply.
	5.wait for the board reset again.
	
#What's more
	zwebs	https://9crk@bitbucket.org/zhouhua/hicat_zwebs.git

#How to use programming with serial port on Hisiv
	libSerial https://github.com/9crk/libSerial.git
	


ATTENTION!!! from hicat20160413 on,the rtsp change to http-rtp server
new video play url is: [http://192.168.1.1:8889/hicat.sdp]


