#include "paintwx.h"
#include <QPainter>
#include <QPen>
using namespace std;
#include <iostream>
#include <QPointF>

PaintWx::PaintWx(double target_height,double target_length,double mount_height,double v_distance)
{

    this->target_length= target_length;
    this ->target_height=target_height;
    this-> mount_height=mount_height;
    this ->v_distance=v_distance;
    resize(800, 600);
    setWindowTitle(tr("Paint Demo"));
}

void PaintWx::paintEvent(QPaintEvent *event)
{
        drawpcl(v_distance);
        return;

}

void  PaintWx::drawv()
{

    double W=800;
    double H=600;
    double ox=10;
    double oy=H-10;
    double xfactor=(W-ox*2)/v_distance;
    double vfactor=xfactor*floor(v_distance/target_height)/5;
    QPainter painter(this);
     painter.setPen(QPen(Qt::red));
    painter.drawLine(ox, oy, ox, oy-mount_height*vfactor);
    double targety=oy-target_height*vfactor;
    double my= oy-mount_height*vfactor;
    double targetx=ox+v_distance*xfactor;
    double targetendx=targetx+target_length*xfactor;

    painter.setPen(QPen(Qt::red));

    painter.drawLine(targetx,                                     oy,                                      targetx,                        targety);
    painter.drawLine(targetx,                                     targety,                                 targetendx,                     targety);
    painter.drawLine(targetendx,                                  targety,                                 targetendx,                     oy);
    painter.drawText(QPoint(targetendx,                           targety),
                     QString("L:"+QString::number(target_length)+"m H:"+QString::number(target_height))+"m");
    painter.setPen(QPen(Qt::gray));
    painter.drawLine(10, H-10, W, H-10);
    painter.setPen(QPen(Qt::blue));
    double dotsize=3.8;
    for ( QList<double>::iterator it=verlist.begin(); it != verlist.end(); it++)
    {
//          if((*it)<0)
//          {continue;}
        painter.drawLine(ox,                                     my,                                       ox+v_distance*xfactor,           oy-(*it)*vfactor);
        painter.fillRect(ox+v_distance*xfactor-dotsize/2,        oy-(*it)*vfactor-dotsize/2, dotsize,                                       dotsize, QBrush(Qt::darkYellow));
        painter.setPen(QPen(Qt::blue));
        painter.drawText(QPoint(ox+v_distance*xfactor,           oy-(*it)*vfactor), QString(QString::number(*it,10,1)+"m"));
        painter.setPen(QPen(Qt::gray));
    }

    for ( QList<double>::iterator it=dislist.begin(); it != dislist.end(); it++)
    {
//            painter.drawLine(ox,                                     my,                                      ox+(*it)*xfactor,                 oy);
        painter.fillRect(ox+(*it)*xfactor-dotsize/2,             oy-dotsize/2,               dotsize,                                       dotsize, QBrush(Qt::darkYellow));
        painter.setPen(QPen(Qt::blue));
        painter.drawText(QPoint( ox+(*it)*xfactor,               oy),                        QString(QString::number(*it,10,1)+"m"));
        painter.setPen(QPen(Qt::gray));
    }

}

void PaintWx::drawpcl(double distance)
{
    double W=800;
    double H=600;
    double ox=400;
    double oy=300;
    double margin=20;
    double factor=(H-oy-margin)/distance;
    QPainter painter(this);
    painter.setPen(QPen(Qt::green,1));
    double drawx;
    double drawy;
    double lastdrawx;
    double lastdrawy;
    cout<<drawx<<","<<drawy<<endl;

    cout.precision(6);

    for ( QList<LINE_ELLIPSE>::iterator it=pcl.begin(); it != pcl.end(); it++)
    {
        lastdrawx=-1e5;
        lastdrawy=-1e5;
        //cout<<"bg"<<endl;
        for ( QList<QPointF>::iterator it2=(*it).begin(); it2 != (*it).end(); it2++)
        {
            if(lastdrawy<-1e4)
            {
                lastdrawx=factor*(*it2).x()+ox;
                lastdrawy=factor*(*it2).y()+oy;

                continue;
            }
            drawx=factor*(*it2).x()+ox;
            drawy=factor*(*it2).y()+oy;
            //cout<<"last"<<lastdrawx<<","<<lastdrawy<<endl;
            //cout<<"curret"<<drawx<<","<<drawy<<endl;
            painter.drawPoint(QPointF(drawx,drawy));
            //painter.fillRect(drawx,       drawy, 1,                                       2, QBrush(Qt::darkYellow));
            //lastdrawx=drawx;
            //lastdrawy=drawy;
            //painter.drawLine(lastdrawx, lastdrawy, drawx, drawy);
        }
         //cout<<"--------------------------";
    }

}