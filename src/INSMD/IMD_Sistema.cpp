#include "IMD_Sistema.h"

CIMDSistema::CIMDSistema()
{

    IMD_InputDevicesInfo  = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    IMD_OutPutDevicesInfo = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);

    qWarning() << "===========================================";
    qWarning() << "Configuracao Plataforma Multimidia         ";
    qWarning() << "===========================================";
    qWarning() << "Criando os Devices de Entrada:             ";
    for(int i=0; i<IMD_InputDevicesInfo.size();i++ )
    {
        IMD_InputAudioDevices.push_back(new CIMDAudioDevice(&IMD_InputDevicesInfo[i],
                                                            IMD_AUDIO_MODE_INPUT    ));
    }

    qWarning() << "Criando os Devices de Saida  :             ";
    for(int i=0; i<IMD_OutPutDevicesInfo.size();i++ )
    {
        IMD_OutPutAudioDevices.push_back(new CIMDAudioDevice(&IMD_OutPutDevicesInfo[i],
                                                            IMD_AUDIO_MODE_OUTPUT     ));
    }

}
