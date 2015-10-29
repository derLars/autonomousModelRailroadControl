#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>

#include <QGraphicsLineItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1000,1000);
    ui->graphicsView->setScene(scene);

    //std::shared_ptr<CurvedRail>curved(new CurvedRail(QPointF(100,400), 0, 45, 100, 1,*scene));
    //std::shared_ptr<CurvedRail>curved4(new CurvedRail(curved->end, 45, 100, 1,*scene));
    //std::shared_ptr<CurvedRail>curved5(new CurvedRail(curved4->end, 45, 100, -1,*scene));
    //std::shared_ptr<CurvedRail>curved6(new CurvedRail(curved5->end, 45, 100, -1,*scene));
    //std::shared_ptr<CurvedRail>curved7(new CurvedRail(curved6->end, 45, 100, -1,*scene));
    //std::shared_ptr<CurvedRail>curved8(new CurvedRail(curved7->end, 45, 100, -1,*scene));
    //std::shared_ptr<CurvedRail>curved9(new CurvedRail(curved8->end, 45, 100, 1,*scene));
    //std::shared_ptr<CurvedRail>curved10(new CurvedRail(curved9->end, 45, 100, 1,*scene));
    //std::shared_ptr<CurvedRail>curved11(new CurvedRail(curved10->end, 45, 100, 1,*scene));
    //std::shared_ptr<CurvedRail>curved12(new CurvedRail(curved11->end, 45, 100, 1,*scene));

    //curved->beginn->checkIt();
                                                                                //(QPoint start, double startAngle, rail angle, int direction, QGraphicsScene &scene)
    std::shared_ptr<StraightCurvedSwitchRail>weiche(new StraightCurvedSwitchRail(QPointF(100,400),30,StraightCurvedSwitchRail::R_9170,*scene));



    /*
    straight0.reset(new StraightRail(StraightRail::R_9100,QPoint(100,0),0,*scene));

    std::shared_ptr<StraightRail>straight1(new StraightRail(StraightRail::R_9100,straight0->end,*scene));
    straight0->connectNext(straight1->beginn);

    std::shared_ptr<StraightRail>straight2(new StraightRail(StraightRail::R_9100,straight1->end,*scene));
    straight1->connectNext(straight2->beginn);

    std::shared_ptr<CurvedRail>curved0(new CurvedRail(192, 45.0, straight2->end, *scene));
    straight2->connectNext(curved0->beginn);

    std::shared_ptr<CurvedRail>curved1(new CurvedRail(192, 45.0, curved0->end, *scene));
    curved0->connectNext(curved1->beginn);

    std::shared_ptr<CurvedRail>curved2(new CurvedRail(192, 45.0, curved1->end, *scene));
    curved1->connectNext(curved2->beginn);

    std::shared_ptr<CurvedRail>curved3(new CurvedRail(192, 45.0, curved2->end, *scene));
    curved2->connectNext(curved3->beginn);

    std::shared_ptr<StraightRail>straight3(new StraightRail(StraightRail::R_9100,curved3->end,*scene));
    curved3->connectNext(straight3->beginn);

    std::shared_ptr<StraightRail>straight4(new StraightRail(StraightRail::R_9100,straight3->end,*scene));
    straight3->connectNext(straight4->beginn);

    std::shared_ptr<StraightRail>straight5(new StraightRail(StraightRail::R_9100,straight4->end,*scene));
    straight4->connectNext(straight5->beginn);

    std::shared_ptr<CurvedRail>curved4(new CurvedRail(192, 45.0, straight5->end, *scene));
    straight5->connectNext(curved4->beginn);

    std::shared_ptr<CurvedRail>curved5(new CurvedRail(192, 45.0, curved4->end, *scene));
    curved4->connectNext(curved5->beginn);

    std::shared_ptr<CurvedRail>curved6(new CurvedRail(192, 45.0, curved5->end, *scene));
    curved5->connectNext(curved6->beginn);

    std::shared_ptr<CurvedRail>curved7(new CurvedRail(192, 45.0, curved6->end, *scene));
    curved6->connectNext(curved7->beginn);

    curved7->connectNext(straight0->beginn);
    straight0->connectPrev(curved7->end);

    std::cout << "start.x " << curved0->beginn->start.x() << std::endl;
    std::cout << "end.x " << curved1->end->end.x() << std::endl;


    StraightCurvedSwitchRail(StraightCurvedSwitchRail::R_9170, QPoint(150,150), 0, *scene);
*/
   // straight0->beginn->checkIt();

    /*


    std::shared_ptr<StraightRail>straight2(new StraightRail(StraightRail::R_9101,straight1->end,*scene));
    straight1->connectNext(straight2->beginn);

    std::shared_ptr<CurvedRail>curved1(new CurvedRail(192, 45.0, QPoint(50,50), 0, *scene));
    std::shared_ptr<CurvedRail>curved2(new CurvedRail(192, 45.0, curved1->end, *scene));
    curved1->connectNext(curved2->beginn);
    std::shared_ptr<CurvedRail>curved3(new CurvedRail(192, 45.0, curved2->end, *scene));
    curved2->connectNext(curved3->beginn);
    std::shared_ptr<CurvedRail>curved4(new CurvedRail(192, 45.0, curved3->end, *scene));
    curved3->connectNext(curved4->beginn);
    std::shared_ptr<CurvedRail>curved5(new CurvedRail(192, 45.0, curved4->end, *scene));
    curved4->connectNext(curved5->beginn);
    std::shared_ptr<CurvedRail>curved6(new CurvedRail(192, 45.0, curved5->end, *scene));
    curved5->connectNext(curved6->beginn);
    std::shared_ptr<CurvedRail>curved7(new CurvedRail(192, 45.0, curved6->end, *scene));
    curved6->connectNext(curved7->beginn);
    std::shared_ptr<CurvedRail>curved8(new CurvedRail(192, 45.0, curved7->end, *scene));
    curved7->connectNext(curved8->beginn);
   */
}

MainWindow::~MainWindow()
{
    delete ui;
}
