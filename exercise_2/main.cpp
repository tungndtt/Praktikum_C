#include "food.hpp"
#include "map.hpp"
#include <iostream>
#include <stdexcept>

const std::string dateiname = "speisen.csv";

// print items
void printList(std::vector<Item>& list) {
    for(Item item : list) {
        std::cout << item.first << ", " << item.second << "| ";
    }
    std::cout << std::endl;
}

// test map method
void map_test() {
    Map map(3);

    // create orders
    std::string k1 = "ab";
    std::vector<Item> s1 = {
        Item(1, "hotdog"),
        Item(2, "cola")
    };
    std::string k2 = "ba";
    std::vector<Item> s2 = {
        Item(3, "pizza"),
        Item(4, "fanta")
    };
    std::string k3 = "abc";
    std::vector<Item> s3 = {
        Item(2, "cola"),
        Item(2, "cola")
    };
    std::string k4 = "abc";
    std::vector<Item> s4 = {
        Item(4, "fanta"),
        Item(2, "cola")
    };
    std::string k5 = "abcd";
    std::vector<Item> s5 = {
        Item(1, "hotdog"),
        Item(5, "juice")
    };
    std::string k6 = "ab";
    std::vector<Item> s6 = {
        Item(3, "pizza"),
        Item(5, "juice")
    };


    std::vector<Item> r;
    map.insert(k1, s1);
    r = map.get(k1);
    printList(r);
    map.insert(k2, s2);
    r = map.get(k2);
    printList(r);
    map.insert(k3, s3);
    r = map.get(k3);
    printList(r);

    map.remove(k2);
    r = map.get(k2);
    std::cout << "Size = " << r.size() << std::endl;

    map.insert(k4, s4);
    map.insert(k5, s5);
    r = map.get(k5);
    printList(r);

    r = map.get(k4);
    printList(r);

    map.insert(k6, s6);
    r = map.get(k1);
    printList(r);

    map.insert(k2,s2);

    map.remove(k3);
    r = map.get(k3);
    std::cout << "Size = " << r.size() << std::endl;
}

// create speisen karte method
void createSpeisenKarte() {
    std::vector<Food> saveSpeisen = {
        Food(1, "hotdog", 5.0),
        Food(2, "pizza", 7.5),
        Food(3, "apple", 1.2),
        Food(4, "orange", 1.5),
        Food(5, "cola", 1.0),
        Food(6, "fanta", 1.0),
        Food(7, "pepsi", 1.0),
        Food(8, "juice", 2.2)
    };
    
    speichern(dateiname, saveSpeisen);
}

// get food from list of foods based on order number
Food getFoodFromOrderNr(int bestellNr, std::vector<Food>& speisen) {
    for(Food food : speisen) {
        if(food.getBestellnummer() == bestellNr) {
            return food;
        }
    }
    return Food(-1, "", -1);
}

int main() {

    // initialize speisen karte
    createSpeisenKarte();

    std::vector<Food> speisen;
    try {
        laden("speisen.csv", speisen);
    }
    catch(std::exception &e) {
        std::cout << "No path to given file is found!" << std::endl;
        return -1;
    }

    // initialize the map with size = 8
    size_t mapSize = 8;
    Map map(mapSize);
    
    char c;
    std::string orderKey;
    std::string exitChar = "e";

    // run the program
    while(true) {
        std::cout << "#################################### OPTIONS ########################################" << std::endl;
        std::cout << "Press character to select option. Be carefuly of capslock!" << std::endl;
        std::cout << "Options: Create new order (c) | Show the order (o) | Delete order (d) | Show all (a) | End (e)" << std::endl;
        std::cin >> c;
        if(c == 'c') {
            bool orderDone = false;
            while(true) {
                std::cout << "#################################### CREATE ORDER ########################################" << std::endl;
                std::cout << "Enter e to exit ..." << std::endl;
                std::cout << "Provide the order key: ";
                std::cin.ignore();
                std::getline(std::cin, orderKey);
                if(orderKey.length() == 0) {
                    std::cout << "Order key cannot be empty!" << std::endl;
                }
                else if(orderKey.compare(exitChar) == 0) break;
                else {
                    std::vector<Item> orders;
                    while(true) {
                        int orderNr;
                        std::cout << std::endl;
                        std::cout << "Please provide the order number. Enter -1 to cancel, 0 to finish ordering!" << std::endl;
                        std::cout << "Order number? : ";
                        std::cin >> orderNr;
                        if(orderNr == -1) {
                            orders.clear();
                            break;
                        }
                        else if(orderNr == 0) {
                            map.insert(orderKey, orders);
                            break;
                            orderDone = true;
                        }
                        else {
                            Food ordered = getFoodFromOrderNr(orderNr, speisen);
                            if(ordered.getBestellnummer() != -1) {
                                std::cout << ordered.toString() << std::endl;
                                orders.push_back(Item(ordered.getBestellnummer(), ordered.getBezeichnung()));
                            }
                            else std::cout << "Invalid order number!" << std::endl;
                        }
                    }
                }
                if(orderDone) break;
            }
            
        }
        else if(c == 'o') {
            while(true) {
                std::cout << "##################################### SHOW ORDER #######################################" << std::endl;
                std::cout << "Enter e to exit ..." << std::endl;
                std::cout << "Enter order key? : ";
                std::cin.ignore();
                std::getline(std::cin, orderKey);
                if(orderKey.compare(exitChar) == 0) break;
                else {
                    std::vector<Item> orders = map.get(orderKey);
                    if(orders.size() != 0) {
                        for(Item order : orders) {
                            std::cout << "Order number: " << order.first << " ; description: " << order.second << std::endl;
                        }
                        break;
                    }
                    else std::cout << "Order key does not exist!" << std::endl;
                }
            }
        }
        else if(c == 'd') {
            while(true) {
                std::cout << "################################## DELETE ORDER #######################################" << std::endl;
                std::cout << "Enter e to exit ..." << std::endl;
                std::cout << "Enter order key? : ";
                std::cin.ignore();
                std::getline(std::cin, orderKey);
                if(orderKey.compare(exitChar) == 0) break;
                else {
                    if(map.get(orderKey).size() > 0) {
                        map.remove(orderKey);
                        std::cout << "Deleted order with order key: " << orderKey << std::endl;
                        break;
                    }
                    else std::cout << "No order with given order key exists!" << orderKey << std::endl;
                }
            }
        }
        else if(c == 'a') {
            std::cout << "################################## SHOW ALL ########################################" << std::endl;
            std::cout << "Order number | Description | Price ..." << std::endl;
            for(Food food : speisen) {
                std::cout << food.getBestellnummer() << ". " << food.getBezeichnung() << " # " << food.getPreis() << " Euro" << std::endl;
            }
        }
        else if(c == 'e') break;
        else std::cout << "Invalid option input! Try again" << std::endl;
    }
   return 0;
}