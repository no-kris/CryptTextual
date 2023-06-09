/*
 * Class Name: OrderBook
 * Description:
 *
 * Author: Kris Treska
 * Date: 2023/06/08
 */

#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVFileReader.h"

class OrderBook
{
public:
    OrderBook(const std::string fileName);
    ~OrderBook();

public:
    std::vector<std::string> getKnownProducts();
    std::vector<OrderBookEntry> getOrders(const OrderBookType type,
                                          const std::string product,
                                          const std::string timeframe);
    std::string getEarliestTime();
    std::string getNextTime(std::string &timestamp);
    static double getHighPrice(std::vector<OrderBookEntry> &orders);
    static double getLowPrice(std::vector<OrderBookEntry> &orders);

private:
    std::vector<OrderBookEntry> mOrders;
};

#endif /* ORDERBOOK_H */