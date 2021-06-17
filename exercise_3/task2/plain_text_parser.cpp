#include "plain_text_parser.hpp"
#include <sstream>
#include <string>

std::vector<Row> PlainTextParser::parse(File& file) {
    std::vector<Row> serie;
    while(file.hasNextLine()) {
        std::string line = file.getline();
        Row row;
        row.insert("0", line);
        serie.push_back(row);
    }
    return serie;
}

void PlainTextParser::write(File& file, std::vector<Row> rows) {
    std::string line;
    if(rows.size() > 0) {
        auto iterator = rows[0].begin();
        line = iterator->second;
    }
    for(int i=1; i<rows.size(); i++) {
        auto iterator = rows[i].begin();
        line += "\n" + iterator->second;
    }
    file.write(line);
}