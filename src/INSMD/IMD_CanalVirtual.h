#ifndef IMD_CANALVIRTUAL_H
#define IMD_CANALVIRTUAL_H

#include "IMD_GlobalDef.h"

class CIMDCanalVirtual : public QIODevice
{
public:
    CIMDCanalVirtual(                      );

    CIMDCanalVirtual(QAudioFormat IMD_Formato     ,
                     qint64       IMD_Duracao     ,
                     int          IMD_FrequenciaHz);

    CIMDCanalVirtual(QByteArray   pIMD_Data);
    CIMDCanalVirtual(QString      pIMD_File);
   ~CIMDCanalVirtual(                      );
private:
    QAudioBuffer   IMD_AudioBuffer;
    QAudioDecoder *IMD_Decoder;

    QByteArray GeraBuffer(QAudioFormat IMD_Formato     ,
                          qint64       IMD_Duracao     ,
                          int          IMD_FrequenciaHz);
};

#endif // IMD_CANALVIRTUAL_H
