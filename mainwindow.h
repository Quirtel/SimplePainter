#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
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

private:
    Ui::MainWindow *ui;
    PaintField *field;
    QGridLayout *layout;
};

#endif // MAINWINDOW_H
