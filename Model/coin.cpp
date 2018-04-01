#include "coin.h"

Coin::Coin(QString name, QString symbol)
    : name{name},
      symbol{symbol},
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

QIcon Coin::getIcon() const
{
    return icon;
}

void Coin::setIcon(const QIcon &value)
{
    icon = value;
}

long Coin::getAvailable_supply() const
{
    return available_supply;
}

void Coin::setAvailable_supply(long value)
{
    available_supply = value;
}


