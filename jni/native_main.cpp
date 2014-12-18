#include <jni.h>
#include <android/log.h>
#include <android_key_code.h>

#include "native_interface.h"
#include "Window.h"
#include "Render.h"
#include "OpenGLRender.h"
#include "OpenGL2Render.h"
#include "Engine.h"


#include "Xuewei/3dxuewei.h"
#include "os.h"



CRender* render;
CWindow* window;
CScene* app;

CScene* xuewei;


void native_gl_resize(JNIEnv *env UNUSED, jclass clazz UNUSED, jint w, jint h)
{
	LOGI("native_gl_resize %d %d", w, h);
	g_Engine->OnReshape(w,h);
}

void native_gl_render(JNIEnv *env UNUSED, jclass clazz UNUSED)
{
	//LOGI("native_gl_render");
	g_Engine->OnIdle();
	g_Engine->OnDisplay();
}

void native_start(JNIEnv *env UNUSED, jclass clazz UNUSED)
{
	/* init conditions */
	LOGI("native_start");
	Engine* engine = g_Engine;
	engine->MediaPath = "/sdcard/xuewei/";
	//engine->MediaPath = "/mnt/sdcard/";
#ifdef GL11
	render = new COpenGLRender();
#elif defined GL20
	render = new COpenGL2Render();
#endif
	window = new CWindow();   

	xuewei = new C3DXueWei();  
	engine->SetEnginePara(render,window);  
	engine->SetScene(0,xuewei);           
	engine->SwitchScene(0);     
}
void native_key_event(JNIEnv *env,jclass clazz,jint key,jint status)
{    
	LOGI("native_key_event  key:%d action:%d",key,status);

	static int start = 0;
	static long time = 0;   
	bool longPress = false;
	if(os::getTickCount() - time >= 2000 && time!=0)
		longPress = true;

	if(status == 0)
	{
		if(time ==0)
			time = os::getTickCount();
	}else
	{
		if(key ==KEY_SUBMENU)
		{
			key = KEY_SPACE;
		}
		g_Engine->OnKeyboard(key,0,0);
		time = 0;
	}

	if(key == VOLUME_UP)
	{
		key = KEY_UP;
		g_Engine->OnKeyboard(key,0,0);

	}else if(key == VOLUME_DOWN)
	{
		key = KEY_DOWN;
		g_Engine->OnKeyboard(key,0,0);
	}
}
int LastMultiTouchStatus = -1;
int LastTouchStatus = -1;
#define ANDROID_MOUSE_DOWN 2
#define ANDROID_MOUSE_UP 1
#define ANDROID_MOUSE_MOVE 4

void native_touch_event(JNIEnv *env,jclass clazz,jfloat x,jfloat y,jint status)
{
	//LOGI("native_touch_event status = %d",status);
	if(LastMultiTouchStatus == ANDROID_MOUSE_DOWN)
	{
		native_multi_touch_event(env,clazz,x,y,0,0,ANDROID_MOUSE_UP);
		return;
	}

	if(status == ANDROID_MOUSE_DOWN && LastTouchStatus == ANDROID_MOUSE_DOWN)
	{
		g_Engine->OnMouse(MOUSE_MOVE,status,x,y);
		LOGI("SINGLE touch move!");
	}
	else if(status ==ANDROID_MOUSE_DOWN)
	{
		g_Engine->OnMouse(MOUSE_LBUTTON_DOWN,status,x,y);
		LOGI("SINGLE touch Down!");
	}
	else if(status ==ANDROID_MOUSE_UP)
	{
		LOGI("SINGLE touch Up!");
		g_Engine->OnMouse(MOUSE_LBUTTON_UP,status,x,y);
	}
	LastTouchStatus = status;
}


void native_multi_touch_event(JNIEnv *env,jclass clazz,jfloat x0,jfloat y0,jfloat x1,jfloat y1,jint status)
{
	static int downDis = 0;
	if(LastTouchStatus==ANDROID_MOUSE_DOWN)
	{
		LOGI("Double touch Down!");
		native_touch_event(env,clazz,x0,y0,ANDROID_MOUSE_UP);
		return;
	}


	if(status == ANDROID_MOUSE_DOWN && LastMultiTouchStatus == ANDROID_MOUSE_DOWN)
	{
		//Double Move or Scale
		point2f p0 = point2f(x0,y0);
		point2f p1 = point2f(x1,y1);
		int moveDis = p0.DistanceTo(p1);
		if(moveDis - downDis > 20)
		{
			g_Engine->OnMouse(TOUCH_SCALEUP,status,x0,y0);
			LOGI("Double touch Move Scale Up!");
			downDis = moveDis;
		}else if(moveDis - downDis < -20)
		{
			g_Engine->OnMouse(TOUCH_SCALEDOWN,status,x0,y0);
			downDis = moveDis;
			LOGI("Double touch Move Scale Down!");
		}else
		{
			g_Engine->OnMouse(TOUCH_MOVE,status,x0,y0);
			LOGI("Double touch Move Translate!");
		}
	}
	else if(status ==ANDROID_MOUSE_DOWN)
	{
		g_Engine->OnMouse(TOUCH_DOWN,status,x0,y0);
		point2f p0 = point2f(x0,y0);
		point2f p1 = point2f(x1,y1);
		downDis = p0.DistanceTo(p1);
		
	}
	else if(status ==ANDROID_MOUSE_UP)
	{
		LOGI("Double touch Up!");
		g_Engine->OnMouse(TOUCH_UP,status,x0,y0);
		downDis = 0;
	}
	LastMultiTouchStatus = status;
	
}

int TextureIDs[100];
void native_set_texture_arr(JNIEnv *env,jclass clazz,jintArray arr)
{
	LOGI("native_set_texture_arr");
	jint size = env->GetArrayLength(arr);
	env->GetIntArrayRegion(arr,0,size,TextureIDs);
}