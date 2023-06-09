/*
 * File Name: MainAccount.h
 * Description: This file contains functions to be used for
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

struct Account
{
    double balance; // Amount left in account
    double coins;   // Amount of coins owned
};

// Function prototypes

void test();
void banner();
double getInitialDeposit();
void initializeAccount(Account *account, double deposit);
void printMenu(const std::string &currentTime);
int getMenuOption(const std::string &currentTime);
void displayMenuOption(int menuOption, Account *account, OrderBook &orderBook, std::string &timeframe);
void printHelp();
void printMarketStats(OrderBook &orderBook, std::string &timeframe);
void makeOffer();
void makeBid();
void printAccount(Account *account);
void continueNextTimeframe(std::string &timeframe, OrderBook &orderBook);

#endif /* MAINACCOUNT.H */