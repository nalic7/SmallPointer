#ifndef NALI_SURFACE_ANDROID_H
#define NALI_SURFACE_ANDROID_H

#define LOOPER_ID_INPUT 1

extern ANativeWindow *m_anativewindow_p;
extern ANativeActivity *m_anativeactivity_p;
extern AInputQueue *m_ainputqueue_p;

void a_wait();

#endif