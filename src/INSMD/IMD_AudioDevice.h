#ifndef IMD_AUDIODEVICE_H
#define IMD_AUDIODEVICE_H

#include "IMD_GlobalDef.h"

class CIMDAudioDevice
{
public:
    CIMDAudioDevice(                                 );
    CIMDAudioDevice(QAudioDeviceInfo *pIMD_DeviceInfo,int pIMD_DeviceMode);

private:
    QString                         IMD_DeviceName; //Nome do Device
    int                             IMD_DeviceMode; //Modo de IO (Input/OutPut)
    QAudioFormat                    IMD_AudioFormat;//Formato de Dados de Audio Atual
    QList<int>                      IMD_SupportedSampleRates;
    QList<int>                      IMD_SupportedChannelCounts;
    QStringList                     IMD_SupportedCodecs;
    QList<int>                      IMD_SupportedSampleSizes;
    QList<QAudioFormat::SampleType> IMD_SupportedSampleTypes;
    QList<QAudioFormat::Endian>     IMD_SupportedByteOrders;
};

#endif // IMD_AUDIODEVICE_H
