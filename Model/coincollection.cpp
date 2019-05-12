#include <utility>

#include "coincollection.h"

const QHash<QString, CoinPtr> &CoinCollection::getTrackedCoins() const { return trackedCoins; }

void CoinCollection::addNewTrackedCoin(const QString &coinSymbol, const CoinPtr &coin) {
    if (!trackedCoins.contains(coinSymbol))
        trackedCoins.insert(coinSymbol, coin);
    else
        qDebug() << "Duplicated Coin";
}

void CoinCollection::removeTrackedCoin(const QString &coinSymbol) {
    if (trackedCoins.remove(coinSymbol))
        qDebug() << "Remove Tracked Coin successfully ";
    else
        qDebug() << "Remove Tracked Coin failed ";
}

const QString &CoinCollection::getName() const { return name; }

void CoinCollection::setName(const QString &value) { name = value; }
CoinCollection::CoinCollection(QString name) : name{std::move(name)} {}

QHash<QString, CoinPtr> &CoinCollection::getRefTrackedCoins() { return trackedCoins; }
