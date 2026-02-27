#include "cansetmode.h"
#include <QDebug>


static const UINT kAbitTiming[] = {
    0x00018B2E,//1Mbps
    0x00018E3A,//800kbps
    0x0001975E,//500kbps
    0x0001AFBE,//250kbps
    0x0041AFBE,//125kbps
    0x0041BBEE,//100kbps
    0x00C1BBEE //50kbps
};
static const UINT kDbitTiming[] = {
    0x00010207,//5Mbps
    0x0001020A,//4Mbps
    0x0041020A,//2Mbps
    0x0081830E //1Mbps
};
static const BYTE kTiming0[] = {
    0x00,//1000kbps
    0x00,//800kbps
    0x00,//500kbps
    0x01,//250kbps
    0x03,//125kbps
    0x04,//100kbps
    0x09,//50kbps
    0x18,//20kbps
    0x31,//10kbps
    0xBF //5kbps
};
static const BYTE kTiming1[] = {
    0x14,//1000kbps
    0x16,//800kbps
    0x1C,//500kbps
    0x1C,//250kbps
    0x1C,//125kbps
    0x1C,//100kbps
    0x1C,//50kbps
    0x1C,//20kbps
    0x1C,//10kbps
    0xFF //5kbps
};
static const unsigned kBaudrate[] = {
    1000000,
    800000,
    500000,
    250000,
    125000,
    100000,
    50000,
    20000,
    10000,
    5000
};

//类的构造函数
CanSetModel::CanSetModel(QObject *parent) : QObject(parent)
{

}
//CAN设备类的设置函数，设置设备类型，设备索引，通道号，波特率
void CanSetModel::SetPara(int type, int index, int ch, char *br)
{
    this->DeviceType = type;
    this->DeveiceIndex = index;
    this->ChannelIndex = ch;
    this->BaudRate = br;
    this->BaudRateFd = br;
}
//数据的接收
void CanSetModel::DataReceive()
{
    //ZCAN_Receive_Data结构体中包含 ID 数据长度 数据和时间戳，单位微秒，基于设备启动时间
    ZCAN_Receive_Data can_data[100];
    //    ZCAN_ReceiveFD_Data canfd_data[100];
    UINT len;
    while(isStart)
    {
        //从通道中读取CAN报文的数目 第二个参数：0=CAN，1=CANFD，2=合并接收。这里只接受CAN 返回报文数目
        if (ZCAN_GetReceiveNum(chHandle, TYPE_CAN))
        {
                //如果有报文就接收报文，参数：通道的句柄 缓冲区 缓冲区的长度 阻塞的时间 返回返回实际接收的报文数目。
            len = ZCAN_Receive(chHandle, can_data, 100, 10);
            AddData(can_data, len);
        }
    }
}

void CanSetModel::AddData(const ZCAN_Receive_Data *data, UINT len)
{
    //QString item;
    //len就是缓冲区中含有的报文的数目
    for (UINT i = 0; i < len; ++i)
    {
        const ZCAN_Receive_Data& can = data[i];
        const canid_t& id = can.frame.can_id;//记录ID

        CanDataBase *cdb = new CanDataBase();
        cdb->SetTime(data->timestamp);//记录时间戳 单位是us
        //将ID 数据 CAN数据的长度 CAN的类型 是否远程帧
        cdb->SetData(GET_ID(id),(unsigned char*)can.frame.data,can.frame.can_dlc,IS_EFF(id),IS_RTR(id));

        AddData(cdb);
    }
}

void CanSetModel::AddData(const ZCAN_ReceiveFD_Data *data, UINT len)
{
    QString item;
    for (UINT i = 0; i < len; ++i)
    {
        const ZCAN_ReceiveFD_Data& canfd = data[i];
        const canid_t& id = canfd.frame.can_id;

        CanDataBase *cdb = new CanDataBase();
        cdb->SetTime(data->timestamp);

        cdb->SetData(GET_ID(id),(unsigned char*)canfd.frame.data,canfd.frame.len,IS_EFF(id),IS_RTR(id));

        AddData(cdb);
    }
}

void CanSetModel::AddData(CanDataBase *cdb)
{
    //记录下系统时间
    cdb->SetTime(QDateTime::currentDateTime());
    //cdb->getStrData();
    //传递信号到DataUpdata
    emit this->DataUpdata(cdb);
}

bool CanSetModel::CanConnect()
{
    bool isCanFd = false;

    if(DeviceType == ZCAN_USBCANFD_200U || DeviceType == ZCAN_USBCANFD_100U || DeviceType == ZCAN_USBCANFD_MINI)
        isCanFd = true;


    dhandle = ZCAN_OpenDevice(DeviceType, DeveiceIndex, 0);

    if (INVALID_DEVICE_HANDLE == dhandle)
    {
        qDebug( "打开设备失败" );
        //emit this->openresult("打开设备失败");
        return false;
    }


    ZCAN_CHANNEL_INIT_CONFIG cfg;

    if(isCanFd)
    {
        //仲裁域波特率
        if (0 == ZCAN_SetValue(dhandle, "0/canfd_abit_baud_rate", BaudRateFd))
        {
            qDebug() << "设置波特率失败" ;
            //emit this->openresult("设置波特率失败");
            ZCAN_CloseDevice(dhandle);
            return false;
        }


        // 数据域波特率
        if (0 == ZCAN_SetValue(dhandle, "0/canfd_dbit_baud_rate", BaudRate))
        {
            qDebug() << "设置波特率失败" ;
            //emit this->openresult("设置波特率失败");
            ZCAN_CloseDevice(dhandle);
            return false;
        }

        memset(&cfg, 0, sizeof(cfg));
        cfg.can_type = TYPE_CANFD;//CANFD设备为TYPE_CANFD
        cfg.can.filter = 0;
        cfg.can.mode = 0; //正常模式, 1为只听模式
        cfg.can.acc_code = 0;
        cfg.can.acc_mask = 0xffffffff;
        //CAN_SetValue
    }
    else
    {
        if (ZCAN_SetValue(dhandle, "0/baud_rate", BaudRate)!= STATUS_OK)
        {
            qDebug() << "设置波特率失败" ;
            ZCAN_CloseDevice(dhandle);
            return false;
        }

        memset(&cfg, 0, sizeof(cfg));
        cfg.can_type = TYPE_CAN;//CANFD设备为TYPE_CANFD
        cfg.can.filter = 0;
        cfg.can.mode = 0; //正常模式, 1为只听模式
        cfg.can.acc_code = 0;
        cfg.can.acc_mask = 0xffffffff;

    }

    chHandle = ZCAN_InitCAN(dhandle, ChannelIndex, &cfg);
    if (INVALID_CHANNEL_HANDLE == chHandle)
    {
        qDebug() << "初始化通道失败";
        ZCAN_CloseDevice(dhandle);
        return false;
    }

    if (ZCAN_StartCAN(chHandle) != STATUS_OK)
    {
        qDebug() << "启动通道失败" ;
        ZCAN_CloseDevice(dhandle);
        return false;
    }

    isStart =true;
    qDebug() << "设备打开成功" ;
    return true;

}

void CanSetModel::CanClose()
{

    ZCAN_CloseDevice(dhandle);

    isStart = false;
}

bool CanSetModel::CanSend(CanDataBase *data)
{

    ZCAN_Transmit_Data frame;
    memset(&frame, 0, sizeof(frame));


    frame.frame.can_id = MAKE_CAN_ID(data->id,data->isExtendFrame(),0,0);
    frame.frame.can_dlc =data->Len();
    for( int i = 0; i < data->Len(); i++ )
    {
        frame.frame.data[i] =  data->Data[i];
    }

    if (ZCAN_Transmit(chHandle, &frame, 1) != 1)
    {
        qDebug() << "发送数据失败" ;
        return false;
    }

    //data->sTime = frame.frame.`

    return true;
}


