#include "BestUsers.h"
#include <sstream>
#include <map>
using namespace std;

void BestUsers::read(istream &in, bool allow_empty) {
	if (!in.bad()) {
		while (!in.eof()) {
			string s;
			getline(in, s);
			if (s.empty()) {
				continue;
			}
			istringstream ss(s);
			User user;
			user.read(ss);
			if (allow_empty && !user.has_all()) {
				continue;
			}
			users.push_back(user);
		}
	}
}

vector <string> BestUsers::get_best_ids(const User &wish, const int amount) {
	if (amount <= 0) {
		return vector <string>();
	}
	multimap<int, string> matches_to_user_id;
	for (User &user : users) {
		if (user.get_user_id() == wish.get_user_id()) {
			continue;
		}
		int cm = user.count_matches(wish);
		matches_to_user_id.insert(make_pair(cm, user.get_user_id()));
	}
	vector<string> best_user_ids;
	for (auto it = matches_to_user_id.rbegin(); it != matches_to_user_id.rend(); it++) {
		string user_id = it->second;
		best_user_ids.push_back(user_id);
		if (best_user_ids.size() == amount) {
			break;
		}
	}
	return best_user_ids;
}

void BestUsers::get_result(std::ostream &out, const int amount_of_best, const BestUsers &wishes, BestUsers &list_of_users) {
	for (User &wish : wishes.get_users()) {
		vector<string> user_ids = list_of_users.get_best_ids(wish, amount_of_best);
		out << "Best for " << wish.get_user_id() << " : ";
		for (auto it = user_ids.begin(); it != user_ids.end(); it++) {
			out << *it << ' ';
		}
		out << endl;
	}
}

std::vector <User> BestUsers::get_users() const{
	return users;
}
