#include "mainwindow.h"
#include "ui_collectioncoinmanagementdialog.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      dataStation{new CoinDataStation(this)},
      collectionManagerDialog{new CollectionCoinManagementDialog(this)},
      chartView{new QChartView(this)},
      chart(new QChart()) {
    ui->setupUi(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setAnimationOptions(QChart::AllAnimations);
    chart->setAnimationOptions(QChart::AllAnimations);
    // setupAutoCompleterForComboBoxCrytoList();
    setCentralWidget(chartView);
    //------------------------------------------------------
    QObject::connect(ui->toolButtonAddNewList, SIGNAL(clicked(bool)), collectionManagerDialog, SLOT(showAddNewCollectionCoin()));
    QObject::connect(ui->toolButtonAddNewList, SIGNAL(clicked(bool)), this, SLOT(disableAllToolButtonRelativeWithCollectionList()));

    QObject::connect(ui->toolButtonConfigList, SIGNAL(clicked(bool)), this, SLOT(checkCollectionContentsBeforeConfiguringIt()));
    QObject::connect(ui->toolButtonConfigList, SIGNAL(clicked(bool)), this, SLOT(disableAllToolButtonRelativeWithCollectionList()));
    // QObject::connect(ui->toolButtonAddNewList, SIGNAL(clicked(bool)), dataStation, SLOT(getLastValueOfAllCoins()));
    QObject::connect(
        dataStation, &CoinDataStation::parseLastValueOfAllCoinsCompleted, collectionManagerDialog, &CollectionCoinManagementDialog::setAvailableCoins);
    QObject::connect(dataStation, &CoinDataStation::parseLastValueOfAllCoinsCompleted, dataStation, &CoinDataStation::getMaxValueIn7DaysOfAllCoins);

    QObject::connect(collectionManagerDialog, &CollectionCoinManagementDialog::finishedPreloadAvailableCoins, this, &MainWindow::show);
    QObject::connect(collectionManagerDialog, SIGNAL(finishedCurrentAction()), this, SLOT(enableAllToolButtonRelativeWithCollectionList()));

    // First action
    dataStation->getLastValueOfAllCoins();
    QObject::connect(
        collectionManagerDialog, &CollectionCoinManagementDialog::requestToCreateANewCollectionWith, dataStation, &CoinDataStation::createANewCollection);
    QObject::connect(collectionManagerDialog,
                     &CollectionCoinManagementDialog::requestToModifyCurrentCollectionContents,
                     dataStation,
                     &CoinDataStation::modifyCollectionContents);
    QObject::connect(dataStation, &CoinDataStation::creatingANewCollectionCompleted, this, &MainWindow::addNewCollectionNameToComboBoxCryptoList);
    QObject::connect(dataStation, &CoinDataStation::modifyingCollectionContentsCompleted, this, &MainWindow::loadCollectionContents);

    QObject::connect(ui->comboBoxCryptoList, &QComboBox::currentTextChanged, this, &MainWindow::loadCollectionContents);
    QObject::connect(ui->buttonShowBarChart, &QCommandLinkButton::clicked, this, &MainWindow::drawTrackingBarChart);
    QObject::connect(ui->buttonShowPieChart, &QCommandLinkButton::clicked, this, &MainWindow::drawTrackingPieChart);
    QObject::connect(ui->sliderPeriod, &QSlider::valueChanged, this, &MainWindow::updateChartPeriodProperties);
    QObject::connect(ui->listWidgetTrackedCoins, &QListWidget::currentTextChanged, this, &MainWindow::loadCurrentSelectedTrackedCoin);
    QObject::connect(ui->listWidgetTrackedCoins, &QListWidget::currentTextChanged, this, &MainWindow::updatePieChartSlice);
    QObject::connect(ui->comboBoxChartTheme, SIGNAL(currentIndexChanged(int)), this, SLOT(updateChartTheme(int)));
    QObject::connect(ui->toolButtonRemoveList, &QToolButton::clicked, this, &MainWindow::confirmDeletingACollection);
    QObject::connect(ui->lineEditFilter, &QLineEdit::returnPressed, this, &MainWindow::changeSelectedCoinWhenUserSearchItOnLineEditFiler);
    QObject::connect(ui->radioButtonChange, &QRadioButton::clicked, this, &MainWindow::updateChartTrackedValue);
    QObject::connect(ui->radioButtonMarketcap, &QRadioButton::clicked, this, &MainWindow::updateChartTrackedValue);
    QObject::connect(ui->radioButtonPrice, &QRadioButton::clicked, this, &MainWindow::updateChartTrackedValue);
    QObject::connect(ui->radioButtonVolume, &QRadioButton::clicked, this, &MainWindow::updateChartTrackedValue);
    QObject::connect(ui->actionAbout_Qt, &QAction::triggered, this, &MainWindow::aboutQt);
}

MainWindow::~MainWindow() { delete ui; }

QChartView *MainWindow::getChartView() const { return chartView; }

void MainWindow::setupAutoCompleterForComboBoxCrytoList() {
    QStringList wordCoinList{};
    for (int rowIndex{}; rowIndex < ui->listWidgetTrackedCoins->count(); rowIndex++) {
        wordCoinList.append(ui->listWidgetTrackedCoins->item(rowIndex)->text());
    }
    QCompleter *completer = new QCompleter(wordCoinList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEditFilter->setCompleter(completer);
}

void MainWindow::changeSelectedCoinWhenUserSearchItOnLineEditFiler() {
    QString searchCoin{ui->lineEditFilter->text()};
    QList<QListWidgetItem *> matchItems{ui->listWidgetTrackedCoins->findItems(searchCoin, Qt::MatchFlag::MatchExactly)};
    if (matchItems.size() > 0) ui->listWidgetTrackedCoins->setCurrentItem(matchItems.at(0));
}

void MainWindow::disableAllToolButtonRelativeWithCollectionList() {
    ui->toolButtonAddNewList->setDisabled(true);
    ui->toolButtonConfigList->setDisabled(true);
    ui->toolButtonRemoveList->setDisabled(true);
}

void MainWindow::enableAllToolButtonRelativeWithCollectionList() {
    ui->toolButtonAddNewList->setEnabled(true);
    ui->toolButtonConfigList->setEnabled(true);
    ui->toolButtonRemoveList->setEnabled(true);
}

void MainWindow::addNewCollectionNameToComboBoxCryptoList(const QString &collectionName) {
    ui->comboBoxCryptoList->addItem(QIcon(":/ico/collection.ico"), collectionName);
    ui->comboBoxCryptoList->setCurrentIndex(ui->comboBoxCryptoList->count() - 1);
}

void MainWindow::loadCollectionContents(const QString &collectionName) {
    ui->listWidgetTrackedCoins->clear();
    /*for (int index{}; index < collectionManagerDialog->getUi()->listWidgetTrackedCoins->count(); index++)
    {
        QListWidgetItem* item{new QListWidgetItem(collectionManagerDialog->getUi()->listWidgetTrackedCoins->item(index)->icon(),
    collectionManagerDialog->getUi()->listWidgetTrackedCoins->item(index)->text())}; ui->listWidgetTrackedCoins->addItem(item);
        //ui->listWidgetTrackedCoins->addItem("FERER");
        qDebug() << index;
    }*/
    if (dataStation->getRefObservers().contains(collectionName)) {
        DataObserverPtr currentCollection{dataStation->getObservers().value(collectionName)};
        QHash<QString, CoinPtr> trackedCoins{currentCollection->getTrackedCoins()};
        QHashIterator<QString, CoinPtr> trackedCoinsIter{trackedCoins};
        while (trackedCoinsIter.hasNext()) {
            trackedCoinsIter.next();
            QListWidgetItem *item{new QListWidgetItem(trackedCoinsIter.value()->getDisplayItem()->icon(), trackedCoinsIter.value()->getDisplayItem()->text())};
            ui->listWidgetTrackedCoins->addItem(item);
        }
    }
    ui->listWidgetTrackedCoins->show();
    setupAutoCompleterForComboBoxCrytoList();
}

void MainWindow::updateChartPeriodProperties() {
    if (ui->buttonShowBarChart->isChecked())
        drawTrackingBarChart();
    else if (ui->buttonShowPieChart->isChecked())
        return;
}

void MainWindow::updateChartTrackedValue() {
    if (ui->buttonShowBarChart->isChecked())
        drawTrackingBarChart();
    else if (ui->buttonShowPieChart->isChecked())
        return;
}

void MainWindow::updatePieChartSlice() {
    if (ui->buttonShowBarChart->isChecked())
        return;
    else if (ui->buttonShowPieChart->isChecked())
        drawTrackingPieChart();
}

void MainWindow::drawTrackingBarChart() {
    QBarSeries *series{new QBarSeries()};

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%.2f");
    axisY->setMinorTickCount(10);
    axisY->setTickCount(10);
    axisY->setTickCount(series->count());
    // axisY->setLabelsAngle(45);
    QDateTime time{QDateTime::currentDateTime()};
    int dayPeriod{ui->spinBoxPeriod->value()};
    if (dataStation->getRefObservers().contains(ui->comboBoxCryptoList->currentText())) {
        DataObserverPtr currentCollection{dataStation->getObservers().value(ui->comboBoxCryptoList->currentText())};
        QHash<QString, CoinPtr> trackedCoins{currentCollection->getTrackedCoins()};
        QHashIterator<QString, CoinPtr> trackedCoinsIter{trackedCoins};

        while (trackedCoinsIter.hasNext()) {
            trackedCoinsIter.next();
            QBarSet *valueSet{new QBarSet(trackedCoinsIter.value()->getSymbol())};
            QVector<Coin::value> values{trackedCoinsIter.value()->getRefAllValues()};

            // Previous values
            for (int dayPre{dayPeriod - 1}; dayPre >= 0; dayPre--) {
                if (dayPre >= values.size()) continue;
                if (ui->radioButtonMarketcap->isChecked()) {
                    valueSet->append(values.at(dayPre).marketcap);
                } else if (ui->radioButtonPrice->isChecked()) {
                    valueSet->append(values.at(dayPre).price);
                } else if (ui->radioButtonVolume->isChecked()) {
                    valueSet->append(values.at(dayPre).volume_24h);
                } else if (ui->radioButtonChange->isChecked()) {
                    valueSet->append(values.at(dayPre).changedPercent_24h.toDouble());
                }
            }
            // Current value
            if (ui->radioButtonMarketcap->isChecked()) {
                valueSet->append(trackedCoinsIter.value()->getLastValue().marketcap);
                axisY->setTitleText("$");
            } else if (ui->radioButtonPrice->isChecked()) {
                valueSet->append(trackedCoinsIter.value()->getLastValue().price);
                axisY->setTitleText("$");
            } else if (ui->radioButtonVolume->isChecked()) {
                valueSet->append(trackedCoinsIter.value()->getLastValue().volume_24h);
                axisY->setTitleText("$");
            } else if (ui->radioButtonChange->isChecked()) {
                valueSet->append(trackedCoinsIter.value()->getLastValue().changedPercent_24h.toDouble());
                axisY->setTitleText("%");
            }
            // Append all the value set to series
            series->append(valueSet);
        }
    }

    // Set the categories for the value set
    QStringList dateCategories;
    for (int index{dayPeriod}; index >= 0; index--) {
        dateCategories.append(time.addDays(-index).toString("dd/MM/yyyy"));
    }

    QBarCategoryAxis *axisX{new QBarCategoryAxis};
    axisX->append(dateCategories);
    axisX->setTitleText("Date");
    // axisX->setRange(time.addDays(-ui->sliderPeriod->value()).toString(), time.addDays(0).toString());

    chart->removeAllSeries();
    chart->removeAxis(chart->axisX());
    chart->removeAxis(chart->axisY());
    chart->addSeries(series);
    // chart->createDefaultAxes();
    chart->setTitle("Cryptocurrency Track Bar Chart");
    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);
    // chart->axisY()->max;
    chart->legend()->setAlignment(Qt::AlignTop);
    chartView->setChart(chart);
}
// Pie chart for Available supply only
void MainWindow::drawTrackingPieChart() {
    chartView->chart()->removeAllSeries();
    chartView->chart()->removeAxis(chart->axisX());
    chartView->chart()->removeAxis(chart->axisY());

    QString collectionName{ui->comboBoxCryptoList->currentText()};
    int currentSelectedCoinRow{ui->listWidgetTrackedCoins->currentRow()};
    QStringList selectedCoinInfo;
    if (currentSelectedCoinRow != -1)
        selectedCoinInfo = ui->listWidgetTrackedCoins->item(currentSelectedCoinRow)->text().split(" - ", QString::SplitBehavior::SkipEmptyParts);
    // Initialize pie properties
    long totalAvailableSupplies{};
    QPieSeries *series{new QPieSeries()};
    series->setHoleSize(0.4);

    // Initialize value for our pie series
    if (dataStation->getObservers().contains(collectionName)) {
        // Get collection ptr from dataStation
        DataObserverPtr currentCollection{dataStation->getObservers().value(collectionName)};
        // Get collection's tracked coins
        QHash<QString, CoinPtr> trackedCoins{currentCollection->getTrackedCoins()};
        QHashIterator<QString, CoinPtr> trackedCoinsIter{trackedCoins};
        // let's iterate through all tracked coins and calculate the total available supplies
        while (trackedCoinsIter.hasNext()) {
            trackedCoinsIter.next();
            totalAvailableSupplies += trackedCoinsIter.value()->getAvailable_supply();
        }
        qDebug() << "Total supplies: " << totalAvailableSupplies;
        while (trackedCoinsIter.hasPrevious()) {
            trackedCoinsIter.previous();
            double percentage{static_cast<double>(trackedCoinsIter.value()->getAvailable_supply()) / totalAvailableSupplies * 100.0};
            QString percentageInString{trackedCoinsIter.value()->getSymbol() + ": " + QString::number(percentage, 'f', 2) + "%"};
            // qDebug() << QString::number(static_cast<double>(trackedCoinsIter.value()->getAvailable_supply()) / totalAvailableSupplies, 'f', 6);

            if (currentSelectedCoinRow != -1 && trackedCoinsIter.value()->getSymbol() == selectedCoinInfo.at(0)) {
                QPieSlice *slice = series->append(percentageInString, percentage);
                slice->setExploded();
                slice->setLabelVisible();
            } else {
                series->append(percentageInString, percentage);
            }
        }
    }

    chartView->chart()->addSeries(series);
    chartView->chart()->setTitle("Available Supplies Percentage Chart");
}

void MainWindow::loadCurrentSelectedTrackedCoin(const QString &currentCoinSymbol) {
    QStringList infoList{currentCoinSymbol.split(" - ", QString::SplitBehavior::SkipEmptyParts)};
    if (infoList.size() == 0) return;
    QString coinSymbol{infoList.at(0)};
    // qDebug() << "infolist size: " << infoList.size();
    ui->labelCoinName->setText(infoList.at(0));
    ui->labelCoinIcon->setPixmap(QPixmap(QString(":/ico/colorIcons/%1.png").arg(coinSymbol)));
    if (dataStation->getTrackedCoins().contains(coinSymbol)) {
        // Get the coin is being selected by user
        CoinPtr coinPtr{dataStation->getTrackedCoins().value(coinSymbol)};
        // get coin information and show it
        ui->labelCoinAvailableSupply->setText(QString::number(coinPtr->getAvailable_supply()));
        ui->labelCoinPrice->setText(QString::number(coinPtr->getLastValue().price, 'f'));
        ui->labelCoinMarketCap->setText(QString::number(coinPtr->getLastValue().marketcap, 'f'));
        ui->labelCoinVolume24h->setText(QString::number(coinPtr->getLastValue().volume_24h, 'f'));
        ui->labelChange1h->setText(coinPtr->getLastValue().changedPercent_1h);
        ui->labelChange24h->setText(coinPtr->getLastValue().changedPercent_24h);
    }
}

void MainWindow::updateChartTheme(int themeID) { chartView->chart()->setTheme(static_cast<QChart::ChartTheme>(themeID)); }

void MainWindow::checkCollectionContentsBeforeConfiguringIt() {
    if (ui->comboBoxCryptoList->currentText() == "Choose your Collection")
        QMessageBox::information(this, "Invalid Action", "Please select an existing collection for configuring");
    else {
        DataObserverPtr collectionPtr{dataStation->getRefObservers().value(ui->comboBoxCryptoList->currentText())};
        collectionManagerDialog->showConfigureCurrentCollectionCoin(*dataStation, *collectionPtr.get());
    }
}

void MainWindow::confirmDeletingACollection() {
    QString collectionName{ui->comboBoxCryptoList->currentText()};
    QMessageBox::StandardButton userAnsquer{
        QMessageBox::question(this, "Confirm when delete an collection", QString("Do you actually want to delete %1 collection ? ").arg(collectionName))};
    if (userAnsquer == QMessageBox::StandardButton::Cancel)
        return;
    else {
        if (dataStation->getObservers().contains(collectionName)) {
            // Remove from data station
            dataStation->removeObserver(dataStation->getObservers().value(collectionName));
            ui->comboBoxCryptoList->removeItem(ui->comboBoxCryptoList->currentIndex());
        }
    }
}

void MainWindow::aboutQt() { QMessageBox::aboutQt(this, "About Qt lib"); }
