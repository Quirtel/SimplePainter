#include "paintfield.h"
#include <QPixmap>
#include <QtCore>
#include <QMouseEvent>
#include <QGridLayout>
#include <QGraphicsView>
#include <QGraphicsScene>

PaintField::PaintField(QWidget *parent, const QString &fn) : QWidget(parent), filename(fn)
{
    graphView = new GraphView(this);

    graphView->layout = new QGridLayout(this);

    if (filename.isEmpty())
    {
        graphView->image = new QPixmap(640,480);
        graphView->image->fill(Qt::black);
    }
    else
    {
        graphView->image = new QPixmap(filename);
    }

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
    graphView->scale(factor * 0.1 ,factor * 0.1);
}

void PaintField::undo()
{
    if (graphView->graphScene->items().length() > 1)
    {
        graphView->temp.push_back(graphView->graphScene->items().first());
        graphView->graphScene->removeItem(graphView->graphScene->items().first());
    }
}

void PaintField::redo(){
    if (!graphView->temp.isEmpty())
    {
        graphView->graphScene->addItem(graphView->temp.last());
        graphView->temp.removeLast();
    }
}

void GraphView::mousePressEvent(QMouseEvent *event)
{
    pen.setColor(Qt::white);
    pen.setWidth(6);

    auto map = mapToScene(event->pos().x(),event->pos().y());
    pen.setCapStyle(Qt::RoundCap);

    this->graphScene->addEllipse(map.x(), map.y(), 2,2, pen, QBrush(Qt::white, Qt::SolidPattern));

    prev_pos = event->pos();
}

void GraphView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        pen.setColor(Qt::white);
        pen.setWidth(6);
        pen.setCapStyle(Qt::RoundCap);

        this->graphScene->addLine(QLineF(mapToScene(prev_pos),mapToScene(event->pos().x(), event->pos().y())), pen);

        prev_pos = event->pos();
        event->accept();
    }
}
