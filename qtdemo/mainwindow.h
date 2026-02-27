#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canframe.h"
#include "config.h"
#include "typedef.h"
#include "zlgcan.h"
#include "cansetmode.h"
#include <QThread>
#include <QStandardItem>
#include <QButtonGroup>
#include <QTimer>
#include "MyTypedef.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void CloseWin();
    void UpdataReceive(CanDataBase * cdb);
    void handleResults(const QString &result);
    void time_Func(void);

    void SendFF(void);


    void on_pbFactoryTest_clicked();

    void on_pbChangeID_clicked();

    void on_sLedSet_valueChanged(int value);

    //void on_pbOpenFile_clicked();

    void on_pbEmptyDataDisplay_clicked();

    void on_pushButton_2_clicked();

signals:
    void StartDataReceive();//开始接收数据的信号
private:
    Ui::MainWindow *ui;
    CanSetModel *CanSet;
    QThread *myThread;
#ifdef MY_DEVICE_STATE
    Device_State *MyDeviceState;
#endif
    QTimer *time_LED;
};


#endif // MAINWINDOW_H
