#include "coindatastation.h"

const QHash<QString, CoinPtr> &CoinDataStation::getTrackedCoins() const
{
    return trackedCoins;
}

CoinDataStation::CoinDataStation(QObject *parent)
    : QObject(parent),
      networkManager{new QNetworkAccessManager(this)}
{
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(gotLastValueOfALLCoins(QNetworkReply*)));
}

void CoinDataStation::getLastValueOfAllCoins()
{
    networkManager->get(QNetworkRequest(QUrl(API.getGetDataWithoutAllValues())));
}

void CoinDataStation::gotLastValueOfALLCoins(QNetworkReply *replyFromServer)
{
    //qDebug() << replyFromServer->readAll();
    QString jsonString{replyFromServer->readAll()};
    QJsonDocument jsonDoc{QJsonDocument::fromJson(jsonString.toUtf8())};
    if (jsonDoc.isEmpty())
        qDebug() << "Empty";
    else if (jsonDoc.isObject())
        qDebug() << "Object";
    else if (jsonDoc.isArray())
        qDebug() << "Array";
    QJsonArray jsonArray{jsonDoc.array()};
    for (int i{}; i < jsonArray.at(0).toArray().size(); i++)
    {
        QJsonObject currentObj{jsonArray.at(0).toArray().at(i).toObject()};
        QJsonObject currentValue{currentObj.value("last_values").toObject()};
        QString symbol{currentObj.value("symbol").toString()};
        QString name{currentObj.value("name").toString()};
        //qDebug() << currentValue.value("price").toDouble() << currentValue.value("timeStamp").toDouble();
        CoinPtr currentCoin{make_shared<Coin>(name, symbol)};
        trackedCoins.insert(symbol, currentCoin);
        //qDebug() << jsonArray.at(0).toArray().at(i).toObject().value("symbol").toString();
        //
    }
    emit parseLastValueOfAllCoinsCompleted(trackedCoins);
}


void CoinDataStation::registerObserver(const DataObserverPtr &observer)
{
}

void CoinDataStation::removeObserver(const DataObserverPtr &observer)
{
}

void CoinDataStation::notifyAllObservers()
{
}
