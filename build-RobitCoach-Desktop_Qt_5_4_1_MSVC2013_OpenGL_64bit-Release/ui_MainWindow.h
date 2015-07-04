/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <WidgetsPlus/FieldMap.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionEmergency_Stop;
    QAction *actionChange_Side;
    QAction *actionAttack_Action;
    QAction *actionStop_One_Agent;
    QWidget *centralWidget;
    QLabel *label_FieldMap_R2L;
    QLabel *label_FieldMap_L2R;
    QLabel *label;
    QLabel *label_Agent_1_Online;
    QLineEdit *lineEdit_Agent_1_IP;
    QLineEdit *lineEdit_Agent_1_LapBat;
    QLineEdit *lineEdit_Agent_1_AgBat;
    QLabel *label_2;
    QLabel *label_Agent_2_Online;
    QLineEdit *lineEdit_Agent_2_LapBat;
    QLineEdit *lineEdit_Agent_2_IP;
    QLineEdit *lineEdit_Agent_2_AgBat;
    QLabel *label_3;
    QLabel *label_Agent_3_Online;
    QLineEdit *lineEdit_Agent_3_LapBat;
    QLineEdit *lineEdit_Agent_3_IP;
    QLineEdit *lineEdit_Agent_3_AgBat;
    QLabel *label_4;
    QLabel *label_Agent_4_Online;
    QLineEdit *lineEdit_Agent_4_LapBat;
    QLineEdit *lineEdit_Agent_4_IP;
    QLineEdit *lineEdit_Agent_4_AgBat;
    QLabel *label_5;
    QLabel *label_Agent_5_Online;
    QLineEdit *lineEdit_Agent_5_LapBat;
    QLineEdit *lineEdit_Agent_5_IP;
    QLineEdit *lineEdit_Agent_5_AgBat;
    QLineEdit *lineEdit_Agent_1_CurStatus;
    QLineEdit *lineEdit_Agent_2_CurStatus;
    QLineEdit *lineEdit_Agent_3_CurStatus;
    QLineEdit *lineEdit_Agent_4_CurStatus;
    QLineEdit *lineEdit_Agent_5_CurStatus;
    QLabel *label_1;
    QLineEdit *lineEdit_Agent_6_LapBat;
    QLineEdit *lineEdit_Agent_6_AgBat;
    QLineEdit *lineEdit_Agent_6_IP;
    QLineEdit *lineEdit_Agent_6_CurStatus;
    QLabel *label_Agent_6_Online;
    QTextBrowser *textBrowser;
    QLabel *label_sideTag;
    QLineEdit *lineEdit_RefIP;
    QPushButton *pushButton_ConnectREF;
    QPushButton *pushButton_KickOff;
    QPushButton *pushButton_FreeKick;
    QPushButton *pushButton_CornerKick;
    QPushButton *pushButton_GoalKick;
    FieldMap *label_FieldMap;
    QLineEdit *lineEdit_Status;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuOption;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(841, 594);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionEmergency_Stop = new QAction(MainWindow);
        actionEmergency_Stop->setObjectName(QStringLiteral("actionEmergency_Stop"));
        actionChange_Side = new QAction(MainWindow);
        actionChange_Side->setObjectName(QStringLiteral("actionChange_Side"));
        actionAttack_Action = new QAction(MainWindow);
        actionAttack_Action->setObjectName(QStringLiteral("actionAttack_Action"));
        actionStop_One_Agent = new QAction(MainWindow);
        actionStop_One_Agent->setObjectName(QStringLiteral("actionStop_One_Agent"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_FieldMap_R2L = new QLabel(centralWidget);
        label_FieldMap_R2L->setObjectName(QStringLiteral("label_FieldMap_R2L"));
        label_FieldMap_R2L->setGeometry(QRect(120, 20, 492, 345));
        label_FieldMap_R2L->setFrameShape(QFrame::Panel);
        label_FieldMap_R2L->setPixmap(QPixmap(QString::fromUtf8(":/Image/Config/R2LFullField.bmp")));
        label_FieldMap_L2R = new QLabel(centralWidget);
        label_FieldMap_L2R->setObjectName(QStringLiteral("label_FieldMap_L2R"));
        label_FieldMap_L2R->setGeometry(QRect(120, 20, 492, 345));
        label_FieldMap_L2R->setFrameShape(QFrame::Panel);
        label_FieldMap_L2R->setPixmap(QPixmap(QString::fromUtf8(":/Image/Config/L2RFullField.bmp")));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 410, 51, 21));
        label_Agent_1_Online = new QLabel(centralWidget);
        label_Agent_1_Online->setObjectName(QStringLiteral("label_Agent_1_Online"));
        label_Agent_1_Online->setGeometry(QRect(80, 411, 31, 20));
        label_Agent_1_Online->setAutoFillBackground(true);
        label_Agent_1_Online->setFrameShape(QFrame::Panel);
        lineEdit_Agent_1_IP = new QLineEdit(centralWidget);
        lineEdit_Agent_1_IP->setObjectName(QStringLiteral("lineEdit_Agent_1_IP"));
        lineEdit_Agent_1_IP->setGeometry(QRect(20, 440, 91, 20));
        lineEdit_Agent_1_IP->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_1_IP->setReadOnly(true);
        lineEdit_Agent_1_LapBat = new QLineEdit(centralWidget);
        lineEdit_Agent_1_LapBat->setObjectName(QStringLiteral("lineEdit_Agent_1_LapBat"));
        lineEdit_Agent_1_LapBat->setGeometry(QRect(20, 501, 41, 20));
        lineEdit_Agent_1_LapBat->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_1_LapBat->setReadOnly(true);
        lineEdit_Agent_1_AgBat = new QLineEdit(centralWidget);
        lineEdit_Agent_1_AgBat->setObjectName(QStringLiteral("lineEdit_Agent_1_AgBat"));
        lineEdit_Agent_1_AgBat->setGeometry(QRect(70, 501, 41, 20));
        lineEdit_Agent_1_AgBat->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_1_AgBat->setReadOnly(true);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(160, 410, 51, 21));
        label_Agent_2_Online = new QLabel(centralWidget);
        label_Agent_2_Online->setObjectName(QStringLiteral("label_Agent_2_Online"));
        label_Agent_2_Online->setGeometry(QRect(220, 411, 31, 20));
        label_Agent_2_Online->setAutoFillBackground(true);
        label_Agent_2_Online->setFrameShape(QFrame::Panel);
        lineEdit_Agent_2_LapBat = new QLineEdit(centralWidget);
        lineEdit_Agent_2_LapBat->setObjectName(QStringLiteral("lineEdit_Agent_2_LapBat"));
        lineEdit_Agent_2_LapBat->setGeometry(QRect(160, 501, 41, 20));
        lineEdit_Agent_2_LapBat->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_2_LapBat->setReadOnly(true);
        lineEdit_Agent_2_IP = new QLineEdit(centralWidget);
        lineEdit_Agent_2_IP->setObjectName(QStringLiteral("lineEdit_Agent_2_IP"));
        lineEdit_Agent_2_IP->setGeometry(QRect(160, 440, 91, 20));
        lineEdit_Agent_2_IP->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_2_IP->setReadOnly(true);
        lineEdit_Agent_2_AgBat = new QLineEdit(centralWidget);
        lineEdit_Agent_2_AgBat->setObjectName(QStringLiteral("lineEdit_Agent_2_AgBat"));
        lineEdit_Agent_2_AgBat->setGeometry(QRect(210, 501, 41, 20));
        lineEdit_Agent_2_AgBat->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_2_AgBat->setReadOnly(true);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(300, 410, 51, 21));
        label_Agent_3_Online = new QLabel(centralWidget);
        label_Agent_3_Online->setObjectName(QStringLiteral("label_Agent_3_Online"));
        label_Agent_3_Online->setGeometry(QRect(360, 411, 31, 20));
        label_Agent_3_Online->setAutoFillBackground(true);
        label_Agent_3_Online->setFrameShape(QFrame::Panel);
        lineEdit_Agent_3_LapBat = new QLineEdit(centralWidget);
        lineEdit_Agent_3_LapBat->setObjectName(QStringLiteral("lineEdit_Agent_3_LapBat"));
        lineEdit_Agent_3_LapBat->setGeometry(QRect(300, 501, 41, 20));
        lineEdit_Agent_3_LapBat->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_3_LapBat->setReadOnly(true);
        lineEdit_Agent_3_IP = new QLineEdit(centralWidget);
        lineEdit_Agent_3_IP->setObjectName(QStringLiteral("lineEdit_Agent_3_IP"));
        lineEdit_Agent_3_IP->setGeometry(QRect(300, 440, 91, 20));
        lineEdit_Agent_3_IP->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_3_IP->setReadOnly(true);
        lineEdit_Agent_3_AgBat = new QLineEdit(centralWidget);
        lineEdit_Agent_3_AgBat->setObjectName(QStringLiteral("lineEdit_Agent_3_AgBat"));
        lineEdit_Agent_3_AgBat->setGeometry(QRect(350, 501, 41, 20));
        lineEdit_Agent_3_AgBat->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_3_AgBat->setReadOnly(true);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(440, 410, 51, 21));
        label_Agent_4_Online = new QLabel(centralWidget);
        label_Agent_4_Online->setObjectName(QStringLiteral("label_Agent_4_Online"));
        label_Agent_4_Online->setGeometry(QRect(500, 411, 31, 20));
        label_Agent_4_Online->setAutoFillBackground(true);
        label_Agent_4_Online->setFrameShape(QFrame::Panel);
        lineEdit_Agent_4_LapBat = new QLineEdit(centralWidget);
        lineEdit_Agent_4_LapBat->setObjectName(QStringLiteral("lineEdit_Agent_4_LapBat"));
        lineEdit_Agent_4_LapBat->setGeometry(QRect(440, 501, 41, 20));
        lineEdit_Agent_4_LapBat->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_4_LapBat->setReadOnly(true);
        lineEdit_Agent_4_IP = new QLineEdit(centralWidget);
        lineEdit_Agent_4_IP->setObjectName(QStringLiteral("lineEdit_Agent_4_IP"));
        lineEdit_Agent_4_IP->setGeometry(QRect(440, 440, 91, 20));
        lineEdit_Agent_4_IP->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_4_IP->setReadOnly(true);
        lineEdit_Agent_4_AgBat = new QLineEdit(centralWidget);
        lineEdit_Agent_4_AgBat->setObjectName(QStringLiteral("lineEdit_Agent_4_AgBat"));
        lineEdit_Agent_4_AgBat->setGeometry(QRect(490, 501, 41, 20));
        lineEdit_Agent_4_AgBat->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_4_AgBat->setReadOnly(true);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(580, 410, 51, 21));
        label_Agent_5_Online = new QLabel(centralWidget);
        label_Agent_5_Online->setObjectName(QStringLiteral("label_Agent_5_Online"));
        label_Agent_5_Online->setGeometry(QRect(640, 411, 31, 20));
        label_Agent_5_Online->setAutoFillBackground(true);
        label_Agent_5_Online->setFrameShape(QFrame::Panel);
        lineEdit_Agent_5_LapBat = new QLineEdit(centralWidget);
        lineEdit_Agent_5_LapBat->setObjectName(QStringLiteral("lineEdit_Agent_5_LapBat"));
        lineEdit_Agent_5_LapBat->setGeometry(QRect(580, 501, 41, 20));
        lineEdit_Agent_5_LapBat->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_5_LapBat->setReadOnly(true);
        lineEdit_Agent_5_IP = new QLineEdit(centralWidget);
        lineEdit_Agent_5_IP->setObjectName(QStringLiteral("lineEdit_Agent_5_IP"));
        lineEdit_Agent_5_IP->setGeometry(QRect(580, 440, 91, 20));
        lineEdit_Agent_5_IP->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_5_IP->setReadOnly(true);
        lineEdit_Agent_5_AgBat = new QLineEdit(centralWidget);
        lineEdit_Agent_5_AgBat->setObjectName(QStringLiteral("lineEdit_Agent_5_AgBat"));
        lineEdit_Agent_5_AgBat->setGeometry(QRect(630, 501, 41, 20));
        lineEdit_Agent_5_AgBat->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_5_AgBat->setReadOnly(true);
        lineEdit_Agent_1_CurStatus = new QLineEdit(centralWidget);
        lineEdit_Agent_1_CurStatus->setObjectName(QStringLiteral("lineEdit_Agent_1_CurStatus"));
        lineEdit_Agent_1_CurStatus->setGeometry(QRect(20, 471, 91, 20));
        lineEdit_Agent_1_CurStatus->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_1_CurStatus->setReadOnly(true);
        lineEdit_Agent_2_CurStatus = new QLineEdit(centralWidget);
        lineEdit_Agent_2_CurStatus->setObjectName(QStringLiteral("lineEdit_Agent_2_CurStatus"));
        lineEdit_Agent_2_CurStatus->setGeometry(QRect(160, 471, 91, 20));
        lineEdit_Agent_2_CurStatus->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_2_CurStatus->setReadOnly(true);
        lineEdit_Agent_3_CurStatus = new QLineEdit(centralWidget);
        lineEdit_Agent_3_CurStatus->setObjectName(QStringLiteral("lineEdit_Agent_3_CurStatus"));
        lineEdit_Agent_3_CurStatus->setGeometry(QRect(300, 471, 91, 20));
        lineEdit_Agent_3_CurStatus->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_3_CurStatus->setReadOnly(true);
        lineEdit_Agent_4_CurStatus = new QLineEdit(centralWidget);
        lineEdit_Agent_4_CurStatus->setObjectName(QStringLiteral("lineEdit_Agent_4_CurStatus"));
        lineEdit_Agent_4_CurStatus->setGeometry(QRect(440, 471, 91, 20));
        lineEdit_Agent_4_CurStatus->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_4_CurStatus->setReadOnly(true);
        lineEdit_Agent_5_CurStatus = new QLineEdit(centralWidget);
        lineEdit_Agent_5_CurStatus->setObjectName(QStringLiteral("lineEdit_Agent_5_CurStatus"));
        lineEdit_Agent_5_CurStatus->setGeometry(QRect(580, 471, 91, 20));
        lineEdit_Agent_5_CurStatus->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_5_CurStatus->setReadOnly(true);
        label_1 = new QLabel(centralWidget);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setGeometry(QRect(720, 409, 51, 21));
        lineEdit_Agent_6_LapBat = new QLineEdit(centralWidget);
        lineEdit_Agent_6_LapBat->setObjectName(QStringLiteral("lineEdit_Agent_6_LapBat"));
        lineEdit_Agent_6_LapBat->setGeometry(QRect(720, 500, 41, 20));
        lineEdit_Agent_6_LapBat->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_6_LapBat->setReadOnly(true);
        lineEdit_Agent_6_AgBat = new QLineEdit(centralWidget);
        lineEdit_Agent_6_AgBat->setObjectName(QStringLiteral("lineEdit_Agent_6_AgBat"));
        lineEdit_Agent_6_AgBat->setGeometry(QRect(770, 500, 41, 20));
        lineEdit_Agent_6_AgBat->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_6_AgBat->setReadOnly(true);
        lineEdit_Agent_6_IP = new QLineEdit(centralWidget);
        lineEdit_Agent_6_IP->setObjectName(QStringLiteral("lineEdit_Agent_6_IP"));
        lineEdit_Agent_6_IP->setGeometry(QRect(720, 439, 91, 20));
        lineEdit_Agent_6_IP->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_6_IP->setReadOnly(true);
        lineEdit_Agent_6_CurStatus = new QLineEdit(centralWidget);
        lineEdit_Agent_6_CurStatus->setObjectName(QStringLiteral("lineEdit_Agent_6_CurStatus"));
        lineEdit_Agent_6_CurStatus->setGeometry(QRect(720, 470, 91, 20));
        lineEdit_Agent_6_CurStatus->setAlignment(Qt::AlignCenter);
        lineEdit_Agent_6_CurStatus->setReadOnly(true);
        label_Agent_6_Online = new QLabel(centralWidget);
        label_Agent_6_Online->setObjectName(QStringLiteral("label_Agent_6_Online"));
        label_Agent_6_Online->setGeometry(QRect(780, 410, 31, 20));
        label_Agent_6_Online->setAutoFillBackground(true);
        label_Agent_6_Online->setFrameShape(QFrame::Panel);
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(630, 21, 181, 341));
        label_sideTag = new QLabel(centralWidget);
        label_sideTag->setObjectName(QStringLiteral("label_sideTag"));
        label_sideTag->setGeometry(QRect(10, 60, 91, 31));
        label_sideTag->setFrameShape(QFrame::Panel);
        lineEdit_RefIP = new QLineEdit(centralWidget);
        lineEdit_RefIP->setObjectName(QStringLiteral("lineEdit_RefIP"));
        lineEdit_RefIP->setGeometry(QRect(10, 100, 91, 20));
        pushButton_ConnectREF = new QPushButton(centralWidget);
        pushButton_ConnectREF->setObjectName(QStringLiteral("pushButton_ConnectREF"));
        pushButton_ConnectREF->setGeometry(QRect(10, 130, 91, 23));
        pushButton_KickOff = new QPushButton(centralWidget);
        pushButton_KickOff->setObjectName(QStringLiteral("pushButton_KickOff"));
        pushButton_KickOff->setGeometry(QRect(10, 200, 91, 23));
        pushButton_FreeKick = new QPushButton(centralWidget);
        pushButton_FreeKick->setObjectName(QStringLiteral("pushButton_FreeKick"));
        pushButton_FreeKick->setGeometry(QRect(10, 240, 91, 23));
        pushButton_CornerKick = new QPushButton(centralWidget);
        pushButton_CornerKick->setObjectName(QStringLiteral("pushButton_CornerKick"));
        pushButton_CornerKick->setGeometry(QRect(10, 280, 91, 23));
        pushButton_GoalKick = new QPushButton(centralWidget);
        pushButton_GoalKick->setObjectName(QStringLiteral("pushButton_GoalKick"));
        pushButton_GoalKick->setGeometry(QRect(10, 320, 91, 23));
        label_FieldMap = new FieldMap(centralWidget);
        label_FieldMap->setObjectName(QStringLiteral("label_FieldMap"));
        label_FieldMap->setGeometry(QRect(120, 20, 492, 345));
        label_FieldMap->setFrameShape(QFrame::Panel);
        lineEdit_Status = new QLineEdit(centralWidget);
        lineEdit_Status->setObjectName(QStringLiteral("lineEdit_Status"));
        lineEdit_Status->setGeometry(QRect(320, 20, 91, 20));
        lineEdit_Status->setAlignment(Qt::AlignCenter);
        lineEdit_Status->setReadOnly(true);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 841, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menuOption = new QMenu(menuBar);
        menuOption->setObjectName(QStringLiteral("menuOption"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuOption->menuAction());
        menu->addAction(actionExit);
        menuOption->addAction(actionEmergency_Stop);
        menuOption->addAction(actionChange_Side);
        menuOption->addAction(actionAttack_Action);
        menuOption->addAction(actionStop_One_Agent);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionEmergency_Stop->setText(QApplication::translate("MainWindow", "Emergency Stop", 0));
        actionEmergency_Stop->setShortcut(QApplication::translate("MainWindow", "Space", 0));
        actionChange_Side->setText(QApplication::translate("MainWindow", "Change Side", 0));
        actionAttack_Action->setText(QApplication::translate("MainWindow", "Attack Action", 0));
        actionAttack_Action->setShortcut(QApplication::translate("MainWindow", "A", 0));
        actionStop_One_Agent->setText(QApplication::translate("MainWindow", "Stop One Agent", 0));
        actionStop_One_Agent->setShortcut(QApplication::translate("MainWindow", "S", 0));
        label_FieldMap_R2L->setText(QString());
        label_FieldMap_L2R->setText(QString());
        label->setText(QApplication::translate("MainWindow", " Agent 1:", 0));
        label_Agent_1_Online->setText(QString());
        lineEdit_Agent_1_IP->setText(QApplication::translate("MainWindow", "192.168.1.0", 0));
        lineEdit_Agent_1_LapBat->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_Agent_1_AgBat->setText(QApplication::translate("MainWindow", "0", 0));
        label_2->setText(QApplication::translate("MainWindow", " Agent 2:", 0));
        label_Agent_2_Online->setText(QString());
        lineEdit_Agent_2_LapBat->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_Agent_2_IP->setText(QApplication::translate("MainWindow", "192.168.1.0", 0));
        lineEdit_Agent_2_AgBat->setText(QApplication::translate("MainWindow", "0", 0));
        label_3->setText(QApplication::translate("MainWindow", " Agent 3:", 0));
        label_Agent_3_Online->setText(QString());
        lineEdit_Agent_3_LapBat->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_Agent_3_IP->setText(QApplication::translate("MainWindow", "192.168.1.0", 0));
        lineEdit_Agent_3_AgBat->setText(QApplication::translate("MainWindow", "0", 0));
        label_4->setText(QApplication::translate("MainWindow", " Agent 4:", 0));
        label_Agent_4_Online->setText(QString());
        lineEdit_Agent_4_LapBat->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_Agent_4_IP->setText(QApplication::translate("MainWindow", "192.168.1.0", 0));
        lineEdit_Agent_4_AgBat->setText(QApplication::translate("MainWindow", "0", 0));
        label_5->setText(QApplication::translate("MainWindow", " Agent 5:", 0));
        label_Agent_5_Online->setText(QString());
        lineEdit_Agent_5_LapBat->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_Agent_5_IP->setText(QApplication::translate("MainWindow", "192.168.1.0", 0));
        lineEdit_Agent_5_AgBat->setText(QApplication::translate("MainWindow", "0", 0));
        label_1->setText(QApplication::translate("MainWindow", " Agent 6:", 0));
        lineEdit_Agent_6_LapBat->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_Agent_6_AgBat->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_Agent_6_IP->setText(QApplication::translate("MainWindow", "192.168.1.0", 0));
        label_Agent_6_Online->setText(QString());
        label_sideTag->setText(QApplication::translate("MainWindow", "sideTag", 0));
        pushButton_ConnectREF->setText(QApplication::translate("MainWindow", "Connet REF", 0));
        pushButton_KickOff->setText(QApplication::translate("MainWindow", "m_KickOff", 0));
        pushButton_FreeKick->setText(QApplication::translate("MainWindow", "m_FreeKick", 0));
        pushButton_CornerKick->setText(QApplication::translate("MainWindow", "m_CornerKick", 0));
        pushButton_GoalKick->setText(QApplication::translate("MainWindow", "m_GoalKick", 0));
        label_FieldMap->setText(QString());
        menu->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuOption->setTitle(QApplication::translate("MainWindow", "Option", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
