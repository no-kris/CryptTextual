/*
 * Class Name: MainAccount
 * Description: MainAccount is to be used for
 *              maintaining and updating an account, displaying
 *              the menu and getting menu a option from user
 *
 * Author: Kris Treska
 * Date: 2023/06/04
 */

#ifndef MAINACCOUNT_H
#define MAINACCOUNT_H

#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

class MainAccount
{
public:
    MainAccount();
    ~MainAccount() = default;

    static void test();

private:
    void banner();
    double getInitialDeposit();
    void initializeAccount(double deposit);
    void printMenu();
    int getMenuOption();
    void displayMenuOption(int menuOption, OrderBook &orderBook);
    void printHelp();
    void printMarketStats(OrderBook &orderBook);
    void printNumberAsks(std::vector<OrderBookEntry> &askEntries);
    void printNumberBids(std::vector<OrderBookEntry> &bidEntries);
    void makeAsk(OrderBook &orderBook);
    void validateAskRequest(std::string &userInput, OrderBook &orderBook);
    void makeBid(OrderBook &orderBook);
    void validateBidRequest(std::string &userInput, OrderBook &orderBook);
    void clearInvalidInput();
    void printAccount();
    void continueNextTimeframe(OrderBook &orderBook);

private:
    double mBalance;          // Amount left in account
    double mCoins;            // Amount of coins owned
    std::string mCurrentTime; // Timeframe for trading
};

#endif /* MAINACCOUNT.H */