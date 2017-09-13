#ifndef SIGNALRELAYSOCKET_H
#define SIGNALRELAYSOCKET_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class SignalRelaySocket : public QObject
{
    Q_OBJECT

public:
    explicit SignalRelaySocket(QObject *parent = 0);
    Q_INVOKABLE void connectdevide(QString addr,unsigned int port);
    Q_INVOKABLE void close();
    Q_INVOKABLE void revert_relay(unsigned int index);
public:
    QString message(void);
    void setmessage(const QString msg);
signals:
    void deviceStatusMsg(const QString msg);

public slots:

    void  connected();
    void  disconnected();
    void  readyRead();



private:
    QTcpSocket  * psocket;
};

#endif // SIGNALRELAYSOCKET_H
