#include "MyTypedef.h"



//构造函数
Device_State::Device_State()
{
    this->flg_Device = false;
    this->flg_FactoryTest = false;
    this->id = 0;
}
//析构函数
Device_State::~Device_State()
{

}

//读取设备状态
bool Device_State::Read_FlgDevice(void)
{
    return this->flg_Device;
}
//设置设备读取状态
bool Device_State::Set_FlgDevice(bool flg)
{
    this->flg_Device = flg;
    return this->flg_Device;
}
//读取设备ID
UINT Device_State::Read_ID(void)
{
    return this->id;
}
//设置设备ID
UINT Device_State::Set_ID(UINT id)
{
    this->id = id;
    return this->id;
}
//读取工厂测试状态
bool Device_State::Read_FlgFactoryTest(void)
{
    return this->flg_FactoryTest;
}
//设置工厂测试状态
bool Device_State::Set_FlgFactoryTest(bool flg)
{
    this->flg_FactoryTest = flg;
    return this->flg_FactoryTest;
}

unsigned char drv_U8XorCRC(unsigned char *data, int len)
{
    unsigned char i, valCRC = 0;
    for(i = 0; i < len; i++)
    {
        valCRC ^= *(data + i);
    }
    return valCRC;
}

unsigned char drv_U8SumCRC(unsigned char *data, int len)
{
    int tmp_CRC = 0;
    unsigned char i, valCRC;
    for(i = 0; i < len; i++)
    {
        tmp_CRC += *(data + i);
    }
    tmp_CRC &= 0x00FF;
    valCRC = 0xFF - tmp_CRC;
    return valCRC;
}



































