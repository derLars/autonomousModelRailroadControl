#ifndef RAIL_H
#define RAIL_H

#include "railpiece.h"

class StraightRail
{
public:
    enum rail {R_9100 = 222, R_9101 = 111 ,R_9102 = 57,R_9103 = 55,R_9104 = 27};

    StraightRail(QPointF start, double startAngle, int length, QGraphicsScene &scene);
    StraightRail(std::shared_ptr<Railpiece>prev, int length, QGraphicsScene &scene);
    ~StraightRail();

    std::shared_ptr<Railpiece>beginn;
    std::shared_ptr<Railpiece>end;

    void connectNext(std::shared_ptr<Railpiece>prev);
    void connectPrev(std::shared_ptr<Railpiece>prev);

    //double orientation;
};

class CurvedRail
{
public:
    CurvedRail(QPointF start, double startAngle, double radius, double angle, int direction, QGraphicsScene &scene);
    CurvedRail(std::shared_ptr<Railpiece> prev, double radius, double angle, int direction, QGraphicsScene &scene);
    ~CurvedRail();

    std::shared_ptr<Railpiece> beginn;
    std::shared_ptr<Railpiece> end;

    void connectNext(std::shared_ptr<Railpiece> prev);
    void connectPrev(std::shared_ptr<Railpiece> prev);

    //double orientation;

};

class StraightCurvedSwitchRail
{
public:
    enum rail{R_9171 = 1, R_9170 = -1};

    StraightCurvedSwitchRail(QPointF start, double startAngle, rail direction, QGraphicsScene &scene);
    StraightCurvedSwitchRail(std::shared_ptr<Railpiece> prev, rail direction, QGraphicsScene &scene);
    std::shared_ptr<StraightRail>straight;
    std::shared_ptr<CurvedRail>curved;

    std::shared_ptr<Railpiece> beginn;
    std::shared_ptr<Railpiece> end;
    std::shared_ptr<Railpiece> endStraight;
    std::shared_ptr<Railpiece> endCurved;

    void setStraight();
    void setCurved();
};

#endif // RAIL_H
