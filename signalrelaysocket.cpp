#include "signalrelaysocket.h"
#include <QHostAddress>
#include <QDebug>

SignalRelaySocket::SignalRelaySocket(QObject *parent) : QObject(parent)
{
    psocket = new QTcpSocket(parent);
}

void SignalRelaySocket::connectdevide(QString addr,unsigned int port)
{
    QString s;
    psocket->close();
    delete psocket;
    psocket = new QTcpSocket(this);
    connect(psocket,SIGNAL(connected()),this,SLOT(connected()));
    connect(psocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(psocket,SIGNAL(readyRead()),this,SLOT(readyRead()));

    psocket->connectToHost(QHostAddress(addr),port);
    //qDebug()<<"addr:"<<addr<<" port:"<<port;
    emit deviceStatusMsg("addr = " + addr + " port:" + s.sprintf("%d",port));
}

void SignalRelaySocket::close()
{
    psocket->close();
}

void  SignalRelaySocket::connected()
{
    emit deviceStatusMsg("connected");
}

void  SignalRelaySocket::disconnected()
{
    emit deviceStatusMsg("disconnected");
}

void  SignalRelaySocket::readyRead()
{
}

void SignalRelaySocket::revert_relay(unsigned int index)
{
    QString ss;
    if(index >= 32) {
        return ;
    }
    ss.sprintf("SCMD DIGW %d %d 2",512+index,1);
    emit deviceStatusMsg(ss);
    psocket->write(ss.toLocal8Bit());
}
