#include <string>
#include <vector>

#include "testHelper.hpp"
#include "food.hpp"
#include "map.hpp"

BEGIN_TEST(testFood4){
	Food hotdog(1, "hotdog", 5.0);
	ASSERT_EQUAL("1;hotdog;5.0", hotdog.toString());
}END_TEST(testFood4)

BEGIN_TEST(testFood5){
	std::string givenFood = "1;hotdog;5.0";
	Food apple(3, "apple", 1.2);
	Food hotdog = apple.parse(givenFood);
	ASSERT_EQUAL(1, hotdog.getBestellnummer());
	ASSERT_EQUAL("hotdog", hotdog.getBezeichnung());
	ASSERT_EQUAL(5.0, hotdog.getPreis());
}END_TEST(testFood5)

BEGIN_TEST(testMapCreate){
	ASSERT_THROW(Map map(0), std::runtime_error);
}END_TEST(testMapCreate)
	
BEGIN_TEST(testMapInsert1){
	Map map(2);
	
	std::string k1 = "ab";
    std::vector<Item> s1 = {
        Item(1, "hotdog"),
        Item(2, "cola")
    };
	map.insert(k1, s1);
	std::vector<Item> retr;
	retr = map.get(k1);
	ASSERT_EQUAL(retr.size(), 2);
	ASSERT_EQUAL(retr[0].first, s1[0].first);
	ASSERT_EQUAL(retr[0].second, s1[0].second);
	ASSERT_EQUAL(retr[1].first, s1[1].first);
	ASSERT_EQUAL(retr[1].second, s1[1].second);
	
	std::string k2 = "ba";
    std::vector<Item> s2 = {
        Item(3, "pizza"),
        Item(4, "fanta"),
		Item(2, "cola")
    };
	ASSERT_THROW(map.insert(k2, s2), std::runtime_error);
}END_TEST(testMapInsert1)

BEGIN_TEST(testMapInsert2){
	Map map(3);
	
	std::string k1 = "ab";
    std::vector<Item> s1 = {
        Item(1, "hotdog"),
        Item(2, "cola")
    };
	map.insert(k1, s1);
	std::vector<Item> retr;
	retr = map.get(k1);
	
	std::string k2 = "ba";
    std::vector<Item> s2 = {
        Item(3, "pizza"),
        Item(4, "fanta"),
		Item(1, "hotdog")
    };
	map.insert(k2, s2);
	
	std::vector<Item> s3 = {
        Item(3, "juice"),
		Item(2, "cola"),
		Item(1, "hotdog"),
		Item(0, "fanta")
    };
	map.insert(k2, s3);
	retr = map.get(k2);
	ASSERT_EQUAL(retr.size(), 4);
}END_TEST(testMapInsert2)

BEGIN_TEST(testMapRemove1){
	Map map(2);
	map.remove("bv");
	std::vector<Item> retr;
	retr = map.get("bv");
	ASSERT_EQUAL(retr.size(), 0);
}END_TEST(testMapRemove1)

BEGIN_TEST(testMapRemove2){
	Map map(6);

	std::string k1 = "ab";
    std::vector<Item> s1 = {
        Item(1, "hotdog"),
        Item(2, "cola")
    };
	map.insert(k1, s1);
	std::vector<Item> retr;
	
	std::string k2 = "ba";
    std::vector<Item> s2 = {
        Item(3, "pizza"),
        Item(4, "fanta"),
		Item(1, "hotdog")
    };
	map.insert(k2, s2);
	
	std::vector<Item> s3 = {
        Item(3, "juice"),
		Item(2, "cola"),
		Item(1, "hotdog"),
		Item(0, "fanta")
    };
	map.insert(k2, s3);

	map.remove(k1);
	retr = map.get(k1);
	ASSERT_EQUAL(retr.size(), 0);
	map.remove(k2);
	retr = map.get(k2);
	ASSERT_EQUAL(retr.size(), 0);
}END_TEST(testMapRemove2)

BEGIN_TEST(testAll){
	Map map(6);

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

    std::vector<Item> retr;
	
    map.insert(k1, s1);
    retr = map.get(k1);
	ASSERT_EQUAL(retr.size(), 2);
	ASSERT_EQUAL(retr[0].first, s1[0].first);
	ASSERT_EQUAL(retr[0].second, s1[0].second);
	ASSERT_EQUAL(retr[1].first, s1[1].first);
	ASSERT_EQUAL(retr[1].second, s1[1].second);

    map.insert(k2, s2);
    map.insert(k2, s5);
	map.insert(k2, s4);
	map.insert(k2, s3);
    retr = map.get(k2);
	ASSERT_EQUAL(retr.size(), 2);
    map.remove(k2);
}END_TEST(testAll)