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
    friend class GraphView;
    explicit PaintField(QWidget *parent = nullptr, const QString &fn = "");
    void resizeImage(int factor);
    void undo();
    void redo();
    GraphView *graphView;

    QString filename;
};




class GraphView : public QGraphicsView
{
    Q_OBJECT
public:
    friend class PaintField;
    GraphView(QWidget *parent = nullptr) {

    }
    QPixmap *image;
    QGridLayout *layout;
    QPainter pa;
    QPen pen;

    QGraphicsScene *graphScene;
    QPoint prev_pos;
    QList<QGraphicsItem *> temp;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:

};

#endif // PAINTFIELD_H
