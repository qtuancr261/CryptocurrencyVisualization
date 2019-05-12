#include "crywsapi.h"

QUrl CryWSAPI::getMaxValueIn7DaysOfAllCoinsURL() const { return QUrl(hostname + apiCoins + getMaxValueIn7DaysOfAllCoins); }
QUrl CryWSAPI::getLastValueOfAllCoinsUrl() const { return QUrl(hostname + apiCoins + getLastValueOfAllCoins); }

CryWSAPI::CryWSAPI()
    : hostname{"https://cryws.herokuapp.com"},
      apiCoins{"/api/coins"},
      getMaxValueIn7DaysOfAllCoins{"/chart7days"},
      getLastValueOfAllCoins{"/nonchart"},
      getSpecificCoinDataWithoutAllValues{"/nonchart/%1"} {}
