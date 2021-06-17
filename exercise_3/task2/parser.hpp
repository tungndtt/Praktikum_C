#pragma once
#include <vector>
#include "row.hpp"
#include "file.hpp"

class Parser {
public:
    virtual std::vector<Row> parse(File& file) = 0;
    virtual void write(File& file, std::vector<Row> rows) = 0;
};