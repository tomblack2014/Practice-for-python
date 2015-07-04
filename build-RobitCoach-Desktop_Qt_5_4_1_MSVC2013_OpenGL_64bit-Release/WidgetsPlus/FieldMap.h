#ifndef QLABELMAP_H
#define QLABELMAP_H
#include <QLabel>
#include <QPainter>
#include <QPaintEngine>
#include <qpaintdevice.h>
#include <math.h>
#include "DataLayer/UDPDataHandling.h"
#include <QDebug>
#include <QKeyEvent>
class FieldMap : public QLabel
{
    Q_OBJECT
public:
    explicit FieldMap(QWidget *parent = 0);
    void setReferee(bool con);                          //SetReferee
    void setFieldDirection();
    void getMoveTo();
    void setEnterPoint();
    void inAgentData(Agent *AgentData);
    void receiveStrategyInf(QString strategy);
    void inEliminationData(Ball *inBall, Obstacle *Obst);
    void eraseAll();

protected:
     void paintEvent(QPaintEvent *event);
     void mousePressEvent(QMouseEvent *event);
     void keyPressEvent(QKeyEvent *ev);
private:
     //成员变量
     Agent *m_LocalAgent;
     Ball  *m_LocalBall;                               //Ball info, in the form of array
     Obstacle *m_LocalObst;                            //Obstacle info , m_LocalObst[10]; const int MAX_OBST_NUM_INFIELD = 10;

     bool m_CheckSelectAG;                             //whether there is a agent to be selected
     bool m_CheckSelectMoveTo;                         //whether the ending position has been selected
     bool m_ConnectReferee;                            //whether the referee has been connected
     bool m_ConnectCoach;                              //whether the agent has connected to the coach
     int m_SelectID;                                   //the ID of the selected agent
     QPoint m_MoveTO_Map;                              //the final position on the map
     QPoint m_MoveTo_Real;                             //the final position on the real field
     bool m_FieldDirection;                            //the field's direction
     bool m_SetEPStart;                                //ready to set the enterpoint
     bool m_SetEPDone;                                 //the enterpoint has been set
     QPixmap m_FieldPicture;
     QPoint m_EnterPoint;
     QString m_StrategyInf;
     //成员函数
     QPoint fieldRealToMap(QPoint inPos);

     void drawField();
     void drawOneAgent(QPoint pos,int angle,int status,int ID,int sele_ID);
     void drawTrueBall(QPoint trueball);
     void drawBall(QPoint pball,int ball_id);
     void drawMutiObstacle(QPoint muti_obsta);
     void drawObstacle(QPoint obsta_posi,int Obsta_owner);
     void drawLine(QPoint start_posi,QPoint end_posi);
     double calculateDis(QPoint pos1,QPoint pos2);
     void drawEP(QPoint EP_Position);
signals:
    void clickMove(int x,int y,int ID);
    void shootBall(int ID);
    void stopAction(int ID);
public slots:
};

#endif // QLABELMAP_H
