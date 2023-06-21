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
    nil,     // No order type
    bid,     // Offering to buy
    ask,     // Offering to sell
    bidsale, // sale made for bidding
    asksale  // sale made for selling
};

class OrderBookEntry
{
public:
    OrderBookEntry();
    OrderBookEntry(double price, double amount,
                   std::string timestamp, std::string product,
                   OrderBookType orderType,
                   std::string username = "dataset");
    ~OrderBookEntry();

public:
    static OrderBookType sToOBE(const std::string &type);
    inline OrderBookType getOrderType() const { return mOrderType; }
    inline void setOrderType(OrderBookType type) { mOrderType = type; }
    inline std::string getProduct() const { return mProduct; }
    inline std::string getTimestamp() const { return mTimestamp; }
    inline double getPrice() const { return mPrice; }
    inline double getAmount() const { return mAmount; }
    inline void setAmount(double amount) { mAmount = amount; }
    inline std::string getUsername() const { return mUsername; }
    inline void setUsername(std::string username) { mUsername = username; }
    static bool compareTimestamps(OrderBookEntry &entry1, OrderBookEntry &entry2);
    static bool compareByPriceAsc(OrderBookEntry &e1, OrderBookEntry &e2);
    static bool compareByPriceDesc(OrderBookEntry &e1, OrderBookEntry &e2);

private:
    double mPrice;
    double mAmount;
    std::string mTimestamp;
    std::string mProduct;
    OrderBookType mOrderType;
    std::string mUsername;
};

#endif /* ORDERBOOKENTRY_H */