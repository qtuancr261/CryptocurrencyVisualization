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
    QObject::connect(ui->toolButtonAddNewList, SIGNAL(clicked(bool)), this , SLOT(disableAllToolButtonRelativeWithCollectionList()));

    QObject::connect(ui->toolButtonConfigList, SIGNAL(clicked(bool)), collectionManagerDialog, SLOT(showConfigureCurrentCollectionCoin()));
    QObject::connect(ui->toolButtonConfigList, SIGNAL(clicked(bool)), this, SLOT(disableAllToolButtonRelativeWithCollectionList()));
    //QObject::connect(ui->toolButtonAddNewList, SIGNAL(clicked(bool)), dataStation, SLOT(getLastValueOfAllCoins()));
    QObject::connect(dataStation, SIGNAL(parseLastValueOfAllCoinsCompleted(QHash<QString,CoinPtr>)), collectionManagerDialog, SLOT(loadAvailableCoins(QHash<QString,CoinPtr>)));
    QObject::connect(collectionManagerDialog, SIGNAL(finishedCurrentAction()), this, SLOT(enableAllToolButtonRelativeWithCollectionList()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::disableAllToolButtonRelativeWithCollectionList()
{
    ui->toolButtonAddNewList->setDisabled(true);
    ui->toolButtonConfigList->setDisabled(true);
    ui->toolButtonRemoveList->setDisabled(true);
}

void MainWindow::enableAllToolButtonRelativeWithCollectionList()
{
    ui->toolButtonAddNewList->setEnabled(true);
    ui->toolButtonConfigList->setEnabled(true);
    ui->toolButtonRemoveList->setEnabled(true);
}
