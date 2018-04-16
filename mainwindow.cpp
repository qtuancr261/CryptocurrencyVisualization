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
    QObject::connect(dataStation, &CoinDataStation::parseLastValueOfAllCoinsCompleted, dataStation, &CoinDataStation::getMaxValueIn7DaysOfAllCoins);

    QObject::connect(collectionManagerDialog, &CollectionCoinManagementDialog::finishedPreloadAvailableCoins,  this, &MainWindow::show);
    QObject::connect(collectionManagerDialog, SIGNAL(finishedCurrentAction()), this, SLOT(enableAllToolButtonRelativeWithCollectionList()));

    // First action
    dataStation->getLastValueOfAllCoins();
    QObject::connect(collectionManagerDialog, &CollectionCoinManagementDialog::requestToCreateANewCollectionWith, dataStation, &CoinDataStation::createANewCollectionWith);
    QObject::connect(dataStation, &CoinDataStation::creatingANewCollectionCompleted, this, &MainWindow::addNewCollectionNameToComboBoxCryptoList);
    QObject::connect(ui->comboBoxCryptoList, &QComboBox::currentTextChanged, this, &MainWindow::loadCollectionContents);
    QObject::connect(ui->buttonShowBarChart, &QCommandLinkButton::clicked, this, &MainWindow::drawTrackingBarChart);
    QObject::connect(ui->buttonShowPieChart, &QCommandLinkButton::clicked, this, &MainWindow::drawTrackingPieChart);
    QObject::connect(ui->sliderPeriod, &QSlider::valueChanged, this, &MainWindow::updateChartProperties);
    QObject::connect(ui->listWidgetTrackedCoins, &QListWidget::currentTextChanged, this, &MainWindow::loadCurrentSelectedTrackedCoin);
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

void MainWindow::updateChartProperties()
{
    if (ui->buttonShowBarChart->isChecked())
        drawTrackingBarChart();
    else if (ui->buttonShowPieChart->isChecked())
        drawTrackingPieChart();
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
    axisY->setLabelFormat("%.2f");
    axisY->setMinorTickCount(10);
    axisY->setTickCount(10);
    axisY->setTickCount(series->count());
    //axisY->setLabelsAngle(45);
    QDateTime time{QDateTime::currentDateTime()};

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
            QVectorIterator<Coin::value> valueIter{trackedCoinsIter.value()->getRefAllValues()};
            //valueSet->append(trackedCoinsIter.value()->getLastValue().volume_24h);
            if (ui->radioButtonAvailableSupply->isChecked())
            {
                valueSet->append(trackedCoinsIter.value()->getAvailable_supply());
                //qDebug() << trackedCoinsIter.value()->getAvailable_supply();
                axisY->setTitleText("Supply");
            }
            else
            {
                valueIter.toBack();
                while(valueIter.hasPrevious())
                {
                    if (ui->radioButtonMarketcap->isChecked())
                    {
                        valueSet->append(valueIter.previous().marketcap);
                        axisY->setTitleText("$");
                    }

                    else if (ui->radioButtonPrice->isChecked())
                    {
                        valueSet->append(valueIter.previous().price);
                        axisY->setTitleText("$");
                    }
                    else if (ui->radioButtonVolume->isChecked())
                    {
                        valueSet->append(valueIter.previous().volume_24h);
                        axisY->setTitleText("$");
                    }
                    else if (ui->radioButtonChange->isChecked())
                    {
                        valueSet->append(valueIter.previous().changedPercent_24h.toDouble());
                        axisY->setTitleText("%");
                    }
                }
            }

            series->append(valueSet);
        }
    }
    QStringList dateCategories;
    /*dateCategories << time.toString("dd/MM/yyyy") << time.addDays(-1).toString("dd/MM/yyyy") << time.addDays(-2).toString("dd/MM/yyyy")
                   << time.addDays(-3).toString("dd/MM/yyyy") << time.addDays(-4).toString("dd/MM/yyyy") << time.addDays(-5).toString("dd/MM/yyyy")
                   << time.addDays(-6).toString("dd/MM/yyyy") << time.addDays(-7).toString("dd/MM/yyyy");*/
    for (int index{ui->sliderPeriod->value()}; index >= 0; index--)
    {
        dateCategories.append(time.addDays(-index).toString("dd/MM/yyyy"));
    }
    QBarCategoryAxis* axisX{new QBarCategoryAxis};
    axisX->append(dateCategories);
    axisX->setTitleText("Date");

    chart->removeAllSeries();
    chart->removeAxis(chart->axisX());
    chart->removeAxis(chart->axisY());
    chart->addSeries(series);
    //chart->createDefaultAxes();
    chart->setTitle("Cryptocurrency Track Bar Chart");
    chart->setAnimationOptions(QChart::SeriesAnimations | QChart::GridAxisAnimations);
    chart->setTheme(QChart::ChartThemeDark);
    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);
    //chart->axisY()->max;
    chart->legend()->setAlignment(Qt::AlignTop);
    chartView->setChart(chart);
}

void MainWindow::drawTrackingPieChart()
{
    chart->removeAllSeries();
    chart->removeAxis(chart->axisX());
    chart->removeAxis(chart->axisY());
    // check if current collection
    if (dataStation->getRefObservers().contains(ui->comboBoxCryptoList->currentText()))
    {
        DataObserverPtr currentCollection{dataStation->getObservers().value(ui->comboBoxCryptoList->currentText())};
        QHash<QString, CoinPtr> trackedCoins{currentCollection->getTrackedCoins()};
        QHashIterator<QString, CoinPtr> trackedCoinsIter{trackedCoins};
        QLineSeries* coinSeries{nullptr};
        while(trackedCoinsIter.hasNext())
        {
            trackedCoinsIter.next();
            coinSeries = new QLineSeries();
            coinSeries->setName(trackedCoinsIter.value()->getSymbol());
            QVectorIterator<Coin::value> valueIter{trackedCoinsIter.value()->getRefAllValues()};
            //valueSet->append(trackedCoinsIter.value()->getLastValue().volume_24h);
            if (ui->radioButtonAvailableSupply->isChecked())
            {
               break;
            }
            else
            {
                valueIter.toBack();
                while(valueIter.hasPrevious())
                {
                    Coin::value currentValue{valueIter.previous()};
                    if (ui->radioButtonMarketcap->isChecked())
                    {
                        coinSeries->append(currentValue.timeStamp.date().day() , currentValue.marketcap);

                    }
                    else if (ui->radioButtonPrice->isChecked())
                    {
                        //valueSet->append(valueIter.previous().price);
                        //axisY->setTitleText("$");
                    }
                    else if (ui->radioButtonVolume->isChecked())
                    {
                        //valueSet->append(valueIter.previous().volume_24h);
                        //axisY->setTitleText("$");
                    }
                    else if (ui->radioButtonChange->isChecked())
                    {
                        //valueSet->append(valueIter.previous().changedPercent_24h.toDouble());
                        //axisY->setTitleText("%");
                    }
                }
                chart->addSeries(coinSeries);
            }
        }
        //chart->createDefaultAxes();
        QValueAxis *axisX = new QValueAxis();
        axisX->setTitleText("Time Stamp");
        axisX->setLabelFormat("%i");
        //axisX->setTickCount(coinSeries->count());
        chart->addAxis(axisX, Qt::AlignBottom);
        coinSeries->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("Price");
        axisY->setLabelFormat("%i");
        //axisY->setTickCount(coinSeries->count());
        chart->addAxis(axisY, Qt::AlignLeft);
        coinSeries->attachAxis(axisY);
        chartView->setChart(chart);


  }

    /*QLineSeries *series = new QLineSeries();
    series->setName("BTC");
    *series << QPointF(10.0, 7000.0) << QPointF(12.0, 7325.0) << QPointF(13.0, 6808.0) << QPointF(14.0, 8200.0)
            << QPointF(15.0, 4325.0) << QPointF(16.0, 1358.0);
    QLineSeries *series_2 = new QLineSeries();

    series_2->setName("ETH");
    *series_2 << QPointF(10.0, 7520.0) << QPointF(12.0, 7025.0) << QPointF(13.0, 9808.0) << QPointF(14.0, 7853.09)
            << QPointF(15.0, 4325.0) << QPointF(16.0, 4520.06);
    //![1]

    //![2]
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->addSeries(series_2);
    //chart->legend()->hide();
    chart->setTitle("Price Tracking Chart");
    //![2]

    //![3]
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Time Stamp");
    axisX->setLabelFormat("%i");
    axisX->setTickCount(series->count());
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Price");
    axisY->setLabelFormat("%i");
    axisY->setTickCount(series->count());
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);*/

}

void MainWindow::loadCurrentSelectedTrackedCoin(const QString &currentCoinSymbol)
{
    ui->labelCoinName->setText(currentCoinSymbol);
}
