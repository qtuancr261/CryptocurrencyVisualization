#ifndef COLLECTIONCOINMANAGEMENTDIALOG_H
#define COLLECTIONCOINMANAGEMENTDIALOG_H

#include <QDialog>
#include <QHelpEvent>
#include <QLineEdit>
#include <QList>
#include <QListWidget>
#include <QMessageBox>
#include <QToolTip>
#include "Model/coincollection.h"
#include "Publisher/coindatastation.h"
namespace Ui {
class CollectionCoinManagementDialog;
}

class CollectionCoinManagementDialog : public QDialog {
    Q_OBJECT
public:
    explicit CollectionCoinManagementDialog(QWidget* parent = nullptr);
    ~CollectionCoinManagementDialog();
    Ui::CollectionCoinManagementDialog* getUi() const;

public slots:
    void showAddNewCollectionCoin();
    void showConfigureCurrentCollectionCoin(const CoinDataStation& coinDataStation, const DataObserver& coinCollection);
    void setAvailableCoins(const QHash<QString, CoinPtr>& availableCoins);
    void loadAvailableCoinsAndTrackedCoins(const CoinDataStation& coinDataStation, const DataObserver& coinCollection);
    void moveSelectedCoinsToTrackedCoins();
    void moveSelectedCoinsToAvailableCoins();
    void moveAllCoinsToTrackedCoins();
    void moveAllCoinsToAvailableCoins();
    void checkCollectionContents();
    // void configureCurrentCollectionContents();
signals:
    void finishedCurrentAction();
    void finishedPreloadAvailableCoins();
    void requestToCreateANewCollectionWith(const QString& collectionName, const QStringList& contents);
    void requestToModifyCurrentCollectionContents(const QString& collectionName, const QStringList& contents);

private:
    Ui::CollectionCoinManagementDialog* ui;
    QHash<QString, CoinPtr> trackedCoins;
    enum class Mode { NoMode, AddNewCollectionMode, ConfigureCurrentCollectionMode };
    Mode dialogMode;
    // QWidget interface
protected:
    // virtual void focusInEvent(QFocusEvent *event) override;
};

#endif  // COLLECTIONCOINMANAGEMENTDIALOG_H
