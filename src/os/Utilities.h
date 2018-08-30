//
// Created by Rob on 7/7/2018.
//

#ifndef DGL_UTILITIES_H
#define DGL_UTILITIES_H

#include <android/log.h>


#define APP_NAME "DGL"

#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, APP_NAME, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, APP_NAME, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, APP_NAME, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, APP_NAME, __VA_ARGS__))


#endif //DGL_UTILITIES_H
