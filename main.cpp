#include "mainwindow.h"
#include <QApplication>
#include <QtCharts>
#include <QLineSeries>
#include <QSplashScreen>
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

    QLineSeries *series = new QLineSeries();
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
    //![3]

    //![4]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //![4]

    //![5]
    //!
    w.setWindowTitle("Cryptocurrency Visualization");
    w.setCentralWidget(chartView);
    //w.resize(800, 600);
    //w.show();
    splashScreen.finish(&w);
    //![5]
    return a.exec();
}
