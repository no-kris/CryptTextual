/***************************************************************
 *  CryptTextual.cpp
 *
 *  Description:
 *  CryptTextual is a text-based cryptocurrency trading program
 *  that provides users with a simplified and interactive way
 *  to engage in crypto trading. It utilizes a command-line
 *  interface to facilitate trading operations.
 *
 *  Author:
 *  - Kris Treska
 *
 *  GitHub Repository: https://github.com/no-kris/CryptTextual.git
 *
 *  DISCLAIMER: CryptTextual is a student project created for
 *  educational purposes only. It does not provide financial
 *  advice, and not intended for making trading decisions.
 **************************************************************/

#include <iostream>

// Function prototypes
void test();
void banner();
int getMenuOption();
void displayMenuOption(int menuOption);

int main(int argc, char *argv[])
{
    test();
    return 0;
}

// Testing program
void test()
{
    banner();
    int menuOption = 0;
    while (menuOption < 1 || menuOption > 6)
    {
        menuOption = getMenuOption();
        displayMenuOption(menuOption);
    } // EO while (menuOption < 1 || menuOption > 6)
}

void banner()
{
    std::cout << "=============\n"
              << "CRYPT-TEXTUAL\n"
              << "=============\n";
}

// Return an integer corresponding to menu option
int getMenuOption()
{
    int menuChoice = 0;
    std::cout << "=================================\n";
    std::cout << "| Select an option (1 ... 6)    |\n";
    std::cout << "| Press 1 to print help         |\n"
              << "| Press 2 to view exchange stats|\n"
              << "| Press 3 to make an offer      |\n"
              << "| Press 4 to make a bid         |\n"
              << "| Press 5 to view your wallet   |\n"
              << "| Press 6 to continue           |\n"
              << "=================================\n";
    std::cout << "Enter choice ... ";
    std::cin >> menuChoice;
    return menuChoice;
}

// @param menuOption represents a case to perform correct operation
void displayMenuOption(int menuOption)
{
    switch (menuOption)
    {
    case 1:
        std::cout << "TODO: print help\n";
        break;
    case 2:
        std::cout << "TODO: view exchange stats\n";
        break;
    case 3:
        std::cout << "TODO: make an offer\n";
        break;
    case 4:
        std::cout << "TODO: make a bid\n";
        break;
    case 5:
        std::cout << "TODO: view wallet\n";
        break;
    case 6:
        std::cout << "TODO: continue\n";
        break;
    default:
        std::cerr << "Not a valid option, try again ... \n";
        // TODO: handleInvalidOption();
        break;
    } // EO switch (menuOption)
}