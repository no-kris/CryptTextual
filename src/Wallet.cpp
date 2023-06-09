#include "Wallet.h"
#include <iostream>
#include "CSVFileReader.h"

Wallet::Wallet() : mBalance(0.0)
{
}

Wallet::~Wallet()
{
}

// Initialize an account with provided currency type and amount
void Wallet::insertCurrency(std::string currType, double amount)
{
    if (amount < 0)
    {
        throw std::exception{};
    }
    if (mWalletCurrency.count(currType) == 0)
    {
        mBalance = 0;
    }
    else
    {
        mBalance = mWalletCurrency[currType];
    }
    mBalance += amount;
    mWalletCurrency[currType] = mBalance;
}

// @return true if currency is in wallet, else return false
bool Wallet::removeCurrency(std::string currType, double amount)
{
    if (amount < 0)
    {
        return false;
    }
    if (mWalletCurrency.count(currType) == 0)
    {
        return false;
    }
    else
    {
        // Check if there is enough
        if (containsCurrency(currType, amount))
        {
            mWalletCurrency[currType] -= amount;
            return true;
        }
        else
        {
            return false;
        }
    }
}

// @return true if wallet contains passed in currency, else return false
bool Wallet::containsCurrency(std::string currType, double amount)
{
    if (mWalletCurrency.count(currType) == 0)
    {
        return false;
    }
    else
    {
        return mWalletCurrency[currType] >= amount;
    }
}

// @return true if wallet can fullfill ask or bid, else return false
bool Wallet::canFulfillOrder(OrderBookEntry order)
{
    std::string orderProduct = order.getProduct();
    std::vector<std::string> currencies = CSVFileReader::tokenise(orderProduct, '/');
    if (order.getOrderType() == OrderBookType::ask)
    {
        double amount = order.getAmount();
        std::string currencyType = currencies[0];
        std::cout << "Wallet::canFulfillOrder " << currencyType << " , " << amount << '\n';
        return containsCurrency(currencyType, amount);
    }
    if (order.getOrderType() == OrderBookType::bid)
    {
        double amount = order.getAmount() * order.getPrice();
        std::string currencyType = currencies[1];
        std::cout << "Wallet::canFulfillOrder " << currencyType << " , " << amount << '\n';
        return containsCurrency(currencyType, amount);
    }
    return false;
}

// @param sale process sale for updating users wallet
void Wallet::processSale(OrderBookEntry &sale)
{
    std::string orderProduct = sale.getProduct();
    std::vector<std::string> currencies = CSVFileReader::tokenise(orderProduct, '/');
    if (sale.getOrderType() == OrderBookType::asksale)
    {
        double moneySpent = sale.getAmount();
        std::string currencySpent = currencies[0];
        double moneyGained = sale.getAmount() * sale.getPrice();
        std::string currencyGained = currencies[1];
        mWalletCurrency[currencySpent] -= moneySpent;
        mWalletCurrency[currencyGained] += moneyGained;
    }
    if (sale.getOrderType() == OrderBookType::bidsale)
    {
        double moneyGained = sale.getAmount();
        std::string currencyGained = currencies[0];
        double moneySpent = sale.getAmount() * sale.getPrice();
        std::string currencySpent = currencies[1];
        mWalletCurrency[currencySpent] -= moneySpent;
        mWalletCurrency[currencyGained] += moneyGained;
    }
}

// Print content of wallet, as a pair of currency type and currency amount
void Wallet::printWallet()
{
    std::cout << "\n============== Account =================\n";
    std::string wallet;
    for (std::pair<std::string, double> pair : mWalletCurrency)
    {
        std::string currencyName = pair.first;
        double currencyAmount = pair.second;
        wallet += currencyName + " ... " + std::to_string(currencyAmount) + '\n';
    }
    std::cout << wallet;
}
