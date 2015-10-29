#include "rail.h"
#include <iostream>
#define PI 3.1415


StraightRail::StraightRail(QPointF start, double startAngle, int length, QGraphicsScene &scene)
{    
    int i;
    beginn.reset(new StraightPiece(start,startAngle,scene));

    std::shared_ptr<Railpiece>tmp(new StraightPiece(beginn,scene));
    beginn->next = tmp;
    for(i=2; i<length; i++)
    {
        end.reset(new StraightPiece(tmp,scene));
        tmp->next = end;

        tmp = end;    
    }
    //this->orientation = orientation;

    //QPen pen(Qt::black);
    //pen.setWidth(2);

    //scene.addEllipse(beginn->start.x(),beginn->start.y()-5,-5,10,pen);
    //scene.addEllipse(end->end.x(),end->end.y()-5,+5,10,pen);
}

StraightRail::StraightRail(std::shared_ptr<Railpiece> prev, int length, QGraphicsScene &scene)
    :StraightRail(prev->end, prev->endAngle, length, scene)
{
}

StraightRail::~StraightRail()
{}

CurvedRail::CurvedRail(QPointF start, double startAngle, double angle, double radius, int direction, QGraphicsScene &scene)
{
    beginn.reset(new CurvedPiece(start, startAngle, radius, 2.5, direction, scene));

    end.reset(new CurvedPiece(beginn, radius, 2.5, direction, scene));
    end->connect(beginn,end);

    angle -= 5;
    while(angle)
    {
        std::shared_ptr<Railpiece> tmp(new CurvedPiece(end, radius, 2.5, direction, scene));
        end->connect(end,tmp);
        end = tmp;
        angle -= 2.5;
    }
}

CurvedRail::CurvedRail(std::shared_ptr<Railpiece> prev, double radius, double angle, int direction, QGraphicsScene &scene)
    :CurvedRail(prev->end,prev->direction == direction ? prev->endAngle : 360 - prev->endAngle,radius,angle,direction,scene)
{
    this->beginn->connect(prev,this->beginn);
}

CurvedRail::~CurvedRail()
{}


StraightCurvedSwitchRail::StraightCurvedSwitchRail(QPointF start, double startAngle, rail direction, QGraphicsScene &scene)
    //:straight(new StraightRail(start, startAngle, StraightRail::R_9100, scene)), curved(new CurvedRail(start, startAngle, angle, 430, direction, scene))
{
    straight.reset(new StraightRail(start, startAngle, StraightRail::R_9101, scene));
    curved.reset(new CurvedRail(start, (direction > 0 ? startAngle : 360 - startAngle), 15, 430, direction, scene));
}

StraightCurvedSwitchRail::StraightCurvedSwitchRail(std::shared_ptr<Railpiece> prev, rail direction, QGraphicsScene &scene)
{
    straight.reset(new StraightRail(prev, StraightRail::R_9101, scene));
    //TODO: Der Winkel muss irgendwie angepasst werden
    //curved.reset(new CurvedRail(prev->end, (direction > 0 ? startAngle : 360 - startAngle), 15, 430, direction, scene));
}
