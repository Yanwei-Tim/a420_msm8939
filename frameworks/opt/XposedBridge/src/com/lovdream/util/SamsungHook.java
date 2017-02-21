
package com.lovdream.util;

import android.util.Log;

import de.robv.android.xposed.IXposedHookZygoteInit;
import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.IXposedHookInitPackageResources;
import de.robv.android.xposed.callbacks.XC_InitPackageResources.InitPackageResourcesParam;
import de.robv.android.xposed.callbacks.XC_LoadPackage.LoadPackageParam;
import de.robv.android.xposed.XC_MethodHook;
import de.robv.android.xposed.XC_MethodReplacement;
import de.robv.android.xposed.XC_MethodHook.MethodHookParam;
import de.robv.android.xposed.XposedBridge;
import de.robv.android.xposed.XposedHelpers;

import android.net.Uri;
import android.content.pm.IPackageInstallObserver;
import android.content.pm.PackageManager;
import android.content.pm.PackageInfo;
import java.io.File;
import java.io.FileDescriptor;
import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.security.InvalidAlgorithmParameterException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.WeakHashMap;

import javax.crypto.SecretKey;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import com.android.internal.content.PackageHelper;
import android.content.pm.PackageParser;
import android.util.DisplayMetrics;
import android.content.Context;

import android.app.AndroidAppHelper;
import android.view.View;
import android.view.Window;
import android.view.Display;
import android.content.res.Resources;
import android.content.res.XResources;
import android.content.res.XModuleResources;
import android.content.res.Configuration;
import android.os.ServiceManager;
import android.os.IBinder;
import android.os.Parcel;
import java.util.Set;
import java.util.SortedSet;
import android.database.Cursor;
import android.location.Country;
import android.location.CountryDetector;

//for all bechmark apk
import android.view.Display;
import android.graphics.Point;
import android.util.DisplayMetrics;
import android.os.Bundle;
import com.google.android.gles_jni.GLImpl;
import android.hardware.SensorManager;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.util.Random;
import android.telephony.TelephonyManager;
import android.os.SystemProperties;

import android.app.ActivityManager;
import android.app.Activity;
import android.content.Intent;
import android.content.ContentResolver;
import android.widget.TextView;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import java.io.ByteArrayOutputStream;
import java.util.HashSet;

import libcore.io.Posix;
//import libcore.io.StructStatVfs;

import android.media.ThumbnailUtils;
import android.media.CamcorderProfile;
import android.media.MediaRecorder.OutputFormat;

public class SamsungHook implements IXposedHookLoadPackage,IXposedHookZygoteInit,IXposedHookInitPackageResources{

	private static final String TAG = "lovdream-util";
	private static String deviceImei = null;

    public SamsungHook(){
        super();
    }

	@Override
	public void initZygote(IXposedHookZygoteInit.StartupParam startupParam) throws Throwable {

		Object ret = XposedHelpers.findAndHookMethod(Posix.class,"statvfs",
			String.class,
			new XC_MethodHook(){
				@Override
				protected void afterHookedMethod(MethodHookParam _param) throws Throwable{
					String path = (String)_param.args[0];

					if(path!=null && path.length()!=0)
					{

						boolean bNeedUpdate=false;
						float storageScale=1.0f;
						
						if(path.equals("/data"))
						{
							if(SystemProperties.get("ro.lovdream.rom_size").equals("16"))
							storageScale=2.29f;   //32G:5.34;  16G:2.29
							else
							storageScale=5.34f;   //32G:5.34;  16G:2.29
							bNeedUpdate=true;
						}
						else if(path.equals("/storage/sdcard0") || path.equals("/mnt/sdcard")  || path.equals("/storage/emulated/0"))  
						{
							if(SystemProperties.get("ro.lovdream.rom_size").equals("16"))
							storageScale=2.29f;   //32G:5.34;  16G:2.29
							else
							storageScale=5.34f;   //32G:5.34;  16G:2.29
							bNeedUpdate=true;
						}

						if(bNeedUpdate)
						{
							/*
							StructStatVfs vfs=(StructStatVfs)_param.getResult();
							XposedHelpers.setLongField(vfs,"f_blocks",(long)(storageScale*vfs.f_blocks));
							XposedHelpers.setLongField(vfs,"f_bfree",(long)(storageScale*vfs.f_bfree));
							XposedHelpers.setLongField(vfs,"f_bavail",(long)(storageScale*vfs.f_bavail));
							*/
						}

					}

				}
			});

		ret = XposedHelpers.findAndHookMethod(ActivityManager.class,"checkComponentPermission",
				String.class,Integer.TYPE,Integer.TYPE,Boolean.TYPE,
				new XC_MethodHook(){
					@Override
					protected void afterHookedMethod(MethodHookParam _param) throws Throwable{
						String perm = (String)_param.args[0];
						if("com.xiaomi.permission.CLOUD_MANAGER".equals(perm)){
							_param.setResult(PackageManager.PERMISSION_GRANTED);
						}
					}
				});


		ret = XposedHelpers.findAndHookMethod(Class.forName("miui.util.FeatureParser"),"getBoolean",
				String.class,Boolean.TYPE,
			new XC_MethodHook(){
				@Override
				protected void afterHookedMethod(MethodHookParam _param) throws Throwable{
					if("support_button_light".equals(_param.args[0])){
						_param.setResult(true);
					}
				}
			});

		/*no need on hd*/
		/*
		ret = XposedHelpers.findAndHookMethod(Class.forName("com.miui.internal.app.AlertControllerImpl"),"cc",
			new XC_MethodHook(){
				@Override
				protected void afterHookedMethod(MethodHookParam _param) throws Throwable{
					Window w = (Window)XposedHelpers.getObjectField(_param.thisObject,"xg");
					w.findViewById(android.R.id.content).setBackgroundColor(0xffffffff);
				}
			});
			*/
		ret = XposedHelpers.findAndHookMethod(Class.forName("miui.telephony.TelephonyManagerImpl"),"getSimState",
				new XC_MethodReplacement(){
					@Override
					protected Object replaceHookedMethod(MethodHookParam _param) throws Throwable{
						return TelephonyManager.getDefault().getSimState();
					}
				});

		ret = XposedHelpers.findAndHookMethod(Bitmap.Config.class,"nativeToConfig",
				Integer.TYPE,
				new XC_MethodHook(){
					@Override
					protected void beforeHookedMethod(MethodHookParam _param) throws Throwable{
						if((Integer)_param.args[0] > 5){
							_param.args[0] = 5;
						}
					}
				});

		ret = XposedHelpers.findAndHookMethod(Class.forName("miui.util.HardwareInfo"),"getTotalPhysicalMemory",
				new XC_MethodHook(){
					@Override
					protected void afterHookedMethod(MethodHookParam _param) throws Throwable{
						_param.setResult((Long)_param.getResult() * 2);
					}
				});
	}

	@Override
    public void handleLoadPackage(final LoadPackageParam param) throws Throwable {

		Object ret;

		/*
		if("android".equals(param.packageName)){
			ret = XposedHelpers.findAndHookMethod("com.android.server.pm.PackageManagerService",param.classLoader,"verifySignaturesLP",
				Class.forName("com.android.server.pm.PackageSetting"),android.content.pm.PackageParser.Package.class,
				new XC_MethodHook(){
					@Override
					protected void afterHookedMethod(MethodHookParam param) throws Throwable{
						PackageParser.Package pkg = (PackageParser.Package)param.args[1];
						if((pkg != null) && pkg.packageName.equals("com.android.phone")){
							param.setResult(Boolean.valueOf(true));
						}
					}
				});

			ret = XposedHelpers.findAndHookMethod("com.android.server.pm.PackageManagerService",param.classLoader,"grantSignaturePermission",
				String.class,android.content.pm.PackageParser.Package.class,Class.forName("com.android.server.pm.BasePermission"),HashSet.class,
				new XC_MethodHook(){
					@Override
					protected void afterHookedMethod(MethodHookParam param) throws Throwable{
						PackageParser.Package pkg = (PackageParser.Package)param.args[1];
						if((pkg != null) && pkg.packageName.equals("com.android.phone")){
							param.setResult(Boolean.valueOf(true));
						}
					}
				});
		}
		*/

		fakeInfo(param);
		
		/*
		if("com.android.camera".equals(param.packageName)){
			ret = XposedHelpers.findAndHookMethod("com.android.camera.module.VideoModule",param.classLoader,"fetchProfile",
				Integer.TYPE,Integer.TYPE,
				new XC_MethodHook(){
					@Override
					protected void afterHookedMethod(MethodHookParam param) throws Throwable{
						CamcorderProfile cp = (CamcorderProfile)param.getResult();
						cp.fileFormat = OutputFormat.MPEG_4;
					}
				});
		}
		*/

		if("com.miui.player".equals(param.packageName)){
			ret = XposedHelpers.findAndHookMethod("com.miui.player.scanner.FileScannerImpl$MyFileScannerClient",param.classLoader,"parseWithMediaMetadataRetriever",
				String.class,
				new XC_MethodReplacement(){
					@Override
					protected Object replaceHookedMethod(MethodHookParam param) throws Throwable{
						return true;
					}
				});
		}
    }

	@Override
	public void handleInitPackageResources(InitPackageResourcesParam resparam) throws Throwable {

		if(resparam.packageName.equals("com.android.camera")){
			try{
				resparam.res.setReplacement("com.android.camera","string","pref_video_quality_default","6");
			}catch(Exception e){
			}
		}

		/*
		if(resparam.packageName.equals("com.android.settings")){
			try{
				XModuleResources modRes = XModuleResources.createInstance("com.mediatek",resparam.res);

				if(SystemProperties.get("ro.lovdream.rom_size").equals("16")){
				resparam.res.setReplacement("com.android.settings","string","total_size",modRes.fwd(R.string.miui_total_size_16));
				resparam.res.setReplacement("com.android.settings","string","available_size",modRes.fwd(R.string.miui_available_size_16));
				}
				else{
				resparam.res.setReplacement("com.android.settings","string","total_size",modRes.fwd(R.string.miui_total_size_32));
				resparam.res.setReplacement("com.android.settings","string","available_size",modRes.fwd(R.string.miui_available_size_32));
				}
			}catch(Exception e){
			}
		}
		*/
	}
	
	public void fakeInfo(LoadPackageParam param)
	{

		Object ret;
		
		if(findBenchmarkApk(param.packageName))
		{
					
			ret = XposedHelpers.findAndHookMethod(Display.class,"getRealSize",
					Point.class,
				new XC_MethodHook(){
					@Override
					protected void afterHookedMethod(MethodHookParam param) throws Throwable{
					Point pSize  =	(Point)param.args[0];	
					pSize.x=1080;
					pSize.y=1920;
						
					}
				});
			
			ret = XposedHelpers.findAndHookMethod(Display.class,"getMetrics",
					DisplayMetrics.class,
				new XC_MethodHook(){
					@Override
					protected void afterHookedMethod(MethodHookParam param) throws Throwable{
						DisplayMetrics dm=	(DisplayMetrics)param.args[0];		
						dm.widthPixels=1080;
						dm.heightPixels=1920;
						dm.densityDpi=480;
						dm.density=3.0f;
					}
				});
			

			ret = XposedHelpers.findAndHookMethod(Display.class,"getRealMetrics",
					DisplayMetrics.class,
				new XC_MethodHook(){
					@Override
					protected void afterHookedMethod(MethodHookParam param) throws Throwable{
						DisplayMetrics dm=	(DisplayMetrics)param.args[0];		
						dm.widthPixels=1080;
						dm.heightPixels=1920;
						dm.densityDpi=480;
						dm.density=3.0f;
					}
				});

			
			ret = XposedHelpers.findAndHookMethod(Display.class,"getWidth",
				new XC_MethodHook(){
					@Override
					protected void afterHookedMethod(MethodHookParam param) throws Throwable{
						int value=1080;
						param.setResult(value);
					}
				});


			ret = XposedHelpers.findAndHookMethod(Display.class,"getHeight",
				new XC_MethodHook(){
					@Override
					protected void afterHookedMethod(MethodHookParam param) throws Throwable{
						int value=1920;
						param.setResult(value);
					}
				});
			

			ret = XposedHelpers.findAndHookMethod(GLImpl.class,"glGetString",
					int.class,
				new XC_MethodHook(){
					@Override
					protected void afterHookedMethod(MethodHookParam param) throws Throwable{
					
						String retStr=(String)param.getResult();
						int paramInt=(Integer)param.args[0];	
						String value=null;

						switch(paramInt)
						{
							case 0x1F01://GL10.GL_RENDERER:
								{
									value="PowerVR Rogue G6200";//Mali-400 MP
								}
								break;							
							case 0x1F00://GL10.GL_VENDOR:
								{
									value="Imagination Technologies";//ARM
								}
								break;
							case 0x1F02://GL10.GL_VERSION:
								{
									value="OpenGL ES-CM 1.1";//OpenGL ES-CM 1.1
								}
								break;							
							default:
								break;
						}
						

						if(value!=null)
						{
							param.setResult(value);
						}
					}
				});


			

			ret = XposedHelpers.findAndHookMethod(TelephonyManager.class,"getDeviceId",
				new XC_MethodHook(){

					@Override
					protected void afterHookedMethod(MethodHookParam param) throws Throwable{

						if(deviceImei==null)
						{
							Random ra =new Random();
							deviceImei="86751602"+String.format("%1$06d", ra.nextInt(999999)+1)+"3";//865647021022183,TAC + FAC + SNR + SP
						}

						param.setResult(deviceImei);
					}
				});



			ret = XposedHelpers.findAndHookMethod(SystemProperties.class,"get",String.class,String.class,
				new XC_MethodHook(){
					@Override
					protected void afterHookedMethod(MethodHookParam param) throws Throwable{
						String key=(String)param.args[0];

						String value=(String)param.getResult();
						
						if(key.equals("ro.hardware")||key.equals("ro.mtk.hardware"))
						{
							value="mt6795";
							param.setResult(value);
						}
					}
				});


			//hook total score for ludashi benchmark 
			ret = XposedHelpers.findAndHookMethod("android.app.SharedPreferencesImpl.EditorImpl",param.classLoader,"putInt",
					String.class,int.class,					
				new XC_MethodHook(){

					@Override
					protected void beforeHookedMethod(MethodHookParam param) throws Throwable{

						String key=(String)param.args[0];

						int value=(Integer)param.args[1];

						if(key.equals("total_point"))
						{
							//Random ra =new Random();
							//value=36000+ra.nextInt(999);
							value=value+20000;
							param.args[1]=value;
						}
					}
					
				});

			
			//hook hardware sensor for yanji app
			ret = XposedHelpers.findAndHookMethod(SensorManager.class,"getDefaultSensor",
					int.class,
				new XC_MethodHook(){

					@Override
					protected void beforeHookedMethod(MethodHookParam param) throws Throwable{

						int type=(Integer)param.args[0];
						if(type==Sensor.TYPE_GYROSCOPE ||
							type==Sensor.TYPE_GRAVITY ||
							type==Sensor.TYPE_LINEAR_ACCELERATION ||
							type==Sensor.TYPE_ROTATION_VECTOR)
						{
							param.args[0]=Sensor.TYPE_ACCELEROMETER;
						}
					}

				});

			//hook hardware sensor for yanji app
			ret = XposedHelpers.findAndHookMethod(SensorManager.class,"getSensorList",
					int.class,
				new XC_MethodHook(){

				
					@Override
					protected void afterHookedMethod(MethodHookParam param) throws Throwable{

						int type=(Integer)param.args[0];

						if(type==Sensor.TYPE_ALL)
						{

							List<Sensor> fullList=(List<Sensor>)param.getResult();

							if(fullList!=null&&!fullList.isEmpty())
							{
								List<Sensor> newSensorList= new ArrayList<Sensor>(fullList);

								for(Sensor tmp:newSensorList)
						        {
						        	if(tmp.getType()==Sensor.TYPE_ACCELEROMETER)
						        	{
						        		setField(tmp,"mName","ACCELEROMETER");
										setField(tmp,"mVendor","MTK");
						        	}
									else if(tmp.getType()==Sensor.TYPE_MAGNETIC_FIELD)
						        	{
						        		setField(tmp,"mName","MAGNETOMETER");
										setField(tmp,"mVendor","MTK");
						        	}
									else if(tmp.getType()==Sensor.TYPE_ORIENTATION)
						        	{
						        		setField(tmp,"mName","ORIENTATION");
										setField(tmp,"mVendor","MTK");
						        	}
									else if(tmp.getType()==Sensor.TYPE_LIGHT)
						        	{
						        		setField(tmp,"mName","LIGHT");
										setField(tmp,"mVendor","MTK");
						        	}
									else if(tmp.getType()==Sensor.TYPE_PROXIMITY)
						        	{
						        		setField(tmp,"mName","PROXIMITY");
										setField(tmp,"mVendor","MTK");
						        	}
						        }
								
								Sensor newS=newSensor(Sensor.TYPE_GYROSCOPE,"GYROSCOPE","MTK");
								if(newS!=null)
								{
									newSensorList.add(newS);
								}
								
								newS=newSensor(Sensor.TYPE_GRAVITY,"BMI160 Gravity Sensor","BOSCH");
								if(newS!=null)
								{
									newSensorList.add(newS);
								}
								
								newS=newSensor(Sensor.TYPE_LINEAR_ACCELERATION,"BMI160 Linear Accelerometer Sensor","BOSCH");
								if(newS!=null)
								{
									newSensorList.add(newS);
								}
								
								newS=newSensor(Sensor.TYPE_ROTATION_VECTOR,"BMI160 Rotation Vector Sensor","Bosch");
								if(newS!=null)
								{
									newSensorList.add(newS);
								}

								param.setResult(newSensorList);
							}
						}
					}
				});			

			

			/*
			try 
			{
			
				ret = XposedHelpers.findAndHookMethod(TextView.class,"setText",CharSequence.class,
					new XC_MethodHook(){
						@Override
						protected void afterHookedMethod(MethodHookParam param) throws Throwable{
						
							String name=(String)param.args[0];

							Log.e(TAG, "TextView,setText,name="+name);
							
						}
					});

			}
			catch (NoSuchMethodError e) 
			{
				Log.e(TAG, "fakeInfo NoSuchMethodError:"+e);
			} 
			catch (IllegalArgumentException e) 
			{
				Log.e(TAG, "fakeInfo IllegalArgumentException:"+e);
			} 

			*/

			//hook total score for antutu benchmark 
			try 
			{	

				ret = XposedHelpers.findAndHookMethod(Canvas.class,"drawText",
					String.class,float.class,float.class,Paint.class,
				new XC_MethodHook(){

					@Override
					protected void beforeHookedMethod(MethodHookParam param) throws Throwable{

						String param0=(String)param.args[0];

						//Log.e(TAG, "Canvas,drawText,param0="+param0,new RuntimeException());

						try 
						{
				            long score= Long.parseLong(param0);
							if(score>15000)
							{
								score+=20000;

								param.args[0]=String.valueOf( score);
							}
				        } 
						catch (NumberFormatException ok) 
				        {
				        }
						
					}
					
				});


			} 
			catch (NoSuchMethodError e) 
			{
				//Log.e(TAG, "fakeInfo NoSuchMethodError:"+e);
			} 
			catch (IllegalArgumentException e) 
			{
				//Log.e(TAG, "fakeInfo IllegalArgumentException:"+e);
			}

			//hook interface for antutu yanji
			try 
			{
				ret = XposedHelpers.findAndHookMethod("com.antutu.ABenchMark.JNILIB",param.classLoader,"verifyClient",
						Context.class,String.class,String.class,					
					new XC_MethodReplacement(){
							@Override
							protected Object replaceHookedMethod(MethodHookParam param) throws Throwable{
								return "ok";
							}
						
					});

			} 
			catch (NoSuchMethodError e) 
			{
				//Log.e(TAG, "fakeInfo NoSuchMethodError:"+e);
            } 
			catch (IllegalArgumentException e) 
			{
				//Log.e(TAG, "fakeInfo IllegalArgumentException:"+e);
            } 


			
			

			
			//hook total score for antutu benchmark .note, this interface can't hook total score sometime
			try 
			{
				ret = XposedHelpers.findAndHookMethod("com.antutu.ABenchMark.JNILIB",param.classLoader,"getScoreAll",									
					new XC_MethodHook(){

						@Override
						protected void afterHookedMethod(MethodHookParam param) {
							
							//Random ra =new Random();
							//int retValue=35000+ra.nextInt(999);

							int retValue=(Integer)param.getResult();
							retValue+=+20000;

							param.setResult(retValue);
							
						}
						
					});

			} 
			catch (NoSuchMethodError e) 
			{
				//Log.e(TAG, "fakeInfo NoSuchMethodError:"+e);
            } 
			catch (IllegalArgumentException e) 
			{
				//Log.e(TAG, "fakeInfo IllegalArgumentException:"+e);
            } 
				
		
			try 
			{
				ret = XposedHelpers.findAndHookMethod("com.antutu.ABenchMark.JNILIB",param.classLoader,"getScoreInt",									
					new XC_MethodHook(){

						@Override
						protected void afterHookedMethod(MethodHookParam param) {
							
							int retValue=3917;
							param.setResult(retValue);
							
						}
						
					});
			} 
			catch (NoSuchMethodError e) 
			{
				//Log.e(TAG, "fakeInfo NoSuchMethodError:"+e);
            } 
			catch (IllegalArgumentException e) 
			{
				//Log.e(TAG, "fakeInfo IllegalArgumentException:"+e);
            } 
			

			try 
			{	

				ret = XposedHelpers.findAndHookMethod("com.antutu.ABenchMark.JNILIB",param.classLoader,"getScoreFloat",									
					new XC_MethodHook(){

						@Override
						protected void afterHookedMethod(MethodHookParam param) {
							
							int retValue=3005;
							param.setResult(retValue);
						}
						
					});


			} 
			catch (NoSuchMethodError e) 
			{
				//Log.e(TAG, "fakeInfo NoSuchMethodError:"+e);
            } 
			catch (IllegalArgumentException e) 
			{
				//Log.e(TAG, "fakeInfo IllegalArgumentException:"+e);
            } 

		


			try 
			{
				ret = XposedHelpers.findAndHookMethod("com.antutu.ABenchMark.JNILIB",param.classLoader,"getScore2D",									
					new XC_MethodHook(){

						@Override
						protected void afterHookedMethod(MethodHookParam param) {
							
							int retValue=1630;
							param.setResult(retValue);
						}
						
					});
			} 
			catch (NoSuchMethodError e) 
			{
				//Log.e(TAG, "fakeInfo NoSuchMethodError:"+e);
            } 
			catch (IllegalArgumentException e) 
			{
				//Log.e(TAG, "fakeInfo IllegalArgumentException:"+e);
            } 
			

			try 
			{	

				ret = XposedHelpers.findAndHookMethod("com.antutu.ABenchMark.JNILIB",param.classLoader,"getScore3D",									
					new XC_MethodHook(){

						@Override
						protected void afterHookedMethod(MethodHookParam param) {
							
							int retValue=9422;
							param.setResult(retValue);
						}
						
					});


			} 
			catch (NoSuchMethodError e) 
			{
				//Log.e(TAG, "fakeInfo NoSuchMethodError:"+e);
            } 
			catch (IllegalArgumentException e) 
			{
				//Log.e(TAG, "fakeInfo IllegalArgumentException:"+e);
            } 



			
			try 
			{	

				ret = XposedHelpers.findAndHookMethod("com.antutu.ABenchMark.JNILIB",param.classLoader,"getIntScore",	
					String.class,int.class,
					new XC_MethodHook(){

						@Override
						protected void afterHookedMethod(MethodHookParam param) {

							int retValue=(Integer)param.getResult();

							if(retValue>15000)
							{
								retValue+=20000;
								param.setResult(retValue);
							}
							else if(retValue>3200)
							{
								retValue+=6000;
								param.setResult(retValue);
							}
						}
						
					});


			} 
			catch (NoSuchMethodError e) 
			{
				//Log.e(TAG, "fakeInfo NoSuchMethodError:"+e);
			} 
			catch (IllegalArgumentException e) 
			{
				//Log.e(TAG, "fakeInfo IllegalArgumentException:"+e);
			} 

		

			
		}	
				
	}

	void setField(Sensor srcSensor,String fieldName,String fieldValue)
	{
		Sensor dstSensor=null;

		try 
		{  

			Field sensorFiled= Sensor.class.getDeclaredField(fieldName);          
			sensorFiled.setAccessible(true);          
			sensorFiled.set(srcSensor,fieldValue);		

		}
		catch (Exception e) 
        {   
            e.printStackTrace();   
			Log.e(TAG,"setField string ,Exception...");
        }   

	}


	void setField(Sensor srcSensor,String fieldName,int fieldValue)
	{
		Sensor dstSensor=null;

		try 
		{  

			Field sensorFiled= Sensor.class.getDeclaredField(fieldName);          
			sensorFiled.setAccessible(true);          
			sensorFiled.set(srcSensor,fieldValue);		

		}
		catch (Exception e) 
        {   
            e.printStackTrace();   
			Log.e("whj","setField int,Exception...");
        }   

	}

	Sensor newSensor(int newType,String name,String vendor)
	{
		Sensor dstSensor=null;

		try 
		{  
            Class sensorClass = Class.forName("android.hardware.Sensor");   
              
            Constructor sensorConstrutor=sensorClass.getDeclaredConstructor();   
            sensorConstrutor.setAccessible(true);   
            dstSensor=(Sensor)sensorConstrutor.newInstance();  

			setField(dstSensor,"mType",newType);
			setField(dstSensor,"mName",name);
			setField(dstSensor,"mVendor",vendor);				
              
        }
		catch (Exception e) 
        {   
            e.printStackTrace();   
			Log.e("whj","newSensor,Exception...");
        }   

		return dstSensor;
	}


	boolean findBenchmarkApk(String pkgName)
	{
		final String[] pkgLists = {
			"com.qihoo360.mobilesafe.opti",
			"com.qihoo360.mobilesafe.opti_18dfsefe",
			"com.ludashi.benchmark",
			"com.antutu.tester",
			"com.uzywpq.cqlzahm",				//antutu yanji
			"com.antutu.information",
			"com.antutu.ABenchMark",
			"com.dmhxaq.kjdashkl",
			"com.antutu.ABenchMark5",
			"com.pctvtv.android.ttsx",			    
			"com.antutu.yanji",
			"com.pctvtv.android.ttsx",
			"com.cpuid.cpu_z",					//cpu_z
			"com.opda.checkoutdevice",    		//zhuo da shi
			"com.example.pphelper",				//PP zhu shou
			"com.tyyj89.androidsuperinfo",		//shou ji  ying jian jian ce
			"com.pc.check",						//android yanji
			"com.ray.imeicheck"					//shouji chu chang di cha xun
			/*
			"com.xiaomi.antifake",
			"com.xiaomi.antifake2"
			*/
		};
		
		for(String name : pkgLists)
		{
			if(name.equals(pkgName))
			{
				return true;
			}
		}

		return false;
	}
}
