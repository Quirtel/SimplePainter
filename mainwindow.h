#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QtCore>
#include <QLabel>
#include "paintfield.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_new_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_sliderMoved(int position);

    void on_pushButton_undo_clicked();

    void on_pushButton_redo_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_open_clicked();

    void on_actionSolid_triggered();

    void on_actionDot_triggered();

    void on_actionDashDot_triggered();

protected:
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    PaintField *field;
    QGridLayout *layout;
    QLabel coords;
    QString filename;
};

#endif // MAINWINDOW_H
