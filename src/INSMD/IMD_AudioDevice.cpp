#include "IMD_AudioDevice.h"

CIMDAudioDevice::CIMDAudioDevice()
{

}

CIMDAudioDevice::CIMDAudioDevice(QAudioDeviceInfo *pIMD_DeviceInfo, int pIMD_DeviceMode)
{
   IMD_DeviceName = pIMD_DeviceInfo->deviceName();
   IMD_DeviceMode = pIMD_DeviceMode;

   IMD_SupportedSampleRates   = pIMD_DeviceInfo->supportedSampleRates();
   IMD_SupportedChannelCounts = pIMD_DeviceInfo->supportedChannelCounts();
   IMD_SupportedCodecs        = pIMD_DeviceInfo->supportedCodecs();
   IMD_SupportedSampleSizes   = pIMD_DeviceInfo->supportedSampleSizes();
   IMD_SupportedSampleTypes   = pIMD_DeviceInfo->supportedSampleTypes();
   IMD_SupportedByteOrders    = pIMD_DeviceInfo->supportedByteOrders();

   qWarning() << "===========================================";
   qWarning() << "Nome Device       :" << IMD_DeviceName ;
   qWarning() << "Device Mode       :" << IMD_DeviceMode ;
   qWarning() << "Codecs Suportados :";
   for(int i=0; i<IMD_SupportedCodecs.size();i++ )
   {
       qWarning() << "Codec :" << IMD_SupportedCodecs[i];

       for(int j=0; j<IMD_SupportedSampleRates.size();j++ )
       {
           qWarning() << "Sample Rates Suportados :" << IMD_SupportedSampleRates[j];
       }

       for(int j=0; j<IMD_SupportedChannelCounts.size();j++ )
       {
           qWarning() << "Qtd Canais Suportados :" << IMD_SupportedChannelCounts[j];
       }

       for(int j=0; j<IMD_SupportedSampleSizes.size();j++ )
       {
           qWarning() << "Tamanho Samplers Suportados :" << IMD_SupportedSampleSizes[j];
       }

       for(int j=0; j<IMD_SupportedSampleTypes.size();j++ )
       {
           qWarning() << "Tipos de Samplers Suportados :" << IMD_SupportedSampleTypes[j];
       }

       for(int j=0; j<IMD_SupportedByteOrders.size();j++ )
       {
           qWarning() << "Ordem de Bytes Suportados :" << IMD_SupportedByteOrders[j];
       }
   }

   //Realiza o Setup do formato de dados Atual como o primeiro das listas de dados suportados
   //pelo dispositivo

   if(IMD_SupportedChannelCounts.size()>0)IMD_AudioFormat.setChannelCount(IMD_SupportedChannelCounts[0]);
   if(IMD_SupportedCodecs       .size()>0)IMD_AudioFormat.setCodec       (IMD_SupportedCodecs       [0]);
   if(IMD_SupportedSampleRates  .size()>0)IMD_AudioFormat.setSampleRate  (IMD_SupportedSampleRates  [0]);
   if(IMD_SupportedSampleSizes  .size()>0)IMD_AudioFormat.setSampleSize  (IMD_SupportedSampleSizes  [0]);
   if(IMD_SupportedSampleTypes  .size()>0)IMD_AudioFormat.setSampleType  (IMD_SupportedSampleTypes  [0]);
   if(IMD_SupportedByteOrders   .size()>0)IMD_AudioFormat.setByteOrder   (IMD_SupportedByteOrders   [0]);

}
