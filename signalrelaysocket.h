#ifndef SIGNALRELAYSOCKET_H
#define SIGNALRELAYSOCKET_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QByteArray>
#include <QDateTime>
#include <QVector>
#include "tcp2000_command.h"
#include "jthread.h"

typedef struct _relay_info_st
{
    QStringList     addrs;
    QStringList     ports;
} relay_info_st;

enum tcp_state_st {
    tcp_powerup,
    tcp_wait_connected,
    tcp_wait_init_ack,
    tcp_wait_normal_ack,

    tcp_connecting,

    tcp_connected,
    tcp_disconnected,
    tcp_wait_rx_ack,
    tcp_wait_rx_continue,
};

#define REG_TYPE_BITS_READ   0
#define REG_TYPE_BITS_WRITE  1
#define REG_TYPE_WORD_READ   2
#define REG_TYPE_WORD_WRITE  3
#define REG_TYPE_BLOCK_READ   4
#define REG_TYPE_BLOCK_WRITE  5
#define REG_TYPE_IONAME_READ  6

typedef struct _RegisterNode {
    unsigned char type;
    uint16_t addr;
    uint16_t regcount;
    uint16_t data_byte_count;
} RegisterNode;

//36*36,72*72,96*96


class SignalRelaySocket : public QObject
{
    Q_OBJECT

public:
    explicit SignalRelaySocket(QObject *parent = 0);
    Q_INVOKABLE void connectdevide(QString addr,unsigned int port);
    Q_INVOKABLE void close();
    Q_INVOKABLE void revert_relay(unsigned int index);
    Q_INVOKABLE void set_relay(unsigned int index,bool on);

    Q_INVOKABLE void load_data(void);
    Q_INVOKABLE void save_data(void);
    Q_INVOKABLE void add_addrs(QString addr,unsigned int port);
    Q_INVOKABLE void del_note(int index);
    Q_INVOKABLE int  getcount(void);
    Q_INVOKABLE QString getaddr(int index);
    Q_INVOKABLE QString getport(int index);
    Q_INVOKABLE QString statusmsg;
    Q_INVOKABLE int  get_last_host_index(void);
    Q_INVOKABLE void set_last_host_index(int index);

public:
    QString message(void);
    void setmessage(const QString msg);
signals:
    void deviceStatusMsg(const QString msg);
    void uiStatus(const QString msg);
    void uidebug(const QString msg);
    void relaychange(int index,bool on);
    void connectedsig(const QString addr);
    void ioOutName(const QString name,unsigned int index);
    void devName(const QString name);
    void devGroup1Name(const QString name);
private:
    void set_tcp_state(tcp_state_st state);
    bool get_tcp_timeout(int timeout);
    void reconnect_to_host(void);
    void read_dig_val(unsigned int addr,unsigned int count);
    QString buffertostring(QByteArray str);
    void tcp_read_name(unsigned int index);
    void tcp_read_rtc(void);
    void tcp_read_word_register(unsigned int addr,unsigned int count);
    void tcp_register_read_back(unsigned int addr,uint16_t reg);
    void tcp_register_read_commit(QVector<uint16_t> & regarry,unsigned int addr,unsigned int count);
    void tcp_read_io_name(unsigned int addr);
    void tcp_read_io_name_commit(unsigned int addr);

    QString dumpdata(QByteArray & data);

    uint16_t get_sys_tick16(void);

    void rtc_backrun_thread(void);


public slots:
    void  connected();
    void  disconnected();
    void  readyRead();
    void  tcptimeout(void);



private:
    QString       last_host_addr;
    unsigned int  last_port;
    QTcpSocket  * psocket;
    relay_info_st info;
    unsigned int  last_host_index;

    QTimer       tcptim;
    tcp_state_st tcpstate;
    QByteArray   tcpreadrx;
    int          tcp_timeout_count;
    bool         is_inited;

    unsigned int time_curr_tick;
    unsigned int time_tick_sec;

    jt_ctl       jtcp;
    QByteArray   tcp_rtc_data;
    jt_ctl       jrtc;
    bool         user_command_trig;
    bool         is_connect_ok;
    uint16_t     rtc_display_tick;

    QVector<RegisterNode> init_reg_list;
};

#endif // SIGNALRELAYSOCKET_H
