#ifndef COLLECTIONCOINMANAGEMENTDIALOG_H
#define COLLECTIONCOINMANAGEMENTDIALOG_H

#include <QDialog>
#include <QListWidget>
#include "Publisher/coindatastation.h"
#include "Model/coincollection.h"
#include <QList>
#include <QMessageBox>
#include <QHelpEvent>
#include <QToolTip>
#include <QLineEdit>
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
    void showConfigureCurrentCollectionCoin();
    void getAvailableCoins(const QHash<QString, CoinPtr>& availableCoins);
    void loadAvailableCoinsAndTrackedCoins(const CoinDataStation& coinDataStation, const CoinCollection& coinCollection);
    void moveSelectedCoinsToTrackedCoins();
    void moveSelectedCoinsToAvailableCoins();
    void moveAllCoinsToTrackedCoins();
    void moveAllCoinsToAvailableCoins();
    void checkNewCollectionContents();
signals:
    void finishedCurrentAction();
    void finishedPreloadAvailableCoins();
private:
    Ui::CollectionCoinManagementDialog *ui;
    QHash<QString, CoinPtr> trackedCoins;
    enum class Mode
    {
        NoMode,
        AddNewCollectionMode,
        ConfigureCurrentCollectionMode
    };
    Mode dialogMode;
    // QWidget interface
protected:
    //virtual void focusInEvent(QFocusEvent *event) override;
};

#endif // COLLECTIONCOINMANAGEMENTDIALOG_H
