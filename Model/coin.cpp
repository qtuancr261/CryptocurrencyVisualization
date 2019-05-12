#include "coin.h"

QListWidgetItemPtr &Coin::getRefDisplayItem() { return displayItem; }

void Coin::setDisplayItem(const QListWidgetItemPtr &value) { displayItem = value; }

Coin::~Coin() { qDebug() << "Coin has been deleted"; }

QListWidgetItemPtr Coin::getDisplayItem() const { return displayItem; }

Coin::value &Coin::getLastValue() { return lastValue; }

void Coin::setLastValue(const value &value) { lastValue = value; }

const QVector<Coin::value> &Coin::getAllValues() const { return allValues; }

QVector<Coin::value> &Coin::getRefAllValues() { return allValues; }

void Coin::setAllValues(const QVector<value> &value) { allValues = value; }

Coin::Coin(QString name, QString symbol)
    : name{name}, symbol{symbol}, displayItem{make_shared<QListWidgetItem>(QIcon(":/ico/coin.png"), symbol + " - " + name)}, available_supply{}, lastValue{} {
    //
}

QString Coin::getName() const { return name; }

void Coin::setName(const QString &value) { name = value; }

QString Coin::getSymbol() const { return symbol; }

void Coin::setSymbol(const QString &value) { symbol = value; }

long Coin::getAvailable_supply() const { return available_supply; }

void Coin::setAvailable_supply(long value) { available_supply = value; }
