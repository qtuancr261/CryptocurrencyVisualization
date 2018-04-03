#include "coindatastation.h"

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
        qDebug() << currentObj.value("symbol").toString() << " - " << currentObj.value("name").toString();
        qDebug() << currentValue.value("price").toString() << currentValue.value("timeStamp").toString();

        //qDebug() << jsonArray.at(0).toArray().at(i).toObject().value("symbol").toString();
        //
    }
    /*QJsonArray jsonArray2{jsonArray.at(0)};
    if (jsonArray2.isEmpty())
        qDebug() << "Empty";
    else if (jsonArray2.at(0).isObject())
        qDebug() << "Object";
    else if (jsonArray2.at(0).isArray())
        qDebug() << "Array";
    QJsonArray jsonArray3{jsonArray2.at(0)};
    QJsonArray jsonArray4{jsonArray3.at(0).toArray()};
    qDebug() << jsonArray3.at(0).toArray().at(0);*/
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
