#ifndef TCP2000_COMMAND_H
#define TCP2000_COMMAND_H


#define  CMD_REQ_START             0
#define  CMD_REQ_NEXT              1
#define  CMD_REQ_DONE              2

#define  CMD_CURRENT_START        0
#define  CMD_CURRENT_DOING        1
#define  CMD_CURRENT_DONE         2







#define   CMD_GET_IO_OUT_VALUE           1
#define   CMD_GET_IO_IN_VALUE            2
#define   CMD_SET_IO_OUT_VALUE           3
#define   CMD_GET_IO_NAME                4
#define   CMD_SET_IO_NAME                5
#define   CMD_GET_TIMING_INFO            6
#define   CMD_SET_TIMING_INFO            7
#define   CMD_GET_RTC_VALUE              8
#define   CMD_SET_RTC_VALUE              9
#define   CMD_SET_TIMING_ON_MSK          10
#define   CMD_GET_TIMING_ON_MSK          11
#define   CMD_SET_INPUT_CTL_ON_MSK       12
#define   CMD_GET_INPUT_CTL_ON_MSK       13
#define   CMD_SET_HOST_ADDRESS           14
#define   CMD_GET_HOST_ADDRESS           15
#define   CMD_SET_SYSTEM_RESET           16
#define   CMD_REV_IO_SOME_BIT            36
#define   CMD_SET_IO_ONE_BIT             37 //
#define   CMD_CLR_IO_ONE_BIT             38 //
#define   CMD_REV_IO_ONE_BIT             39 //
#define   CMD_SET_IP_CONFIG              33
#define   CMD_GET_IP_CONFIG              34
#define   CMD_GET_INPUT_CTL_MODE_INDEX   40
#define   CMD_SET_INPUT_CTL_MODE_INDEX   41
#define   CMD_SET_INPUT_CTL_MODE         42
#define   CMD_GET_INPUT_CTL_MODE         43
#define   CMD_GET_TIMING2                0x2C
#define   CMD_SET_TIMING2                0x2D
//新增定时器接口
#define   CMD_READ_REGISTER              80
#define   CMD_WRITE_REGISTER             81
//PLC程序读写
#define   CMD_PLC_READ                   82  //0x52
#define   CMD_PLC_WRITE                  83  //0x53
//块读写
#define   CMD_READ_BLOCK                 84
#define   CMD_WRITE_BLOCK                85
//上报指令
#define   CMD_BYTE_REPORT                86
#define   CMD_WORD_REPORT                87
#define   CMD_BLOCK_REPORT               88

#define   CMD_SET_IO_SOME_BIT            89
#define   CMD_RST_IO_SOME_BIT            90







//9个字节
typedef struct _OriCmdHead
{
  uint8_t  cmd;
  uint8_t  index_lsb;
  uint8_t  index_hsb;
  uint8_t  cmd_option;
  uint8_t  len_lsb;
  uint8_t  len_hsb;
  uint8_t  pad;
} OriCmdHead;

//9个字节
typedef struct _CmdHead
{
  //原始的数据结构
  uint8_t  cmd;
  uint8_t  index_lsb;
  uint8_t  index_hsb;
  uint8_t  cmd_option;
  uint8_t  len_lsb;
  uint8_t  len_hsb;
  uint8_t  pad;
} CmdHead;

#define GET_CMD_DATA(pCmd)         ((void *)(((char *)pCmd)+sizeof(CmdHead)))
#define GET_CMD_OK(pcmd)           (((pcmd)->cmd_option)&CMD_ACK_OK)
#define SET_CMD_OK(pcmd,ok)        do{if(!ok){(pcmd)->cmd_option &= ~CMD_ACK_OK;}else{(pcmd)->cmd_option |= CMD_ACK_OK;}}while(0)
#define GET_CMD_STATE(pcmd)        ((((pcmd)->cmd_option)&0xF0)>>4)
#define SET_CMD_STATE(pcmd,mode)   do{(pcmd)->cmd_option &= ~0xF0;(pcmd)->cmd_option |= ((mode)&0xF)<<4; }while(0)



//5个字节
typedef struct _CmdIoValue
{
  uint8_t    io_count;
  uint8_t    io_value[4];
} CmdIoValue;

typedef struct _CmdIoIndex
{
  uint8_t    io_msk[4];
} CmdIobitmap;

typedef struct _CmdIoName
{
    uint8_t   io_addr[2];
    uint8_t   io_name[20];
} CmdIoName;


#define  TIME_TYPE_E_ST_LEN      7



typedef struct _CmdIpConfigData
{
  uint8_t   ipaddr[4];
  uint8_t   netmask[4];
  uint8_t   gateway[4];
  uint8_t   dns[4];
  uint8_t   port_lsb;
  uint8_t   port_hsb;
  uint8_t   webport_lsb;
  uint8_t   webport_hsb;
} CmdIpConfigData;


#define INPUT_TRIGGER_FLIP_MODE          0x00  //触发反转模式
#define INPUT_SINGLE_TRIGGER_MODE        0x01  //单触发模式
#define INPUT_TRIGGER_TO_OPEN_MODE       0x02  //触发开通模式
#define INPUT_TRIGGER_TO_OFF_MODE        0x03  //触发关闭模式
#define INPUT_EDGE_TRIG_MODE             0x04  //边沿触发模式
#define INPUT_LEVEL_CTL_ON_MODE          0x05  //输入电平控制开模式
#define INPUT_LEVEL_CTL_OFF_MODE         0x06  //输入电平控制关模式
#define INPUT_TRIGGER_OFF_MODE           0x07  //控制关闭


typedef struct _CmdInputModeIndex
{
  uint8_t    index;
  uint8_t    mode;
} CmdInputModeIndex;


//读写寄存器的通用接口
typedef struct _CmdRegister
{
  uint8_t  reg_addr_hi;
  uint8_t  reg_addr_lo;
  uint8_t  reg_len_hi;
  uint8_t  reg_len_lo;
  uint8_t  reg_base;
} CmdRegister;
//寄存器读写,基于字的读写

//dig input values bit array
#define   INPUT_BASE            0
#define   INPUT_COUNT                         64
//dig output values bit array
#define   OUTPUT_BASE           64  //0x40
#define   OUTPUT_COUNT                        64
//dig input counts
#define   DIG_INPUT_NUM_BASE    8000  //0x1F40
#define   DIG_INPUT_NUM_COUNT                 1
//dig output counts
#define   DIG_OUTPUT_NUM_BASE   8001  //0x1F41
#define   DIG_OUTPUT_NUM_COUNT                1
//ethernet mac
#define   ETH_MAC_ADDR_BASE     8002  //0x1F42
#define   ETH_MAC_ADDR_COUNT                  3
//RTC times
#define   RTC_TIME_BASE          8008  //0x1F48
#define   RTC_TIME_COUNT                      7

//system version
#define   SYS_VERSION_BASE        8015
#define   SYS_VERSION_COUNT                   1
//device id code
#define   DEVICE_UNICODE_ID       8016
#define   DEVICE_UNICODE_ID_COUNT             32  //up to 64 bytes
//system control
#define   SYS_CONTROL_FLAG        8048
#define   SYS_CONTROL_COUNT                   1
//device name
#define   DEV_NAME_BASE           8049
#define   DEV_NAME_COUNT                       32
//device group1
#define   DEV_GROUP1_BASE         8081
#define   DEV_GROUP1_COUNT                       16
//device group2
#define   DEV_GROUP2_BASE         8097
#define   DEV_GROUP2_COUNT                       16
//device model id
#define   DEV_MODEL_ID_BASE       8113
#define   DEV_MODEL_ID_COUNT                    1
//timing data count
#define   TIMING_DATA_COUNT_BASE       8114
#define   TIMING_DATA_COUNT_COUNT                        4 //TYPE,ENABLE,COUNT
//plc size
//dig input
#define   IO_INPUT_NAMES_BASE     9000  //0x2328
#define   IO_INPUT_NAMES_COUNT                (64*32) //one channel is 64bytes(32words),the total is 64 channels
//dig output
#define   IO_OUTPUT_NAMES_BASE    11048 //0x2B28
#define   IO_OUTPUT_NAMES_COUNT               (64*32)
//主机地址
#define   REMOTE_TCP_HOST_ADDR          14002  //
#define   REMOTE_TCP_HOST_COUNT                32  //
#define   REMOTE_TCP_PORT_BASE          14034
#define   REMOTE_TCP_PORT_COUNT                 1   //

//remote host and control
#define   PASSWORD_BASE                 14035
#define   PASSWORD_COUNT                            10

//device tcp/ip infamation
#define   DEVICE_IPCONFIG_BASE      15793
#define   DEVICE_IPCONFIG_COUNT                 11    //one ip addr is two words

//AC current ma
#define   DEVICE_AC_CURRENT_BASE    16500
#define   DEVICE_AC_CURRENT_COUNT               128
#define   DEVICE_AC_VOLTAGE_BASE    16756
#define   DEVICE_AC_BOLTAGE_COUNT               128
//temperature sample
#define   TEMPERATURE_BASE          16884
#define   TEMPERATURE_COUNT                     128
//humidity sample
#define   HUMIDITY_BASE            17012
#define   HUMIDITY_COUNT                        128




/**********************************************************
  *  块读写寄存器
  */

#define   BLOCK_SECTOR_SIZE        64    //64 Byte of one block sizes
//timing block,all of 100 timings
#define   BLOCK_TIMING_BASE          20480
#define   BLOCK_TIMING_COUNT                      300
#define   BLOCK_NAMES_BLOCK          20780
#define   BLOCK_NAMES_COUNT                       (256+256)   //256 diginput in,256 digoutput,256 else
#define   BLOCK_ELSE_NAMES           21292
#define   BLOCK_ELSE_COUNT                        (256+256+256)
#define   BLOCK_WEB_DATA             22060
#define   BLOCK_WEB_COUNT                         (512)       //32 KByte size web spaces



#endif

