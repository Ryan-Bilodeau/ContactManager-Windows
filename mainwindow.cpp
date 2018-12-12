#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datamanager.h"
#include "contact.h"

#include <stdexcept>
#include <iostream>

using std::cout; using std::endl;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow), dataManager(DataManager()) {
    ui->setupUi(this);

    // Catches error that may be thrown in dataManager constructor
    try {} catch (std::runtime_error e) {
        cout << e.what() << endl;
        this->close();
    }

    dataManager.printAllContacts();
    dataManager.printAllGroups();
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

void MainWindow::on_actionExit_triggered()
{

}
