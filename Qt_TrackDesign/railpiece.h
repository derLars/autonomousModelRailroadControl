#ifndef RAILPIECE_H
#define RAILPIECE_H

#include "QPoint"
#include <memory>

#include <QGraphicsScene>
#include <QGraphicsLineItem>

#define LEFT -1
#define STRAIGHT 0
#define RIGHT 1

class Railpiece
{
public:
    //enum angle {LEFT = -5, STRAIGHT = 0, RIGHT = 5};

    Railpiece(QPointF start, double startAngle, double angle, int direction);
    ~Railpiece();

    void connect(std::shared_ptr<Railpiece> prev, std::shared_ptr<Railpiece> next);
    void checkIt();

    QPointF start;
    QPointF end;

    std::shared_ptr<Railpiece> prev;
    std::shared_ptr<Railpiece> next;

    double startAngle;
    double endAngle;

    double offsetX;
    double offsetY;

    int direction;

    QGraphicsLineItem* line;
};

class StraightPiece : public Railpiece
{
public:
    StraightPiece(QPointF start, double startAngle, QGraphicsScene& scene);
    StraightPiece(std::shared_ptr<Railpiece> prev, QGraphicsScene& scene);
    ~StraightPiece();

    //void connectNext(std::shared_ptr<Railpiece> next);
};

class CurvedPiece : public Railpiece
{
public:
    //CurvedPiece(QPointF start, double orientation, double radius, double direction, QGraphicsScene& scene);
   // CurvedPiece(std::shared_ptr<Railpiece> prev, double radius, double direction, QGraphicsScene& scene);

    CurvedPiece(QPointF start, double startAngle, double radius, double angle, int direction, QGraphicsScene& scene);
    CurvedPiece(std::shared_ptr<Railpiece> prev, double radius, double angle, int direction, QGraphicsScene& scene);
    ~CurvedPiece();

    double radius;

};

#endif // RAILPIECE_H
