#include "railpiece.h"
#include <iostream>
#define PI 3.1415

Railpiece::Railpiece(QPointF start, double startAngle, double angle, int direction)
    :start(start),direction(direction)
{     
    if(startAngle >= 360.0)
    {
       this->startAngle = startAngle - 360.0;
    }
    this->endAngle = startAngle + angle;
}

Railpiece::~Railpiece()
{
    //std::cout << this << " railpiece destructor called" << std::endl;
}

void Railpiece::connect(std::shared_ptr<Railpiece> prev, std::shared_ptr<Railpiece> next)
{
    prev->next = next;
    next->prev = prev;
}

void Railpiece::checkIt()
{
    QPen pen(Qt::red);
    pen.setWidth(6);
    this->line->setPen(pen);
    if(this->next)
    {
        this->next->checkIt();
    }
}


StraightPiece::StraightPiece(QPointF start, double startAngle, QGraphicsScene& scene)
    :Railpiece(start,startAngle,0,0)
{
    offsetX =  (1 * cos(startAngle * PI / 180.0));
    offsetY =  (1 * sin(startAngle * PI / 180.0));

    this->end.setX(start.x() + (int)offsetX);
    this->end.setY(start.y() + (int)offsetY);

    offsetX -= (int)offsetX;
    offsetY -= (int)offsetY;

    QPen pen(Qt::black);
    pen.setWidth(6);
    line = scene.addLine(start.x(),start.y(),end.x(),end.y(),pen);

    std::cout << " offsetX: " << offsetX << " offsetY: " << offsetY << std::endl;
}

StraightPiece::StraightPiece(std::shared_ptr<Railpiece> prev, QGraphicsScene& scene)
    :Railpiece(prev->end,prev->endAngle,0,0)
{
    offsetX = prev->offsetX + (1 * cos(prev->endAngle * PI / 180.0));
    offsetY = prev->offsetY + (1 * sin(prev->endAngle * PI / 180.0));

    this->end.setX(start.x() + (int)offsetX);
    this->end.setY(start.y() + (int)offsetY);

    offsetX -= (int)offsetX;
    offsetY -= (int)offsetY;

    QPen pen(Qt::black);
    pen.setWidth(6);
    line = scene.addLine(start.x(),start.y(),end.x(),end.y(),pen);

    std::cout << " offsetX: " << offsetX << " offsetY: " << offsetY << std::endl;
}

StraightPiece::~StraightPiece()
{}

/*
StraightPiece::StraightPiece(std::shared_ptr<Railpiece> prev, QGraphicsScene& scene)
    :Railpiece(prev->end,prev->orientation)
{
    offsetX = prev->offsetX + (1 * cos(prev->orientation* PI / 180.0));
    offsetY = prev->offsetY + (1 * sin(prev->orientation* PI / 180.0));

    end.setX(start.x() + (int)offsetX);
    end.setY(start.y() + (int)offsetY);

    offsetX -= (int)offsetX;
    offsetY -= (int)offsetY;
    QPen pen(Qt::black);
    pen.setWidth(6);
    line = scene.addLine(start.x(),start.y(),end.x(),end.y(),pen);
}


*/

CurvedPiece::CurvedPiece(QPointF start, double startAngle, double radius, double angle, int direction, QGraphicsScene& scene)
    :Railpiece(start, startAngle, angle, direction),radius(radius)
{
    double startX = radius * sin((startAngle) * M_PI /180.0);
    double startY = radius - (radius * cos((startAngle) * M_PI /180.0));

    double endX = radius * sin((startAngle + angle) * M_PI /180.0);
    double endY = radius - (radius * cos((startAngle + angle) * M_PI /180.0));

    end.setX(start.x() + (endX - startX));
    end.setY(start.y() + direction * (endY - startY));

    QPen pen(Qt::black);
    pen.setWidth(6);
    line = scene.addLine(start.x(),start.y(),end.x(),end.y(),pen);
}

CurvedPiece::CurvedPiece(std::shared_ptr<Railpiece> prev, double radius, double angle, int direction, QGraphicsScene& scene)
    :CurvedPiece(prev->end, prev->endAngle, radius, angle, direction, scene)
{

}

CurvedPiece::~CurvedPiece()
{
    //std::cout << this << " curved destructor called" << std::endl;
}
