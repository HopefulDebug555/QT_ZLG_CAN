#include "candatabase.h"



CanDataBase::CanDataBase()//构造函数
{
    this->issend = false;
    this->lenght = false;
    this->isextendFrame = false;
    this->isremoteFrame = false;

}

bool CanDataBase::isSend()//是否为发送帧
{
    return this->issend;
}

bool CanDataBase::isExtendFrame()//是否为扩展帧
{
    return this->isextendFrame;
}

void CanDataBase::setExtendFrame(bool isex)//设置扩展帧
{
    this->isextendFrame = isex;
}

bool CanDataBase::isRemoteFrame()//是否为远程帧
{
    return this->isremoteFrame;
}

void CanDataBase::SetTime(QDateTime time)//设置时间
{
    this->Time = time;

}
void CanDataBase::SetTime(quint64 ustime)//设置时间
{
    this->sTime = ustime/1000000.0;

}

void CanDataBase::SetIsSend(bool send)//设置发送
{
    this->issend = send;
}
//id 数据 数据长度 是否为扩展帧 是否为远程帧
void CanDataBase::SetData(uint id,unsigned char * data,int len,bool extend ,bool remote)//设置CAN数据
{
    this->id = id;
    this->Data =data;
    this->isextendFrame = extend;
    this->isremoteFrame = remote;
    this->lenght = len;
}

QString CanDataBase::getStrData()//返回字符串数据
{
    if(this->lenght==0)
    {
        return "00 00 00 00 00 00 00 00";
    }
    else
    {
        QString str ="";

        for(int i=0;i<this->lenght;i++)
        {
            //将this->Data[i]变成长度为2的16进制数 长度不足2的前面补0
            str += QString("%1 ").arg( this->Data[i],2,16,QLatin1Char('0'));
        }
        return str;
    }
}

int CanDataBase::Len()//获取长度
{
    return this->lenght;
}

void CanDataBase::setLen(int len)//设置长度
{
    this->lenght = len;
}
