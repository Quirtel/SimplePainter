#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintfield.h"
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>
#include <QGridLayout>
#include <QtCore>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->addWidget(&coords);
    coords.show();
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

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    coords.setText("X: " + QString::number(event->pos().x()) + " Y: " + QString::number(event->pos().y()));
    coords.show();
    event->accept();
}

void MainWindow::on_pushButton_undo_clicked()
{
    field->undo();
}

void MainWindow::on_pushButton_redo_clicked()
{
    field->redo();
}

void MainWindow::on_pushButton_save_clicked()
{
    if (!filename.isEmpty())
    {
        QImage image(field->graphView->graphScene->sceneRect().size().toSize(), QImage::Format_ARGB32);
        QPainter painter(&image);

        field->graphView->graphScene->render(&painter);
        painter.end();

        image.save(filename,"PNG");
    }
    else
    {
        filename = QFileDialog::getSaveFileName(this, "Save picture", "", "All Files(*)");
        QImage image(field->graphView->graphScene->sceneRect().size().toSize(), QImage::Format_ARGB32);
        QPainter painter(&image);

        field->graphView->graphScene->render(&painter);
        painter.end();
        image.save(filename,"PNG");
    }
}

void MainWindow::on_pushButton_open_clicked()
{
    filename = QFileDialog::getOpenFileName(this, "Open picture", "", "All Files(*)");
    field = new PaintField(this, this->filename);
    ui->scrollArea->setWidget(field);
    field->show();
}

void MainWindow::on_actionSolid_triggered()
{
    if (field != nullptr)
    {
        field->graphView->pen.setStyle(Qt::SolidLine);
    }
}

void MainWindow::on_actionDot_triggered()
{
    if (field != nullptr)
    {
        field->graphView->pen.setStyle(Qt::DotLine);
    }
}

void MainWindow::on_actionDashDot_triggered()
{
    if (field != nullptr)
    {
        field->graphView->pen.setStyle(Qt::DashDotLine);
    }
}
