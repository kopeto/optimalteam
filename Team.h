#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include "Athlete.h"


Discipline str_to_discipline(std::string& discipline);
std::string discipline_to_string(Discipline discipline);

struct Team
{
    Team(const int MAX_SIZE); 

    std::vector<const Athlete *> athletes;
    const size_t max_size;

    size_t size() const;
    bool is_full() const;
    bool at_least_1_in(Discipline discipline) const;
    bool at_least_1_per_discipline() const;
    bool per_country_max(const int max_per_country) const;
    
    int total_price() const;
    int total_points() const;    
    void print() const;

    void push(const Athlete* ath);
    void pop();

};