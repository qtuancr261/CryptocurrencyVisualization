#ifndef COINCOLLECTION_H
#define COINCOLLECTION_H

#include <QObject>
#include "Observer/dataobserver.h"
#include "Model/coin.h"
class CoinCollection : public QObject, public DataObserver
{
    Q_OBJECT
private:
    QVector<Coin*> coins;
public:
    explicit CoinCollection(QObject *parent = nullptr);

signals:

public slots:
};

#endif // COINCOLLECTION_H
