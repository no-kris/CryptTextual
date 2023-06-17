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
#include "Wallet.h"

class MainAccount
{
public:
    MainAccount();
    ~MainAccount() = default;

    static void test();
    void process();
    void banner();
    void printMenu();
    int getMenuOption();
    void displayMenuOption(int menuOption);
    void printHelp();
    void printMarketStats();
    void printNumberAsks(std::vector<OrderBookEntry> &askEntries);
    void printNumberBids(std::vector<OrderBookEntry> &bidEntries);
    void makeAsk();
    void validateAskRequest(std::string &userInput);
    void makeBid();
    void validateBidRequest(std::string &userInput);
    void clearInvalidInput();
    void continueNextTimeframe();

private:
    std::string mCurrentTime;                   // Timeframe for trading
    OrderBook orderBook{"CryptoDataSheet.csv"}; // Account order book
    Wallet mUsersWallet;
};

#endif /* MAINACCOUNT.H */