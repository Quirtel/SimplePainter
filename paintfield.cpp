#include "paintfield.h"
#include <QPixmap>
#include <QtCore>
#include <QMouseEvent>
#include <QGridLayout>
#include <QGraphicsView>
#include <QGraphicsScene>

PaintField::PaintField(QWidget *parent) : QWidget(parent)
{
    graphView = new GraphView(this);

    graphView->layout = new QGridLayout(this);
    graphView->image = new QPixmap("/Users/raiden/Pictures/4k-wallpaper-9.jpg");

    graphView->graphScene = new QGraphicsScene(this);
    graphView->graphScene->addPixmap(*graphView->image);

    graphView->setScene(graphView->graphScene);

    qDebug() << graphView->image->devicePixelRatio();

    graphView->layout->addWidget(graphView);
    graphView->show();
    qDebug() << graphView->image->width();
}

void PaintField::resizeImage(int factor)
{
    graphView->scale(factor/10,factor/10);
}


void GraphView::mousePressEvent(QMouseEvent *event)
{
    pa.begin(image);
    pen.setColor(Qt::white);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(6);

    pen.setCapStyle(Qt::RoundCap);
    pa.setPen(pen);
    pa.drawPoint(mapToScene(event->pos().x(), event->pos().y()));

    pa.end();
    graphScene->clear();
    graphScene->addPixmap(*image);
    prev_pos = event->pos();
}

void GraphView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        pa.begin(image);
        pen.setColor(Qt::white);
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(6);

        pen.setCapStyle(Qt::RoundCap);
        pa.setPen(pen);
        pa.drawLine(mapToScene(prev_pos),mapToScene(event->pos().x(), event->pos().y()));

        //graphScene->clear();
        graphScene->addPixmap(*image);
        pa.end();

        prev_pos = event->pos();
        event->accept();
    }
}
