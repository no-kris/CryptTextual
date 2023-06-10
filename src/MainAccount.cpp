/*
 * File Name: MainAccount.cpp
 * Description: This file contains the function definitions from MainAccount.h
 *
 * Author: Kris Treska
 * Date: 2023/06/04
 */

#include <string>
#include <limits>
#include "MainAccount.h"
#include "CSVFileReader.h"

// Construct and init a main account
MainAccount::MainAccount() : mBalance(0.0), mCoins(0.0)
{
    banner();
    OrderBook orderBook("CryptoDataSheet.csv");
    mCurrentTime = orderBook.getEarliestTime();
    double initialDeposit = getInitialDeposit();
    initializeAccount(initialDeposit);
    int menuOption = 0;
    while (menuOption != 7)
    {
        menuOption = getMenuOption();
        displayMenuOption(menuOption, orderBook);
    } // EO while (menuOption != 7)
}

// Test program
void MainAccount::test()
{
    MainAccount mainAccount;
}

// Display banner
void MainAccount::banner()
{
    std::cout << "============================================================\n"
              << "CRYPTTEXTUAL: Crypto Trading Program\n\n"
              << "Learn and Practice Crypto Trading.\n\n"
              << "Hands-on trading simulation  |  Practice trading strategies\n"
              << "============================================================\n\n";
}

// Return a value to create an initial account balance
double MainAccount::getInitialDeposit()
{
    double initialDeposit = 0.0;
    do
    {
        if (initialDeposit < 0)
        {
            std::cout << "Cannot start with a negative balance ... \n";
        }
        if (std::cin.fail())
        {
            clearInvalidInput();
        }
        std::cout << "Enter an initial deposit ... ";
    } while (!(std::cin >> initialDeposit) || initialDeposit < 0);
    return initialDeposit;
}

// Initialize an account with provided deposit and 0 coins owned
void MainAccount::initializeAccount(double deposit)
{
    mBalance = deposit;
    mCoins = 0.0;
}

// Display menu options
void MainAccount::printMenu()
{
    std::cout << "\nCurrent time ... " << mCurrentTime << '\n';
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
int MainAccount::getMenuOption()
{
    int menuChoice = 0;
    do
    {
        if (std::cin.fail())
        {
            clearInvalidInput();
        }
        printMenu();
        std::cout << "Enter choice ... ";
    } while (!(std::cin >> menuChoice));
    return menuChoice;
}

// @param menuOption represents a case to perform correct operation
// @param orderBook holds data that some cases need to access
void MainAccount::displayMenuOption(int menuOption, OrderBook &orderBook)
{
    switch (menuOption)
    {
    case 1:
        printHelp();
        break;
    case 2:
        printMarketStats(orderBook);
        break;
    case 3:
        makeAsk();
        break;
    case 4:
        makeBid();
        break;
    case 5:
        printAccount();
        break;
    case 6:
        continueNextTimeframe(orderBook);
        break;
    case 7:
        std::cout << "Now ending application, bye!\n";
        break;
    default:
        std::cerr << "Not a valid option, try again ... \n";
        break;
    } // EO switch (menuOption)
}

// Clarify each menu option
void MainAccount::printHelp()
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

// @return exchange stats: number of entries, bids and asks, highest and lowest asking price
void MainAccount::printMarketStats(OrderBook &orderBook)
{
    for (std::string const &key : orderBook.getKnownProducts())
    {
        std::cout << "\nProduct ... " << key << '\n';
        std::vector<OrderBookEntry> entries =
            orderBook.getOrders(OrderBookType::ask, key, mCurrentTime);
        std::cout << "Number of asks ... " << entries.size() << '\n';
        std::cout << "Highest asking price ... "
                  << OrderBook::getHighPrice(entries) << '\n';
        std::cout << "Lowest asking price ... "
                  << OrderBook::getLowPrice(entries) << '\n';
    } // EO for (std::string const &key : orderBook.getKnownProducts())
}

// Prompt user to make an order book entry
void MainAccount::makeAsk()
{
    std::cout << "\nAsk for an offer in the format"
              << "...(product, price, amount)...eg. BTC/ETH,0.5,300\n";
    std::cout << "Enter offer ... ";
    std::string userInput;
    std::getline(std::cin >> std::ws, userInput);
    validateAskRequest(userInput);
}

// @param userInput handle any input stream errors entered from user
void MainAccount::validateAskRequest(std::string &userInput)
{
    std::vector<std::string> tokens = CSVFileReader::tokenise(userInput, ',');
    if (tokens.size() != 3)
    {
        std::cerr << "Bad input entered ... " << userInput << '\n';
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVFileReader::makeOrderBookEntry(tokens[1], tokens[2],
                                                                   mCurrentTime, tokens[0],
                                                                   OrderBookType::ask);
        }
        catch (const std::exception &e)
        {
            std::cout << "MainAccount::makeAsk something went wrong ... \n";
            clearInvalidInput();
        } // EO try .. catch
    }
    std::cout << "you entered ... " << userInput << '\n';
}

void MainAccount::makeBid()
{
    // TODO: ask user to make bid
}

// Clear input stream if user enters bad input
void MainAccount::clearInvalidInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Unrecognizable input, try again ... \n";
}

void MainAccount::printAccount()
{
    std::cout << "Account balance ... $" << mBalance << '\n';
    std::cout << "Coins owned ... " << mCoins << '\n';
}

// @param orderBook holds data for next time frame
void MainAccount::continueNextTimeframe(OrderBook &orderBook)
{
    std::cout << "Continuing to next time frame ... \n";
    mCurrentTime = orderBook.getNextTime(mCurrentTime);
}