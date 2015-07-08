#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_isFieldLeft2Right = true;               // set Field Left to right as default
    ui->label_FieldMap_R2L->setVisible(false);// hide another label

    ui->label_FieldMap->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_FieldMap->setStyleSheet("background:transparent");


    //initialize timer refresher
    GUIReresher = new QTimer(this);
    connect(GUIReresher,&QTimer::timeout,this,&MainWindow::refreshGUI);
    GUIReresher->setInterval(20);// refresh at a frequency of 50Hz(theoretically)
    GUIReresher->start();

    AgentOnlineChecker = new QTimer(this);
    connect(AgentOnlineChecker,&QTimer::timeout,this,&MainWindow::chekAgentOnlie);
    AgentOnlineChecker->setInterval(2000);
    AgentOnlineChecker->start();

    //initialize lable list for information presentation
    onlineLabelList <<ui->label_Agent_1_Online\
                    <<ui->label_Agent_1_Online<<ui->label_Agent_2_Online\
                    <<ui->label_Agent_3_Online<<ui->label_Agent_4_Online\
                    <<ui->label_Agent_5_Online<<ui->label_Agent_6_Online;

    ipEditList      <<ui->lineEdit_Agent_1_IP\
                    <<ui->lineEdit_Agent_1_IP<<ui->lineEdit_Agent_2_IP\
                    <<ui->lineEdit_Agent_3_IP<<ui->lineEdit_Agent_4_IP\
                    <<ui->lineEdit_Agent_5_IP<<ui->lineEdit_Agent_6_IP;

    statusEditList  <<ui->lineEdit_Agent_1_CurStatus\
                    <<ui->lineEdit_Agent_1_CurStatus<<ui->lineEdit_Agent_2_CurStatus\
                    <<ui->lineEdit_Agent_3_CurStatus<<ui->lineEdit_Agent_4_CurStatus\
                    <<ui->lineEdit_Agent_5_CurStatus<<ui->lineEdit_Agent_6_CurStatus;

    lapBatEditList  <<ui->lineEdit_Agent_1_LapBat\
                    <<ui->lineEdit_Agent_1_LapBat<<ui->lineEdit_Agent_2_LapBat\
                    <<ui->lineEdit_Agent_3_LapBat<<ui->lineEdit_Agent_4_LapBat\
                    <<ui->lineEdit_Agent_5_LapBat<<ui->lineEdit_Agent_6_LapBat;

    RobBatEditList  <<ui->lineEdit_Agent_1_AgBat\
                    <<ui->lineEdit_Agent_1_AgBat<<ui->lineEdit_Agent_2_AgBat\
                    <<ui->lineEdit_Agent_3_AgBat<<ui->lineEdit_Agent_4_AgBat\
                    <<ui->lineEdit_Agent_5_AgBat<<ui->lineEdit_Agent_6_AgBat;



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buildConnection(Agent *inAgent, CUDPDataHandling *inSender,ipCtrl *inCtrl,TCPRefClient *ref)
{
    m_Agent = inAgent;
    m_Sender= inSender;
    m_IpCtrl= inCtrl;
    ui->label_FieldMap->inAgentData(inAgent);
    m_Referee = ref;
}

void MainWindow::refreshGUI()
{
    ui->lineEdit_Status->setText(m_Referee->getStatusName());
    /// the code below is designed to refresh the mainwindow
    /// ------------------------------------------------
    for (int i  = 1 ; i <=AG_NUM; i++)
    {
        if (m_Agent[i].IsAgOnline())
        {
            onlineLabelList[i]->setPalette(Qt::green);
            ipEditList[i]    ->setText(QString::fromStdString(m_Agent[i].GetIP()));
            statusEditList[i]->setText(printAgentStatus(m_Agent[i].GetStatus()));
            lapBatEditList[i]->setText(QString::number(m_Agent[i].GetLaptopBattery(),10));
            RobBatEditList[i]->setText(QString::number(m_Agent[i].GetRobotVoltage(),10));
        }
        else
        {
            onlineLabelList[i]->setPalette(Qt::red);
            ipEditList[i]    ->setText("0.0.0.0");
            statusEditList[i]->setText("Off Line!");
            lapBatEditList[i]->setText("#");
            RobBatEditList[i]->setText("#");
        }
    }

    /// ------------------------------------------------
    /// code to refresh mainwindow ends here

    //*******************************************************************

    /// code designed to updholing the IP Control List
    /// ----------------------------------------------

    setTargetChecking();

    /// ----------------------------------------------
    /// ends here

    //**********************************************************************

    /// the code below is designed to refresh the map
    /// ------------------------------------------------

    ui->label_FieldMap->repaint();


    /// ------------------------------------------------
    /// code to refresh map ends here

    //*******************************************************************

    /// code below designed to eliminate balls and obstacle
    /// ---------------------------------------------------

    fieldInfoElimination();


    ///----------------------------------------------------
    ///  code ends here


}

QString MainWindow::printAgentStatus(AgentStatus inCode)
{
    //!!!wzc. this function needs to be finished

    switch (inCode) {
    case CTRL_ATTACK:
        return "Attack!";
        break;
    case CTRL_STOP:
        return "Stop!";
        break;
    case CTRL_GOALKEEP:
        return "GoalKeep";
        break;
    case ROBST_ERR:
        return "Stand By";
    case CTRL_MOVETO:
        return "MoveTo";
        break;
    default:
        return "UnDefined";
        break;
    }
}

void MainWindow::print(QString info)
{
    ui->textBrowser->insertPlainText(info+"\n");
}

void MainWindow::on_actionChange_Side_triggered()
{
    // side exchange;
    if (m_isFieldLeft2Right == true)
    {
        ui->label_FieldMap_L2R->setVisible(false);
        ui->label_FieldMap_R2L->setVisible(true);
        m_isFieldLeft2Right = false;
    }
    else
    {
        ui->label_FieldMap_L2R->setVisible(true);
        ui->label_FieldMap_R2L->setVisible(false);
        m_isFieldLeft2Right = true;
    }
    ui->label_FieldMap->setFieldDirection();
}

void MainWindow::setTargetChecking()
{
    for (int i = 1 ; i <= AG_NUM; i++)
    {
        if (m_IpCtrl[i].hasBeenSet == false)
        {
            m_Sender[i].SetTarget(m_IpCtrl[i].ip.c_str(),20090+i);
            m_IpCtrl[i].hasBeenSet = true;
        }
    }
}

void MainWindow::chekAgentOnlie()
{

    for (int i = 1; i<=AG_NUM;i++)
    {
        if (m_IpCtrl[i].isOnline == false)
        {
            m_Agent[i].SetIsOnline(false);
        }
        m_IpCtrl[i].isOnline = false;
    }
}


void MainWindow::on_pushButton_ConnectREF_clicked()
{
   // TEST_REFRESH();
    string tmpIP = ui->lineEdit_RefIP->text().toStdString();
    int port = 8686;
    emit setRefPara(tmpIP,port);
    m_Referee->SetIPPort((char*)tmpIP.c_str(),8686);
    m_Referee->Connectto((char*)tmpIP.c_str(),28097);
    m_Referee->SetSide(true);
}

void MainWindow::on_label_FieldMap_clickMove(int x, int y, int ID)
{
    m_Sender[ID].MoveCmd(x,y,0,0,false);
}

void MainWindow::on_actionEmergency_Stop_triggered()
{
    m_Referee->ManualSetStatus('S');
    for (int i = 1; i <= AG_NUM; i++)
    {
       m_Sender[i].CtrlCmd(CTRL_STOP,0,0,0,0,false);
    }
    ui->label_FieldMap->eraseAll();
    print("All STOP!!!!!!");
}

void MainWindow::initializeInfoElimination(Ball *inBall, Obstacle *inObst)
{
    m_BallEli = inBall;
    m_ObstEli = inObst;
    ui->label_FieldMap->inEliminationData(inBall,inObst);
}

void MainWindow::fieldInfoElimination()
{

    int tmpX;
    int tmpY;
    int tmpDst;
    int outID;
    int maxDst;
    bool foundflag = false;
    maxDst = 999999;
    tmpX = tmpY = 0;
    for (int i = 1; i <= AG_NUM; i++)
    {
        if (m_Agent[i].IsAgOnline() && m_Agent[i].GetStatus()!=ROBST_ERR)
        {
            foundflag = true;
            //ball --------
            tmpX = m_Agent[i].GetX() - m_Agent[i].GetBallInfo().GetX();
            tmpY = m_Agent[i].GetY() - m_Agent[i].GetBallInfo().GetY();
            tmpDst = tmpX*tmpX + tmpY*tmpY;
            if (tmpDst < maxDst)
            {
                maxDst = tmpDst;
                outID = i;
            }
            //Obstacle--------
            //TODO:```````````

        }
    }

    if (!foundflag)
    {
        m_BallEli->SetOwner(-1);
        m_BallEli->SetPosition(0,0);
    }
    else
    {
        m_BallEli->SetPosition(m_Agent[outID].GetBallInfo().GetX(),
                           m_Agent[outID].GetBallInfo().GetY());
        m_BallEli->SetIsUpdated(true);
        m_BallEli->SetOwner(outID);
    }

    m_ObstEli[0].SetPosition(0,0);
}


void MainWindow::on_label_FieldMap_stopAction(int ID)
{
    //select an agent and make it stop
    m_Sender[ID].CtrlCmd(CTRL_STOP,0,0,0,0,false);

}

void MainWindow::on_label_FieldMap_shootBall(int ID)
{
    //select an agent and make it do attack action
    //!!!!!!!!!!ATTENTION!!!!!!!!!!!!!!!!
    /// parameter inbField stands for the attack direction , it remains undesigned
    m_Sender[ID].CtrlCmd(CTRL_ATTACK,1800,600,0,0,false);
}

void MainWindow::on_pushButton_KickOff_clicked()
{
    //on_label_FieldMap_shootBall(4);
    m_Referee->SetSide(true);

    m_Referee->ManualSetStatus('K');
}

void MainWindow::on_actionAttack_Action_triggered()
{
    int id = ui->label_FieldMap->getSelectedAgent();
    if (id <=0 || id >6)
    {
        return ;
    }
    on_label_FieldMap_shootBall(id);
    print("Select "+QString::number(id,10)+" To Attack!");
}

void MainWindow::on_actionStop_One_Agent_triggered()
{
    int id = ui->label_FieldMap->getSelectedAgent();
    if (id <=0 || id >6)
    {
        return ;
    }
    on_label_FieldMap_stopAction(id);
    print("Selected "+QString::number(id,10)+" Stopped!");
}

void MainWindow::on_pushButton_FreeKick_clicked()
{
    m_Referee->ManualSetStatus('F');
}

void MainWindow::on_pushButton_Start_clicked()
{
    m_Referee->ManualSetStatus('s');
}

void MainWindow::on_pushButton_CornerKick_clicked()
{
    m_Referee->ManualSetStatus('C');
}

void MainWindow::on_pushButton_GoalKick_clicked()
{
    m_Referee->ManualSetStatus('G');
}

void MainWindow::on_pushButton_Throwin_clicked()
{
    m_Referee->ManualSetStatus('T');
}

void MainWindow::on_pushButton_Dropball_clicked()
{
    m_Referee->ManualSetStatus('N');
}
