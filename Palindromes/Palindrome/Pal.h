#ifndef _PALINDROM
#define _PALINDROM
#include <string>

class Palindrom {
public:
	Palindrom();
	~Palindrom();
	static std::string words(const std::string &in);
	static std::string sentence_as_a_word(const std::string &in);
	static std::string sentence_as_a_set(const std::string &in);
private:
	static std::string output_word(const std::string &in, const std::string &out, const std::string &result);
	static  std::string get_low(const std::string &in);
	static std::string reverse_word(const std::string &in);
};

#endif
