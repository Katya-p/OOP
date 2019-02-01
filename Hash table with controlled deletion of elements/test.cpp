#include "pch.h"
#include "HashTable.h"
TEST(TestCaseName, SpecifiedNumberOfHits) {
	HashTable<int, std::string, SpecifiedNumberOfHits<int, 3> > table;
	table.insert(1, "one");
	table.insert(2, "two");
	table.insert(3, "three");
	table.insert(4, "four");
	table.insert(5, "five");
	EXPECT_EQ(table.find(1)->second, "one");
	EXPECT_EQ(table.find(2)->second, "two");
	EXPECT_EQ(table.find(4)->second, "four");
	EXPECT_EQ(table.find(5)->second, "five");

	EXPECT_EQ(table.find(3)->second, "three");
	std::string s = table.at(3);
	EXPECT_EQ(s, "three");
	std::string s2 = table[3];
	EXPECT_EQ(s2, "three");
	EXPECT_EQ(table.find(3)->second, "four");
	EXPECT_EQ(table.find(3)->second, "four");
	std::string s3 = table.at(3);
	EXPECT_EQ(s3, "four");
	std::string s4 = table[3];
	EXPECT_EQ(s4, "");//оператор [] вставляет новый элемент, если элемент с ключом key не найден
}

TEST(TestCaseName, SpecifiedTime) {
	HashTable<int, std::string, SpecifiedTime<int, 1> > table;
	table.insert(1, "one");
	table.insert(2, "two");
	table.insert(3, "three");
	table.insert(4, "four");
	table.insert(5, "five");
	EXPECT_EQ(table.find(1)->second, "one");
	EXPECT_EQ(table.find(2)->second, "two");
	EXPECT_EQ(table.find(4)->second, "four");
	EXPECT_EQ(table.find(5)->second, "five");
	for (size_t i = 0; i < 500000; i++) {
		table.find(3);
	}
	EXPECT_EQ(table.find(3)->second, "four");	
} 

TEST(TestCaseName, NeverDelete) {
	HashTable<int, std::string, NeverDelete<int> > table;
	table.insert(1, "one");
	table.insert(2, "two");
	table.insert(3, "three");
	table.insert(4, "four");
	table.insert(5, "five");
	EXPECT_EQ(table.find(1)->second, "one");
	EXPECT_EQ(table.find(2)->second, "two");
	EXPECT_EQ(table.find(3)->second, "three");
	EXPECT_EQ(table.find(4)->second, "four");
	EXPECT_EQ(table.find(5)->second, "five");
	for (size_t i = 0; i < 500000; i++) {
		table.find(1);
		table.find(2);
		table.find(3);
		table.find(4);
		table.find(5);
	}

	EXPECT_EQ(table.find(1)->second, "one");
	EXPECT_EQ(table.find(2)->second, "two");
	EXPECT_EQ(table.find(3)->second, "three");
	EXPECT_EQ(table.find(4)->second, "four");
	EXPECT_EQ(table.find(5)->second, "five");
}
