#ifndef PAINTFIELD_H
#define PAINTFIELD_H

#include <QPixmap>
#include <QColor>
#include <QWidget>
#include <QPainter>
#include <QGridLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class GraphView;

class PaintField : public QWidget
{
    Q_OBJECT
public:
    explicit PaintField(QWidget *parent = nullptr);
    void resizeImage(int factor);

private:
    GraphView *graphView;
};




class GraphView : public QGraphicsView
{
    Q_OBJECT
public:
    friend class PaintField;
    GraphView(QWidget *parent = nullptr) {

    }

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QPixmap *image;
    QGridLayout *layout;
    QPainter pa;
    QPen pen;

    QGraphicsScene *graphScene;
    QPoint prev_pos;
};

#endif // PAINTFIELD_H
