#include "jni.h"
#include <android/log.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <signal.h>
#include "nativehelper/JNIHelp.h"
#include "utils/misc.h"

#define LOG_TAG "PoGoPin-JNI"

/* new */
#define HSL_UART_IOC_MAGIC 'H'
#define HSL_UART_SWITCH     _IOW(HSL_UART_IOC_MAGIC, 0, unsigned char)

#define LOGI(...) do {__android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__);} while(0)
#define LOGW(...) do {__android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__);} while(0)
#define LOGE(...) do {__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__);} while(0)

#define UART_SWITCH_PATH  "/sys/class/bd_gps/bd_gps/bd_enable"
#define RAW_SWITCH_PATH  "/sys/kernel/debug/msm_serial_hsl/loopback.3"

static int fd, switch_fd, fd_bd, fd_raw;
static int nmea_output = 0;
static char nmea4_1[36] = {0xB5,0x62,0x06,0x17,0x14,0x00,0x00,0x41,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00\
		,0x00,0x00,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x9E,0xB5,0x62,0x06,0x17,0x00,0x00,0x1D,0x5D};
static char single_bd[60] = {0xb5,0x62,0x6,0x3e,0x2c,0x0,0x0,0x0,0x20,0x5,0x0,0x8,0x10,0x0,0x0,0x0,0x1,0x1,0x1,\
	0x1,0x3,0x0,0x0,0x0,0x1,0x1,0x3,0x8,0x10,0x0,0x1,0x0,0x1,0x1,0x5,0x0,0x3,0x0,0x0,0x0,0x1,0x1,0x6,0x8,0xe,0x0,\
	0x0,0x0,0x1,0x1,0xfc,0x1,0xb5,0x62,0x6,0x3e,0x0,0x0,0x44,0xd2};
static char single_gps[52] = {0xB5,0x62,0x06,0x3E,0x2C,0x00,0x00,0x00,0x20,0x05,0x00,0x08,0x10,0x00,0x01,0x00,0x01,\
	0x01,0x01,0x01,0x03,0x00,0x01,0x00,0x01,0x01,0x03,0x08,0x10,0x00,0x00,0x00,0x01,0x01,0x05,0x00,0x03,0x00,\
	0x01,0x00,0x01,0x01,0x06,0x08,0x0E,0x00,0x00,0x00,0x01,0x01,0xFE,0x39};
static char bd_plus_gps_1[8] = {0xB5,0x62,0x06,0x3E,0x00,0x00,0x44,0xD2};
static char bd_plus_gps_2[52] ={0xb5,0x62,0x6,0x3e,0x2c,0x0,0x0,0x0,0x20,0x5,0x0,0x8,0x10,0x0,0x1,0x0,0x1,\
	0x1,0x1,0x1,0x3,0x0,0x0,0x0,0x1,0x1,0x3,0x8,0x10,0x0,0x1,0x0,0x1,0x1,0x5,0x0,0x3,0x0,0x0,0x0,0x1,0x1,0x6,\
	0x8,0xe,0x0,0x0,0x0,0x1,0x1,0xfd,0x25};
static char bd_plus_gps_3[8] ={0xB5,0x62,0x06,0x3E,0x00,0x00,0x44,0xD2};

static char single_gps_sbas[52] = {0xB5,0x62,0x06,0x3E,0x2C,0x00,0x00,0x00,0x20,0x05,\
0x00,0x08,0x10,0x00,0x01,0x00,0x01,0x01,0x01,0x01,\
0x03,0x00,0x01,0x00,0x01,0x01,0x03,0x08,0x10,0x00,\
0x00,0x00,0x01,0x01,0x05,0x00,0x03,0x00,0x01,0x00,\
0x01,0x01,0x06,0x08,0x0E,0x00,0x00,0x00,0x01,0x01,\
0xFE,0x39};
static char bd_plus_gps_sbas[52] = {0xB5,0x62,0x06,0x3E,0x2C,0x00,0x00,0x00,0x20,0x05,\
0x00,0x08,0x10,0x00,0x01,0x00,0x01,0x01,0x01,0x01,\
0x03,0x00,0x01,0x00,0x01,0x01,0x03,0x08,0x10,0x00,\
0x01,0x00,0x01,0x01,0x05,0x00,0x03,0x00,0x01,0x00,\
0x01,0x01,0x06,0x08,0x0E,0x00,0x00,0x00,0x01,0x01,\
0xFF,0x4D};
static char glonass_plus_gps_sbas[52] = {0xB5,0x62,0x06,0x3E,0x2C,0x00,0x00,0x00,0x20,0x05,\
0x00,0x08,0x10,0x00,0x01,0x00,0x01,0x01,0x01,0x01,\
0x03,0x00,0x01,0x00,0x01,0x01,0x03,0x08,0x10,0x00,\
0x00,0x00,0x01,0x01,0x05,0x00,0x03,0x00,0x01,0x00,\
0x01,0x01,0x06,0x08,0x0E,0x00,0x01,0x00,0x01,0x01,\
0xFF,0x3D};

static char bd_115200[28] ={0xB5,0x62,0x06,0x00,0x14,0x00,0x01,0x00,0x00,0x00,0xD0,0x08,0x00,\
	0x00,0x00,0xC2,0x01,0x00,0x07,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0xC0,0x7E};

static char low_walk_mode[44] ={0xB5,0x62,0x06,0x24,0x24,0x00,0xFF,0xFF,0x00,0x03,0x00,0x00,\
	0x00,0x00,0x10,0x27,0x00,0x00,0x05,0x00,0xFA,0x00,0xFA,0x00,0x64,0x00,0x2C,0x01,0x00,\
	0x00,0x00,0x00,0x10,0x27,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x47,0x0F};

//static char disable_gll[11] ={0xB5,0x62,0x06,0x01,0x03,0x00,0xF0,0x01,0x00,0xFB,0x11};
//static char disable_vtg[11] ={0xB5,0x62,0x06,0x01,0x03,0x00,0xF0,0x05,0x00,0xFF,0x19};
//static char disable_zda[16] ={0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x5B};

//static char open_sbas[16] = {0xB5,0x62,0x06,0x16,0x08,0x00,0x01,0x03,0x03,0x00,0x80,0x01,0x00,0x00,0xAC,0xBC};
static char close_sbas[16] = {0xB5,0x62,0x06,0x16,0x08,0x00,0x00,0x03,0x03,0x00,0x80,0x01,0x00,0x00,0xAB,0xB4};
static char gst_en[11] = {0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x07, 0x01, 0x02, 0x1E};

static jint android_util_PoGoPin_openBeidou_9600
(JNIEnv *env, jobject obj, jstring device)
{
	const char* dev = env->GetStringUTFChars(device, 0);
	LOGI("##jni,openBeidou()... %s", dev);

	fd_bd = open("dev/ttyHSL2", O_RDWR);
	if(fd_bd < 0){
		LOGE("openPin():Open serial port ttyHSL2 error\n");
		return -1;
	}

//----------------------------------
	struct termios  ios_bd;
	tcgetattr( fd_bd, &ios_bd );

	ios_bd.c_cc[VTIME]    = 11;   /* inter-character timer unused */
	ios_bd.c_cc[VMIN]     = 0;   /* blocking read until 1 chars received */

	ios_bd.c_cflag &= ~CSIZE;
	ios_bd.c_cflag |= (CS8 | CLOCAL | CREAD);
	ios_bd.c_cflag &=~PARENB;
	ios_bd.c_cflag &=~CRTSCTS;
	ios_bd.c_iflag = IGNPAR;
	ios_bd.c_oflag = 0;
	ios_bd.c_lflag = 0;

	cfsetospeed(&ios_bd, B9600);
	cfsetispeed(&ios_bd, B9600);
	ioctl(fd_bd, TCSETS, &ios_bd); 

    LOGI("configure complete for ttyHSL2\n");

    if(tcsetattr(fd_bd, TCSANOW, &ios_bd) != 0)
    {
        LOGI("serial error1");
        return -1;
    }
//----------------------------------
	LOGE("init serial success beidou. \n");
	return fd;
}

static jint android_util_PoGoPin_openBeidou
(JNIEnv *env, jobject obj, jstring device)
{
	const char* dev = env->GetStringUTFChars(device, 0);
	LOGI("##jni,openBeidou()... %s", dev);

	fd_bd = open("dev/ttyHSL2", O_RDWR);
	if(fd_bd < 0){
		LOGE("openPin():Open serial port ttyHSL2 error\n");
		return -1;
	}

//----------------------------------
	struct termios  ios_bd;
	tcgetattr( fd_bd, &ios_bd );

	ios_bd.c_cc[VTIME]    = 11;   /* inter-character timer unused */
	ios_bd.c_cc[VMIN]     = 0;   /* blocking read until 1 chars received */

	ios_bd.c_cflag &= ~CSIZE;
	ios_bd.c_cflag |= (CS8 | CLOCAL | CREAD);
	ios_bd.c_cflag &=~PARENB;
	ios_bd.c_cflag &=~CRTSCTS;
	ios_bd.c_iflag = IGNPAR;
	ios_bd.c_oflag = 0;
	ios_bd.c_lflag = 0;

	cfsetospeed(&ios_bd, B115200);
	cfsetispeed(&ios_bd, B115200);
	ioctl(fd_bd, TCSETS, &ios_bd); 

    LOGI("configure complete for ttyHSL2\n");

    if(tcsetattr(fd_bd, TCSANOW, &ios_bd) != 0)
    {
        LOGI("serial error1");
        return -1;
    }
//----------------------------------
	LOGE("init serial success beidou. \n");
	return fd;
}

static jint android_util_PoGoPin_openUart9600
(JNIEnv *env, jobject obj, jstring device)
{
	const char* dev = env->GetStringUTFChars(device, 0);
	LOGI("##jni,openUart()... %s", dev);

	fd = open("dev/ttyHSL1", O_RDWR);
	if(fd < 0){
		LOGE("openPin():Open serial port ttyHSL1 error\n");
		return -1;
	}

	//----------------------------
        struct termios  ios;
        tcgetattr( fd, &ios );

        ios.c_cc[VTIME]    = 11;   /* inter-character timer unused */
    	ios.c_cc[VMIN]     = 0;   /* blocking read until 1 chars received */

    	ios.c_cflag &= ~CSIZE;
    	ios.c_cflag |= (CS8 | CLOCAL | CREAD);
    	ios.c_cflag &=~PARENB;
    	ios.c_cflag &=~CRTSCTS;
    	ios.c_iflag = IGNPAR;
        ios.c_oflag = 0;
    	ios.c_lflag = 0;

    	cfsetospeed(&ios, B9600);
    	cfsetispeed(&ios, B9600);
    	ioctl(fd, TCSETS, &ios); 

    LOGI("configure complete for ttyHSL1\n");

    if(tcsetattr(fd, TCSANOW, &ios) != 0)
    {
        LOGI("serial error");
        return -1;
    }

	LOGE("init serial success uart. \n");
	nmea_output = 1;
	return fd;
}

static jint android_util_PoGoPin_openUart
(JNIEnv *env, jobject obj, jstring device)
{
	const char* dev = env->GetStringUTFChars(device, 0);
	LOGI("##jni,openUart()... %s", dev);

	fd = open("dev/ttyHSL1", O_RDWR);
	if(fd < 0){
		LOGE("openPin():Open serial port ttyHSL1 error\n");
		return -1;
	}

	//----------------------------
        struct termios  ios;
        tcgetattr( fd, &ios );

        ios.c_cc[VTIME]    = 11;   /* inter-character timer unused */
    	ios.c_cc[VMIN]     = 0;   /* blocking read until 1 chars received */

    	ios.c_cflag &= ~CSIZE;
    	ios.c_cflag |= (CS8 | CLOCAL | CREAD);
    	ios.c_cflag &=~PARENB;
    	ios.c_cflag &=~CRTSCTS;
    	ios.c_iflag = IGNPAR;
        ios.c_oflag = 0;
    	ios.c_lflag = 0;

    	cfsetospeed(&ios, B115200);
    	cfsetispeed(&ios, B115200);
    	ioctl(fd, TCSETS, &ios); 

    LOGI("configure complete for ttyHSL1\n");

    if(tcsetattr(fd, TCSANOW, &ios) != 0)
    {
        LOGI("serial error");
        return -1;
    }

	LOGE("init serial success uart. \n");
	nmea_output = 1;
	return fd;
}

static jint android_util_PoGoPin_closeBeidou
(JNIEnv *env, jobject obj)
{
	return close(fd_bd);
}

static jint android_util_PoGoPin_closeUart
(JNIEnv *env, jobject obj)
{
	nmea_output = 0;
	return close(fd);
}

static jint android_util_PoGoPin_exist
(JNIEnv *env, jobject obj)
{
	return 1;
}

static jint android_util_PoGoPin_readDevice
(JNIEnv *env, jobject obj, jbyteArray btArr, jint len)
{
	char data[10]={0};//read too many the data is not completed,some data maybe lost!

	int count = read(fd_bd, data, len);
	if(count < 0){
	  LOGW("Could not readDevice, fd_bd\n");
	  return -100;
	}
	//for(int i=0;i<len;i++){
//      if(data[0] != 0 || data[1] != 0 ||data[2] != 0 || data[3] != 0)
      //LOGE("##jni,readDevice_________data__:%s()len=%d,count=%d", data,len,count);
       //}

	if(nmea_output)
	write(fd, data, count);

	jbyte* by = (jbyte*) data;
	
	env->SetByteArrayRegion(btArr, 0, len, by);

	return count;
}

static jint android_util_PoGoPin_readRawData
(JNIEnv *env, jobject obj, jbyteArray btArr, jint len)
{
	char data[10]={0};//read too many the data is not completed,some data maybe lost!

	int count = read(fd, data, len);
	if(count < 0){
	  LOGW("Could read readRawData fd\n");
	  return -100;
	}

	if(fd_bd > 0)
		write(fd_bd, data, count);
	//for(int i=0;i<len;i++){
//      if(data[0] != 0 || data[1] != 0 ||data[2] != 0 || data[3] != 0)
      //LOGW("%s", data);
       //}

	jbyte* by = (jbyte*) data;

	env->SetByteArrayRegion(btArr, 0, len, by);

	return count;
}

static jint android_util_PoGoPin_writeDevice
(JNIEnv *env, jobject obj, jbyteArray btArr, jint len)
{
	jbyte * tempData = env->GetByteArrayElements(btArr, NULL);
	char * data = (char *)tempData;
	//char end_flag[1] = {0x0A};
    //for(int i=0;i<len;i++)
    //LOGW("##jni,writeDevice_________data__:  %d", data);

	int count = write(fd_bd, data, len);
	//write(fd, end_flag, 1);

	env->ReleaseByteArrayElements(btArr,tempData,0);

	return count;
}

static jint android_util_PoGoPin_switchDevice
(JNIEnv * env, jobject obj, jint mode)
{
	char switch_state = mode == 1 ? '1' : '0';
	switch_fd = open(UART_SWITCH_PATH, O_WRONLY);
	if(-1!=switch_fd)
    {
       int wnum = write(switch_fd, &switch_state, 1);
       //LOGE(" switch_state  = %c\n", switch_state);
       if (wnum < 0)
		{
	       LOGE("Write Failed. wnum=%d\n", wnum);
		   	close(switch_fd);
			return -2;
		}
		LOGI("switch Write success. %c \n",switch_state);
		close(switch_fd);
		return 0;
    }
	LOGE("Write Failed. switch_fd=%d\n", switch_fd);
	return -1;
}

static jint android_util_PoGoPin_switchRawData
(JNIEnv * env, jobject obj, jint mode)
{
	char switch_state = mode == 1 ? '1' : '0';
	fd_raw = open(RAW_SWITCH_PATH, O_RDWR);
	if(-1!=fd_raw)
    {
       int wnum = write(fd_raw, &switch_state, 1);
       //LOGE(" switch_state  = %c\n", switch_state);
       if (wnum < 0)
		{
	       LOGE("switchRawData failed. wnum=%d\n", wnum);
		   close(fd_raw);
			return -2;
		}
		LOGI("switchRawData success. %c \n",switch_state);
		close(fd_raw);
		return 0;
    }
	LOGE("switchRawData Failed. switch_fd=%d\n", fd_raw);
	return -1;
}

static jint android_util_PoGoPin_ioctlDevice
(JNIEnv * env, jobject obj, jint mode)
{
/*
	LOGI("ioctlDevice()... ioctl begin, mode: %d", mode);

	if(ioctl(fd, HSL_UART_SWITCH, mode)) {
		LOGE("ioctl error, errno: %s",strerror(errno));
		return -2;
	}
	return 0;

	char data[64]={0};//read too many the data is not completed,some data maybe lost!

	int count = read(fd_bd, data, 64);
	if(count < 0){
	  LOGW("Could not read uart from ttyHSL2: %s\r\n", strerror(errno));
	  return 0;
	}

	if(count > 0)
		write(fd, data, count);
*/

	if(fd_bd < 0){
		LOGE("BD file not open!!\n");
		return 0;
	}

	if(mode == 2){
		LOGE("update nmea\n");
		write(fd_bd, nmea4_1, 36);
		//write(fd_bd, disable_gll, 11);
		//write(fd_bd, disable_vtg, 11);
		//write(fd_bd, disable_zda, 16);
	}
	else if(mode == 1){
		LOGE("BD mode = BD+GPS write it\n");
		write(fd_bd, bd_plus_gps_1, 8);
		write(fd_bd, bd_plus_gps_2, 52);
		write(fd_bd, bd_plus_gps_3, 8);
	}
	else if(mode == 11){
		LOGE("BD mode = BD+GPS SBAS write it\n");
		write(fd_bd, bd_plus_gps_sbas, 52);
	}
	else if(mode == 3){
		LOGE("BD mode = single GPS write it\n");
		write(fd_bd, single_gps, 52);
	}
	else if(mode == 13){
		LOGE("BD mode = single GPS SBAS write it\n");
		write(fd_bd, single_gps_sbas, 52);
	}
	else if(mode == 14){
		LOGE("BD mode = GPS+GLONASS SBAS write it\n");
		write(fd_bd, glonass_plus_gps_sbas, 52);
	}
	else if(mode == 15){
		LOGE("Send mode for low walk\n");
		write(fd_bd, low_walk_mode, 44);
		write(fd_bd, gst_en, 11);
	}
	else if(mode == 33){
		LOGE("BD mode = write tty 115200\n");
		write(fd_bd, bd_115200, 28);
	}
	else if(mode == 55){
		LOGE("BD mode = close sbas mode\n");
		write(fd_bd, close_sbas, 16);
	}
	else{
		LOGE("BD mode = single BD write it\n");
		write(fd_bd, single_bd, 60);
	}

	return 0;
}

/*static jint open_file(){
   
   fd_file = open("/sdcard/BD_Jni.txt",O_CREAT | O_RDWR, S_IRWXU); 
   	if(fd_file < 0){
		LOGE("/sdcard/BD_Jni.txt open error!);
		return -1;
	}
}*/

/*
 * JNI registration.
 */
static JNINativeMethod gMethods[] = {
    /* name, signature, funcPtr */
	{ "openBeidou",      "(Ljava/lang/String;)I",
            (void*) android_util_PoGoPin_openBeidou },
	{ "openBeidou_9600",      "(Ljava/lang/String;)I",
            (void*) android_util_PoGoPin_openBeidou_9600 },
	{ "openUart",      "(Ljava/lang/String;)I",
            (void*) android_util_PoGoPin_openUart },
	{ "openUart9600",      "(Ljava/lang/String;)I",
            (void*) android_util_PoGoPin_openUart9600 },
	{ "closeBeidou",      "()I",
            (void*) android_util_PoGoPin_closeBeidou },
	{ "closeUart",      "()I",
            (void*) android_util_PoGoPin_closeUart },
	{ "exist",      "()I",
            (void*) android_util_PoGoPin_exist },
	{ "ioctlDevice",      "(I)I",
            (void*) android_util_PoGoPin_ioctlDevice },
	{ "switchDevice",      "(I)I",
            (void*) android_util_PoGoPin_switchDevice },
	{ "switchRawData",      "(I)I",
            (void*) android_util_PoGoPin_switchRawData },
	{ "readDevice",      "([BI)I",
            (void*) android_util_PoGoPin_readDevice },
	{ "readRawData",      "([BI)I",
            (void*) android_util_PoGoPin_readRawData },
	{ "writeDevice",      "([BI)I",
            (void*) android_util_PoGoPin_writeDevice },
};

int register_android_util_PoGoPin(JNIEnv* env)
{
    return jniRegisterNativeMethods(env, "android/util/PoGoPin",
        gMethods, NELEM(gMethods));
}
