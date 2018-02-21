#include "paintfield.h"
#include <QPixmap>
#include <QtCore>
#include <QMouseEvent>
#include <QGridLayout>
#include <QGraphicsView>
#include <QGraphicsScene>

PaintField::PaintField(QWidget *parent, const QString &fn) : QWidget(parent), filename(fn)
{
    graphView = new GraphView();

    graphView->layout = new QGridLayout(this);

    if (filename.isEmpty())
    {
        graphView->image = new QPixmap(640,480);
        graphView->image->fill(Qt::white);
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
    graphView->setStyleSheet("border:2px solid black;");
    qDebug() << graphView->image->width();

}

void PaintField::resizeImage(int factor)
{ //TODO: complete the resize feature
    if (prev_factor < factor)
        graphView->scale(1.1 ,1.1);
    else if (prev_factor > factor)
        graphView->scale(1 / 1.1 , 1 / 1.1);
    else if (prev_factor == 0 || factor == 0)
        graphView->scale(1,1);
    prev_factor = factor;
}

void PaintField::undo()
{
    if (graphView->graphScene->items().length() > 1)
    {
        graphView->temp.push_back(graphView->graphScene->items().first());
        graphView->graphScene->removeItem(graphView->graphScene->items().first());
    }
}

void PaintField::redo()
{
    if (!graphView->temp.isEmpty())
    {
        graphView->graphScene->addItem(graphView->temp.last());
        graphView->temp.removeLast();
    }
}

void GraphView::mousePressEvent(QMouseEvent *event)
{
    pen.setWidth(6);

    auto map = mapToScene(event->pos().x(),event->pos().y());
    if (map.x() <= this->image->width() && map.x() >= 0 && map.y() >= 0 && map.y() <= this->image->height())
    {
        if(event->modifiers() == Qt::ShiftModifier)
        {
            pen.setCapStyle(Qt::RoundCap);
            this->graphScene->addLine(QLineF(mapToScene(prev_pos),mapToScene(event->pos().x(), event->pos().y())), pen);

            prev_pos = event->pos();
        }
        else
        {
            pen.setCapStyle(Qt::RoundCap);
            this->graphScene->addEllipse(map.x(), map.y(), 2,2, pen, QBrush(Qt::white, Qt::SolidPattern));

            prev_pos = event->pos();
        }
    }
}

void GraphView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        auto map = mapToScene(event->pos().x(),event->pos().y());
        qDebug() << map;
        if (map.x() <= this->image->width() && map.x() >= 0 && map.y() >= 0 && map.y() <= this->image->height())
        {
            pen.setWidth(6);
            pen.setCapStyle(Qt::RoundCap);

            this->graphScene->addLine(QLineF(mapToScene(prev_pos),mapToScene(event->pos().x(), event->pos().y())), pen);

            prev_pos = event->pos();
            event->accept();
        }
    }
}
