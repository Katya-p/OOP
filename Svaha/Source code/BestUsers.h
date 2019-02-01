#ifndef BESTUSERS_H
#define BESTUSERS_H

#include "User.h"

//—писок пользователей.
class BestUsers {
public:
	//—читывает список из входного потока. allow_empty = true, если в данном списке могут содержатьс€ пользователи с незаданными пол€ми. »наче false.
	void read(std::istream &in, bool allow_empty = false);
	//¬озвращает вектор из id пользователей в пор€дке убывани€ количества сопадений с желаемыми данными, т. е. первый - самый подход€щий.
	std::vector <std::string> get_best_ids(const User &wish, const int amount);
	//¬ыводит значение пол€ users дл€ данного списка.
	std::vector <User> get_users() const;
	//¬ыводит конечный результат.
	static void get_result(std::ostream &out, const int amount_of_best, const  BestUsers &wishes, BestUsers &list_of_users);
private:
	std::vector <User> users;
};

#endif
