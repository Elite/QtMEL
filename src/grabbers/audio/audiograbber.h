#ifndef AUDIOGRABBER_H
#define AUDIOGRABBER_H

#include "../abstractgrabber.h"

#include <QAudioDeviceInfo>
#include <QAudioFormat>
#include <QPointer>

class QAudioInput;

class AudioGrabber : public AbstractGrabber
{
    Q_OBJECT

public:
    explicit AudioGrabber(QObject *parent = 0);
    ~AudioGrabber();

    void setDevice(const QAudioDeviceInfo &device);
    QAudioDeviceInfo device() const;

    void setFormat(const QAudioFormat &format);
    QAudioFormat format() const;

    int grabbedAudioDataSize() const;

public slots:
    bool start();
    void stop();
    void suspend();
    void resume();

signals:
    void frameAvailable(const QByteArray &frame);

private slots:
    void onReadyRead();

private:
    void init();
    void cleanup();

    QPointer<QAudioInput> m_inputDevice;
    QAudioDeviceInfo m_deviceInfo;
    QAudioFormat m_format;
    QIODevice *m_buffer;
    int m_grabbedAudioDataSize;
}

#endif // AUDIOGRABBER_H
