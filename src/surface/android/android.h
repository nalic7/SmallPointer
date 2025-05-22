#ifndef NALI_SURFACE_ANDROID_H
#define NALI_SURFACE_ANDROID_H

#define LOOPER_ID_INPUT 1

extern ANativeWindow *sa_anativewindow_p;
extern ANativeActivity *sa_anativeactivity_p;
extern AInputQueue *sa_ainputqueue_p;

void sa_wait();

#endif