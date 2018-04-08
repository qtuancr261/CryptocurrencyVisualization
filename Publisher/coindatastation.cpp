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
        // Parse Coin Object and its last Value
        QJsonObject currentObj{jsonArray.at(0).toArray().at(i).toObject()};
        QJsonObject currentValue{currentObj.value("last_values").toObject()};
        // Get the value we want from the key we provide
        QString symbol{currentObj.value("symbol").toString()};
        QString name{currentObj.value("name").toString()};
        long availableSupply{currentObj.value("available_supply").toString().toLong()};

        QDateTime time;
        time.setTime_t(currentValue.value("timeStamp").toInt());
        qDebug() << time.toString("dd MM yyyy");
        //qDebug() << currentValue.value("price").toDouble() << currentValue.value("timeStamp").toDouble();
        CoinPtr currentCoin{make_shared<Coin>(name, symbol)};
        currentCoin->setAvailable_supply(availableSupply);
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
