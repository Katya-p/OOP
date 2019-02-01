#include <gtest\gtest.h>
#include <BestUsers.h>
#include <User.h>
//#include <iostream>
//#include <string>
#include <fstream>
#include <sstream>
using namespace std;

TEST(testcase, test) {
	string users = "Ivan M   15 NSK school cars, anime\nJessica F 30 NY MSU cars, physics, food\nKate F 35 NSK Kambridge beer, food, science\nMike M 35 LA MSU memes, beer, work, anime\nAngela F 30 NY KSU nails, lashes, physics\nFassbender M 15 NY Kambridge memes, work, beer";
	string wishes = "Ivan M 15 NSK  ?   school, anime\nJessica M 35 Moskow PTU cars, physics\nKate M 30 ? ? beer, food\nMike F 35 ? MSU ?\nAngela F 30 ? ? ?\nFassbender ? ? ? ? science, beer";
	string expected = "Best for Ivan : Fassbender Mike Kate Angela Jessica\nBest for Jessica : Mike Ivan Fassbender Angela Kate\nBest for Kate : Fassbender Mike Jessica Angela Ivan\nBest for Mike : Kate Jessica Angela Fassbender Ivan\nBest for Angela : Jessica Kate Fassbender Mike Ivan\nBest for Fassbender : Kate Mike Angela Jessica Ivan";

	istringstream users_stream(users);
	istringstream wishes_stream(wishes);
	BestUsers list_of_users;
	BestUsers list_of_wishes;
	list_of_users.read(users_stream, true);
	list_of_wishes.read(wishes_stream, false);
	ofstream out("buffer.txt");
	BestUsers::get_result(out, 5, list_of_wishes, list_of_users);
	out.close();
	ifstream result("buffer.txt");
	istringstream expected_stream(expected);
	string s_res, s_exp;
	while (result) {
		result >> s_res;
		expected_stream >> s_exp;
		ASSERT_EQ(s_res, s_exp);
	}
}

TEST(testcase1, test1) {
	string users = "Ivan M   15 NSK Kambridge	 cars, anime, work\nJessica F 30 NY MSU			 cars, physics, food\nJessica1 ? ? ? MSU			 cars, physics, food\nKate F 35 NSK Kambridge		 beer, food, anime\nMike M 35 LA MSU			 beer, work, anime\nMike ? 35 LA MSU ?\nAngela F 15 NY Kambridge	 physics, anime, beer\nFassbender M 30 NY Kambridge food, work, beer";
	string wishes = "Ivan F   ? ? ?				 anime, work, physics, beer\nJessica F 30 NY MSU ?\nKate M 35 ? Kambridge ?\nMike F ? ? ? memes, beer, work, anime\nAngela M ? NY Kambridge		 physics\nFassbender ? ? ? ? anime";
	string expected = "Best for Ivan : Angela\nBest for Jessica : Fassbender\nBest for Kate : Fassbender\nBest for Mike : Angela\nBest for Angela : Fassbender\nBest for Fassbender : Angela";

	istringstream users_stream(users);
	istringstream wishes_stream(wishes);
	BestUsers list_of_users;
	BestUsers list_of_wishes;
	list_of_users.read(users_stream, true);
	list_of_wishes.read(wishes_stream, false);
	ofstream out("buffer.txt");
	BestUsers::get_result(out, 1, list_of_wishes, list_of_users);
	out.close();
	ifstream result("buffer.txt");
	istringstream expected_stream(expected);
	string s_res, s_exp;
	while (result) {
		result >> s_res;
		expected_stream >> s_exp;
		ASSERT_EQ(s_res, s_exp);
	}
}

TEST(testcase2, test2) {	
	string users = "Ivan M   15 NSK Kambridge	 cars, anime, work\nJessica F 30 NY MSU			 cars, physics, food\nKate F 35 NSK Kambridge		 beer, food, anime\nMike M 35 LA MSU			 beer, work, anime\nAngela F 15 NY Kambridge	 physics, anime, beer\n	Fassbender M 30 NY Kambridge food, work, beer";
	string wishes = "Ivan M   15 NSK Kambridge	 cars, anime, work\nJessica F 30 NY MSU			 cars, physics, food\nKate F 35 NSK Kambridge		 beer, food, anime\nMike M 35 LA MSU			 beer, work, anime\nAngela F 15 NY Kambridge	 physics, anime, beer\nFassbender M 30 NY Kambridge food, work, beer";
	string expected = "Best for Ivan : Fassbender Angela\nBest for Jessica : Fassbender Angela\nBest for Kate : Angela Fassbender\nBest for Mike : Fassbender Kate\nBest for Angela : Kate Fassbender\nBest for Fassbender : Angela Mike";

	istringstream users_stream(users);
	istringstream wishes_stream(wishes);
	BestUsers list_of_users;
	BestUsers list_of_wishes;
	list_of_users.read(users_stream, true);
	list_of_wishes.read(wishes_stream, false);
	ofstream out("buffer.txt");
	BestUsers::get_result(out, 2, list_of_wishes, list_of_users);
	out.close();
	ifstream result("buffer.txt");
	istringstream expected_stream(expected);
	string s_res, s_exp;
	while (result) {
		result >> s_res;
		expected_stream >> s_exp;
		ASSERT_EQ(s_res, s_exp);
	}
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
