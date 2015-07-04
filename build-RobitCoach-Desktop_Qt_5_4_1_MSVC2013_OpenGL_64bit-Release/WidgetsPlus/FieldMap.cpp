#include "FieldMap.h"
#include "QMouseEvent"


/*-------------------------------------------------------------------------------------------*/
 FieldMap::FieldMap(QWidget *parent) :
     QLabel(parent)
 {
     m_FieldDirection = false;  //to right
     m_ConnectReferee=false;
     m_ConnectCoach=false;
     m_CheckSelectAG=false;
     m_CheckSelectMoveTo=false;
     m_SetEPDone=false;
     m_SetEPStart=false;
     m_SelectID=0;
 }
/*-------------------------------------------------------------------------------------------*/





/*-------------------------------------------------------------------------------------------*/
 void FieldMap::inAgentData(Agent *AgentData)
 {
     m_LocalAgent = AgentData;
 }
/*-------------------------------------------------------------------------------------------*/




/*-------------------------------------------------------------------------------------------*/

 QPoint FieldMap::fieldRealToMap(QPoint inPos) //the size of the map is 492*345
 {
     QPoint out;
     out.setX(inPos.x()*400/1800 + 48);
     out.setY(inPos.y()*266/1200+39);

     if (m_FieldDirection == true)
     {
         out.setX(492 - out.x());
     }
     else
     {
         out.setY(345 - out.y());
     }
     return out;
 }

void FieldMap::setEnterPoint()
{
     m_SetEPStart=true;
     m_SetEPDone=false;
}
void FieldMap::setReferee(bool con)
{
     m_ConnectReferee=con;
}
 double FieldMap::calculateDis(QPoint pos1,QPoint pos2)
{
    return (pow(pos1.x()-pos2.x(),2)+pow(pos1.y()-pos2.y(),2));
}
void FieldMap::receiveStrategyInf(QString strategy)
{
    m_StrategyInf=strategy;
}
void FieldMap::eraseAll()
{
    m_CheckSelectMoveTo = false;
    m_CheckSelectAG=false;
    m_SelectID=0;
}

void FieldMap::inEliminationData(Ball *inBall, Obstacle *inObst)
{
    m_LocalBall = inBall;
    m_LocalObst = inObst;
}
/*-------------------------------------------------------------------------------------------*/





/*-------------------------------------------------------------------------------------------*/
//Mouse click event:
 void FieldMap::mousePressEvent(QMouseEvent *event)
 {
   QPoint mousePressCordinate;
     if( event->button()==Qt::LeftButton)//on left button
     {
       mousePressCordinate.setX(event->x()) ;//get the current pisition of the click;
       mousePressCordinate.setY(event->y()) ;
        if(!m_ConnectCoach)//haven't connect the coach
        {
            QPoint temp_posi;
            if(!m_CheckSelectAG)//haven't choos the agent
            {
                bool flag=false;
                for(int i=1;i<=AG_NUM;i++)
                {

                    temp_posi.setX(m_LocalAgent[i].GetPosition().GetX());
                    temp_posi.setY(m_LocalAgent[i].GetPosition().GetY());
                    if(m_LocalAgent[i].IsAgOnline()&&calculateDis(fieldRealToMap(temp_posi),mousePressCordinate)<64)
                    {
                       m_CheckSelectAG=true;
                       m_SelectID=m_LocalAgent[i].GetID();
                       flag=true;
                       break;
                    }
                }
                if(!flag)
                {
                    if(m_SetEPStart&&!m_SetEPDone)//is okay to start setting the enterpoint but haven't do it
                    {
                        m_EnterPoint=mousePressCordinate;
                        m_SetEPDone=true;
                        m_SetEPStart=false;
                    }
                }
            }
            else{
                for(int i=1;i<=AG_NUM;i++)
                {
                    temp_posi.setX(m_LocalAgent[i].GetPosition().GetX());
                    temp_posi.setY(m_LocalAgent[i].GetPosition().GetY());
                    if(m_LocalAgent[i].GetID()==m_SelectID)
                    {
                        if(m_LocalAgent[i].IsAgOnline()&&calculateDis(fieldRealToMap(temp_posi),mousePressCordinate)>64)
                        {
                            bool change=false;
                            for(int j=1;j<=AG_NUM;j++)
                            {
                                if(j!=i)
                                {
                                    temp_posi.setX(m_LocalAgent[j].GetPosition().GetX());
                                    temp_posi.setY(m_LocalAgent[j].GetPosition().GetY());
                                    if(calculateDis(fieldRealToMap(temp_posi),mousePressCordinate)<64)
                                    {
                                        m_SelectID=m_LocalAgent[j].GetID();
                                        change=true;
                                        m_CheckSelectMoveTo=false;
                                        break;
                                    }
                                }
                            }
                            if(change)
                                 break;
                            m_CheckSelectMoveTo=true;
                            m_MoveTO_Map=mousePressCordinate;                          
                            m_MoveTo_Real.setX((m_MoveTO_Map.x()-48)*1800/400);
                            m_MoveTo_Real.setY((m_MoveTO_Map.y()-39)*1200/266);
                            if(m_FieldDirection)
                            {
                                m_MoveTo_Real.setX(1800- m_MoveTo_Real.x());
                            }
                            else
                            {
                                m_MoveTo_Real.setY(1200- m_MoveTo_Real.y());
                            }
                           emit clickMove(m_MoveTo_Real.x(),m_MoveTo_Real.y(),m_SelectID);
                        }
                    }

                }

            }
        }

     }
    else if(event->button()==Qt::RightButton)
     {
         if(m_CheckSelectAG)
         {
             m_CheckSelectAG=false;
             m_SelectID=0;
             m_CheckSelectMoveTo=false;//haq:remain to be seen
         }
     }
 }
/*-------------------------------------------------------------------------------------------*/





 /*-------------------------------------------------------------------------------------------*/
void FieldMap::keyPressEvent(QKeyEvent *ev)
{

    if(ev->key()==Qt::Key_1||
       ev->key()==Qt::Key_2||
       ev->key()==Qt::Key_3||
       ev->key()==Qt::Key_4||
       ev->key()==Qt::Key_5||
       ev->key()==Qt::Key_6)
    {
        if(!m_CheckSelectAG)
            m_CheckSelectAG=true;
        m_SelectID=ev->key();
    }
    else if(ev->key()==Qt::Key_A)
    {
        if(m_CheckSelectAG)
            emit shootBall(m_SelectID);
    }
    else if(ev->key()==Qt::Key_S)
    {
        if(m_CheckSelectAG)
            emit stopAction(m_SelectID);
    }


}

 /*-------------------------------------------------------------------------------------------*/





/*-------------------------------------------------------------------------------------------*/

 void FieldMap::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);


    QPainter text_inf(this);//text on the map
    QFont font1;
    font1.setPixelSize(15);
    font1.setWeight(50);
    text_inf.setFont(font1);

    text_inf.setPen(QColor::fromRgb(152,0,0));//strategy information
    text_inf.drawText(205,15,m_StrategyInf);

    text_inf.setPen(QColor::fromRgb(255,255,0));//Enterpoint
    if(m_SetEPStart)
    {
        text_inf.drawText(400,330,"Set Entrance Point");
    }
    if(m_SetEPDone)
    {
        drawEP(m_EnterPoint);//draw the enterpoint
    }

    //if(m_ConnectReferee)
    //    referee.drawText(205,330,"裁判盒已连接");
    //else
    //    referee.drawText(210,330,"裁判盒未连接");

    for(int i=1;i<=AG_NUM;i++)
       if(m_LocalAgent[i].IsAgOnline())
       {
           QPoint temp_posi;
           temp_posi.setX(m_LocalAgent[i].GetPosition().GetX());
           temp_posi.setY(m_LocalAgent[i].GetPosition().GetY());
           drawOneAgent(fieldRealToMap(temp_posi),
                        m_LocalAgent[i].GetAngle(),
                        m_LocalAgent[i].GetStatus(),
                        m_LocalAgent[i].GetID(),m_SelectID);           //draw the agent

           if(m_LocalAgent[i].GetID()==m_SelectID&&m_CheckSelectMoveTo)
              //when the agent has been selected and is moving to the destination
           {
               if(calculateDis(temp_posi,m_MoveTo_Real)<400)//finish moving
               {
                   m_CheckSelectMoveTo=false;
               }
               if(m_CheckSelectMoveTo)
               {
                   drawLine(fieldRealToMap(temp_posi),m_MoveTO_Map);
               }
           }
           //if(Agent_haq[i].Found_ball)
           // drawball(fieldRealToMap(Agent_haq[i].Ball.Position),i);
           //for(int j=1;j<=AG_OBST_NUM;j++)
           //  if(Agent_haq[i].Obstacle[j].isValid)
           //    drawObstacle(fieldRealToMap(Agent_haq[i].Obstacle[j].Position),i);
       }
    QPoint temp_ball;
    temp_ball.setX(m_LocalBall->GetX());
    temp_ball.setY(m_LocalBall->GetY());
    temp_ball=fieldRealToMap(temp_ball);
    drawTrueBall(temp_ball);
    QPoint temp_obsta;
    for(int i=1;i<=10;i++)
    {
        if(!m_LocalObst[i].GetX()&&!m_LocalObst[i].GetY())
            break;
        temp_obsta.setX(m_LocalObst[i].GetX());
        temp_obsta.setY(m_LocalObst[i].GetY());
        drawMutiObstacle(fieldRealToMap(temp_obsta));
    }

}

/*-------------------------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------------------------*/

void FieldMap::setFieldDirection()
{
    if(m_FieldDirection == true)
      m_FieldDirection = false;
    else m_FieldDirection = true;
}

void FieldMap::drawOneAgent(QPoint pos,int angle, int status,int ID,int sele_ID)
{
    int step = 5;
    int radius = 8;
    int x = pos.x();
    int y = pos.y();
    QString outID = QString::number(ID,10);
    QString outStatus=QString::number(status,10);
    QPainter ag_painter(this);
    //--------Draw Direction---------
    ag_painter.setPen(QPen(QColor::fromRgb(252,75,137),4));
    if (m_FieldDirection == true)
    {
        ag_painter.drawLine(x,y,x-cos(angle*3.14/180)*(radius+6),y+sin(angle*3.14/180)*(radius+6));
    }
    else
    {
        ag_painter.drawLine(x,y,x+cos(angle*3.14/180)*(radius+6),y-sin(angle*3.14/180)*(radius+6));
    }


    //---------Draw Point------------
    if(sele_ID==ID)
       ag_painter.setPen(QPen(QColor::fromRgb(255,255,0),2));
    else ag_painter.setPen(QPen(QColor::fromRgb(0,127,255), 2));
    ag_painter.setBrush(QColor::fromRgb(0,127,255));
    ag_painter.drawEllipse(pos,radius,radius);

    //---------Tag Status------------
    QFont font;
    font.setPixelSize(15);
    ag_painter.setFont(font);
    ag_painter.setPen(QPen(Qt::black,15));
    pos.setX(x+step);
    pos.setY(y-step);
    ag_painter.drawText(pos,outStatus);

    //--------Tag ID------------
    font.setPixelSize(18);
    ag_painter.setFont(font);
    pos.setX(x-step);
    pos.setY(y+step+1);
    ag_painter.drawText(pos,outID);
}
void FieldMap::drawBall(QPoint pball,int ball_id)
{
    QPainter ball_painter(this);
    ball_painter.setBrush(QColor::fromRgb(255,155,0));
    ball_painter.drawEllipse(pball,7,7);
    QFont font2;
    font2.setPixelSize(15);
    ball_painter.setFont(font2);
    ball_painter.setPen(QPen(Qt::black, 10));
    QString outid = QString::number(ball_id,10);
    QPoint ball_number;
    ball_number.setX(pball.x()-4);
    ball_number.setY(pball.y()+5);
    ball_painter.drawText(ball_number,outid);
}
void FieldMap::drawTrueBall(QPoint trueball)
{
    QPainter trueball_painter(this);
    trueball_painter.setBrush(Qt::red);
    trueball_painter.drawEllipse(trueball,6,6);

}
void  FieldMap::drawObstacle(QPoint obsta_posi,int Obsta_owner)
{
    QPainter Obstacle_painter(this);
    Obstacle_painter.setBrush(Qt::black);
    QPoint rr;
    rr=obsta_posi;
    rr.setX( obsta_posi.x());
    rr.setY( obsta_posi.y());
    Obstacle_painter.drawEllipse(rr,8,8);
    QFont font2;
    font2.setPixelSize(15);
    Obstacle_painter.setFont(font2);
    Obstacle_painter.setPen(QPen(Qt::white, 10));
    QString outowner = QString::number(Obsta_owner,10);
    rr.setX( obsta_posi.x()-4);
    rr.setY( obsta_posi.y()+5);
    Obstacle_painter.drawText(rr,outowner);
}
void FieldMap::drawMutiObstacle(QPoint muti_obsta)
{
    QPainter bosta_painter(this);
    bosta_painter.setBrush(Qt::black);
    bosta_painter.drawEllipse(muti_obsta,8,8);
}

void FieldMap::drawLine(QPoint start_posi,QPoint end_posi)
{
    QPainter line(this);
    line.setPen(QColor::fromRgb(0,155,100));
    line.setPen(QPen(Qt::DashLine));
    //line.setPen(QPen(Qt::black,1));
    line.drawLine(start_posi,end_posi);
}
 void FieldMap::drawEP(QPoint EP_Position)
 {
     QPainter EP(this);
     EP.setPen(QPen(Qt::yellow,3));
     EP.drawLine(EP_Position.x()-8,EP_Position.y(),EP_Position.x()+8,EP_Position.y());
     EP.drawLine(EP_Position.x(),EP_Position.y()-8,EP_Position.x(),EP_Position.y()+8);

 }
/*-------------------------------------------------------------------------------------------*/
