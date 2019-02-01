#include "Gistogramma.h"
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

Gistogramma::Gistogramma(istream &in) {   
    vector <string> v;
    string word;
    while (!in.eof()) {
        in >> word;
        v.push_back(word);
    }
    vector_to_gist(v);
}

Gistogramma::Gistogramma(const vector<string> &source) {
    vector <string> v = source;
    vector_to_gist(v);
}

Gistogramma::Gistogramma(const Gistogramma &sourñe)
    : dictionary(sourñe.dictionary)
{
}

Gistogramma::const_iterator Gistogramma::find(const std::string & key) const
{
    return dictionary.find(key);
}

void Gistogramma::vector_to_gist(const std::vector<std::string>& source)
{          
    for (const auto & elem : source) {
        auto it = dictionary.find(elem);
        if (it == dictionary.end()){
            dictionary.insert(pair<const string, int>(elem, 1));
        }
        else {
            it->second++;
        }
    }    
}

Gistogramma operator+(const Gistogramma & a, const Gistogramma & b)
{
    Gistogramma res(a);
    for (auto element_b : b) {
        res.dictionary[element_b.first] += element_b.second;
    }
    return res;
}

Gistogramma operator-(const Gistogramma &a, const Gistogramma &b) {
    Gistogramma res(a);
    for (auto element_a : res) {
        auto it = b.find(element_a.first);
        if (it != b.end()) {
            int new_value = std::max(element_a.second - (*it).second, 0);
            res.dictionary[(*it).first] = new_value;
        }
    }
    return res;
}

bool operator==(const Gistogramma &a, const Gistogramma &b) {    
    for (const auto & element_a : a) {
        auto it = b.find(element_a.first);
        if (it == b.end()) {
            return false;
        }
        if (element_a.second != (*it).second) {
            return false;
        }
    }
    for (const auto & element_b : b) {
        auto it = a.find(element_b.first);
        if (it == a.end()) {
            return false;
        }
        if (element_b.second != (*it).second) {
            return false;
        }
    }
    return true;
}