// Created on Thu June 20 2013

#ifndef _RUS_CAMERA_H_
#define _RUS_CAMERA_H_

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void rus_camera_open();
EXTERNC void rus_camera_close();
EXTERNC int rus_camera_update();
EXTERNC int find_pole();

#endif
