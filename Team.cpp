#include "Team.h"

Team::Team(const int SIZE) : max_size(SIZE) {}

size_t Team::size() const
{
    return athletes.size();
}

bool  Team::is_full() const
{
    return athletes.size() >= max_size;
}

void  Team::push(Athlete* ath)
{
    athletes.push_back(ath);
}

void  Team::pop()
{
    athletes.pop_back();
}

int  Team::total_price() const
{   
    int total_price = 0;
    for(const auto* ath: athletes)
    {
        total_price += ath->price;
    }
    return  total_price;
}

int  Team::points() const
{
    int points = 0;
    for(const auto* ath: athletes)
    {
        points += ath->points;
    }
    return  points;
}

bool  Team::at_least_1_in(std::string discipline) const
{
    for(const auto* ath: athletes )
    {
        if(ath->discipline == discipline)
            return true;
    }
    return false;
}

bool  Team::at_least_1_per_discipline() const
{
    return at_least_1_in("C1M") && at_least_1_in("C1W") && at_least_1_in("K1M") && at_least_1_in("K1W");
}

bool  Team::per_country_max(const int max_per_country) const
{
    std::multiset<std::string> countries;
    for (const auto ath : athletes)
    {
        countries.insert(ath->country);
        if (countries.count(ath->country) > max_per_country)
        {
            return false;
        }
    }
    return true;
}


void  Team::print() const
{
    int points = 0;
    int price = 0;
    for (const auto ath : athletes)
    {
        if (ath)
        {
            printf("%16s | %3s | %3s | %5d | %d\n", ath->name.c_str(), ath->country.c_str(), ath->discipline.c_str(), ath->points, ath->price);
        }
    }

    std::cout << "Price:  " << Team::candidate.total_price() << "\n";
    std::cout << "Points: " << Team::candidate.points() << "\n";
}