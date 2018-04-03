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
