/*
 * Class Name: OrderBookEntry
 * Description: The OrderBookEntry class represents an entry in an order book,
 *              which contains information about a specific order,
 *              such as price, amount, timestamp, product, and order type.
 *
 * Author: Kris Treska
 * Date: 2023/06/04
 */

#ifndef ORDERBOOKENTRY_H
#define ORDERBOOKENTRY_H

#include <vector>
#include <string>

enum class OrderBookType
{
    NIL, // No order type
    BID, // Offering to buy
    ASK  // Offering to sell
};

class OrderBookEntry
{
public:
    OrderBookEntry();
    OrderBookEntry(double mPrice, double mAmount,
                   std::string mTimestamp, std::string mProduct,
                   OrderBookType mOrderType);
    ~OrderBookEntry();

public:
    static OrderBookType sToOBE(const std::string &type);
    OrderBookType mOrderType;

private:
    double mPrice;
    double mAmount;
    std::string mTimestamp;
    std::string mProduct;
};

#endif /* ORDERBOOKENTRY_H */