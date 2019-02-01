#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

enum class Sex {
	male, female, unknown
};

class User {
public:
	void read(std::istream &in);
	int count_matches(const User &wish) const;
	std::string get_user_id() const;
	bool has_all() const;
private:
	std::string user_id;
	Sex sex;
	int age;
	std::string city;
	std::string education;
	std::vector <std::string> interests;
	bool has_sex() const;
	bool has_age() const;
	bool has_city() const;
	bool has_education() const;
	bool has_interests() const;
};

#endif
