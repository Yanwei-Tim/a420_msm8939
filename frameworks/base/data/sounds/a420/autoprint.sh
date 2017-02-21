#!/bin/bash

#首先将该文件复制到frameworks/base/data/sounds/所在项目下
#注意文件的存放格式必须满足一下条件
#所有ogg文件需放入文件夹下
#否则脚本执行不成功 ps: 执行前请执行 chmod a+x autoprint.sh

OGGS=`find . -name *.ogg`
Project='/a420'
#所有ogg文件
for ogg in $OGGS
do
#ogg所在目录
	tmp=${ogg:1}
	dirname=${tmp%/*}
	filename=${tmp##*/}
#ogg保存的路径
#    $(LOCAL_PATH)/notifications/ogg/Adara.ogg:system/media/audio/notifications/Adara.ogg \
#输出
	echo "    \$(LOCAL_PATH)$Project$dirname/$filename:system/media/audio$dirname/$filename \\"
done
