package android.util;

public class PoGoPin {

	public PoGoPin() {}

	public static native int openBeidou (String device);

	public static native int openBeidou_9600 (String device);

	public static native int openUart (String device);

	public static native int openUart9600 (String device);

	public static native int closeBeidou ();

	public static native int closeUart ();

	public static native int exist ();

	public static native int ioctlDevice (int mode);

	public static native int switchDevice (int mode);

	public static native int switchRawData (int mode);

	public static native int readDevice (byte[] b, int len);

	public static native int readRawData (byte[] b, int len);

	public static native int writeDevice (byte[] b, int len);


}
