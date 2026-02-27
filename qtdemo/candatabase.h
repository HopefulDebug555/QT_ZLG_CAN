#ifndef CANDATABASE_H
#define CANDATABASE_H

//CAN数据管理的基类
#include <QObject>
#include <QDateTime>

class CanDataBase
{
public:


    unsigned char *Data;//数据

    QDateTime Time;//时间戳

    double sTime;//单位为s的时间戳

    uint id;//ID

    CanDataBase();//构造函数

    bool isSend();//是否为发送帧

    bool isExtendFrame();//是否为扩展帧

    void setExtendFrame(bool isex);//设置扩展帧

    bool isRemoteFrame();//是否为远程帧

    void SetTime(QDateTime time);//设置时间
    void SetTime(quint64 ustime);//设置时间

    void SetIsSend(bool send);//设置发送

    void SetData(uint id,unsigned char * data,int len,bool extend = false,bool remote = false);//设置CAN数据

    QString getStrData();//返回字符串数据

    int Len();//获取长度

    void setLen(int len);//设置长度

protected:

    QString strData;//字符串
    int lenght;//长度


    bool issend;//是否为发送帧

    bool isextendFrame;//是否扩展

    bool isremoteFrame;//是否远程

};

#endif // CANDATABASE_H
