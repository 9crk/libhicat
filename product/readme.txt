1.this is the last version.on 2016-11-29
	a.flash uboot+uImage+rootfs
	 you can use loadb or loady command under uboot.
	 or use an SPI programmer to flash them
	 0-1M  uboot   size:1M
     1-5M  uImage  size:4M
	 5-16M rootfs  size:11M
	
	b.uboot param:
	 setenv bootargs 'mem=32M console=ttyAMA0,115200 root=/dev/mtdblock2 rootfstype=jffs2 mtdparts=hi_sfc:1M(boot),4M(kernel),11M(rootfs)'
	 setenv bootcmd 'sf probe 0;sf read 0x82000000 0x100000 0x400000;bootm 0x82000000'
	
	c.the basic function contains AP(ATTENTION:no sta mode!!!) rtspserver libhisiv_test .etc
	 telnet 192.168.1.1
	 user:root password:(no password)
	 cd /hicat/
	 ./launch.sh
	 now everything is OK
	 the wireless configure file: wifi.conf
	 the video configure file: video.conf
	 modify it and then reboot
	 or just use ./launch.sh ap newSSID newPassword
	
	d.press button > 3s	to back to AP mode(with default SSID(hicat)&password(88888888))

	e.press button > 10s to restore to the factory mode
	 But.you should insert an SD card and mount it first(and with hicat_failsafe.tar inside)
	 see.
		./launch.sh sd format|mount|umount

	f.how to use station mode?(you should extract the hicatEx.tar in SD card)
		./launch.sh sd mount
		./launch.sh sd hicatEx
		./launch.sh sta ssid password
		then it's ok.also the param will be stored in wifi.conf
			
	g.how to watch video in web browser
		checkout the "launch.sh" and the "guard.sh" file
		you'll find the VIDEO_SERVER definition inside
		modify it to the below
		VIDEO_SERVER=libhisiv_test
		then visit http://192.168.1.1:8080 with chrome
		(Attention:some web browser is not supported directy,like IE)
	
	h.how to copy files with WinSCP on windows of scp command Under unix-like system		
		the dropbear is in hicatEx directory
		cd /www/mmc/hicatEx
		source env.sh
		dropbear &
		then you can use winscp to copy files and use ssh to connect the board.

	i.how to use OpenCV
		checkout the libhicat/APP/
		
