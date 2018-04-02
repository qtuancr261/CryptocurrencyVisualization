#include "crywsapi.h"

QString CryWSAPI::getGetDataInSevenDays() const
{
    return hostname + apiCoins + getDataInSevenDays;
}

QString CryWSAPI::getGetDataWithoutAllValues() const
{
    return hostname + apiCoins + getDataWithoutAllValues;
}

CryWSAPI::CryWSAPI()
    : hostname{"https://cryws.herokuapp.com"},
      apiCoins{"/api/coins"},
      getDataInSevenDays{"/"},
      getDataWithoutAllValues{"/nonchart"},
      getSpecificCoinDataWithoutAllValues{"/nonchart/%1"}

{

}
