#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_collectioncoinmanagementdialog.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dataStation{new CoinDataStation(this)},
    collectionManagerDialog{new CollectionCoinManagementDialog(this)},
    chartView{new QChartView(this)},
    chart(new QChart())
{
    ui->setupUi(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(chartView);
    //------------------------------------------------------
    QObject::connect(ui->toolButtonAddNewList, SIGNAL(clicked(bool)), collectionManagerDialog, SLOT(showAddNewCollectionCoin()));
    QObject::connect(ui->toolButtonAddNewList, SIGNAL(clicked(bool)), this , SLOT(disableAllToolButtonRelativeWithCollectionList()));

    QObject::connect(ui->toolButtonConfigList, SIGNAL(clicked(bool)), collectionManagerDialog, SLOT(showConfigureCurrentCollectionCoin()));
    QObject::connect(ui->toolButtonConfigList, SIGNAL(clicked(bool)), this, SLOT(disableAllToolButtonRelativeWithCollectionList()));
    //QObject::connect(ui->toolButtonAddNewList, SIGNAL(clicked(bool)), dataStation, SLOT(getLastValueOfAllCoins()));
    QObject::connect(dataStation, &CoinDataStation::parseLastValueOfAllCoinsCompleted, collectionManagerDialog, &CollectionCoinManagementDialog::getAvailableCoins);
    QObject::connect(collectionManagerDialog, &CollectionCoinManagementDialog::finishedPreloadAvailableCoins,  this, &MainWindow::show);
    QObject::connect(collectionManagerDialog, SIGNAL(finishedCurrentAction()), this, SLOT(enableAllToolButtonRelativeWithCollectionList()));

    // First action
    dataStation->getLastValueOfAllCoins();
    QObject::connect(collectionManagerDialog, &CollectionCoinManagementDialog::requestToCreateANewCollectionWith, dataStation, &CoinDataStation::createANewCollectionWith);
    QObject::connect(dataStation, &CoinDataStation::creatingANewCollectionCompleted, this, &MainWindow::addNewCollectionNameToComboBoxCryptoList);
    QObject::connect(ui->comboBoxCryptoList, &QComboBox::currentTextChanged, this, &MainWindow::loadCollectionContents);
    QObject::connect(ui->buttonShowBarChart, &QCommandLinkButton::clicked, this, &MainWindow::drawTrackingBarChart);
    QObject::connect(ui->buttonShowLineChart, &QCommandLinkButton::clicked, this, &MainWindow::drawTrackingLineChart);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QChartView *MainWindow::getChartView() const
{
    return chartView;
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

void MainWindow::addNewCollectionNameToComboBoxCryptoList(const QString &collectionName)
{
    ui->comboBoxCryptoList->addItem(QIcon(":/ico/collection.ico"), collectionName);
    ui->comboBoxCryptoList->setCurrentIndex(ui->comboBoxCryptoList->count() - 1);
}

void MainWindow::loadCollectionContents(const QString &collectionName)
{

    ui->listWidgetTrackedCoins->clear();
    /*for (int index{}; index < collectionManagerDialog->getUi()->listWidgetTrackedCoins->count(); index++)
    {
        QListWidgetItem* item{new QListWidgetItem(collectionManagerDialog->getUi()->listWidgetTrackedCoins->item(index)->icon(), collectionManagerDialog->getUi()->listWidgetTrackedCoins->item(index)->text())};
        ui->listWidgetTrackedCoins->addItem(item);
        //ui->listWidgetTrackedCoins->addItem("FERER");
        qDebug() << index;
    }*/
    if (dataStation->getRefObservers().contains(collectionName))
    {
        DataObserverPtr currentCollection{dataStation->getObservers().value(collectionName)};
        QHash<QString, CoinPtr> trackedCoins{currentCollection->getTrackedCoins()};
        QHashIterator<QString, CoinPtr> trackedCoinsIter{trackedCoins};
        while(trackedCoinsIter.hasNext())
        {
            trackedCoinsIter.next();
            QListWidgetItem* item{new QListWidgetItem(trackedCoinsIter.value()->getDisplayItem()->icon(), trackedCoinsIter.value()->getDisplayItem()->text())};
            ui->listWidgetTrackedCoins->addItem(item);
        }
    }
    ui->listWidgetTrackedCoins->show();
}

void MainWindow::drawTrackingBarChart()
{
    QBarSeries* series{new QBarSeries()};
    //series->append(btcSet);
    //series->append(ethSet);
    //series->append(nycSet);
    //series->append(bsdSet);
    //series->append(qtumSet);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("USD");
    axisY->setLabelFormat("%.2f");
    axisY->setMinorTickCount(10);
    axisY->setTickCount(10);
    axisY->setTickCount(series->count());

    QDateTime time{QDateTime::currentDateTime()};
    //axis->setRange("01/04/2018", "03/04/2018");
    if (dataStation->getRefObservers().contains(ui->comboBoxCryptoList->currentText()))
    {
        DataObserverPtr currentCollection{dataStation->getObservers().value(ui->comboBoxCryptoList->currentText())};
        QHash<QString, CoinPtr> trackedCoins{currentCollection->getTrackedCoins()};
        QHashIterator<QString, CoinPtr> trackedCoinsIter{trackedCoins};
        while(trackedCoinsIter.hasNext())
        {
            trackedCoinsIter.next();
            //QListWidgetItem* item{new QListWidgetItem(trackedCoinsIter.value()->getDisplayItem()->icon(), trackedCoinsIter.value()->getDisplayItem()->text())};
            QBarSet* valueSet{new QBarSet(trackedCoinsIter.value()->getSymbol())};
            valueSet->append(trackedCoinsIter.value()->getLastValue().volume_24h);
            series->append(valueSet);
        }
    }
    QStringList dateCategories;
    dateCategories << time.toString("dd/MM/yyyy");
    QBarCategoryAxis* axis{new QBarCategoryAxis};
    axis->append(dateCategories);
    axis->setTitleText("Date");
    //chart->createDefaultAxes();
    chart->removeAllSeries();
    chart->removeAxis(chart->axisX());
    chart->removeAxis(chart->axisY());
    chart->addSeries(series);
    chart->setTitle("Cryptocurrency Track Bar Chart");
    chart->setAnimationOptions(QChart::SeriesAnimations | QChart::GridAxisAnimations);
    chart->setTheme(QChart::ChartThemeLight);
    chart->setAxisX(axis, series);
    chart->setAxisY(axisY, series);
    chart->legend()->setAlignment(Qt::AlignRight);
    chartView->setChart(chart);
}

void MainWindow::drawTrackingLineChart()
{
    chart->removeAllSeries();
    chart->removeAxis(chart->axisX());
    chart->removeAxis(chart->axisY());
}
