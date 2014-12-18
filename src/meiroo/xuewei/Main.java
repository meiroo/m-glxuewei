package meiroo.xuewei;


import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;

import android.opengl.GLSurfaceView;
import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.os.SystemClock;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.PixelFormat;
import android.util.AttributeSet;
import android.view.KeyEvent;
import android.view.MotionEvent;
import meiro.xuewei.R;
import meiroo.xuewei.AndroidFontTool.*;
import meiroo.xuewei.AndroidGL.*;

public class Main extends Activity {
	
	GlBufferView view;
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		view =  new GlBufferView(this);
		setContentView(view);
		
		Utils.CopyAssets(getResources().getAssets(), "/sdcard/", "xuewei");
		
	}
	
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event)
	{
		view.onKeyDown(keyCode, event);
		return true;
	}
	
	@Override
	public boolean onKeyUp(int keyCode, KeyEvent event)
	{
		view.onKeyUp(keyCode, event);
		return true;
	}
}

class GlBufferView extends GLSurfaceView {
	private static native void native_start();
	private static native void native_gl_resize(int w, int h);
	private static native void native_gl_render();
	private static native void native_key_event(int key, int status);
	private static native void native_touch_event(float x, float y, int status);
	private static native void native_multi_touch_event(float x0, float y0, float x1, float y1, int status);
	private static native void native_set_texture_arr(int[] textures);
	private static String TAG = "MGLApp";

	public GlBufferView(Context context) {
		super(context);		
		
		getHolder().setFormat(PixelFormat.TRANSLUCENT);
        setEGLContextClientVersion(2);
		setRenderer(new MyRenderer());
	}
	@Override
    public boolean onTouchEvent(final MotionEvent event)
	{
		final int numEvents = event.getPointerCount();
		final float x0;
		final float y0;
		final float x1;
		final float y1;
		final int action;
		if(numEvents >= 2){
			x0 = event.getX(0);
			y0 = event.getY(0);
			x1 = event.getX(1);
			y1 = event.getY(1);			
		}else
		{
			x0 = event.getX();
			y0 = event.getY();
			x1 = 0;
			y1 = 0;
		}
		action = event.getAction();
		queueEvent(new Runnable() {
            public void run() {            	
        		if(numEvents >= 2)
        		{
        			native_multi_touch_event(x0,y0,x1,y1,action);
        		}else
        			native_touch_event(x0,y0,action);
            }});		
		return true;
	}
	
	@Override
	public boolean onKeyDown(final int keyCode, final KeyEvent event)
	{
		queueEvent(new Runnable() {
            public void run() {
            	native_key_event(keyCode, event.getAction());
            }});		
		return false;
	}
	
	@Override
	public boolean onKeyUp(final int keyCode, final KeyEvent event)
	{
		queueEvent(new Runnable() {
            public void run() {
            	native_key_event(keyCode, event.getAction());
            }});		
		return false;
	}

	class MyRenderer implements GLSurfaceView.Renderer {
		public void onSurfaceCreated(GL10 gl, EGLConfig c) { 
			/* do nothing */ 
			Bitmap bitmaps[] = new Bitmap[1];
			int textureID[] = new int[1];
			//bitmaps[0] = AndroidFontTool.DrawNameOnBitmap("abda我的文件basd");
			//bitmaps[0] = AndroidFontTool.DrawNineBitmaps();
			//textureID = AndroidGL.GenerateTexture(gl, 1, bitmaps);
			//native_set_texture_arr(textureID);
			
			native_start();
		}

		public void onSurfaceChanged(GL10 gl, int w, int h) {
			native_gl_resize(w, h);
		}

		public void onDrawFrame(GL10 gl) {
			time = SystemClock.uptimeMillis();

			if (time >= (frameTime + 1000.0f)) {
				frameTime = time;
				avgFPS += framerate;
				framerate = 0;
			}

			if (time >= (fpsTime + 3000.0f)) {
				fpsTime = time;
				avgFPS /= 3.0f;
				Log.d("MGLAppFPS", "FPS: " + Float.toString(avgFPS));
				avgFPS = 0;
			}
			framerate++;
			native_gl_render();
		}
		public long time = 0;
		public short framerate = 0;
		public long fpsTime = 0;
		public long frameTime = 0;
		public float avgFPS = 0;
	}

	static {
		System.loadLibrary("mglxuewei");
	}
}
