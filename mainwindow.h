#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "Publisher/coindatastation.h"
#include "collectioncoinmanagementdialog.h"
#include <QtCharts>
#include <QChart>
#include <QChartView>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QPieSeries>
#include <QPieSlice>
#include <QValueAxis>
#include <QComboBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QChartView *getChartView() const;

private:
    Ui::MainWindow *ui;
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
};

#endif // MAINWINDOW_H
