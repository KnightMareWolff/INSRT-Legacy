#include "IMD_Video.h"

CIMDVideo::CIMDVideo(QString pIMD_NomeArquivo)
{
    if(pIMD_NomeArquivo != "")
    {
        IMD_VideoCapture.open(pIMD_NomeArquivo.toStdString());
        if(!IMD_VideoCapture.isOpened())
        {
            IMD_VideoStatus = IMD_VIDEO_STATUS_OPENERROR;
        }
        else
        {
            IMD_VideoStatus = IMD_VIDEO_STATUS_OPENOK;
        }
    }
    IMD_ExecutionMode = IMD_VIDEO_EXEC_LOOP;
}

CIMDVideo::CIMDVideo(int pIMD_CameraId)
{
    if(pIMD_CameraId >= 0)
    {
        IMD_VideoCapture.open(pIMD_CameraId);
        if(!IMD_VideoCapture.isOpened())
        {
            IMD_VideoStatus = IMD_VIDEO_STATUS_OPENERROR;
        }
        else
        {
            IMD_VideoStatus = IMD_VIDEO_STATUS_OPENOK;
        }
    }
    IMD_ExecutionMode = IMD_VIDEO_EXEC_FOREVER;
}

CIMDVideo::~CIMDVideo()
{
    IMD_VideoCapture.release();
    IMD_VideoStatus = IMD_VIDEO_STATUS_FINISH;
}

bool   CIMDVideo::PegaPropriedades(unsigned int &pIMA_Altura    ,
                                   unsigned int &pIMA_Largura   ,
                                   unsigned int &pIMA_Formato   )
{
    pIMA_Altura  = 256;
    pIMA_Largura = 256;
    pIMA_Formato = GL_RGB;

    return true;
}

uchar* CIMDVideo::PegaFrame()
{
    if(IMD_VideoCapture.read(IMD_VideoFrame))
    {
       Size sz;
       sz.height = 256;
       sz.width  = 256;

       resize(IMD_VideoFrame,IMD_VideoFrame,sz,0,0);

       IMD_VideoStatus = IMD_VIDEO_STATUS_PROCESSING;

       return IMD_VideoFrame.ptr();
    }
    else
    {
        if(IMD_ExecutionMode == IMD_VIDEO_EXEC_LOOP)
        {
            IMD_VideoCapture.set(CV_CAP_PROP_POS_MSEC,0);
            if(IMD_VideoCapture.read(IMD_VideoFrame))
            {
                Size sz;
                sz.height = 256;
                sz.width  = 256;

                //como estamos em realtime uma textura 256 e o suficiente
                resize(IMD_VideoFrame,IMD_VideoFrame,sz,0,0);

                IMD_VideoStatus = IMD_VIDEO_STATUS_PROCESSING;

                return IMD_VideoFrame.ptr();
            }
        }
        if(IMD_ExecutionMode == IMD_VIDEO_EXEC_ONESHOT)
        {
           IMD_VideoStatus = IMD_VIDEO_STATUS_FINISH;
           return NULL;
        }
    }
}

uint CIMDVideo::PegaStatus()
{
    return IMD_VideoStatus;
}

