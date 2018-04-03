#ifndef COLLECTIONCOINMANAGEMENTDIALOG_H
#define COLLECTIONCOINMANAGEMENTDIALOG_H

#include <QDialog>

namespace Ui {
class CollectionCoinManagementDialog;
}

class CollectionCoinManagementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CollectionCoinManagementDialog(QWidget *parent = 0);
    ~CollectionCoinManagementDialog();

private:
    Ui::CollectionCoinManagementDialog *ui;
};

#endif // COLLECTIONCOINMANAGEMENTDIALOG_H
