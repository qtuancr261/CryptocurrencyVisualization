#include "coin.h"

QListWidgetItem &Coin::getDisplayItem()
{
    return displayItem;
}

void Coin::setDisplayItem(const QListWidgetItem &value)
{
    displayItem = value;
}

Coin::Coin(QString name, QString symbol)
    : name{name},
      symbol{symbol},
      displayItem{QListWidgetItem(QIcon(":/ico/coin.png"), name + " - " + symbol)},
      available_supply{},
      lastValue{}
{
    //
}

QString Coin::getName() const
{
    return name;
}

void Coin::setName(const QString &value)
{
    name = value;
}

QString Coin::getSymbol() const
{
    return symbol;
}

void Coin::setSymbol(const QString &value)
{
    symbol = value;
}

long Coin::getAvailable_supply() const
{
    return available_supply;
}

void Coin::setAvailable_supply(long value)
{
    available_supply = value;
}


