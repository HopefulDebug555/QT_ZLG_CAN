#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zlgcan.h"
#include <QDebug>
#include <QMessageBox>
#include <QListView>
#include <QListWidget>
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QTableWidget>
#include <QTreeView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QPalette>
#include "MyTypedef.h"


static UINT LED_Older = 0;

typedef struct _DeviceInfo
{
    QString name;
    UINT device_type;  //设备类型
    UINT channel_count;//设备的通道个数
}DeviceInfo;

static const DeviceInfo kDeviceType[] = {
    {"ZCAN_USBCAN2",ZCAN_USBCAN2, 2},
    {"ZCAN_USBCAN1",ZCAN_USBCAN1, 1},
    {"ZCAN_USBCAN_E_U",ZCAN_USBCAN_E_U, 1},
    {"ZCAN_USBCAN_2E_U",ZCAN_USBCAN_2E_U, 2},
    {"ZCAN_USBCANFD_200U",ZCAN_USBCANFD_200U, 2},
    {"ZCAN_USBCANFD_100U",ZCAN_USBCANFD_100U, 1},
    {"ZCAN_USBCANFD_MINI",ZCAN_USBCANFD_MINI, 1},
    };

typedef struct _BaudRateInfo
{
    QString name;
    QString value;
}BaudRateInfo;

static const BaudRateInfo kBaudRateInfo[] =
    {
        {"250Kbps","250000"},
        {"500Kbps","500000"},
        {"125Kbps","125000"},
        };

// 该函数将label控件变成一个圆形指示灯，需要指定颜色color以及直径size
// color 0:grey 1:red 2:green 3:yellow
// size  单位是像素
void setLED(QLabel* label, int color, int size)
{
    // 将label中的文字清空
    label->setText("");
    // 先设置矩形大小
    // 如果ui界面设置的label大小比最小宽度和高度小，矩形将被设置为最小宽度和最小高度；
    // 如果ui界面设置的label大小比最小宽度和高度大，矩形将被设置为最大宽度和最大高度；
    QString min_width = QString("min-width: %1px;").arg(size);              // 最小宽度：size
    QString min_height = QString("min-height: %1px;").arg(size);            // 最小高度：size
    QString max_width = QString("max-width: %1px;").arg(size);              // 最小宽度：size
    QString max_height = QString("max-height: %1px;").arg(size);            // 最小高度：size
    // 再设置边界形状及边框
    QString border_radius = QString("border-radius: %1px;").arg(size/2);    // 边框是圆角，半径为size/2
    QString border = QString("border:1px solid black;");                    // 边框为1px黑色
    // 最后设置背景颜色
    QString background = "background-color:";
    switch (color) {
    case 0:
        // 灰色
        background += "rgb(190,190,190)";
        break;
    case 1:
        // 红色
        background += "rgb(255,0,0)";
        break;
    case 2:
        // 绿色
        background += "rgb(0,255,0)";
        break;
    case 3:
        // 黄色
        background += "rgb(255,255,0)";
        break;
    default:
        break;
    }

    const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background;
    label->setStyleSheet(SheetStyle);
}




//构造函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //添加设备信息
    for(int i=0;i<7;i++)
    {
        ui->cmbDeviceType->addItem(kDeviceType[i].name);
    }

    for(int i=0;i<3;i++)
    {
        ui->cmbBaudrate->addItem(kBaudRateInfo[i].name);
    }

    ui->cmbDeviceldnex->addItem("0");
    ui->cmbDeviceldnex->addItem("1");
    ui->cmbChannelldnex->addItem("0");
    ui->cmbChannelldnex->addItem("1");
    //设置修改ID的文本格式
    ui->leIdChange->setInputMask("99");
    ui->leIdChange->setPlaceholderText("输入ID");

    //设置LED
    setLED(ui->lb_LED1,0,16);
    setLED(ui->lb_LED2,0,16);

    //初始化定时器
    time_LED = new QTimer(this);
    time_LED->setInterval(10);//设置定时器的计时时间（ms）

    CanSet = new CanSetModel;//初始化CAN设置
#ifdef MY_DEVICE_STATE
    MyDeviceState = new Device_State;//初始化设备
#endif

    myThread = new QThread(this);//主线程中创建一个线程
    CanSet->moveToThread(myThread);//把CanSet对象放到线程中执行，主要执行的是他的接收函数
    //定时器的信号函数
    connect(time_LED,&QTimer::timeout,this,&MainWindow::time_Func);
    //将MainWindow中的StartDataReceive信号连接到CanSet的DataReceive函数
    connect(this,&MainWindow::StartDataReceive,CanSet,&CanSetModel::DataReceive);
    //将MainWindow中的destroyed信号连接到MainWindow的CloseWin函数，用于窗口销毁是关闭设备
    connect(this,&MainWindow::destroyed,this,&MainWindow::CloseWin);
    //将CanSet中的DataUpdata信号连接到MainWindow的UpdataReceive函数，用的是BlockingQueuedConnection连接方法，会在CanSet的线程中执行
    connect(CanSet,&CanSetModel::DataUpdata,this,&MainWindow::UpdataReceive,Qt::BlockingQueuedConnection);
    //CanSet中的openresult信号连接到MainWindow的handleResults函数，并在MainWindow的线程中执行
    connect(CanSet,&CanSetModel::openresult,this,&MainWindow::handleResults);

    time_LED->start();

}

MainWindow::~MainWindow()
{
    CloseWin();
    delete ui;//关闭UI
}

void MainWindow::CloseWin()
{
    //如果线程在运行
    if(myThread->isRunning())
    {
        //执行关闭函数
        CanSet->CanClose();
        // ui->btnConnect->setText("连接并启动");
        //关闭线程
        myThread->quit();
        myThread->wait();
        //销毁CanSet对象
        delete CanSet;
    }
}

void MainWindow::SendFF(void)
{
    if((true == CanSet->isStart) && (true == myThread->isRunning()))
    {
        CanDataBase* Send_ChangeID = new CanDataBase;
        uchar data[8] = {0};
        uint id = 0x1800FF00;
        Send_ChangeID->SetIsSend(true);
        Send_ChangeID->SetData(id,data,8,true,false);
        Send_ChangeID->SetTime(QDateTime::currentDateTime());
        if(true == CanSet->CanSend(Send_ChangeID))
        {
            this->UpdataReceive(Send_ChangeID);
        }
    }

}
static UINT LED = 0;
static UINT cnt = 0;
//定时器中断函数
void MainWindow::time_Func(void)
{
    if(cnt < 100)
    {
        cnt++;
    }
    else
    {
        //定时器LED的槽函数
        if(LED == 0)
        {
            LED = 1;
            setLED(ui->lb_LED2,0,16);
        }
        else if(LED == 1)
        {
            LED = 0;
            setLED(ui->lb_LED2,3,16);
        }
        cnt = 0;
        SendFF();
    }
    //在这里更新、检查设备状态
#ifdef MY_DEVICE_STATE
    //在等待工厂测试帧
    if(true == MyDeviceState->flg_WaitFactoryTest)
    {
        if(MyDeviceState->FactoryTestWaitTime > 0)
        {//等待时间大于0
            MyDeviceState->FactoryTestWaitTime -= 10;
            //如果已经等到了
            if(true == MyDeviceState->flg_CompleteFactoryTest)
            {
                //设置工厂测试标志
                MyDeviceState->Set_FlgDevice(true);
                MyDeviceState->Set_FlgFactoryTest(true);
                MyDeviceState->Set_FlgDevice(false);
                ui->pbFactoryTest->setText("关闭工厂测试");
                MyDeviceState->flg_WaitFactoryTest = false;//等到了就不等了
                MyDeviceState->FactoryTestWaitTime = 0;//等待时间清空
            }
        }
        else
        {//超时了
            MyDeviceState->flg_CompleteFactoryTest = false;//没等到
            MyDeviceState->flg_WaitFactoryTest = false;//没等到就不等了

            MyDeviceState->Set_FlgDevice(true);
            MyDeviceState->Set_FlgFactoryTest(false);
            MyDeviceState->Set_FlgDevice(false);
        }
    }

    if(true == MyDeviceState->flg_WaitChangeID)
    {
        if(MyDeviceState->ChangeIDWaitTime > 0)
        {//等待时间大于0
            MyDeviceState->ChangeIDWaitTime -= 10;
            //如果已经等到了
            if(true == MyDeviceState->flg_CompleteChangeID)
            {

                MyDeviceState->flg_WaitChangeID = false;//等到了就不等了
                MyDeviceState->ChangeIDWaitTime = 0;//等待时间清空

                QListWidgetItem *item = new QListWidgetItem("修改ID成功");
                item->setForeground(Qt::red);
                ui->lwDataDisplay->addItem(item);//添加到列表控件
                ui->lwDataDisplay->scrollToBottom();//滚动到底部
                //当消息数量大于100时，移除第0个消息
                if(ui->lwDataDisplay->count() >= 100)
                    ui->lwDataDisplay->removeItemWidget(ui->lwDataDisplay->takeItem(0));
            }
        }
        else
        {//超时了

            MyDeviceState->flg_CompleteChangeID = false;//没等到
            MyDeviceState->flg_WaitChangeID = false;//没等到就不等了

            QListWidgetItem *item = new QListWidgetItem("修改ID失败");
            item->setForeground(Qt::red);
            ui->lwDataDisplay->addItem(item);//添加到列表控件
            ui->lwDataDisplay->scrollToBottom();//滚动到底部
            //当消息数量大于100时，移除第0个消息
            if(ui->lwDataDisplay->count() >= 100)
                ui->lwDataDisplay->removeItemWidget(ui->lwDataDisplay->takeItem(0));
        }
    }


    if(false == MyDeviceState->Read_FlgDevice())
    {
        MyDeviceState->Set_FlgDevice(true);
        if(false == MyDeviceState->Read_FlgFactoryTest())
        { //如果不是工厂测试模式
            //这里更新界面
            ui->pbFactoryTest->setText("开启工厂测试");
        }
        else
        {
            //这里更新界面
            ui->pbFactoryTest->setText("关闭工厂测试");
        }
        MyDeviceState->Set_FlgDevice(false);
    }

#endif
}

//数据解析函数
void MainWindow::UpdataReceive(CanDataBase * cdb)
{
    //数据解析函数
    QString str,hw_ver,sw_ver,STM32_T,DHT11_T,CO_PPM,CO_AD;
    uint idcheck,device_id;
    str += cdb->isSend()?"发送 ":"接收 ";
    str += cdb->Time.toString("HH:mm:ss.zzz");
    str += "  ID:0x";
    str += QString::number(cdb->id,16);
    str += cdb->isExtendFrame()?" 扩展帧 ":" 标准帧 ";
    str += " 数据：";
    str += cdb->getStrData();

    if(false == cdb->isSend())
    {
        //只有收到的CAN帧才会解析
        idcheck = cdb->id & 0xffff0000;
        device_id = cdb->id & 0x000000ff;
        //根据ID进行解析
        if(0x18010000 == idcheck)
        {

            hw_ver = QString::number(cdb->Data[7]/10.0,'f',1);
            sw_ver = QString::number(cdb->Data[6]/10.0,'f',1);
            STM32_T = QString::number(cdb->Data[0]+cdb->Data[1]/100.0,'f',2);
            DHT11_T = QString::number(cdb->Data[2]+cdb->Data[3]/100.0,'f',2);

            ui->leHwVer->setText(hw_ver);
            ui->leSwVer->setText(sw_ver);
            ui->leDeviceID->setText(QString::number(device_id,10));
            ui->leSTM32T->setText(STM32_T);
            ui->leDHT11T->setText(DHT11_T);

        }
        else if(0x18c10000 == (idcheck & 0xffff0000))
        {
            //如果是工厂测试的ID
            if((cdb->Data[6] == drv_U8XorCRC(cdb->Data,6)) && (cdb->Data[7] == drv_U8SumCRC(cdb->Data,7)))
            {
                //校验通过
                if((cdb->Data[0] == 0xbb)&(cdb->Data[5] == 0xaa))
                {
                    MyDeviceState->flg_CompleteFactoryTest = true;
                }
            }
        }
        else if(ID_HostCMD == idcheck)
        {
            //如果是工厂测试的ID
            if((cdb->Data[6] == drv_U8XorCRC(cdb->Data,6)) && (cdb->Data[7] == drv_U8SumCRC(cdb->Data,7)))
            {
                //校验通过
                //qDebug("111");
                if(CAN_ACK == cdb->Data[5])
                {
                    switch(cdb->Data[0])
                    {
                        case CAN_HostCommand:
                            if(CAN_ChangeID == cdb->Data[1])
                            {
                                MyDeviceState->flg_CompleteChangeID = true;
                                device_id = cdb->Data[2];
                                ui->leDeviceID->setText(QString::number(device_id,10));

                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        else if((idcheck&0xffff0000) == 0x188B0000)
        {
            CO_PPM = QString::number(((cdb->Data[6]<<8)+cdb->Data[7])/10,'f',1);
            ui->CO_PPM->setText(CO_PPM);
        }
        else if((idcheck&0xffff0000) == 0x18400000)
        {
            CO_AD = QString::number(((cdb->Data[6]<<8)+cdb->Data[7]),'f',0);
            ui->CO_AD->setText(CO_AD);
        }



    }

    //把数据处理一下添加到显示框中
    //QListWidgetItem是QListWidget中的单个消息条目
    QListWidgetItem *item = new QListWidgetItem(str);

    if(cdb->isSend())//如果是发送帧，就把字体设置为红色
        item->setForeground(Qt::red);

    ui->lwDataDisplay->addItem(item);//添加到列表控件
    ui->lwDataDisplay->scrollToBottom();//滚动到底部
    //当消息数量大于100时，移除第0个消息
    if(ui->lwDataDisplay->count() >= 100)
        ui->lwDataDisplay->removeItemWidget(ui->lwDataDisplay->takeItem(0));
}

void MainWindow::handleResults(const QString &result)
{
    QMessageBox::critical(this, "错误信息", result);
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->pushButton->isChecked() == false)
    {
        ui->pushButton->setText("连接并启动");
        setLED(ui->lb_LED1,0,16);
        if(myThread->isRunning())
        {
            CanSet->CanClose();
            myThread->quit();
            myThread->wait();
        }

    }
    else
    {
        uint index = ui->cmbDeviceType->currentIndex();
        uint device_type = kDeviceType[index].device_type;
        uint deviceIndex = ui->cmbDeviceldnex->currentIndex();
        uint channelIndex = ui->cmbChannelldnex->currentIndex();
        uint br =  ui->cmbBaudrate->currentIndex();

        char * brv  = kBaudRateInfo[br].value.toLatin1().data();

        CanSet->SetPara(device_type,deviceIndex,channelIndex,brv);

        bool isok = CanSet->CanConnect();

        if(isok)
        {
            ui->pushButton->setText("断开连接");
            setLED(ui->lb_LED1,2,16);
            myThread->start();
            emit this->StartDataReceive();
        }
    }
}



//工厂测试按钮
void MainWindow::on_pbFactoryTest_clicked()
{
    if((true == CanSet->isStart) && (true == myThread->isRunning()))
    {
        CanDataBase* Send_FactoryTest = new CanDataBase;
        uchar data[8] = {0};
        uint id = 0x18C1FF00;
        data[0] = 0xaa;
        data[5] = 0xbb;
        data[6] = drv_U8XorCRC(data,6);
        data[7] = drv_U8SumCRC(data,7);
        Send_FactoryTest->SetIsSend(true);
        if(ui->pbFactoryTest->isChecked() == false)
        {
            //data[6] = 0x02;
            Send_FactoryTest->SetData(id,data,8,true,false);
            Send_FactoryTest->SetTime(QDateTime::currentDateTime());
            if(true == CanSet->CanSend(Send_FactoryTest))
            {

                this->UpdataReceive(Send_FactoryTest);
                if(false == MyDeviceState->flg_WaitFactoryTest)
                {
                    MyDeviceState->flg_CompleteFactoryTest = false;

                    MyDeviceState->flg_WaitFactoryTest = true;//开始等待
                }
                MyDeviceState->FactoryTestWaitTime = WaitTime_ms;
            }
        }
        else
        {
            //data[6] = 0x01;
            Send_FactoryTest->SetData(id,data,8,true,false);
            Send_FactoryTest->SetTime(QDateTime::currentDateTime());
            if(true == CanSet->CanSend(Send_FactoryTest))
            {

#ifdef MY_DEVICE_STATE

                MyDeviceState->Set_FlgDevice(true);
                MyDeviceState->Set_FlgFactoryTest(false);
                MyDeviceState->Set_FlgDevice(false);
#endif
                this->UpdataReceive(Send_FactoryTest);
            }
        }
        delete Send_FactoryTest;
    }
}

//修改ID按钮
void MainWindow::on_pbChangeID_clicked()
{
    if((true == CanSet->isStart) && (true == myThread->isRunning()))
    {
        CanDataBase* Send_ChangeID = new CanDataBase;
        bool ok;
        uchar data[8] = {0};
        uint id = 0x18CB00FF;
        data[0] = CAN_HostCommand;
        data[1] = CAN_ChangeID;
        data[2] = ui->leIdChange->text().toInt(&ok,10);
        if(0 == data[2])
        {
            data[2] = 1;
        }
        data[6] = drv_U8XorCRC(data,6);
        data[7] = drv_U8SumCRC(data,7);
        Send_ChangeID->SetIsSend(true);
        Send_ChangeID->SetData(id,data,8,true,false);
        Send_ChangeID->SetTime(QDateTime::currentDateTime());
        if(true == CanSet->CanSend(Send_ChangeID))
        {
            this->UpdataReceive(Send_ChangeID);
            /*
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, "提示", "修改ID成功");
            msgBox->setAttribute(Qt::WA_DeleteOnClose); // 确保关闭后自动释放内存
            msgBox->setWindowModality(Qt::NonModal);   // 设置为非模态
            msgBox->show();
            */
            if(false == MyDeviceState->flg_WaitChangeID)
            {
                MyDeviceState->flg_CompleteChangeID = false;//没有等待成功

                MyDeviceState->flg_WaitChangeID = true;//开始等待
            }
            MyDeviceState->ChangeIDWaitTime = WaitTime_ms;

        }
        else
        {
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, "提示", "修改ID失败");
            msgBox->setAttribute(Qt::WA_DeleteOnClose); // 确保关闭后自动释放内存
            msgBox->setWindowModality(Qt::NonModal);   // 设置为非模态
            msgBox->show();
        }
        delete Send_ChangeID;
    }
}

//改变LED亮度的滑块回调函数
void MainWindow::on_sLedSet_valueChanged(int value)
{
    qDebug("滑块当前值%d",value);
    if((true == CanSet->isStart) && (true == myThread->isRunning()))
    {
        CanDataBase* Send_SETLED = new CanDataBase;
        uchar data[8] = {0};
        uint id = ID_FactoryTest;
        data[0] = 0xAA;
        data[2] = value;
        data[7] = 0xBB;

        Send_SETLED->SetIsSend(true);//设置是不是发送
        Send_SETLED->SetData(id,data,8,true,false);
        Send_SETLED->SetTime(QDateTime::currentDateTime());

        if(true == CanSet->CanSend(Send_SETLED))
        {   //发送成功
            this->UpdataReceive(Send_SETLED);
            LED_Older = value;//记录下改变成功后的LED亮度
            QListWidgetItem *item = new QListWidgetItem("修改LED亮度成功");
            item->setForeground(Qt::red);
            ui->lwDataDisplay->addItem(item);//添加到列表控件
            ui->lwDataDisplay->scrollToBottom();//滚动到底部
            //当消息数量大于100时，移除第0个消息
            if(ui->lwDataDisplay->count() >= 100)
                ui->lwDataDisplay->removeItemWidget(ui->lwDataDisplay->takeItem(0));
        }
        else
        {
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, "提示", "修改LED亮度失败");
            msgBox->setAttribute(Qt::WA_DeleteOnClose); // 确保关闭后自动释放内存
            msgBox->setWindowModality(Qt::NonModal);   // 设置为非模态
            msgBox->show();
            ui->sLedSet->setValue(LED_Older);
        }
        delete Send_SETLED;
    }
}

void MainWindow::on_pbEmptyDataDisplay_clicked()
{
    ui->lwDataDisplay->clear();
}


void MainWindow::on_pushButton_2_clicked()
{
    //复位按钮
}

