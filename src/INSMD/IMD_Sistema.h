#ifndef IMD_SISTEMA_H
#define IMD_SISTEMA_H

#include "IMD_GlobalDef.h"
#include "IMD_AudioDevice.h"
#include "IMD_VideoDevice.h"

class CIMDSistema
{
public:
    CIMDSistema();

private:
    QAudioDeviceInfo   IMD_InfoSistemaAudio;
    CIMDVideoDevice    IMD_InfoSistemaVideo;

    QList<QAudioDeviceInfo> IMD_InputDevicesInfo;
    QList<QAudioDeviceInfo> IMD_OutPutDevicesInfo;

    vector<CIMDAudioDevice *> IMD_InputAudioDevices;
    vector<CIMDAudioDevice *> IMD_OutPutAudioDevices;
};

#endif // IMD_SISTEMA_H
