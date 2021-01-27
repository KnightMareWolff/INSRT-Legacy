#include "IMD_CanalVirtual.h"

CIMDCanalVirtual::~CIMDCanalVirtual()
{
    close();
}

CIMDCanalVirtual::CIMDCanalVirtual()
{
   open(QIODevice::ReadWrite);
   IMD_Decoder = new QAudioDecoder(this);
}

CIMDCanalVirtual::CIMDCanalVirtual(QAudioFormat IMD_Formato     ,
                                   qint64       IMD_Duracao     ,
                                   int          IMD_FrequenciaHz)
{
   open(QIODevice::ReadWrite);

   write(GeraBuffer(IMD_Formato,IMD_Duracao,IMD_FrequenciaHz));

   IMD_Decoder = new QAudioDecoder(this);

   IMD_Decoder->start();
   while(IMD_Decoder->bufferAvailable())
   {
      IMD_AudioBuffer = IMD_Decoder->read();
      qWarning() << "Buffer size: " << IMD_AudioBuffer.byteCount();
   }
}

CIMDCanalVirtual::CIMDCanalVirtual(QByteArray pIMD_Data)
{
   open(QIODevice::ReadWrite);

   write(pIMD_Data);

   IMD_Decoder = new QAudioDecoder(this);

   IMD_Decoder->start();
   while(IMD_Decoder->bufferAvailable())
   {
      IMD_AudioBuffer = IMD_Decoder->read();
      qWarning() << "Buffer size: " << IMD_AudioBuffer.byteCount();
   }
}

CIMDCanalVirtual::CIMDCanalVirtual(QString pIMD_File)
{
   open(QIODevice::ReadWrite);
   IMD_Decoder = new QAudioDecoder(this);
   IMD_Decoder->setSourceFilename(pIMD_File);
   IMD_Decoder->start();
   while(IMD_Decoder->bufferAvailable())
   {
      IMD_AudioBuffer = IMD_Decoder->read();
      qWarning() << "Buffer size: " << IMD_AudioBuffer.byteCount();
   }
}

QByteArray CIMDCanalVirtual::GeraBuffer(QAudioFormat IMD_Formato,
                                        qint64       IMD_Duracao,
                                        int          IMD_FrequenciaHz)
{
    QByteArray m_buffer;

    const int channelBytes = IMD_Formato.sampleSize() / 8;
    const int sampleBytes  = IMD_Formato.channelCount() * channelBytes;

    qint64 length = (IMD_Formato.sampleRate  ()       *
                     IMD_Formato.channelCount()       *
                     channelBytes                   ) *
                     IMD_Duracao / 100000;

    Q_ASSERT(length % sampleBytes == 0);
    Q_UNUSED(sampleBytes) // suppress warning in release builds

    m_buffer.resize(length);
    unsigned char *ptr = reinterpret_cast<unsigned char *>(m_buffer.data());
    int sampleIndex = 0;

    while (length)
    {
        const qreal x = qSin(2 * M_PI * IMD_FrequenciaHz * qreal(sampleIndex % IMD_Formato.sampleRate()) / IMD_Formato.sampleRate());

        for (int i=0; i<IMD_Formato.channelCount(); ++i)
        {
            if (IMD_Formato.sampleSize() == 8 && IMD_Formato.sampleType() == QAudioFormat::UnSignedInt)
            {
                const quint8 value = static_cast<quint8>((1.0 + x) / 2 * 255);
                *reinterpret_cast<quint8*>(ptr) = value;
            }
            else if (IMD_Formato.sampleSize() == 8 && IMD_Formato.sampleType() == QAudioFormat::SignedInt)
            {
                const qint8 value = static_cast<qint8>(x * 127);
                *reinterpret_cast<quint8*>(ptr) = value;
            }
            else if (IMD_Formato.sampleSize() == 16 && IMD_Formato.sampleType() == QAudioFormat::UnSignedInt)
            {
                quint16 value = static_cast<quint16>((1.0 + x) / 2 * 65535);
                if (IMD_Formato.byteOrder() == QAudioFormat::LittleEndian)
                    qToLittleEndian<quint16>(value, ptr);
                else
                    qToBigEndian<quint16>(value, ptr);
            }
            else if (IMD_Formato.sampleSize() == 16 && IMD_Formato.sampleType() == QAudioFormat::SignedInt)
            {
                qint16 value = static_cast<qint16>(x * 32767);
                if (IMD_Formato.byteOrder() == QAudioFormat::LittleEndian)
                    qToLittleEndian<qint16>(value, ptr);
                else
                    qToBigEndian<qint16>(value, ptr);
            }

            ptr    += channelBytes;
            length -= channelBytes;
        }

        ++sampleIndex;
    }

    return m_buffer;
}
