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

struct Account
{
    double balance; // Amount left in account
    double coins;   // Amount of coins owned
};

struct Orders // data from csv file
{
    std::vector<OrderBookEntry> orders;
};

// Function prototypes

void test();
void banner();
void loadOrderBook(Orders *orderBook);
double getInitialDeposit();
void initializeAccount(Account *account, double deposit);
void printMenu();
int getMenuOption();
void displayMenuOption(int menuOption, Account *account, Orders *orderBook);
void printHelp();
void printMarketStats(Orders *orderBook);
void makeOffer();
void makeBid();
void printAccount(Account *account);
void continueNext();

#endif /* MAINACCOUNT.H */