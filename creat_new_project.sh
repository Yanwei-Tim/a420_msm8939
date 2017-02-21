#!/bin/bash  
#---------------------------------------------------
# created by yuanwei
# 2014.1.14
# version : 1.0
# 2014.9.24
# version : 2.0
#---------------------------------------------------
clear
echo 
echo  "   _   _  _ ___  ___  ___ ___ ___  "
echo  "  /_\ | \| |   \| _ \/ _ \_ _|   \ "
echo  ' / _ \| .` | |) |   / (_) | || |) |'
echo  '/_/ \_\_|\_|___/|_|_\\___/___|___/ '

echo 
echo 
read -p "[Please Input New Project Name]:"  new_project

#if [ `expr "$new_project" : 'msm8x25'` -eq 0 ]; then
#    echo "Error: project name prefix must be msm7627a"
#    exit
#fi

function build_base(){

   read -p "Are you sure to create the new project: $new_project ?(yes/no)" answer
    echo "answer:$answer"
    if [ "$answer"x != "yes"x ]; then
        exit 1
    fi
   read -p "Enter the full name of clone project:" clone_project
   echo "clone from project: $clone_project"

    if [ $new_project != '0' ];then
        echo 
        echo "GOOD Name\n "  
        #continue 
    else
        echo
        echo "Error new_project  name input !!!!!!"
        echo " please input correct project new_project "
        echo "Usage:"
        echo "  msm8x6_v100_e100   ..."
        exit 0
    fi
}

function build_lk(){

    echo "[building lk ]"
    echo 
    cp -rf bootable/bootloader/lk/target/${clone_project}  bootable/bootloader/lk/target/${new_project}
    cp bootable/bootloader/lk/project/${clone_project}.mk bootable/bootloader/lk/project/${new_project}.mk
    sed -i "s/${clone_project}/${new_project}/g" bootable/bootloader/lk/project/${new_project}.mk
    echo "[building lk done !]"

}

function build_device(){

    echo "[building device ]"
    echo
    cp -af device/qcom/${clone_project} device/qcom/${new_project}

    mv device/qcom/${new_project}/${clone_project}.mk device/qcom/${new_project}/${new_project}.mk
    sed -i "s/${clone_project}/${new_project}/g" `grep -rsl ${clone_project}  ./device/qcom/${new_project}/*`
    # sed -i "9i device/qcom/${new_project}/radio/"  device/qcom/${new_project}/.gitignore 
    sed -i "/add_lunch_combo ${clone_project}-userdebug/a add_lunch_combo ${new_project}-userdebug" device/qcom/common/vendorsetup.sh
#  sed -i "s/TARGET_BOARD_PLATFORM := ${new_project}/TARGET_BOARD_PLATFORM := msm8226/g" device/qcom/${new_project}/BoardConfig.mk

    cp -rf  device/qcom/common/rootdir/${clone_project} device/qcom/common/rootdir/${new_project}
    sed -i "s/${clone_project}/${new_project}/g" `grep ${clone_project} -rl ./device/qcom/common/rootdir/${new_project}/* `
    echo "[building device done !]"
} 

function build_kernel(){
    echo "[building kernel]"
    echo
    cp  kernel/arch/arm64/configs/${clone_project}_defconfig kernel/arch/arm64/configs/${new_project}_defconfig
    cp -af kernel/arch/arm64/boot/dts/${clone_project} kernel/arch/arm64/boot/dts/${new_project}
    sed -i "s/${clone_project}/${new_project}/g" kernel/arch/arm64/configs/${new_project}_defconfig
    echo "[building kernel done !!!]"
}

function  build_vendor(){
	echo "[building vendor ]"
	echo 
	#   cp -rf vendor/huiye/${clone_project}_overlay vendor/huiye/${new_project}_overlay
	#  cp -rf vendor/qcom/proprietary/common/${clone_project}  vendor/qcom/proprietary/common/${new_project}
	#cp vendor/qcom/proprietary/gps/build/${clone_project}.in vendor/qcom/proprietary/gps/build/${new_project}.in

#	cp -rf vendor/qcom/proprietary/modem-apis/msm8226 vendor/qcom/proprietary/modem-apis/${new_project}
#	cp -rf vendor/qcom/proprietary/wlan/ath6kl-utils/ath6kl_fw/hw2.1.1/${clone_project} vendor/qcom/proprietary/wlan/ath6kl-utils/ath6kl_fw/hw2.1.1/${new_project}
	#ln -s  vendor/qcom/proprietary/prebuilt_HY11/target/product/msm8226  vendor/qcom/proprietary/prebuilt_HY11/target/product/${new_project}
#	cp -rf  vendor/qcom/proprietary/common/msm8226/   vendor/qcom/proprietary/common/${new_project}
	cp -rf vendor/qcom/proprietary/mm-audio/audcal/family-b/acdbdata/8916/QRD/${clone_project} vendor/qcom/proprietary/mm-audio/audcal/family-b/acdbdata/8916/QRD/${new_project}
	cp -rf vendor/qcom/proprietary/fastmmi/mmi/${clone_project}  vendor/qcom/proprietary/fastmmi/mmi/${new_project}	
# cp -rf vendor/qcom/proprietary/prebuilt_HY11/target/product/msm8226  vendor/qcom/proprietary/prebuilt_HY11/target/product/${new_project}
one_project}
	for X  in `find ./vendor/qcom/proprietary/common/config -name "*.mk"`
	do
	sed -i "/PRODUCT_LIST += ${clone_project}/a\PRODUCT_LIST += ${new_project}" $X
#	sed -i "s/msm8226/& ${new_project}/g" $X
	sed -i "/FOTA_PRODUCT_LIST := msm7627a/a\FOTA_PRODUCT_LIST += ${new_project}" $X
	done

	echo "[building vendor done ! ]"
}
function build_package(){
    echo "[building package]"
    echo 
        cp -af packages/thirdparty/${clone_project} packages/thirdparty/${new_project}
        sed -i "s/${clone_project}/${new_project}/g" packages/thirdparty/${new_project}/Android.mk
    echo "[building package  done !!!]"
}

echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++"
build_base
build_lk
build_kernel
build_device
build_vendor
build_package
echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
