#include "collectioncoinmanagementdialog.h"
#include "ui_collectioncoinmanagementdialog.h"

CollectionCoinManagementDialog::CollectionCoinManagementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CollectionCoinManagementDialog)
{
    ui->setupUi(this);
}

CollectionCoinManagementDialog::~CollectionCoinManagementDialog()
{
    delete ui;
}

void CollectionCoinManagementDialog::showAddNewCollectionCoin()
{
    this->setWindowTitle("Add new collection");
    this->setWindowIcon(QIcon(":/ico/collectionAdd.ico"));
    this->exec();
}
