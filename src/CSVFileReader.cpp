/*
 * File Name: CSVFileReader
 * Description: Implementation file for CSVFileReader class
 *
 * Author: Kris Treska
 * Date: 2023/06/06
 */

#include "CSVFileReader.h"
#include <iostream>
#include <fstream>

CSVFileReader::CSVFileReader()
{
}

CSVFileReader::~CSVFileReader()
{
}

// @param csvFileName name of the file to be opened and read from
std::vector<OrderBookEntry> CSVFileReader::readCSVFile(const std::string &csvFileName)
{
    std::ifstream csvFile{csvFileName};
    std::string line;
    std::vector<OrderBookEntry> tokens;
    if (csvFile.is_open())
    {
        while (std::getline(csvFile, line))
        {
            try
            {

                OrderBookEntry OBE = makeOrderBookEntry(tokenise(line, ','));
                tokens.push_back(OBE);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Could not read data, bad input\n";
            } // EO try .. catch
        }     // EO while (std::getline(csvFile, line))
    }
    else
    {
        std::cerr << "Could not open file " << csvFileName << '\n';
    }
    return tokens;
}

// @param csvLine line to be split into seperate strings
// @param seperator delimiter used for seperating strings
std::vector<std::string> CSVFileReader::tokenise(std::string &csvLine, char seperator)
{
    std::vector<std::string> tokens;
    signed int start = 0, end = 0;
    std::string token;
    start = csvLine.find_first_not_of(seperator, 0);
    do
    {
        end = csvLine.find_first_of(seperator, start);
        if (start == csvLine.length() || start == end)
            break;
        if (end >= 0)
            token = csvLine.substr(start, end - start);
        else
            token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;
    } while (end != std::string::npos); // EO do .. while (end != std::string::npos)
    return tokens;
}

// @return an entry in the order book with given data from user
OrderBookEntry CSVFileReader::makeOrderBookEntry(std::string priceStr,
                                                 std::string amountStr,
                                                 std::string timestamp,
                                                 std::string product,
                                                 OrderBookType type)
{
    double price = 0.0, amount = 0.0;
    try
    {
        price = std::stod(priceStr);
        amount = std::stod(amountStr);
    }
    catch (const std::exception &e)
    {
        std::cerr << "CSVFileReader::makeOrderBookEntry Bad value "
                  << price << '\n';
        std::cerr << "CSVFileReader::makeOrderBookEntry Bad value "
                  << amount << '\n';
        throw;
    } // EO try  .. catch
    return OrderBookEntry(price, amount, timestamp, product, type);
}

// @param tokens convert a vector of strings into an OrderBookEntry
OrderBookEntry CSVFileReader::makeOrderBookEntry(std::vector<std::string> &&tokens)
{
    double price = 0, amount = 0;
    if (tokens.size() != 5) // Undesirable token
    {
        std::cout << "Bad line ... \n";
        throw std::exception();
    } // EO if (tokens.size() != 5)
    try
    {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "CSVFileReader::makeOrderBookEntry Bad value "
                  << tokens[3] << '\n';
        std::cerr << "CSVFileReader::makeOrderBookEntry Bad value "
                  << tokens[4] << '\n';
        throw;
    } // EO try  .. catch
    return OrderBookEntry(price, amount, tokens[0], tokens[1],
                          OrderBookEntry::sToOBE(tokens[2]));
}
