#ifndef CIMDVIDEO_H
#define CIMDVIDEO_H

#include "IMD_GlobalDef.h"

class CIMDVideo
{
public:
     CIMDVideo(QString pIMD_NomeArquivo);
     CIMDVideo(int     pIMD_CameraId   );
    ~CIMDVideo(                        );

    bool   PegaPropriedades(unsigned int &pIMA_Altura    ,
                            unsigned int &pIMA_Largura   ,
                            unsigned int &pIMA_Formato   );

    uchar* PegaFrame ();
    uint   PegaStatus();
private:
    Mat          IMD_VideoFrame   ;
    VideoCapture IMD_VideoCapture ;
    uint         IMD_VideoStatus  ;
    uint         IMD_ExecutionMode;
};

#endif // CIMDVIDEO_H
