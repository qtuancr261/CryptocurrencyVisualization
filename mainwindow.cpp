#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dataStation{new CoinDataStation(this)}
{
    ui->setupUi(this);
    dataStation->getLastValueOfAllCoins();
}

MainWindow::~MainWindow()
{
    delete ui;
}
