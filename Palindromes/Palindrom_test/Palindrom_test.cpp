#include <gtest\gtest.h>
#include <Pal.h>
//#include <iostream>
#include <string>
#include <fstream>
using namespace std;

TEST(testcase1, test1) {
	ifstream f;
	f.open("test1.txt");
	string input;
	string &in = input;
	getline(f, in);
	string res;
	while (!f.eof()) {
		string tmp;
		getline(f, tmp);
		res += (tmp + '\n');
	}
	f.close();
	Palindrom object = Palindrom::Palindrom();
	string s1 = object.words(in);
	string s2 = object.sentence_as_a_word(in);
	string s3 = object.sentence_as_a_set(in);
	ASSERT_EQ(s1 + s2 + s3, res);
}

TEST(testcase2, test2) {
	ifstream f;
	f.open("test2.txt");
	string input;
	string &in = input;
	getline(f, in);
	string res;
	while (!f.eof()) {
		string tmp;
		getline(f, tmp);
		res += (tmp + '\n');
	}
	f.close();
	Palindrom object = Palindrom::Palindrom();
	string s1 = object.words(in);
	string s2 = object.sentence_as_a_word(in);
	string s3 = object.sentence_as_a_set(in);
	ASSERT_EQ(s1 + s2 + s3, res);
}

TEST(testcase3, test3) {
	ifstream f;
	f.open("test3.txt");
	string input;
	string &in = input;
	getline(f, in);
	string res;
	while (!f.eof()) {
		string tmp;
		getline(f, tmp);
		res += (tmp + '\n');
	}
	f.close();
	Palindrom object = Palindrom::Palindrom();
	string s1 = object.words(in);
	string s2 = object.sentence_as_a_word(in);
	string s3 = object.sentence_as_a_set(in);
	ASSERT_EQ(s1 + s2 + s3, res);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

