#ifndef CANSETMODE_H
#define CANSETMODE_H

#include <QObject>

#include "zlgcan.h"
#include "typedef.h"
#include "config.h"
#include "canframe.h"
#include "candatabase.h"

class CanSetModel : public QObject
{
    Q_OBJECT
public:
    explicit CanSetModel(QObject *parent = 0);

    CHANNEL_HANDLE chHandle;//通道的句柄

    DEVICE_HANDLE dhandle;//设备的句柄

    int DeviceType;//设备类型

    int DeveiceIndex;//设备索引号
    int ChannelIndex;//通道索引号

    char* BaudRate;//波特率

    char* BaudRateFd;//波特率FD版本


    bool isStart;//是否打开设备

    void SetPara(int type,int index,int ch, char* br);//设置设备类型、索引、通道和波特率


    bool CanConnect();//CAN连接

    void CanClose();//CAN关闭

    bool CanSend(CanDataBase *data);//CAN发送

    void DataReceive();//读取数据

    void AddData(const ZCAN_Receive_Data *data, UINT len);//标准CAN帧数据处理

    void AddData(const ZCAN_ReceiveFD_Data *data, UINT len);//CANFD帧数据处理

    void AddData(CanDataBase *data);//自定义类型的数据处理

signals:

    void DataUpdata(CanDataBase *data);//发送的信号 参数是自定义的CAN数据类型

    void openresult(const QString &s);//设备连接结果信号

public slots:
};

#endif // CANSETMODE_H
