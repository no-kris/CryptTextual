/*
 * File Name: MainAccount.cpp
 * Description: This file contains the function definitions from MainAccount.h
 *
 * Author: Kris Treska
 * Date: 2023/06/04
 */

#include <string>
#include "MainAccount.h"
#include "CSVFileReader.h"

// Test program
void test()
{
    banner();
    OrderBook orderBook("CryptoDataSheet.csv");
    std::string currentTime = orderBook.getEarliestTime();
    Account userAccount;
    double initialDeposit = getInitialDeposit();
    initializeAccount(&userAccount, initialDeposit);
    int menuOption = 0;
    while (menuOption != 7)
    {
        menuOption = getMenuOption(currentTime);
        displayMenuOption(menuOption, &userAccount, orderBook, currentTime);
    } // EO while (menuOption != 7)
}

// Display banner
void banner()
{
    std::cout << "============================================================\n"
              << "CRYPTTEXTUAL: Crypto Trading Program\n\n"
              << "Learn and Practice Crypto Trading.\n\n"
              << "Hands-on trading simulation  |  Practice trading strategies\n"
              << "============================================================\n\n";
}

// Return a value to create an initial account balance
double getInitialDeposit()
{
    double initialDeposit = 0.0;
    do
    {
        std::cout << "Enter an initial deposit ... ";
        std::cin >> initialDeposit;
        if (initialDeposit < 0)
        {
            std::cout << "Cannot start with a negative balance ... \n";
        }
    } while (initialDeposit < 0);
    return initialDeposit;
}

// Initialize an account with provided deposit and 0 coins owned
void initializeAccount(Account *account, double deposit)
{
    account->balance = deposit;
    account->coins = 0.0;
}

// Display menu options
void printMenu(const std::string &currentTime)
{
    std::cout << "\nCurrent time ... " << currentTime << '\n';
    std::cout << "\n============== MENU ==============\n"
              << "| Select an option (1 ... 6)     |\n"
              << "| Press 1 to print help          |\n"
              << "| Press 2 to view exchange stats |\n"
              << "| Press 3 to make an offer       |\n"
              << "| Press 4 to make a bid          |\n"
              << "| Press 5 to view your account   |\n"
              << "| Press 6 to continue            |\n"
              << "| Press 7 to exit application    |\n"
              << "==================================\n";
}

// Return an integer corresponding to menu option
int getMenuOption(const std::string &currentTime)
{
    printMenu(currentTime);
    int menuChoice = 0;
    std::cout << "Enter choice ... ";
    std::cin >> menuChoice;
    return menuChoice;
}

// @param menuOption represents a case to perform correct operation
// @param account represents account to perform operation on
void displayMenuOption(int menuOption, Account *account, OrderBook &orderBook, std::string &timeframe)
{
    switch (menuOption)
    {
    case 1:
        printHelp();
        break;
    case 2:
        printMarketStats(orderBook, timeframe);
        break;
    case 3:
        makeOffer();
        break;
    case 4:
        makeBid();
        break;
    case 5:
        printAccount(account);
        break;
    case 6:
        continueNextTimeframe(timeframe, orderBook);
        break;
    case 7:
        std::cout << "Now ending application, bye!\n";
        break;
    default:
        std::cerr << "Not a valid option, try again ... \n";
        // TODO: handleInvalidOption();
        break;
    } // EO switch (menuOption)
}

// Clarify each menu option
void printHelp()
{
    std::cout << "\n================ HELP ================\n"
              << "Option 1: Print Help\n"
              << "   - This option displays the help menu,\n"
              << "     providing clarifications for each option.\n"
              << "\n"
              << "Option 2: View Exchange Stats\n"
              << "   - This option allows you to view the current\n"
              << "     statistics and information about the exchange.\n"
              << "\n"
              << "Option 3: Make an Offer\n"
              << "   - With this option, you can make an offer\n"
              << "     to buy or sell assets on the exchange platform.\n"
              << "\n"
              << "Option 4: Make a Bid\n"
              << "   - Use this option to make a bid on assets\n"
              << "     available on the exchange.\n"
              << "\n"
              << "Option 5: View Your Account\n"
              << "   - This option displays information about your account,\n"
              << "     including your balance and coins owned.\n"
              << "\n"
              << "Option 6: Continue next timeframe\n"
              << "   - Selecting this option allows you to proceed\n"
              << "     with the current operation.\n"
              << "\n"
              << "Option 7: Exit Application\n"
              << "   - This option terminates the application\n"
              << "     and exits the program.\n"
              << "=======================================\n\n";
}

// Return exchange stats: number of entries, bids and asks
void printMarketStats(OrderBook &orderBook, std::string &timeframe)
{
    for (std::string const &key : orderBook.getKnownProducts())
    {
        std::cout << "\nProduct ... " << key << '\n';
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, key, timeframe);
        std::cout << "Number of asks ... " << entries.size() << '\n';
        std::cout << "Highest asking price ... " << OrderBook::getHighPrice(entries) << '\n';
        std::cout << "Lowest asking price ... " << OrderBook::getLowPrice(entries) << '\n';
    }
}

void makeOffer()
{
    // TODO: ask user to make offer
}

void makeBid()
{
    // TODO: ask user to make bid
}

// @param account display account info
void printAccount(Account *account)
{
    std::cout << "Account balance ... $" << account->balance << '\n';
    std::cout << "Coins owned ... " << account->coins << '\n';
}

// @param timeframe current time frame to be modified
// @param orderBook holds data for next time frame
void continueNextTimeframe(std::string &timeframe, OrderBook &orderBook)
{
    std::cout << "Continuing to next time frame ... \n";
    timeframe = orderBook.getNextTime(timeframe);
}