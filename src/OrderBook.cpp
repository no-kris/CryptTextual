/*
 * File Name: OrderBook.cpp
 * Description: This file contains the function definitions
 *              from the OrderBook class
 *
 * Author: Kris Treska
 * Date: 2023/06/08
 */

#include <map>
#include "OrderBook.h"

// Construct OrderBook
// @param fileName read data from csv file
OrderBook::OrderBook(const std::string fileName)
{
    mOrders = CSVFileReader::readCSVFile(fileName);
}

OrderBook::~OrderBook()
{
}

// @return vector of all known currency products from OrderBook
std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;
    std::map<std::string, bool> productMap;
    // Create and return a unique list of product types
    for (OrderBookEntry &key : mOrders)
    {
        productMap[key.getProduct()] = true;
    } // EO for (OrderBookEntry &key : mOrders)
    for (auto const &value : productMap)
    {
        products.push_back(value.first);
    } // EO for (auto const &value : productMap)
    return products;
}

// @param type order type, bid or ask
// @param product currency
// @param timeframe time the order was put in
// @return vector of OrderBookEntry based on passed in params
std::vector<OrderBookEntry> OrderBook::getOrders(const OrderBookType type,
                                                 const std::string product,
                                                 const std::string timeframe)
{
    std::vector<OrderBookEntry> orderBookEntries;
    for (OrderBookEntry &key : mOrders)
    {
        if (key.getOrderType() == type &&
            key.getProduct() == product &&
            key.getTimestamp() == timeframe)
        {
            orderBookEntries.push_back(key);
        }
    }
    return orderBookEntries;
}

// @return the earliest time from csv data file
std::string OrderBook::getEarliestTime()
{
    return mOrders[0].getTimestamp();
}

// @return next timestamp after the current time in order book
// Wrap program to start if there is no next timestamp
std::string OrderBook::getNextTime(std::string &timestamp)
{
    std::string nextTimestamp = "";
    for (OrderBookEntry &key : mOrders)
    {
        if (key.getTimestamp() > timestamp)
        {
            nextTimestamp = key.getTimestamp();
            break;
        } // EO if (key.getTimestamp() > timestamp)
    }     // EO for (OrderBookEntry &key : mOrders)

    if (nextTimestamp == " ")
    {
        nextTimestamp = mOrders[0].getTimestamp();
    }

    return nextTimestamp;
}

// @param orders iterate over and find highest asking price
// @return the highest price from vector of OrderBookEntry
double OrderBook::getHighPrice(std::vector<OrderBookEntry> &orders)
{
    double max = orders[0].getPrice();
    for (const OrderBookEntry &value : orders)
    {
        if (value.getPrice() > max)
            max = value.getPrice();
    } // EO for (const OrderBookEntry &value : orders)
    return max;
}

// @param orders iterate over and find lowest asking price
// @return the lowest price from vector of OrderBookEntry
double OrderBook::getLowPrice(std::vector<OrderBookEntry> &orders)
{
    double min = orders[0].getPrice();
    for (const OrderBookEntry &value : orders)
    {
        if (value.getPrice() < min)
            min = value.getPrice();
    } // EO for (const OrderBookEntry &value : orders)
    return min;
}
