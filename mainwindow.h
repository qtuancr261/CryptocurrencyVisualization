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
#include <QValueAxis>
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
public slots:
    void disableAllToolButtonRelativeWithCollectionList();
    void enableAllToolButtonRelativeWithCollectionList();
    void addNewCollectionNameToComboBoxCryptoList(const QString& collectionName);
    void loadCollectionContents(const QString& collectionName);
    void updateChartProperties();
    void drawTrackingBarChart();
    void drawTrackingLineChart();
};

#endif // MAINWINDOW_H
