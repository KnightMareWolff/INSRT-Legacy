#ifndef IMD_GLOBALDEF_H
#define IMD_GLOBALDEF_H

#include <QtGlobal>
#include <QtGui>
#include <QtMultimedia>
#include <QAbstractAudioDeviceInfo>
#include <QVideoDeviceSelectorControl>
#include "../INSMT/INSMT.h"

using namespace std;
/****************************/
/*Includes FMOD Sound System*/
/****************************/
#ifdef Q_OS_WIN
   // OpenCV includes
   #include "opencv2/core.hpp"
   #include "opencv2/highgui.hpp"
   #include "opencv2/opencv.hpp"
using namespace cv;
#endif

#define IMD_VIDEO_SOURCE_CAMERA 0
#define IMD_VIDEO_SOURCE_FILE   1
#define IMD_VIDEO_SOURCE_IMAGES 2

#define IMD_VIDEO_STATUS_OPENERROR  0
#define IMD_VIDEO_STATUS_OPENOK     1
#define IMD_VIDEO_STATUS_PROCESSING 2
#define IMD_VIDEO_STATUS_FINISH     3

#define IMD_VIDEO_EXEC_ONESHOT      1
#define IMD_VIDEO_EXEC_LOOP         2
#define IMD_VIDEO_EXEC_FOREVER      3

#define IMD_AUDIO_MODE_INPUT        1
#define IMD_AUDIO_MODE_OUTPUT       2


#endif // IMD_GLOBALDEF_H
