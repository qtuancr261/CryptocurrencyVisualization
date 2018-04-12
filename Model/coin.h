#ifndef COIN_H
#define COIN_H
#include <QString>
#include <QIcon>
#include <QVector>
#include <QListWidgetItem>
#include <QtDebug>
#include <QDateTime>
#include <memory>
using std::shared_ptr;
using std::make_shared;
using QListWidgetItemPtr = shared_ptr<QListWidgetItem>;
using ulong = unsigned long;
class Coin
{
private:
    QString name;
    QString symbol;
    QListWidgetItemPtr displayItem;
    long available_supply;
public:
    explicit Coin(QString name, QString symbol);
    struct value
    {
        QDateTime timeStamp;
        double price;
        double marketcap;
        double volume_24h;
        QString changedPercent_1h;
        QString changedPercent_24h;
    };
    QString getName() const;
    void setName(const QString &value);
    QString getSymbol() const;
    void setSymbol(const QString &value);
    long getAvailable_supply() const;
    void setAvailable_supply(long value);
    QListWidgetItemPtr& getRefDisplayItem();
    void setDisplayItem(const QListWidgetItemPtr &value);
    ~Coin();
    QListWidgetItemPtr getDisplayItem() const;
    value& getLastValue();
    void setLastValue(const value &value);
    const QVector<value>& getAllValues() const;
    QVector<value>& getRefAllValues();

    void setAllValues(const QVector<value> &value);
private:
    value lastValue;
    QVector<value> allValues;
};

#endif // COIN_H
