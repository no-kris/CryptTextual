#ifndef WALLET_H
#define WALLET_H

#include <string>
#include "OrderBookEntry.h"
#include <map>

class Wallet
{
public:
    Wallet();
    ~Wallet();

    void insertCurrency(std::string currType, double amount);
    bool removeCurrency(std::string currType, double amount);
    bool containsCurrency(std::string currType, double amount);
    bool canFulfillOrder(OrderBookEntry order);
    void processSale(OrderBookEntry &sale);
    void printWallet();

private:
    std::map<std::string, double> mWalletCurrency;
    double mBalance; // Amount left in account
};

#endif /* WALLET_H */