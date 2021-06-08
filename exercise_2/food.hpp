#pragma once
#include <string>
#include <vector>

class Food {
public:
    Food() = delete;
    Food(int bestellnummer, std::string bezeichnung, double preis);
    int getBestellnummer();
    std::string getBezeichnung();
    double getPreis();
    std::string toString();
    static Food parse(std::string &foodString);
private:
    int bestellnummer;
    std::string bezeichnung;
    double preis;
};

void speichern(const std::string &dateiname, const std::vector<Food> &speisen);
void laden(const std::string &dateiname, std::vector<Food> &speisen);