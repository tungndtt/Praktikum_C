#include "csv_parser.hpp"
#include <sstream>
#include <string>

std::vector<Row> CSVParser::parse(File& file) {

    std::vector<std::string> keys;
    if(file.hasNextLine()){
        std::string line = file.getline();
        std::stringstream ss(line);
        std::string key;
        while(std::getline(ss, key, ';')) {
            keys.push_back(key);
        }
    }

    std::vector<Row> serie;
    while(file.hasNextLine()) {
        std::string line = file.getline();
        std::stringstream ss(line);
        std::string element;
        int idx = 0;
        Row row;
        while(std::getline(ss, element, ';')) {
            row.insert(keys[idx++], element);
        }
        serie.push_back(row);
    }
    return serie;
}

void CSVParser::write(File& file, std::vector<Row> rows) {
    std::string line;
    if(rows.size() > 0) {
        Row& firstRow = rows[0];
        auto iterator=firstRow.begin();
        std::string descriptor = iterator->first;
        line += iterator->second;
        while(++iterator != firstRow.end()) {
            descriptor += ";" + iterator->first;
            line += ";" + iterator->second;
        }
        line = descriptor + "\n" + line;
    }
    for(int i=1; i<rows.size(); i++) {
        line += "\n";
        auto iterator=rows[i].begin();
        line += iterator->second;
        while(++iterator != rows[i].end()) {
            line += ";" + iterator->second;
        }
    }
    file.write(line);
}