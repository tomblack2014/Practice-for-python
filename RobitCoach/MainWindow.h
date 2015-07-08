#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/******************************************************************************************************
//-----------------------------------------------------------------------------------------------------
//Author       ：Wang ZiCheng @ Robit @ BeiJing Institute Of Technology     wzcizyq@hotmail.com      *|
//               ->[wzc] for short will be used in this project                                      *|
//Time         ：2015-3-14                                                                           *|
//Header File  ：MainWindow.h                                                                        *|
//Declaration  ：                                                                                    *|
//               1.Declaration of the MainWindow class                                               *|                                                       *|
//Source File  ：MainWindow.cpp                                                                      *|
//-----------------------------------------------------------------------------------------------------
//****************************************************************************************************/







#include "Ref/TCPRefClient.h"

#include <QMainWindow>
#include <QTimer>
#include <QLineEdit>
#include "WidgetsPlus/FieldMap.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //get vital communication relevant parameters outside the class
    void buildConnection(Agent *inAgent, CUDPDataHandling *inSender,ipCtrl *inCtrl, TCPRefClient *ref);
    void initializeInfoElimination(Ball *inBall, Obstacle *Obstacle);
    void refreshGUI();    // redraw the GUI;


signals:
    void setRefPara(string ip,int port);

private slots:

/// private class member variables will be defined below
/// ****************************************************
    void on_actionChange_Side_triggered();

    void on_pushButton_ConnectREF_clicked();

    void on_label_FieldMap_clickMove(int x,int y,int ID);
    void on_label_FieldMap_stopAction(int ID);
    void on_label_FieldMap_shootBall(int ID);

    void on_actionEmergency_Stop_triggered();

    void on_pushButton_KickOff_clicked();

    void on_actionAttack_Action_triggered();

    void on_actionStop_One_Agent_triggered();

    void on_pushButton_FreeKick_clicked();

    void on_pushButton_Start_clicked();

    void on_pushButton_CornerKick_clicked();

    void on_pushButton_GoalKick_clicked();

    void on_pushButton_Throwin_clicked();

    void on_pushButton_Dropball_clicked();

private:
    Ui::MainWindow *ui;

    //Field Direction Control
    bool m_isFieldLeft2Right;

    //all of the agent info, in the form of array
    Agent *m_Agent;

    // agent IP management , in the form of array
    CUDPDataHandling *m_Sender;
    TCPRefClient     *m_Referee;
    ipCtrl           *m_IpCtrl;
    int               checkCnt[AG_NUM+1];


    // define GUI refresher
    QTimer *GUIReresher;
    QTimer *AgentOnlineChecker;

    // GUI widgets array
    QList<QLabel *> onlineLabelList;
    QList<QLineEdit *> ipEditList;
    QList<QLineEdit *> statusEditList;
    QList<QLineEdit *> lapBatEditList;
    QList<QLineEdit *> RobBatEditList;

    //Eliminated infomation
    Ball     *m_BallEli;
    Obstacle *m_ObstEli;

///****************************************************



/// private class member functions will be defined below
private:

    QString printAgentStatus(AgentStatus inCode); //designed to show agent status in string
    void print(QString info);
    void setTargetChecking();
    void chekAgentOnlie();
    void fieldInfoElimination();
};

#endif // MAINWINDOW_H
