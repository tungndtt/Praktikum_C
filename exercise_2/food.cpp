#include "food.hpp"
#include <sstream>
#include <fstream>

// Food non-default constructor
Food::Food(int bestellnummer, std::string bezeichnung, double preis): 
    bestellnummer(bestellnummer), bezeichnung(bezeichnung), preis(preis)
{
    // empty constructor body
}

// betellnummer-getter method
int Food::getBestellnummer() {
    return this->bestellnummer;
}

// bezeichnung-getter method
std::string Food::getBezeichnung() {
    return this->bezeichnung;
}

// preis-getter method
double Food::getPreis() {
    return this->preis;
}

// stringify the Food instance
std::string Food::toString() {
    return std::to_string(this->bestellnummer) 
        + ";" + this->bezeichnung 
        + ";" + std::to_string(this->preis);
}

// parse a formatted string to Food object (foodify) 
Food Food::parse(std::string &foodString) {
    std::stringstream ss(foodString);
    std::string part;
    std::vector<std::string> parts;
    while(std::getline(ss, part, ';')) {
        parts.push_back(part);
    }
    return Food(std::stoi(parts[0]), parts[1], std::stoi(parts[2]));
}

// save the list of foods into provided file
void speichern(const std::string &dateiname, const std::vector<Food> &speisen) {
    std::ofstream _file;
    _file.open(dateiname);
    int curLine = 1;
    for(Food food : speisen) {
        _file << food.toString();
        if(curLine < speisen.size()) {
            _file << "\n";
            curLine++;
        }
    }
    _file.close();
}

// load list of foods from file and save into speisen-list
void laden(const std::string &dateiname, std::vector<Food> &speisen) {
    std::ifstream _file(dateiname);
    std::string line;
    while(std::getline(_file, line)) {
        speisen.push_back(Food::parse(line));
    }
}