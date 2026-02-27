#ifndef MYTYPEDEF_H
#define MYTYPEDEF_H

#include "typedef.h"

#include <QObject>

#define CAN_ACK                 0xaa

#define CAN_HostCommand         0U
#define CAN_ChangeID            1U

#define ID_FactoryTest          0x18CA0000
#define ID_HostCMD              0x18CB0000

#define WaitTime_ms              500

#define MY_DEVICE_STATE

class Device_State
{
public://共有
    Device_State();
    ~Device_State();

    //配套的有是否在等待回应，是否等待到回应 等待时间
    bool flg_WaitFactoryTest;//正在等待回应
    bool flg_CompleteFactoryTest;//等到回应
    UINT FactoryTestWaitTime;//等待时间
    //改ID的标志位
    bool flg_WaitChangeID;//正在等待回应
    bool flg_CompleteChangeID;//等到回应
    UINT ChangeIDWaitTime;//等待时间

    //读取设备状态
    bool Read_FlgDevice(void);
    //设置设备状态并返回
    bool Set_FlgDevice(bool flg = false);
    //读取设备ID
    UINT Read_ID(void);
    //设置设备ID
    UINT Set_ID(UINT id);
    //读取设备工厂测试状态
    bool Read_FlgFactoryTest(void);
    //设置设备工厂测试状态并返回
    bool Set_FlgFactoryTest(bool flg = false);
private://私人
    bool flg_Device;//访问状态

    UINT id;//设备ID

    bool flg_FactoryTest;//设备是否开启工厂测试

};

unsigned char drv_U8XorCRC(unsigned char *data, int len);
unsigned char drv_U8SumCRC(unsigned char *data, int len);

#endif // MYTYPEDEF_H
