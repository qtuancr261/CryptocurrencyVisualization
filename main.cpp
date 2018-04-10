#include "mainwindow.h"
#include <QApplication>
#include <QtCharts>
#include <QLineSeries>
#include <QSplashScreen>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QPixmap>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen splashScreen;
    splashScreen.setPixmap(QPixmap(":/ico/splashScreen.jpg"));
    splashScreen.show();
    splashScreen.showMessage("Updating From Server......", Qt::AlignBottom | Qt::AlignLeft, Qt::white);
    //a.processEvents();
    MainWindow w;

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
    series->attachAxis(axisY);
    //![3]*/
    /*QBarSet* btcSet{new QBarSet("BTC")};
    QBarSet* ethSet{new QBarSet("ETH")};
    QBarSet* nycSet{new QBarSet("NYC")};
    QBarSet* bsdSet{new QBarSet("BSD")};
    QBarSet* qtumSet{new QBarSet("QTUMC")};

    *btcSet << 7500 << 7325 << 8750 << 7840 << 7522 << 7140 << 6988 << 6880;
    *ethSet << 6500 << 6325 << 5150 << 5822 << 7822 << 7680 << 5988 << 5880;
    *nycSet << 2800 << 4325 << 3750 << 3840 << 3522 << 4140 << 3988 << 3880;
    *bsdSet << 3500 << 2325 << 4750 << 4840 << 5522 << 3140 << 4900 << 4880;
    *qtumSet << 1500 << 1300 << 750 << 840 << 522 << 1140 << 988 << 1880;

    QBarSeries* series{new QBarSeries()};
    series->append(btcSet);
    series->append(ethSet);
    series->append(nycSet);
    series->append(bsdSet);
    series->append(qtumSet);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Cryptocurrency Track Bar Chart");
    chart->setAnimationOptions(QChart::SeriesAnimations | QChart::GridAxisAnimations);
    chart->setTheme(QChart::ChartThemeQt);
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("USD");
    axisY->setLabelFormat("%i");
    axisY->setTickCount(series->count());

    QStringList dateCategories;
    dateCategories << "01/04/2018" << "02/04/2018" << "03/04/2018" << "04/04/2018" << "05/04/2018" << "06/04/2018" << "07/04/2018" << "08/04/2018";
    QBarCategoryAxis* axis{new QBarCategoryAxis};
    axis->append(dateCategories);
    axis->setTitleText("Date");
    axis->setRange("01/04/2018", "03/04/2018");
    //chart->createDefaultAxes();
    chart->setAxisX(axis, series);
    chart->setAxisY(axisY, series);


    //![4]
    //QChartView *chartView = new QChartView(chart);
    //chartView->setRenderHint(QPainter::Antialiasing);
    //![4]

    //![5]
    //!
    */
    w.setWindowTitle("Cryptocurrency Visualization");
    //w.getChartView()->setChart(chart);
    //w.resize(800, 600);
    //w.show();
    splashScreen.finish(&w);
    //![5]
    return a.exec();
}
