#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datamanager.h"


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

void MainWindow::on_createButton_clicked()
{
    if(ui->fnLineEdit->text() == "")
    {

    }
    else
    {
        ui->fnLineEdit->clear();
        ui->lnLineEdit->clear();
        ui->pLineEdit->clear();
        ui->eLineEdit->clear();
        ui->streetLineEdit->clear();
        ui->cityLineEdit->clear();
        ui->stateLineEdit->clear();
        ui->zipLineEdit->clear();
    }
}

void MainWindow::on_updateButton_clicked()
{

}

void MainWindow::on_deleteButton_clicked()
{

}
