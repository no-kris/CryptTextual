#include "Wallet.h"
#include <iostream>
#include <limits>

Wallet::Wallet() : mBalance(0.0), mCoins(0.0)
{
}

Wallet::~Wallet()
{
}

// Initialize an account with provided deposit and 0 coins owned
void Wallet::insertCurrency(std::string currType, double deposit)
{
}

// Clear input stream if user enters bad input
void Wallet::clearInvalidWalletInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Unrecognizable input, try again ... \n";
}

// @return true if wallet contains passed in currency, else return false
bool Wallet::containsCurrency(std::string currType, double deposit)
{
    return false;
}

void Wallet::printWallet()
{
    std::cout << "Account balance ... $" << mBalance << '\n';
    std::cout << "Coins owned ... " << mCoins << '\n';
}
