#pragma once

#include <vector>
#include "row.hpp"

class SortingStrategy {
public:
    virtual void sort(std::vector<Row>& rows, std::string& key) = 0;
};