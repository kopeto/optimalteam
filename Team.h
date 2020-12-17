#include <vector>
#include <iostream>
#include <set>
#include <numeric>

#include "Athlete.h"


struct Team
{
    Team(const int MAX_SIZE); 

    std::vector<const Athlete *> athletes;
    const size_t max_size;

    size_t size() const;
    bool is_full() const;
    int total_price() const;
    int total_points() const;
    bool at_least_1_in(const std::string& discipline) const;
    bool at_least_1_per_discipline() const;
    bool per_country_max(const int max_per_country) const;
    void print() const;

    void push(const Athlete* ath);
    void pop();

};