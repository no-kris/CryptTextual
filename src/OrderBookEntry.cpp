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
    : OrderBookEntry(0, 0, "Empty", "Empty", OrderBookType::nil)
{
}

// Construct an OrderBookEntry with given data values
OrderBookEntry::OrderBookEntry(double price, double amount,
                               std::string timestamp, std::string product,
                               OrderBookType orderType, std::string username)
    : mPrice(price), mAmount(amount), mTimestamp(timestamp),
      mProduct(product), mOrderType(orderType), mUsername(username)
{
}

OrderBookEntry::~OrderBookEntry()
{
}

// @param type return OrderBookType: BID, ASK, NIL
OrderBookType OrderBookEntry::sToOBE(const std::string &type)
{
    if (type == "bid")
    {
        return OrderBookType::bid;
    }
    else if (type == "ask")
    {
        return OrderBookType::ask;
    }
    else
    {
        return OrderBookType::nil;
    }
}

bool OrderBookEntry::compareTimestamps(OrderBookEntry &entry1, OrderBookEntry &entry2)
{
    return entry1.getTimestamp() < entry2.getTimestamp();
}

bool OrderBookEntry::compareByPriceAsc(OrderBookEntry &entry1, OrderBookEntry &entry2)
{
    return entry1.getPrice() < entry2.getPrice();
}

bool OrderBookEntry::compareByPriceDesc(OrderBookEntry &entry1, OrderBookEntry &entry2)
{
    return entry1.getPrice() > entry2.getPrice();
}
