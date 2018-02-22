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
#include <QMessageBox>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->addWidget(&coords);
    this->setMouseTracking(true);
    coords.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_new_clicked()
{
    ui->actionNew->trigger();
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
    ui->actionUndo->trigger();
}

void MainWindow::on_pushButton_redo_clicked()
{
    ui->actionRedo->trigger();
}

void MainWindow::on_pushButton_save_clicked()
{
    ui->actionSave->trigger();
}

void MainWindow::on_pushButton_open_clicked()
{
    ui->actionOpen->trigger();
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

void MainWindow::on_actionUndo_triggered()
{
    if (field != nullptr)
        field->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    if (field != nullptr)
        field->redo();
}

void MainWindow::on_actionNew_triggered()
{
    if (picture_modified){
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            picture_modified = false;
            ui->actionSave->trigger();
            break;
        case QMessageBox::Discard:
            ui->actionNew->trigger();
            break;
        case QMessageBox::Cancel:
            return;
            break;
        }
    }


    create_field();
}

void MainWindow::on_actionSave_triggered()
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
        if (!filename.isEmpty())
        {
            QImage image(field->graphView->graphScene->sceneRect().size().toSize(), QImage::Format_ARGB32);
            QPainter painter(&image);

            field->graphView->graphScene->render(&painter);
            painter.end();
            image.save(filename,"PNG");
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    if (picture_modified){
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            picture_modified = false;
            ui->actionSave->trigger();
            break;
        case QMessageBox::Discard:
            picture_modified = false;
            ui->actionOpen->trigger();
            break;
        case QMessageBox::Cancel:
            return;
            break;
        }
    }
    else {
        filename = QFileDialog::getOpenFileName(this, "Open picture", "", "All Files(*)");
        if (!filename.isEmpty())
        {
            create_field();
        }
        picture_modified = false;
    }
}

void MainWindow::on_actionColor_2_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"", QColorDialog::DontUseNativeDialog);
    this->field->graphView->pen.setColor(color);
}

void MainWindow::on_pushButton_color_clicked()
{
    ui->actionColor_2->trigger();
}

void MainWindow::create_field()
{
    if (field != nullptr)
    {
        delete field;
        field = nullptr;
    }

    field = new PaintField(this, this->filename);
    ui->scrollArea->setWidget(field);
    field->show();
    connect(field->graphView, &GraphView::pic_modified, this, [&]() {
        picture_modified = false;
    });
}
