#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datamanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    DataManager dataManager;
private slots:
    void on_actionExit_triggered();

    void on_createButton_clicked();

    void on_updateButton_clicked();

    void on_deleteButton_clicked();

    DataManager db;

private:
    Ui::MainWindow *ui;
    Contact * current;
};

#endif // MAINWINDOW_H
