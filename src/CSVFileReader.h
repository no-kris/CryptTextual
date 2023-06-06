/*
 * Class Name: CSVFileReader
 * Description: The CSVFileReader class stores functions for
 *              opening and reading data from a csv file,
 *              tokenising that data and making an OrderBookEntry
 *              from that data
 *
 * Author: Kris Treska
 * Date: 2023/06/06
 */

#ifndef CSVFILEREADER_H
#define CSVFILEREADER_H

#include "OrderBookEntry.h"
#include <string>
#include <vector>

class CSVFileReader
{
public:
    CSVFileReader();
    ~CSVFileReader();

public:
    static std::vector<OrderBookEntry> readCSVFile(const std::string &csvFileName);

private:
    static std::vector<std::string> tokenise(std::string &csvLine, char seperator);
    static OrderBookEntry makeOrderBookEntry(std::vector<std::string> &&tokens);
};

#endif /* CSVFILEREADER_H */