#include "collectioncoinmanagementdialog.h"
#include "ui_collectioncoinmanagementdialog.h"

CollectionCoinManagementDialog::CollectionCoinManagementDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::CollectionCoinManagementDialog), dialogMode{Mode::NoMode} {
    ui->setupUi(this);
    this->setToolTip("GTK");
    ui->lineEditCollectionName->setToolTip("Collection name must not be empty");
    ui->listWidgetAvailableCoins->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->listWidgetTrackedCoins->setSelectionMode(QAbstractItemView::ExtendedSelection);
    QObject::connect(ui->pushButtonMoveItemsToRight, &QPushButton::clicked, this, &CollectionCoinManagementDialog::moveSelectedCoinsToTrackedCoins);
    QObject::connect(ui->pushButtonMoveItemToLeft, &QPushButton::clicked, this, &CollectionCoinManagementDialog::moveSelectedCoinsToAvailableCoins);
    QObject::connect(ui->pushButtonMoveAllToRight, &QPushButton::clicked, this, &CollectionCoinManagementDialog::moveAllCoinsToTrackedCoins);
    QObject::connect(ui->pushButtonMoveAllToLeft, &QPushButton::clicked, this, &CollectionCoinManagementDialog::moveAllCoinsToAvailableCoins);

    QObject::connect(ui->buttonControllerBox, &QDialogButtonBox::accepted, this, &CollectionCoinManagementDialog::checkCollectionContents);
    QObject::connect(this, &CollectionCoinManagementDialog::accepted, this, &CollectionCoinManagementDialog::finishedCurrentAction);
    QObject::connect(this, &CollectionCoinManagementDialog::rejected, this, &CollectionCoinManagementDialog::finishedCurrentAction);
}

CollectionCoinManagementDialog::~CollectionCoinManagementDialog() { delete ui; }

void CollectionCoinManagementDialog::showAddNewCollectionCoin() {
    this->setWindowTitle("Add new collection");
    this->setWindowIcon(QIcon(":/ico/collectionAdd.ico"));
    ui->lineEditCollectionName->setEnabled(true);
    QHashIterator<QString, CoinPtr> iterQHash{trackedCoins};
    // Remove all items when a user loads our dialog in AddNewCollectionMode;
    if (ui->listWidgetAvailableCoins->count() == 0 && ui->listWidgetTrackedCoins->count() == 0) {
        while (iterQHash.hasNext()) {
            iterQHash.next();
            ui->listWidgetAvailableCoins->addItem(iterQHash.value()->getDisplayItem().get());
        }
    } else {
        while (ui->listWidgetTrackedCoins->count() > 0) ui->listWidgetAvailableCoins->addItem(ui->listWidgetTrackedCoins->takeItem(0));
    }
    this->show();
    this->raise();
    // set current mode
    dialogMode = Mode::AddNewCollectionMode;
}

void CollectionCoinManagementDialog::showConfigureCurrentCollectionCoin(const CoinDataStation &coinDataStation, const DataObserver &coinCollection) {
    this->setWindowTitle("Configure collection");
    this->setWindowIcon(QIcon(":/ico/collectionSetting.ico"));
    ui->lineEditCollectionName->setEnabled(false);
    ui->lineEditCollectionName->setText(coinCollection.getName());
    loadAvailableCoinsAndTrackedCoins(coinDataStation, coinCollection);
    this->show();
    this->raise();
    dialogMode = Mode::ConfigureCurrentCollectionMode;
}

void CollectionCoinManagementDialog::setAvailableCoins(const QHash<QString, CoinPtr> &availableCoins) {
    trackedCoins = availableCoins;
    emit finishedPreloadAvailableCoins();
}

void CollectionCoinManagementDialog::loadAvailableCoinsAndTrackedCoins(const CoinDataStation &coinDataStation, const DataObserver &coinCollection) {
    QHash<QString, CoinPtr> availableCoinsFromServer{coinDataStation.getTrackedCoins()};
    QHash<QString, CoinPtr> trackedCoinFromCurrentCollection{coinCollection.getTrackedCoins()};
    qDebug() << "Collection Coin size: " << trackedCoinFromCurrentCollection.size();
    // Removed old Items
    while (ui->listWidgetAvailableCoins->count() > 0) {
        ui->listWidgetAvailableCoins->takeItem(0);
    }
    while (ui->listWidgetTrackedCoins->count() > 0) {
        ui->listWidgetTrackedCoins->takeItem(0);
    }
    // Let's put all Coins in the right position
    QHashIterator<QString, CoinPtr> iterQHash{availableCoinsFromServer};
    while (iterQHash.hasNext()) {
        iterQHash.next();
        if (trackedCoinFromCurrentCollection.contains(iterQHash.key())) ui->listWidgetTrackedCoins->addItem(iterQHash.value()->getDisplayItem().get());
        // ui->listWidgetAvailableCoins->addItem(iterQHash.value()->getDisplayItem().get());
        // qDebug() << "cointain";
        else
            ui->listWidgetAvailableCoins->addItem(iterQHash.value()->getDisplayItem().get());
        // ui->listWidgetTrackedCoins->addItem(iterQHash.value()->getDisplayItem().get());
        // qDebug() << " - ";
    }
}

void CollectionCoinManagementDialog::moveSelectedCoinsToAvailableCoins() {
    if (ui->listWidgetTrackedCoins->selectedItems().count() < 1)
        qDebug() << "Cannot move anything";
    else {
        QList<QListWidgetItem *> currentSelectedDisplayItems{ui->listWidgetTrackedCoins->selectedItems()};
        for (const QListWidgetItem *item : currentSelectedDisplayItems) {
            int itemRow{ui->listWidgetTrackedCoins->row(item)};
            ui->listWidgetAvailableCoins->addItem(ui->listWidgetTrackedCoins->takeItem(itemRow));
        }
    }
}

void CollectionCoinManagementDialog::moveAllCoinsToTrackedCoins() {
    // qDebug() << ui->listWidgetAvailableCoins->count();
    while (ui->listWidgetAvailableCoins->count() > 0) {
        ui->listWidgetTrackedCoins->addItem(ui->listWidgetAvailableCoins->takeItem(0));
    }
}

void CollectionCoinManagementDialog::moveAllCoinsToAvailableCoins() {
    while (ui->listWidgetTrackedCoins->count() > 0) {
        ui->listWidgetAvailableCoins->addItem(ui->listWidgetTrackedCoins->takeItem(0));
    }
}

void CollectionCoinManagementDialog::checkCollectionContents() {
    if (dialogMode == Mode::AddNewCollectionMode) {
        if (ui->lineEditCollectionName->text().isEmpty())
            QMessageBox::warning(this, "Cannot create new collection", "Collection name must not be empty");
        else if (ui->listWidgetTrackedCoins->count() == 0)
            QMessageBox::warning(this, "Cannot create new collection", "You must choose at least one item for collection contents");
        else {
            this->accept();
            QStringList contentsSymbol;
            for (int index{}; index < ui->listWidgetTrackedCoins->count(); index++) {
                contentsSymbol.append(ui->listWidgetTrackedCoins->item(index)->text().section(" ", 0, 0));
                // qDebug() << ui->listWidgetTrackedCoins->item(index)->text().section("
                // ", 0, 0);
            }
            emit requestToCreateANewCollectionWith(ui->lineEditCollectionName->text(), contentsSymbol);
        }
    } else if (dialogMode == Mode::ConfigureCurrentCollectionMode) {
        if (ui->listWidgetTrackedCoins->count() == 0)
            QMessageBox::warning(this, "Cannot modify the collection", "You must choose at least one item for collection contents");
        else {
            this->accept();
            QStringList symbolList;
            for (int index{}; index < ui->listWidgetTrackedCoins->count(); index++) {
                symbolList.append(ui->listWidgetTrackedCoins->item(index)->text().section(" ", 0, 0));
                qDebug() << ui->listWidgetTrackedCoins->item(index)->text().section(" ", 0, 0);
            }
            emit requestToModifyCurrentCollectionContents(ui->lineEditCollectionName->text(), symbolList);
        }
    }
}

Ui::CollectionCoinManagementDialog *CollectionCoinManagementDialog::getUi() const { return ui; }

void CollectionCoinManagementDialog::moveSelectedCoinsToTrackedCoins() {
    if (ui->listWidgetAvailableCoins->selectedItems().count() < 1)
        qDebug() << "Cannot move anything";
    else {
        QList<QListWidgetItem *> currentSelectedDisplayItems{ui->listWidgetAvailableCoins->selectedItems()};
        for (const QListWidgetItem *item : currentSelectedDisplayItems) {
            int itemRow{ui->listWidgetAvailableCoins->row(item)};
            ui->listWidgetTrackedCoins->addItem(ui->listWidgetAvailableCoins->takeItem(itemRow));
        }
    }
}

/*void CollectionCoinManagementDialog::focusInEvent(QFocusEvent *event)
{
    QHelpEvent* hevent{new QHelpEvent(QEvent::ToolTip,
QPoint(ui->lineEditCollectionName->pos().x(),
ui->lineEditCollectionName->pos().y()), QPoint(QCursor::pos().x(),
QCursor::pos().y()))}; QApplication::postEvent(this, hevent);
    QDialog::focusInEvent(event);
}*/
