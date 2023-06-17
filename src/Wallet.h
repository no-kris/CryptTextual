#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <map>

class Wallet
{
public:
    Wallet();
    ~Wallet();

    void insertCurrency(std::string currType, double deposit);
    bool containsCurrency(std::string currType, double deposit);
    void clearInvalidWalletInput();
    void printWallet();

private:
    std::map<std::string, double> mWalletCurrency;
    double mBalance; // Amount left in account
    double mCoins;   // Amount of coins owned
};

#endif /* WALLET_H */