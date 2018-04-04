#ifndef COLLECTIONCOINMANAGEMENTDIALOG_H
#define COLLECTIONCOINMANAGEMENTDIALOG_H

#include <QDialog>
#include <QListWidget>
#include "Publisher/coindatastation.h"
#include "Model/coincollection.h"
#include <QList>
namespace Ui {
class CollectionCoinManagementDialog;
}

class CollectionCoinManagementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CollectionCoinManagementDialog(QWidget *parent = nullptr);
    ~CollectionCoinManagementDialog();
public slots:
    void showAddNewCollectionCoin();
    void loadAvailableCoins(const QHash<QString, CoinPtr>& availableCoins);
    void loadAvailableCoinsAndTrackedCoins(const CoinDataStation& coinDataStation, const CoinCollection& coinCollection);
    void moveSelectedCoinsToTrackedCoins();
    void moveSelectedCoinsToAvailableCoins();
    void moveAllCoinsToTrackedCoins();
    void moveAllCoinsToAvailableCoins();
private:
    Ui::CollectionCoinManagementDialog *ui;
};

#endif // COLLECTIONCOINMANAGEMENTDIALOG_H
