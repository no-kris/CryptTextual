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
MainAccount::MainAccount()
{
}

// Test program
void MainAccount::test()
{
    MainAccount mainAccount;
    mainAccount.process();
}

void MainAccount::process()
{
    banner();
    mCurrentTime = orderBook.getEarliestTime();
    mUsersWallet.insertCurrency("BTC", 20.0);
    mUsersWallet.insertCurrency("USDT", 100000);
    mUsersWallet.removeCurrency("USDT", 95000);
    int menuOption = 0;
    while (menuOption != 7)
    {
        menuOption = getMenuOption();
        displayMenuOption(menuOption);
    } // EO while (menuOption != 7)
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
void MainAccount::displayMenuOption(int menuOption)
{
    switch (menuOption)
    {
    case 1:
        printHelp();
        break;
    case 2:
        printMarketStats();
        break;
    case 3:
        makeAsk();
        break;
    case 4:
        makeBid();
        break;
    case 5:
        mUsersWallet.printWallet();
        break;
    case 6:
        continueNextTimeframe();
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
              << "     to sell assets on the exchange platform.\n"
              << "\n"
              << "Option 4: Make a Bid\n"
              << "   - Use this option to make a bid on currencies\n"
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
void MainAccount::printMarketStats()
{
    for (std::string const &key : orderBook.getKnownProducts())
    {
        std::cout << "\nProduct ... " << key << '\n';
        std::vector<OrderBookEntry> askEntries =
            orderBook.getOrders(OrderBookType::ask, key, mCurrentTime);
        printNumberAsks(askEntries);
        std::cout << std::endl;
        std::vector<OrderBookEntry> bidEntries =
            orderBook.getOrders(OrderBookType::bid, key, mCurrentTime);
        printNumberBids(bidEntries);
        std::cout << "\n----------------------------------\n";

    } // EO for (std::string const &key : orderBook.getKnownProducts())
}

// Print order book data on asks
void MainAccount::printNumberAsks(std::vector<OrderBookEntry> &askEntries)
{
    std::cout << "Number of asks ... " << askEntries.size() << '\n';
    std::cout << "Highest asking price ... "
              << OrderBook::getHighPrice(askEntries) << '\n';
    std::cout << "Lowest asking price ... "
              << OrderBook::getLowPrice(askEntries) << '\n';
}

// Print order book data on bids
void MainAccount::printNumberBids(std::vector<OrderBookEntry> &bidEntries)
{
    std::cout << "Number of bids ... " << bidEntries.size() << '\n';
    std::cout << "Highest asking bid ... "
              << OrderBook::getHighPrice(bidEntries) << '\n';
    std::cout << "Lowest asking bid ... "
              << OrderBook::getLowPrice(bidEntries) << '\n';
}

// Prompt user to enter an offer to sell assets
void MainAccount::makeAsk()
{
    std::cout << "\nAsk for an offer in the format"
              << "...(product, price, amount)...eg. BTC/USDT,0.5,3000\n";
    std::cout << "Enter offer ... ";
    std::string userInput;
    std::getline(std::cin >> std::ws, userInput);
    validateAskRequest(userInput);
}

// @param userInput handle any input stream errors entered from user
// @param orderBook insert valid ask data into orderBook
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
            obe.setUsername("simuser");
            if (mUsersWallet.canFulfillOrder(obe))
            {
                std::cout << "Transaction successful ... \n";
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "Transaction failed, insufficient funds ... \n";
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "MainAccount::makeAsk something went wrong ... \n";
            clearInvalidInput();
        } // EO try .. catch
    }
    std::cout << "You entered ... " << userInput << '\n';
}

// Prompt user to bid to buy assets
void MainAccount::makeBid()
{
    std::cout << "\nBid for an offer in the format "
              << "...(product, price, amount)... eg. BTC/USDT,0.5,3000\n";
    std::cout << "Enter offer ... ";
    std::string userInput;
    std::getline(std::cin >> std::ws, userInput);
    validateBidRequest(userInput);
}

// @param userInput handle any input stream errors entered from user
void MainAccount::validateBidRequest(std::string &userInput)
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
                                                                   OrderBookType::bid);
            obe.setUsername("simuser");
            if (mUsersWallet.canFulfillOrder(obe))
            {
                std::cout << "Transaction successful ... \n";
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "Transaction failed, insufficient funds ... \n";
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "MainAccount::makeBid something went wrong ... \n";
            clearInvalidInput();
        } // EO try .. catch
    }
    std::cout << "You entered ... " << userInput << '\n';
}

// Clear input stream if user enters bad input
void MainAccount::clearInvalidInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Unrecognizable input, try again ... \n";
}

// @param orderBook holds data for next time frame
void MainAccount::continueNextTimeframe()
{
    std::cout << "\nContinuing to next time frame ... \n";
    for (std::string &prod : orderBook.getKnownProducts())
    {
        std::cout << "matching " << prod << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(prod, mCurrentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry &sale : sales)
        {
            std::cout << "Sale price ... " << sale.getPrice() << std::endl;
            if (sale.getUsername() == "simuser") // update wallet
            {
                mUsersWallet.processSale(sale);
            }
        }
    }
    mCurrentTime = orderBook.getNextTime(mCurrentTime);
}