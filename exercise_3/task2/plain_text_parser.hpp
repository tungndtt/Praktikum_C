#pragma once
#include "parser.hpp"

class PlainTextParser : public Parser {
public:
    virtual std::vector<Row> parse(File& file);
    virtual void write(File& file, std::vector<Row> rows);
};