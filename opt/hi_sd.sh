#umount /dev/mmcblk0 
#mkfs.vfat /dev/mmcblk0
mkdir /www/mmc -p
mount -t vfat /dev/mmcblk0 /www/mmc
cd /www/mmc
tar -xf hicat*.tar -C ./
cd hicat
./launch.sh install



