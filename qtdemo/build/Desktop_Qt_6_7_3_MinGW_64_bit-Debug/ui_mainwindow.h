/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_3;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label;
    QComboBox *cmbDeviceType;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_2;
    QComboBox *cmbBaudrate;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_3;
    QComboBox *cmbDeviceldnex;
    QLabel *label_4;
    QComboBox *cmbChannelldnex;
    QSpacerItem *horizontalSpacer_4;
    QListWidget *lwDataDisplay;
    QLabel *label_5;
    QLineEdit *leSwVer;
    QLineEdit *leHwVer;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *leDeviceID;
    QLineEdit *leSTM32T;
    QLabel *label_8;
    QLineEdit *leDHT11T;
    QLabel *label_9;
    QPushButton *pbFactoryTest;
    QLineEdit *leIdChange;
    QPushButton *pbChangeID;
    QSlider *sLedSet;
    QLabel *label_10;
    QPushButton *pbEmptyDataDisplay;
    QLabel *lb_LED1;
    QLabel *lb_LED2;
    QLabel *label_11;
    QLineEdit *CO_PPM;
    QLabel *label_12;
    QLineEdit *CO_AD;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setSizeIncrement(QSize(0, 23));
        MainWindow->setBaseSize(QSize(0, 23));
        QFont font;
        font.setPointSize(10);
        MainWindow->setFont(font);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpenRecent));
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 800, 101));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 70, 801, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setCheckable(true);

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(2, 12, 801, 61));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        label = new QLabel(layoutWidget1);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(label);

        cmbDeviceType = new QComboBox(layoutWidget1);
        cmbDeviceType->setObjectName("cmbDeviceType");

        horizontalLayout_2->addWidget(cmbDeviceType);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(label_2);

        cmbBaudrate = new QComboBox(layoutWidget1);
        cmbBaudrate->setObjectName("cmbBaudrate");

        horizontalLayout_2->addWidget(cmbBaudrate);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(label_3);

        cmbDeviceldnex = new QComboBox(layoutWidget1);
        cmbDeviceldnex->setObjectName("cmbDeviceldnex");

        horizontalLayout_2->addWidget(cmbDeviceldnex);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(label_4);

        cmbChannelldnex = new QComboBox(layoutWidget1);
        cmbChannelldnex->setObjectName("cmbChannelldnex");

        horizontalLayout_2->addWidget(cmbChannelldnex);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        lwDataDisplay = new QListWidget(centralwidget);
        lwDataDisplay->setObjectName("lwDataDisplay");
        lwDataDisplay->setGeometry(QRect(0, 270, 800, 300));
        lwDataDisplay->setFont(font);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 110, 61, 21));
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);
        leSwVer = new QLineEdit(centralwidget);
        leSwVer->setObjectName("leSwVer");
        leSwVer->setGeometry(QRect(70, 110, 60, 19));
        leSwVer->setAlignment(Qt::AlignmentFlag::AlignCenter);
        leSwVer->setReadOnly(true);
        leHwVer = new QLineEdit(centralwidget);
        leHwVer->setObjectName("leHwVer");
        leHwVer->setGeometry(QRect(70, 140, 60, 19));
        leHwVer->setAlignment(Qt::AlignmentFlag::AlignCenter);
        leHwVer->setReadOnly(true);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 140, 61, 21));
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 170, 61, 21));
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);
        leDeviceID = new QLineEdit(centralwidget);
        leDeviceID->setObjectName("leDeviceID");
        leDeviceID->setGeometry(QRect(70, 170, 60, 19));
        leDeviceID->setAlignment(Qt::AlignmentFlag::AlignCenter);
        leDeviceID->setReadOnly(true);
        leSTM32T = new QLineEdit(centralwidget);
        leSTM32T->setObjectName("leSTM32T");
        leSTM32T->setGeometry(QRect(70, 200, 60, 19));
        leSTM32T->setAlignment(Qt::AlignmentFlag::AlignCenter);
        leSTM32T->setReadOnly(true);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 200, 61, 21));
        label_8->setAlignment(Qt::AlignmentFlag::AlignCenter);
        leDHT11T = new QLineEdit(centralwidget);
        leDHT11T->setObjectName("leDHT11T");
        leDHT11T->setGeometry(QRect(70, 230, 60, 19));
        leDHT11T->setAlignment(Qt::AlignmentFlag::AlignCenter);
        leDHT11T->setReadOnly(true);
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(0, 230, 61, 21));
        label_9->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pbFactoryTest = new QPushButton(centralwidget);
        pbFactoryTest->setObjectName("pbFactoryTest");
        pbFactoryTest->setGeometry(QRect(150, 110, 81, 31));
        QFont font1;
        font1.setPointSize(9);
        pbFactoryTest->setFont(font1);
        pbFactoryTest->setIconSize(QSize(10, 10));
        pbFactoryTest->setCheckable(true);
        leIdChange = new QLineEdit(centralwidget);
        leIdChange->setObjectName("leIdChange");
        leIdChange->setGeometry(QRect(240, 150, 113, 31));
        pbChangeID = new QPushButton(centralwidget);
        pbChangeID->setObjectName("pbChangeID");
        pbChangeID->setGeometry(QRect(150, 150, 81, 31));
        pbChangeID->setFont(font1);
        pbChangeID->setIconSize(QSize(10, 10));
        pbChangeID->setCheckable(false);
        sLedSet = new QSlider(centralwidget);
        sLedSet->setObjectName("sLedSet");
        sLedSet->setGeometry(QRect(240, 190, 121, 21));
        sLedSet->setMaximum(100);
        sLedSet->setSingleStep(10);
        sLedSet->setTracking(false);
        sLedSet->setOrientation(Qt::Orientation::Horizontal);
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(160, 190, 61, 21));
        label_10->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pbEmptyDataDisplay = new QPushButton(centralwidget);
        pbEmptyDataDisplay->setObjectName("pbEmptyDataDisplay");
        pbEmptyDataDisplay->setGeometry(QRect(720, 240, 81, 31));
        pbEmptyDataDisplay->setFont(font1);
        pbEmptyDataDisplay->setIconSize(QSize(10, 10));
        pbEmptyDataDisplay->setCheckable(false);
        lb_LED1 = new QLabel(centralwidget);
        lb_LED1->setObjectName("lb_LED1");
        lb_LED1->setGeometry(QRect(195, 77, 31, 16));
        lb_LED2 = new QLabel(centralwidget);
        lb_LED2->setObjectName("lb_LED2");
        lb_LED2->setGeometry(QRect(750, 220, 31, 16));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(390, 120, 61, 21));
        label_11->setAlignment(Qt::AlignmentFlag::AlignCenter);
        CO_PPM = new QLineEdit(centralwidget);
        CO_PPM->setObjectName("CO_PPM");
        CO_PPM->setGeometry(QRect(450, 120, 60, 19));
        CO_PPM->setAlignment(Qt::AlignmentFlag::AlignCenter);
        CO_PPM->setReadOnly(true);
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(390, 150, 61, 21));
        label_12->setAlignment(Qt::AlignmentFlag::AlignCenter);
        CO_AD = new QLineEdit(centralwidget);
        CO_AD->setObjectName("CO_AD");
        CO_AD->setGeometry(QRect(450, 150, 60, 19));
        CO_AD->setAlignment(Qt::AlignmentFlag::AlignCenter);
        CO_AD->setReadOnly(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 19));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ZYdemo", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "CAN\350\256\276\347\275\256", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\345\271\266\345\220\257\345\212\250", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\345\244\215\344\275\215", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207\347\261\273\345\236\213", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207\347\264\242\345\274\225", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\223\345\217\267", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\350\275\257\344\273\266\347\211\210\346\234\254", nullptr));
        leHwVer->setText(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "\347\241\254\344\273\266\347\211\210\346\234\254", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207ID", nullptr));
        leDeviceID->setText(QString());
        leSTM32T->setText(QString());
        label_8->setText(QCoreApplication::translate("MainWindow", "STM32_T", nullptr));
        leDHT11T->setText(QString());
        label_9->setText(QCoreApplication::translate("MainWindow", "DHT11_T", nullptr));
        pbFactoryTest->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\220\257\345\267\245\345\216\202\346\265\213\350\257\225", nullptr));
        pbChangeID->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271ID", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "LED\344\272\256\345\272\246", nullptr));
        pbEmptyDataDisplay->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        lb_LED1->setText(QCoreApplication::translate("MainWindow", "LED1", nullptr));
        lb_LED2->setText(QCoreApplication::translate("MainWindow", "LED2", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "CO\346\265\223\345\272\246", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "COAD\345\200\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
