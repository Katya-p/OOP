#ifndef BESTUSERS_H
#define BESTUSERS_H

#include "User.h"

//������ �������������.
class BestUsers {
public:
	//��������� ������ �� �������� ������. allow_empty = true, ���� � ������ ������ ����� ����������� ������������ � ����������� ������. ����� false.
	void read(std::istream &in, bool allow_empty = false);
	//���������� ������ �� id ������������� � ������� �������� ���������� ��������� � ��������� �������, �. �. ������ - ����� ����������.
	std::vector <std::string> get_best_ids(const User &wish, const int amount);
	//������� �������� ���� users ��� ������� ������.
	std::vector <User> get_users() const;
	//������� �������� ���������.
	static void get_result(std::ostream &out, const int amount_of_best, const  BestUsers &wishes, BestUsers &list_of_users);
private:
	std::vector <User> users;
};

#endif
