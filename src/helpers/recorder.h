#ifndef RECORDER_H
#define RECORDER_H

#include "../qtmel_global.h"

#include <QObject>
#include <QImage>

class AbstractImageGrabber;
class ScreenGrabber;
class CameraGrabber;
class AudioGrabber;
class Encoder;

class QTMELSHARED_EXPORT Recorder : public QObject
{
    Q_OBJECT
public:
    /*! This enum describes the state of the recorder. */
    enum State {
        ActiveState = 0,
        SuspendedState,
        StoppedState
    };

    explicit Recorder(QObject *parent = 0);
    
    void setImageGrabber(AbstractImageGrabber *grabber);
    AbstractImageGrabber* imageGrabber() const;

    void setAudioGrabber(AudioGrabber *grabber);
    AudioGrabber* audioGrabber() const;

    Encoder* encoder() const;

public Q_SLOTS:
    void start();
    void pause();
    void resume();
    void stop();

Q_SIGNALS:
    void error(const QString &errorString);

private Q_SLOTS:
    void startGrabbers();

private:
    void setError(const QString &errorString);
    void onGrabbersError();
    AbstractImageGrabber* castImageGrabber() const;

    ScreenGrabber *m_screenGrabber;
    CameraGrabber *m_cameraGrabber;
    AudioGrabber *m_audioGrabber;
    Encoder *m_encoder;
};

#endif // RECORDER_H
