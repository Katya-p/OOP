#include "Pal.h"
#include <sstream>
using namespace std;

namespace {
	const int CODE_A = 65;
	const int CODE_Z = 90;
	const int DIFFERENCE = 32;
}

Palindrom::Palindrom()
{
}

Palindrom::~Palindrom()
{
}

string Palindrom::get_low(const string &in) {
	string out = in;
	for (size_t i = 0; i < out.size(); i++) {
		if ((out[i] <= CODE_Z) && (out[i] >= CODE_A)) {
			out[i] += DIFFERENCE;
		}
	}
	return out;
}

string Palindrom::output_word(const string &in, const string &out, const string &before) {
	string after;
	if (in == out) {
		after = before + (out + " - y\n");
	}
	else {
		after = before + (out + " - n\n");
	}
	return after;
}

string Palindrom::reverse_word(const string &in) {
	int size = in.size();
	string out;
	for (int i = 0; i < size; i++) {
		out += in[size - i - 1];
	}
	return out;
}

string Palindrom::words(const string &str) {
	string output;
	string in = Palindrom::get_low(str);
	string word, reversed_word;
	istringstream ist = istringstream(in);
	while (!ist.eof()) {
		ist >> word;
		if (!word.empty()) {
			reversed_word = Palindrom::reverse_word(word);
			output = Palindrom::output_word(word, reversed_word, output);
		}
		word.clear();
	}
	return output;
}

string Palindrom::sentence_as_a_word(const string &str) {
	string output;
	string in = Palindrom::get_low(str);
	string no_spaces, reversed_word, word;
	istringstream ist = istringstream(in);
	while (!ist.eof()) {
		ist >> word;
		no_spaces += word;
		word.clear();
	}
	reversed_word = Palindrom::reverse_word(no_spaces);
	output = Palindrom::output_word(no_spaces, reversed_word, output);
	return output;
}

string Palindrom::sentence_as_a_set(const string &str) {
	string output, new_in;
	string in = Palindrom::get_low(str);
	string reversed_string, out, reversed_word, word;
	reversed_string = Palindrom::reverse_word(in);
	istringstream ist1 = istringstream(in);
	in.clear();
	while (!ist1.eof()) {
		ist1 >> word;
		if (!word.empty()) {
			in += word + ' ';
		}
		word.clear();
	}
	in.erase(in.size() - 1, 1);

	istringstream ist = istringstream(reversed_string);
	while (!ist.eof()) {
		ist >> word;
		if (!word.empty()) {
			reversed_word = Palindrom::reverse_word(word);
			out += (reversed_word + ' ');
		}
		word.clear();
	}
	out.erase(out.size() - 1, 1);
	output = Palindrom::output_word(in, out, output);
	return output;
}