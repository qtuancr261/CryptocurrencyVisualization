#include "coincollection.h"

const QHash<QString, CoinPtr> &CoinCollection::getTrackedCoins() const
{
    return trackedCoins;
}

void CoinCollection::addNewTrackedCoin(const QString &coinSymbol, const CoinPtr &coin)
{
    if (!trackedCoins.contains(coinSymbol))
        trackedCoins.insert(coinSymbol, coin);
    else
        qDebug() << "Duplicated Coin";
}

void CoinCollection::removeTrackedCoin(const QString &coinSymbol)
{
    if(trackedCoins.remove(coinSymbol))
        qDebug() << "Remove Tracked Coin successfully ";
    else
        qDebug() << "Remove Tracked Coin failed ";
}

CoinCollection::CoinCollection(QObject *parent) : QObject(parent)
{

}
