#include "Team.h"

Team::Team(const int MAX_SIZE) : max_size(MAX_SIZE) {} 

size_t Team::size() const
{
    return athletes.size();
}

bool  Team::is_full() const
{
    return athletes.size() >= max_size;
}

void  Team::push(const Athlete* ath)
{
    athletes.push_back(ath);
}

void  Team::pop()
{
    athletes.pop_back();
}

int  Team::total_price() const
{   
    return std::accumulate(athletes.begin(), athletes.end(), 0,[](int sum, const Athlete* ath) { return sum + ath->price; });
}

int  Team::total_points() const
{
    return std::accumulate(athletes.begin(), athletes.end(), 0,[](int sum, const Athlete* ath) { return sum + ath->points; });
}

bool  Team::at_least_1_in(const std::string& discipline) const
{
    for(const auto ath: athletes )
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
    for (const auto ath : athletes)
    {
        printf("%4d %9s %4s %4s %5d\n", ath->points, ath->name.c_str(), ath->discipline.c_str(), ath->country.c_str(), ath->price);
    }
    printf("------------------------------\n");
    printf("%4d %19s %5d\n", total_points(), "", total_price());
}