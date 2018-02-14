#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintfield.h"
#include <QImage>
#include <QPixmap>
#include <QMouseEvent>
#include <QGridLayout>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_new_clicked()
{
    field = new PaintField(this);
    ui->scrollArea->setWidget(field);
    field->show();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    //field->resizeImage(value);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    field->resizeImage(position);
    qDebug() << ui->horizontalSlider->value();
}
