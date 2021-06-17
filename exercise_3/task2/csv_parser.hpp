#pragma once
#include "parser.hpp"

class CSVParser : public Parser {
public:
    virtual std::vector<Row> parse(File& file);
    virtual void write(File& file, std::vector<Row> rows);
};