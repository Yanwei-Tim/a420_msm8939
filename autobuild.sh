#/bin/bash
if [ $# -lt 1 ]; then
  echo "Usage:"
  echo "    ./autobuild.sh product_name"
  echo "Product:"
  echo "  msm8916_a539 ..."
  exit;
fi

source /root/.bashrc
source build/envsetup.sh
choosecombo 1 $1 userdebug 1
#repo sync -j8

make clean -j56
make update-api -j56
make -j56
make otapackage -j56

IMG_DIR=./out/target/product/$1
version=`grep "ro.build.inter_version" device/qcom/$1/lovdream.prop`   #obtain the version
version_last=${version:23}
location=$IMG_DIR/$version_last/

#location=$IMG_DIR/`date +%Y%m%d`/
mkdir -p $location


    cp $IMG_DIR/boot.img $location
    cp $IMG_DIR/cache.img $location
    cp $IMG_DIR/persist.img $location
    cp $IMG_DIR/recovery.img $location
    cp $IMG_DIR/emmc_appsboot.mbn $location
    cp $IMG_DIR/userdata.img $location
    cp $IMG_DIR/splash.img $location
    cp $IMG_DIR/ramdisk.img $location
    cp $IMG_DIR/system.img $location
    cp $IMG_DIR/obj/KERNEL_OBJ/vmlinux $location
    cp $IMG_DIR/obj/KERNEL_OBJ/Module.symvers $location
    cp $IMG_DIR/obj/KERNEL_OBJ/System.map $location
cp $IMG_DIR/target_files-package.zip $location
cp $IMG_DIR/*-ota-eng.server6.zip $location

scp -r $location linpeng@10.10.100.100:/home/server3/temp/linpeng/
#if [[ $? = 0 ]];then
#	a=`ls out/target/product/$project/$project-ota-eng.root.zip`
#	echo $?
#	if [[ $? != 0 ]];then
#		make -j8
#	fi
#		
#fi
