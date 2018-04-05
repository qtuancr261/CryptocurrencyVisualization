#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "Publisher/coindatastation.h"
#include "collectioncoinmanagementdialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CoinDataStation* dataStation;
    CollectionCoinManagementDialog* collectionManagerDialog;

public slots:
    void disableAllToolButtonRelativeWithCollectionList();
    void enableAllToolButtonRelativeWithCollectionList();
};

#endif // MAINWINDOW_H
