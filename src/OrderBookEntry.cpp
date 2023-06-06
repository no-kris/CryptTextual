/*
 * File Name: OrderBookEntry.cpp
 * Description: This file contains the function definitions from
 *              the OrderBookEntry class
 *
 * Author: Kris Treska
 * Date: 2023/06/04
 */

#include "OrderBookEntry.h"

// Construct an empty OrderBookEntry
OrderBookEntry::OrderBookEntry()
    : OrderBookEntry(0, 0, "Empty", "Empty", OrderBookType::NIL)
{
}

// Construct an OrderBookEntry with given data values
OrderBookEntry::OrderBookEntry(double price, double amount,
                               std::string timestamp, std::string product,
                               OrderBookType orderType)
    : mPrice(price), mAmount(amount), mTimestamp(timestamp),
      mProduct(product), mOrderType(orderType)
{
}

OrderBookEntry::~OrderBookEntry()
{
}

// @param type return OrderBookType: BID, ASK, NIL
OrderBookType OrderBookEntry::sToOBE(const std::string &type)
{
    if (type == "BID")
    {
        return OrderBookType::BID;
    }
    else if (type == "ASK")
    {
        return OrderBookType::ASK;
    }
    else
    {
        return OrderBookType::NIL;
    }
}