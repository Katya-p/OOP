#include "User.h"
using namespace std;

void User::read(istream &in) {
	if (!in.bad()) {
		in >> this->user_id;
		string s;
		in >> s;
		if (s == "F") { sex = Sex::female; }
		else if (s == "M") { sex = Sex::male; }
		else { sex = Sex::unknown; }
		string age_in_str;
		in >> age_in_str;
		if (age_in_str == "?") {
			age = -1;
		}
		else {
			age = stoi(age_in_str);
		}
		in >> city >> education;
		in >> ws;
		while (getline(in, s, ',')) {
			interests.push_back(s);
			in >> ws;
		}
	}
}

bool User::has_sex() const {
	return sex != Sex::unknown;
}

bool User::has_age() const {
	return  (age > 0);
}

bool User::has_city() const {
	return city != "?";
}

bool User::has_education() const {
	return education != "?";
}

bool User::has_interests() const {
	return (!interests.empty()) && (interests[0] != "?");
}

bool User::has_all() const {
	return has_sex() && has_age() && has_city() && has_education() && has_interests();

}

int User::count_matches(const User &wish) const {
	int res = 0;
	if (wish.has_sex() && (wish.sex == sex)) {
		res++;
	}
	if (wish.has_age() && (wish.age == age)) {
		res++;
	}
	if (wish.has_city() && (wish.city == city)) {
		res++;
	}
	if (wish.has_education() && (wish.education == education)) {
		res++;
	}
	if (wish.has_interests()) {
		for (string s : interests) {
			for (string w : wish.interests) {//set
				if (s == w) {
					res++;
				}
			}
		}
	}
	return res;
}

string User::get_user_id() const {
	return user_id;
}