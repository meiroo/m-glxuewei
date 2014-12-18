#ifndef glbuffer_h_seen
#define glbuffer_h_seen

#include <jni.h>
#define UNUSED  __attribute__((unused))

void native_start(JNIEnv *env, jclass clazz);
void native_gl_resize(JNIEnv *env, jclass clazz, jint w, jint h);
void native_gl_render(JNIEnv *env, jclass clazz);
void native_key_event(JNIEnv *env,jclass clazz,jint key,jint status);
void native_touch_event(JNIEnv *env,jclass clazz,jfloat x,jfloat y,jint status);
void native_multi_touch_event(JNIEnv *env,jclass clazz,jfloat x0,jfloat y0,jfloat x1,jfloat y1,jint status);

void native_set_texture_arr(JNIEnv *env,jclass clazz,jintArray arr);
#endif
