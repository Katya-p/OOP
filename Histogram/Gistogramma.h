#ifndef GISTOGRAMMA_H
#define GISTOGRAMMA_H

#include <string>
#include <map>
#include <vector>

class Gistogramma {
public:
    Gistogramma(std::istream &in);
    Gistogramma(const std::vector<std::string> &source);
    Gistogramma(const Gistogramma &source);
    using map_iter = std::map <std::string, int>::iterator;
    using map_const_iter = std::map <std::string, int>::const_iterator;
    class iterator {
    public:
        iterator(map_iter it) : it(it) {}
        std::pair<const std::string, int>& operator *() { return *it; }
        std::pair<const std::string, int>& operator ->() { return *it; }
        iterator operator ++() { ++it; return *this; }
        bool operator != (const iterator& other) const { return it != other.it; }
        bool operator == (const iterator& other) const { return it == other.it; }
    private:
        map_iter it;
    };
    class const_iterator {
    public:
        const_iterator(map_const_iter it) : it(it) {}
        const std::pair<const std::string, int>& operator *() const { return *it; }
        const std::pair<const std::string, int>& operator ->() const  { return *it; }
        const_iterator operator ++() { ++it; return *this; }
        bool operator != (const const_iterator& other) const { return it != other.it; }
        bool operator == (const const_iterator& other) const { return it == other.it; }
    private:
        map_const_iter it;
    };
    iterator begin() { return iterator(dictionary.begin()); }
    iterator end() { return iterator(dictionary.end()); }
    const_iterator begin() const { return const_iterator(dictionary.cbegin()); }
    const_iterator end() const { return const_iterator(dictionary.cend()); }
    const_iterator find(const std::string & key) const;
private:
    std::map <const std::string, int> dictionary;
    void vector_to_gist(const std::vector<std::string> &source);
    friend Gistogramma operator+(const Gistogramma &a, const Gistogramma &b);
    friend Gistogramma operator-(const Gistogramma &a, const Gistogramma &b);
};

Gistogramma operator+(const Gistogramma &a, const Gistogramma &b);
Gistogramma operator-(const Gistogramma &a, const Gistogramma &b);
bool operator==(const Gistogramma &a, const Gistogramma &b);

#endif