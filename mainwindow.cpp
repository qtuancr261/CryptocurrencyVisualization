#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dataStation{new CoinDataStation(this)},
    collectionManagerDialog{new CollectionCoinManagementDialog(this)}
{
    ui->setupUi(this);
    dataStation->getLastValueOfAllCoins();
    QObject::connect(ui->toolButtonAddNewList, SIGNAL(clicked(bool)), collectionManagerDialog, SLOT(showAddNewCollectionCoin()));
    //QObject::connect(ui->toolButtonAddNewList, SIGNAL(clicked(bool)), dataStation, SLOT(getLastValueOfAllCoins()));
    QObject::connect(dataStation, SIGNAL(parseLastValueOfAllCoinsCompleted(QHash<QString,CoinPtr>)), collectionManagerDialog, SLOT(loadAvailableCoins(QHash<QString,CoinPtr>)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
