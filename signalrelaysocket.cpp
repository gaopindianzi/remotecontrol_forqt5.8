#include "signalrelaysocket.h"
#include <QHostAddress>
#include <QDebug>
#include <QSettings>
#include <QDateTime>
#include <QTextCodec>



SignalRelaySocket::SignalRelaySocket(QObject *parent) : QObject(parent)
{
    uint16_t i;

    psocket = new QTcpSocket(parent);

    connect(&tcptim,SIGNAL(timeout()),this,SLOT(tcptimeout()));
    tcpstate = tcp_powerup;



    RegisterNode node;

    node.type = REG_TYPE_WORD_READ;
    node.addr = DIG_INPUT_NUM_BASE;
    node.regcount = 2;
    init_reg_list.push_back(node);

#if 0
    node.type = REG_TYPE_WORD_READ;
    node.addr = OUTPUT_BASE;
    node.regcount = OUTPUT_COUNT;
    init_reg_list.push_back(node);
#endif
#if 1
    node.type = REG_TYPE_WORD_READ;
    node.addr = DEV_NAME_BASE;
    node.regcount = DEV_NAME_COUNT;
    init_reg_list.push_back(node);

    node.type = REG_TYPE_WORD_READ;
    node.addr = DEV_GROUP1_BASE;
    node.regcount = DEV_GROUP1_COUNT;
    init_reg_list.push_back(node);
#endif
#if 1
    for(i=0;i<32;i++)
    {
        node.type = REG_TYPE_IONAME_READ;
        node.addr = i;
        node.regcount = 0;
        init_reg_list.push_back(node);
    }

#endif
    tcptim.start(10);
    time_tick_sec = time_curr_tick;
}

void SignalRelaySocket::connectdevide(QString addr,unsigned int port)
{
    QString s;

    is_connect_ok = false;
    //tcptimeout();


    psocket->close();
    delete psocket;
    psocket = new QTcpSocket(this);
    connect(psocket,SIGNAL(connected()),this,SLOT(connected()));
    connect(psocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(psocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    //psocket->connectToHost(QHostAddress(addr),port);
    last_host_addr = addr;
    last_port = port;
    qDebug()<<"change host addr:"<<addr<<" port:"<<port;

    tcpstate = tcp_wait_connected;
    //reconnect_to_host();



    //time_tick_sec = time_curr_tick;

    emit uiStatus("选择新设备连接...");
}

void SignalRelaySocket::reconnect_to_host(void)
{
    QString s;
    psocket->close();
    delete psocket;
    psocket = new QTcpSocket(this);
    connect(psocket,SIGNAL(connected()),this,SLOT(connected()));
    connect(psocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(psocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    psocket->connectToHost(QHostAddress(last_host_addr),last_port);
    qDebug()<<"addr:"<<last_host_addr<<" port:"<<last_port;
    is_connect_ok = false;
    emit uiStatus("连接设备...");
}

void SignalRelaySocket::close()
{
    qDebug()<<"socket close";
    emit uiStatus("设备关闭");
    psocket->close();
}

uint16_t SignalRelaySocket::get_sys_tick16(void)
{
    return (uint16_t)(QDateTime::currentMSecsSinceEpoch() & 0xFFFF);
}

void  SignalRelaySocket::connected()
{
    qDebug() << "tcp connected";
    emit connectedsig(last_host_addr);
    emit uiStatus("已经连接");
    if(is_inited) {
        tcpstate = tcp_wait_normal_ack;
    } else {
        tcpstate = tcp_wait_init_ack;
    }
    is_connect_ok = true;
}

void  SignalRelaySocket::disconnected()
{
    tcpstate = tcp_powerup;
    is_inited = false;
    is_connect_ok = false;
    emit uiStatus("连接已断开");
}

QString SignalRelaySocket::buffertostring(QByteArray str)
{
    QString s,ss;
    int i;
    const char * buf = str.data();
    if(str.count() == 0) {
        return "";
    }
    ss.sprintf("%02X",(unsigned int)buf[0]);
    s += ss;
    for(i=1;i<str.count();i++) {
        s += ":";
        s += ss.sprintf("%02X",(unsigned int)buf[i]);
    }
    return s;
}



void SignalRelaySocket::set_tcp_state(tcp_state_st state)
{
    tcp_timeout_count = 0;
    if(tcpstate != state) {
        tcpstate = state;

    } else {

    }
}

bool SignalRelaySocket::get_tcp_timeout(int timeout)
{
    tcp_timeout_count++;
    if(tcp_timeout_count >= (timeout/100)) {
        return true;
    } else {
        return false;
    }
}


QString SignalRelaySocket::dumpdata(QByteArray & data)
{
    QString s,ss;
    int i;
    for(i=0;i<data.size();i++) {
        s.sprintf("%02X",(unsigned char)data.at(i));
        ss += s;
        if(i < data.size()) {
            ss += ' ';
        }
    }
    return ss;
}

void  SignalRelaySocket::readyRead()
{
    tcpreadrx += psocket->readAll();

#if 0
    time_tick_sec = time_curr_tick;

    QString s;

    if(tcpreadrx.count() >= 5) {
        s = tcpreadrx.toStdString().c_str();
        if(s.startsWith("SCMD DIGR")) {
            const char * pbinval = s.toStdString().c_str();
            int i = 0;
            int count = 0;
            qDebug()<<"is scmd digr:"<<s;
            //SCMD DIGR 512 32 00000111010100000000000000000000
            //SCMD DIGR 11100010000000000000000000000000
            pbinval += 17;
            while(1) {
                qDebug()<<"QT:emit relay:"<<i<<"->"<<(char)tcpreadrx.at(10+i);
                emit relaychange(i,(tcpreadrx.at(10+i)=='1')?true:false);
                ++count;
                if(count >= 64) {
                    qDebug()<<" 64 out";
                    break;
                }
                ++i;
                if(tcpreadrx.at(10+i) == '\r' || tcpreadrx.at(10+i) == '\n') {
                    qDebug()<<" rn0 out:" << (int)pbinval[i];
                    break;
                }
            }
        } else if(s.startsWith("SCMD DIGW")) {
            QString index = s.mid(10,3);
            QString val = s.mid(16,1);
            qDebug()<<"index:"<<index<<" val:"<<val;
            emit uiStatus("返回成功");
            emit relaychange(atoi(index.toStdString().c_str())-512,(val=="1")?true:false);
        }
        const char * pbuf = tcpreadrx.data();
        if(pbuf[0] == 0x08) {
            if(tcpreadrx.count() >= 13) {
                unsigned int year = pbuf[7] + 1900;
                unsigned int mon = pbuf[8] + 1;
                unsigned int day = pbuf[9];
                unsigned int hour = pbuf[10];
                unsigned int min = pbuf[11];
                unsigned int sec = pbuf[12];
                s.sprintf("%d-%d-%d %d:%d:%d",year,mon,day,hour,min,sec);
                emit uiStatus(s);
            }
        } else if(pbuf[0] == 0x01) {
            //继电器自动上报
            int i;
            for(i=0;i<32;i++) {
                emit relaychange(i,(pbuf[i/8]&(1<<(i%8)))?true:false);
            }
        } else {
            qDebug()<<"CMD:"<< (int)pbuf[0];
        }
        tcpreadrx.clear();
    }

#endif
}

void SignalRelaySocket::rtc_backrun_thread(void)
{
    static int rtclen = 0;
    static unsigned int tick = 0;

    jt_ctl & jt = jrtc;

    JT_BEGIN(jt);

    user_command_trig = true;

    JT_DELAY_MS_OR_UNTIL(jt,user_command_trig==false,5000);

    while(1)
    {
        JT_DELAY_MS_OR_UNTIL(jt,(tcp_rtc_data.size() != rtclen),1100);
        rtclen = tcp_rtc_data.size();
        if(is_connect_ok == false) {
            continue;
        }
        if(JT_GET_RESULT(jt) == PT_TIMEOUT) {
            qDebug()<<"no rtc report,master read it out.";
            tcp_read_rtc();
            continue;
        }
        if(user_command_trig == false && rtclen >= 13) {
            QString s;
            unsigned char * pbuffer = (unsigned char *)tcp_rtc_data.data();
            unsigned int year = pbuffer[7] + 1900;
            unsigned int mon = pbuffer[8] + 1;
            unsigned int day = pbuffer[9];
            unsigned int hour = pbuffer[10];
            unsigned int min = pbuffer[11];
            unsigned int sec = pbuffer[12];
            s.sprintf("%d-%d-%d %d:%02d:%02d",year,mon,day,hour,min,sec);
            emit uiStatus(s);
        }
        if(user_command_trig == true) {
            JT_DELAY_MS(jt,3000);
            user_command_trig = false;
        }
        tcp_rtc_data.clear();
        rtclen = 0;
        //qDebug()<<"rtc tick:"<<tick++;
    }


    JT_END(jt);
}

void SignalRelaySocket::tcptimeout(void)
{
    static int  i = 0;
    static int  tcplen = 0;
    jt_ctl & jt = jtcp;
    QString s;
    RegisterNode node;

    rtc_backrun_thread();


    JT_BEGIN(jt);

    JT_DELAY_MS(jt,1000);

re_connect_to_host:
    qDebug()<<"TCP connect to host...";
    is_connect_ok = false;
    tcpreadrx.clear();
    tcplen = 0;
    reconnect_to_host();
wait_connect_ok:
    JT_DELAY_MS_OR_UNTIL(jt,is_connect_ok,8000);

    if(!is_connect_ok) {
        goto re_connect_to_host;
    }

    qDebug()<<"开始读取端口名字";
    i = 0;

    while(1) {
read_again:
        if(i >= init_reg_list.count()) {
            qDebug()<<"读取寄存器完毕:"<<i;
            break;
        }
        node = init_reg_list[i];
        if(node.type == REG_TYPE_WORD_READ) {
            qDebug()<<"读取word reg:"<<node.addr;
            tcp_read_word_register(node.addr,node.regcount);
        } else if(node.type == REG_TYPE_IONAME_READ) {
            tcp_read_io_name(node.addr);
        } else {
            i++;
            goto next_node;
        }
wait_next_init_ack:
        JT_WAIT_UNTIL(jt,((tcpreadrx.size()!= tcplen) || is_connect_ok == false));

        if(is_connect_ok == false) {
            qDebug()<<"ERROR: disconnected A ,and Wait connect ok...";
            goto re_connect_to_host;
        }

        tcplen = tcpreadrx.size();
        //qDebug()<<"thread tickA:"<<get_sys_tick16();

        s = tcpreadrx.toStdString().c_str();
        if(s.startsWith("SCMD DIG")) {
            qDebug()<<"tcp get SCMD command.";
            tcpreadrx.clear();
            tcplen = 0;
            goto wait_next_init_ack;
        } else {
            unsigned char * pbuffer = (unsigned char *)tcpreadrx.data();
            if(pbuffer[0] == 80) {
                QVector<uint16_t> regarray;
                unsigned int addr,count,j;
                addr = pbuffer[7];
                addr <<= 8;
                addr |= pbuffer[8];
                count = pbuffer[9];
                count <<= 8;
                count |= pbuffer[10];
                if((unsigned int)(tcplen - (7+4)) <= (count*2)) {
                    qDebug()<<"ERROR:init read word failed!try again:"<<tcplen;
                    goto read_again;
                }
                regarray.clear();
                for(j=0;j<count;j++) {
                    uint16_t word_reg = pbuffer[11 + j*2];
                    word_reg <<= 8;
                    word_reg |= pbuffer[11 + j*2 + 1];
                    //tcp_register_read_back(addr + j,word_reg);
                    regarray.push_back(word_reg);
                }
                qDebug()<<"Read Reg OK:"<<addr<<","<<count;
                tcp_register_read_commit(regarray,addr,count);
                i++;
                tcpreadrx.clear();
                tcplen = 0;
            } else if(pbuffer[0] == 4) {
                if(tcplen >= (7+22)) {
                    unsigned char ioindex = pbuffer[7];
                    unsigned char iotype = pbuffer[8];
                    pbuffer[9+19] = '\0';
                    if(pbuffer[9] != 0xFF) {
                        s = QTextCodec::codecForName("GB2312")->toUnicode((const char *)&pbuffer[9]);
                    } else {
                        s = "";
                    }
                    if(iotype == 0) {
                        if(ioindex < 32) {
                            //qDebug()<<"read io ok:"<<s;
                            emit ioOutName(s,ioindex);
                        }
                        if(ioindex == 31) {
                            qDebug()<<"read io name finished.";
                        }
                    }
                }
                i++;
                tcpreadrx.clear();
                tcplen = 0;
                goto read_again;
            } else if(pbuffer[0] == 0x08) {
                if(tcplen > 13) {
                    qDebug()<<"08 rtc too larger.";
                }

                tcp_rtc_data = tcpreadrx;
                tcpreadrx.clear();
                tcplen = 0;
                qDebug()<<"rtc tick,wait init ack again.";
                goto read_again;
            } else {
                tcpreadrx.clear();
                tcplen = 0;
                qDebug()<<"unkown command:"<<pbuffer[0];
                goto read_again;
            }
        }
next_node:
        if(i >= init_reg_list.count()) {
            qDebug()<<"读取寄存器完毕:"<<i;
            break;
        }
    }


    read_dig_val(512,32);

    qDebug()<<"OK,Wait Rx data...";


    user_command_trig = false;

    while(1)
    {
        JT_WAIT_UNTIL(jt,((tcpreadrx.size()!= tcplen) || is_connect_ok == false));
        if(is_connect_ok == false) {
            qDebug()<<"ERROR: disconnected B,and Wait connect ok...";
            goto re_connect_to_host;
        }

        tcplen = tcpreadrx.size();
        //qDebug()<<"thread tick:"<<get_sys_tick16();

        s = tcpreadrx.toStdString().c_str();
        if(s.startsWith("SCMD DIG")) {
            QString addr;
            QString ss;
            int addrval;
            //qDebug()<<"tcp get SCMD command："<<ss;
            addr = s.mid(10,3);
            ss = s.mid(16,tcplen - 16);
            //qDebug()<<"Ack SCMD Val："<<ss;
            int count = tcplen - 16;
            int i;
            addrval = atoi(addr.toStdString().c_str());
            addrval -= 512;
            for(i=0;i<count;i++) {
                if(s[i] == '1') {
                    emit relaychange(addrval + i,true);
                } else {
                    emit relaychange(addrval + i,false);
                }
            }
            s.sprintf("%d",addrval);
            emit uiStatus("触发:"+s+"成功");
            tcpreadrx.clear();
            tcplen = 0;
            rtc_display_tick = get_sys_tick16();
        } else {
            unsigned char * pbuffer = (unsigned char *)(tcpreadrx.data());
            unsigned int cmd_index = pbuffer[2];
            cmd_index <<= 8;
            cmd_index |= pbuffer[1];


            if(!(pbuffer[3]&0x01)) {
                s.sprintf("%02d",pbuffer[0]);
                s = "指令执行错误:" + s;
                emit uiStatus(s);
                tcpreadrx.clear();
                tcplen = 0;
                continue;
            }

            if(pbuffer[0] == 0x08) {
                tcp_rtc_data += tcpreadrx;
                tcpreadrx.clear();
                tcplen = 0;
            } else if(pbuffer[0] == 0x01) {
                qDebug()<<"CMD Ack:" << dumpdata(tcpreadrx);
                if(tcplen >= 12) {
                    unsigned int i;
                    for(i=0;i<32;i++) {
                        emit relaychange(i,(pbuffer[8+i/8]&(1<<(i%8)))?true:false);
                    }
                    tcpreadrx.remove(0,12);
                }
                //emit uiStatus("更新状态");
                tcplen = 0;
            } else if(pbuffer[0] == CMD_REV_IO_SOME_BIT) {
                qDebug()<<"CMD Ack:" << dumpdata(tcpreadrx);
                if(tcplen >= 11) {
                    unsigned int i;
                    for(i=0;i<32;i++) {
                        emit relaychange(i,(pbuffer[7+i/8]&(1<<(i%8)))?true:false);
                    }
                    tcpreadrx.remove(0,11);
                }
                emit uiStatus("触发成功");
                tcplen = 0;
            } else if(pbuffer[0] == 0x27) {
                qDebug()<<"CMD Ack:" << dumpdata(tcpreadrx);
                //27 00 00 01 02 00 00 20 24 00 00 80
                if(tcplen >= 12) {
                    unsigned int i;
                    for(i=0;i<32;i++) {
                        emit relaychange(i,(pbuffer[8+i/8]&(1<<(i%8)))?true:false);
                    }
                    tcpreadrx.remove(0,12);
                }
                emit uiStatus("触发成功");
                tcplen = 0;
            }
            if(tcplen >= 7) {
                qDebug()<<"CMD Ack Unkown cmd:" << dumpdata(tcpreadrx);
                tcpreadrx.clear();
                tcplen = 0;
            }
        }
    }


    JT_END(jt);




#if 0
    unsigned int esc;
    time_curr_tick++;

    switch(tcpstate) {
    case tcp_powerup:
    {
        //判断网络是否可用
        is_inited = false;
        //网络可用
        tcpstate = tcp_wait_connected;
        reconnect_to_host();
        time_tick_sec = time_curr_tick;
    }
    break;
    case tcp_wait_connected:
    {
        esc = time_curr_tick - time_tick_sec;
        if(esc >= 10) {
            //连接超时
        }
    }
    break;
    case tcp_wait_init_ack:
    {
        tcpstate = tcp_wait_normal_ack;
        time_tick_sec = time_curr_tick;
    }
        break;
    case tcp_wait_normal_ack:
    {
    }
        break;


    default:break;
    }
#endif
}

void SignalRelaySocket::revert_relay(unsigned int index)
{
#if 0
    QString ss;
    if(index >= 256) {
        return ;
    }
    ss.sprintf("SCMD DIGW %d %d 2",512+index,1);
    QString s;
    s.sprintf("%d",index);
    emit uiStatus("触发："+ s + "路");
    user_command_trig = true;
    psocket->write(ss.toLocal8Bit());
#endif

    QString ss;
    QByteArray buffer;
    buffer.resize(7+4);
    unsigned char * pbuf = (unsigned char *)buffer.data();
    pbuf[0] = CMD_REV_IO_SOME_BIT;
    pbuf[1] = 0x00;
    pbuf[2] = 0x00;
    pbuf[3] = 0x00;
    pbuf[4] = 4;
    pbuf[5] = 0x00;
    pbuf[6] = 0x00;

    uint32_t val = (1UL<<index);

    pbuf[7] = (unsigned char)(val>>0);
    pbuf[8] = (unsigned char)(val>>8);
    pbuf[9] = (unsigned char)(val>>16);
    pbuf[10] = (unsigned char)(val>>24);

    ss.sprintf("%d路",index);
    ss = "触发第"+ ss;
    emit uiStatus(ss);
    user_command_trig = true;
    psocket->write(buffer);
}

void SignalRelaySocket::set_relay(unsigned int index,bool on)
{
    QString ss;
    if(index >= 256) {
        return ;
    }
#if 0
    QByteArray buffer;
    buffer.resize(9);
    unsigned char * pbuf = (unsigned char *)buffer.data();

    pbuf[0] = 0x27;
    pbuf[1] = 0x00;
    pbuf[2] = 0x00;
    pbuf[3] = 0x00;
    pbuf[4] = 0x02;
    pbuf[5] = 0x00;
    pbuf[6] = 0x00;

    pbuf[7] = (unsigned char)(index & 0xFF);
    pbuf[8] = (unsigned char)(index >> 8);

    ss.sprintf("%d",index);
    emit uiStatus("触发:"+ ss + "路");

    user_command_trig = true;

    psocket->write(buffer);
#endif

#if 1
    QString s;
    s.sprintf("%d",index);
    if(on) {
        ss.sprintf("SCMD DIGW %d %d 1",512+index,1);
        qDebug()<<ss;
        emit uiStatus("开："+ s + "路");
    } else {
        ss.sprintf("SCMD DIGW %d %d 0",512+index,1);
        qDebug()<<ss;
        emit uiStatus("关："+ s + "路");
    }
    user_command_trig = true;

    psocket->write(ss.toLocal8Bit());
#endif

}

void SignalRelaySocket::read_dig_val(unsigned int addr,unsigned int count)
{
    QByteArray buffer;
    buffer.resize(7);
    unsigned char * pbuf = (unsigned char *)buffer.data();
    pbuf[0] = 0x01;
    pbuf[1] = 0x00;
    pbuf[2] = 0x00;
    pbuf[3] = 0x00;
    pbuf[4] = 0x00;
    pbuf[5] = 0x00;
    pbuf[6] = 0x00;

    psocket->write(buffer);
}

void SignalRelaySocket::add_addrs(QString addr,unsigned int port)
{
    QString s;
    info.addrs.push_back(addr);
    info.ports.push_back(s.sprintf("%d",port));
}

void SignalRelaySocket::load_data()
{
    QSettings set("relaycontroler","HWTEC");
    QString s;
    last_host_addr = set.value("last_host_addr").toString();
    last_port = set.value("last_port").toInt();
    last_host_index = set.value("last_host_index").toInt();
    info.addrs = set.value("setip").toStringList();
    info.ports = set.value("setport").toStringList();
    unsigned int i,count;
    count = info.addrs.count();
    for(i=0;i<count;i++) {
        emit deviceStatusMsg(s.sprintf("%d",i)+" "+info.addrs.at(i)+":"+info.ports.at(i));
    }
    emit uiStatus("读取设备列表完成");
}

void SignalRelaySocket::save_data()
{
    QSettings set("relaycontroler","HWTEC");
    set.setValue("last_host_addr",last_host_addr);
    set.setValue("last_port",last_port);
    set.setValue("last_host_index",last_host_index);
    set.setValue("setip",info.addrs);
    set.setValue("setport",info.ports);
    emit uiStatus("存储设备列表完成");
}

int SignalRelaySocket::get_last_host_index(void)
{
    return last_host_index;
}

void SignalRelaySocket::set_last_host_index(int index)
{
    last_host_index = index;
    save_data();
}

void SignalRelaySocket::del_note(int index)
{
    if(index < info.addrs.count()) {
        info.addrs.removeAt(index);
        info.ports.removeAt(index);
    }
}

int SignalRelaySocket::getcount(void)
{
    return info.addrs.count();
}

QString SignalRelaySocket::getaddr(int index)
{
    return info.addrs.at(index);
}

QString SignalRelaySocket::getport(int index)
{
    return info.ports.at(index);
}

void SignalRelaySocket::tcp_read_rtc(void)
{
    QByteArray buffer;
    buffer.resize(7);
    unsigned char * pbuf = (unsigned char *)buffer.data();
    pbuf[0] = 0x08;
    pbuf[1] = 0x00;
    pbuf[2] = 0x00;
    pbuf[3] = 0x00;
    pbuf[4] = 0x00;
    pbuf[5] = 0x00;
    pbuf[6] = 0x00;

    psocket->write(buffer);
}

void SignalRelaySocket::tcp_read_word_register(unsigned int addr,unsigned int count)
{
    QString ss;
    QByteArray buffer;
    buffer.resize(7+4);
    unsigned char * pbuf = (unsigned char *)buffer.data();
    pbuf[0] = 80;
    pbuf[1] = 0x00;
    pbuf[2] = 0x00;
    pbuf[3] = 0x00;
    pbuf[4] = 4;
    pbuf[5] = 0x00;
    pbuf[6] = 0x00;

    pbuf[7] = (unsigned char)(addr>>8);
    pbuf[8] = (unsigned char)(addr&0xFF);
    pbuf[9] = (unsigned char)(count>>8);
    pbuf[10] = (unsigned char)(count&0xFF);

    ss.sprintf("%d,%d",addr,count);
    ss = "读寄存器:"+ ss;
    qDebug()<<ss;
    emit uiStatus(ss);

    user_command_trig = true;

    psocket->write(buffer);
}

void SignalRelaySocket::tcp_register_read_back(unsigned int addr,uint16_t reg)
{

}

void SignalRelaySocket::tcp_register_read_commit(QVector<uint16_t> & regarry,unsigned int addr,unsigned int count)
{
    QByteArray buffer;
    unsigned char * pbuffer;
    int i;
    QString s;
    for(i=0;i<regarry.count();i++) {
        uint16_t reg = regarry[i];
        buffer.push_back((unsigned char)(reg >> 8));
        buffer.push_back((unsigned char)(reg & 0xFF));
    }
    buffer.push_back('\0');
    pbuffer = (unsigned char *)buffer.data();
    //pbuffer = (unsigned char *)buffer.data();

    qDebug()<<"NAM:"<<dumpdata(buffer);

    if((unsigned char)buffer[0] != 0xFF) {
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QTextDecoder *decoder = codec->makeDecoder();
        s = codec->toUnicode((const char *)pbuffer);
        //s = (const char *)pbuffer;
        qDebug()<<" deve name:"<<s;
    } else if(pbuffer[0] == '0') {
        s = "";
    } else {
        s = "-";
    }
    if(addr >= DEV_NAME_BASE && count == DEV_NAME_COUNT) {
        //设备名字
        //qDebug()<<"read dev name:"<<s;
        emit devName(s);
    } else if(addr >= DEV_GROUP1_BASE && count == DEV_GROUP1_COUNT) {
        //设备名字
        //qDebug()<<"read dev name:"<<s;
        emit devGroup1Name(s);
    }
}

void SignalRelaySocket::tcp_read_io_name(unsigned int addr)
{
    QString ss;
    QByteArray buffer;
    buffer.resize(7+2);
    unsigned char * pbuf = (unsigned char *)buffer.data();
    pbuf[0] = 4;
    pbuf[1] = 0x00;
    pbuf[2] = 0x00;
    pbuf[3] = 0x00;
    pbuf[4] = 2;
    pbuf[5] = 0x00;
    pbuf[6] = 0x00;

    pbuf[7] = (unsigned char)(addr&0xFF);
    pbuf[8] = (unsigned char)(addr>>8);

    ss.sprintf("%d",(unsigned char)(pbuf[7] & 0xFF));
    ss = "读端口名:"+ ss;
    //qDebug()<<ss;
    emit uiStatus(ss);

    user_command_trig = true;

    psocket->write(buffer);
}

void SignalRelaySocket::tcp_read_io_name_commit(unsigned int addr)
{

}
