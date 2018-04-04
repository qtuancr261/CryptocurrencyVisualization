#include "collectioncoinmanagementdialog.h"
#include "ui_collectioncoinmanagementdialog.h"

CollectionCoinManagementDialog::CollectionCoinManagementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CollectionCoinManagementDialog)
{
    ui->setupUi(this);
    ui->listWidgetAvailableCoins->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->listWidgetTrackedCoins->setSelectionMode(QAbstractItemView::ExtendedSelection);
    QObject::connect(ui->pushButtonMoveItemsToRight, &QPushButton::clicked, this, &CollectionCoinManagementDialog::moveSelectedCoinsToTrackedCoins);
    QObject::connect(ui->pushButtonMoveItemToLeft, &QPushButton::clicked, this, &CollectionCoinManagementDialog::moveSelectedCoinsToAvailableCoins);
    QObject::connect(ui->pushButtonMoveAllToRight, &QPushButton::clicked, this, &CollectionCoinManagementDialog::moveAllCoinsToTrackedCoins);
    QObject::connect(ui->pushButtonMoveAllToLeft, &QPushButton::clicked, this, &CollectionCoinManagementDialog::moveAllCoinsToAvailableCoins);
}

CollectionCoinManagementDialog::~CollectionCoinManagementDialog()
{
    delete ui;
}

void CollectionCoinManagementDialog::showAddNewCollectionCoin()
{
    this->setWindowTitle("Add new collection");
    this->setWindowIcon(QIcon(":/ico/collectionAdd.ico"));
    this->show();
}

void CollectionCoinManagementDialog::loadAvailableCoins(const QHash<QString, CoinPtr> &availableCoins)
{
    QHashIterator<QString, CoinPtr> iterQHash{availableCoins};
    while(iterQHash.hasNext())
    {
        iterQHash.next();
        ui->listWidgetAvailableCoins->addItem(&iterQHash.value()->getDisplayItem());
    }
    //ui->listWidgetAvailableCoins->show();
    //showAddNewCollectionCoin();
}

void CollectionCoinManagementDialog::loadAvailableCoinsAndTrackedCoins(const CoinDataStation &coinDataStation, const CoinCollection &coinCollection)
{
    QHash<QString, CoinPtr> availableCoinsFromServer{coinDataStation.getTrackedCoins()};
    QHash<QString, CoinPtr> trackedCoinFromCurrentCollection{coinCollection.getTrackedCoins()};
    // Removed old Items
    ui->listWidgetAvailableCoins->clear();
    ui->listWidgetTrackedCoins->clear();
    // Let's put all Coins in the right position
    QHashIterator<QString, CoinPtr> iterQHash{availableCoinsFromServer};
    while(iterQHash.hasNext())
    {
        iterQHash.next();
        if (trackedCoinFromCurrentCollection.contains(iterQHash.key()))
            ui->listWidgetAvailableCoins->addItem(&iterQHash.value()->getDisplayItem());
        else
            ui->listWidgetTrackedCoins->addItem(&iterQHash.value()->getDisplayItem());
    }

}

void CollectionCoinManagementDialog::moveSelectedCoinsToAvailableCoins()
{
    if(ui->listWidgetTrackedCoins->selectedItems().count() < 1)
        qDebug() << "Cannot move anything";
    else
    {
        QList<QListWidgetItem*> currentSelectedDisplayItems{ui->listWidgetTrackedCoins->selectedItems()};
        for (const QListWidgetItem* item : currentSelectedDisplayItems)
        {
            int itemRow{ui->listWidgetTrackedCoins->row(item)};
            ui->listWidgetAvailableCoins->addItem(ui->listWidgetTrackedCoins->takeItem(itemRow));
        }
    }
}

void CollectionCoinManagementDialog::moveAllCoinsToTrackedCoins()
{
    //qDebug() << ui->listWidgetAvailableCoins->count();
    while (ui->listWidgetAvailableCoins->count() > 0)
    {
        ui->listWidgetTrackedCoins->addItem(ui->listWidgetAvailableCoins->takeItem(0));
    }
}

void CollectionCoinManagementDialog::moveAllCoinsToAvailableCoins()
{
    while (ui->listWidgetTrackedCoins->count() > 0)
    {
        ui->listWidgetAvailableCoins->addItem(ui->listWidgetTrackedCoins->takeItem(0));
    }
}

void CollectionCoinManagementDialog::moveSelectedCoinsToTrackedCoins()
{
    if(ui->listWidgetAvailableCoins->selectedItems().count() < 1)
        qDebug() << "Cannot move anything";
    else
    {
        QList<QListWidgetItem*> currentSelectedDisplayItems{ui->listWidgetAvailableCoins->selectedItems()};
        for (const QListWidgetItem* item : currentSelectedDisplayItems)
        {
            int itemRow{ui->listWidgetAvailableCoins->row(item)};
            ui->listWidgetTrackedCoins->addItem(ui->listWidgetAvailableCoins->takeItem(itemRow));
        }
    }

}
