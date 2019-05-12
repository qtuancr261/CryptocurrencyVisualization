#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QBarCategoryAxis>
#include <QBarSet>
#include <QChart>
#include <QChartView>
#include <QComboBox>
#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QPieSeries>
#include <QPieSlice>
#include <QValueAxis>
#include <QtCharts>
#include "Publisher/coindatastation.h"
#include "collectioncoinmanagementdialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    QChartView* getChartView() const;

private:
    Ui::MainWindow* ui;
    CoinDataStation* dataStation;
    CollectionCoinManagementDialog* collectionManagerDialog;
    QChartView* chartView;
    QChart* chart;
    void setupAutoCompleterForComboBoxCrytoList();
    void changeSelectedCoinWhenUserSearchItOnLineEditFiler();
public slots:
    void disableAllToolButtonRelativeWithCollectionList();
    void enableAllToolButtonRelativeWithCollectionList();
    void addNewCollectionNameToComboBoxCryptoList(const QString& collectionName);
    void loadCollectionContents(const QString& collectionName);
    void updateChartPeriodProperties();
    void updateChartTrackedValue();
    void updatePieChartSlice();
    void drawTrackingBarChart();
    void drawTrackingPieChart();
    void loadCurrentSelectedTrackedCoin(const QString& currentCoinSymbol);
    void updateChartTheme(int themeID);
    void checkCollectionContentsBeforeConfiguringIt();
    void confirmDeletingACollection();
    void aboutQt();
};

#endif  // MAINWINDOW_H
