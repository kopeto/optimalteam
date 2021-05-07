#include "Team.h"

Discipline str_to_discipline(std::string &discipline)
{
    std::runtime_error InvalideDiscipline("RUNTIME ERROR: Invalid discipline.\n");

    std::for_each(discipline.begin(),discipline.end(),[](char& c){ c=std::toupper(c);});

    if (discipline == "C1M")
    {
        return Discipline::C1M;
    }
    else if (discipline == "C1W")
    {
        return Discipline::C1W;
    }
    else if (discipline == "K1M")
    {
        return Discipline::K1M;
    }
    else if (discipline == "K1W")
    {
        return Discipline::K1W;
    }

    std::cout << "\"" << discipline << "\" not recognized.\n";
    throw InvalideDiscipline;
}

std::string discipline_to_string(Discipline discipline)
{
    std::runtime_error InvalideDiscipline("RUNTIME ERROR: Invalid discipline.\n");

    switch (discipline)
    {
    case Discipline::C1M:
        return std::string("C1M");
        break;
    case Discipline::C1W:
        return std::string("C1W");
        break;
    case Discipline::K1M:
        return std::string("K1M");
        break;
    case Discipline::K1W:
        return std::string("K1W");
        break;
    default:
        break;
    }

    throw InvalideDiscipline;
}

Team::Team(const int MAX_SIZE) : max_size(MAX_SIZE) {}

size_t Team::size() const
{
    return athletes.size();
}

bool Team::is_full() const
{
    return athletes.size() >= max_size;
}

void Team::push(const Athlete *ath)
{
    athletes.push_back(ath);
}

void Team::pop()
{
    athletes.pop_back();
}

int Team::total_price() const
{
    return std::accumulate(athletes.cbegin(), athletes.cend(), 0, [](int sum, const Athlete *ath) { return sum + ath->price; });
}

int Team::total_points() const
{
    return std::accumulate(athletes.cbegin(), athletes.cend(), 0, [](int sum, const Athlete *ath) { return sum + ath->points; });
}

bool Team::at_least_1_in(Discipline discipline) const
{
    return std::find_if(athletes.cbegin(), athletes.cend(), [&discipline](const Athlete* ath){ return ath->discipline == discipline; }) != athletes.cend();
}

bool Team::at_least_1_per_discipline() const
{
    return at_least_1_in(Discipline::C1M) && at_least_1_in(Discipline::C1W) && at_least_1_in(Discipline::K1M) && at_least_1_in(Discipline::K1W);
}

bool Team::per_country_max(const int max_per_country) const
{
    for(auto it = athletes.begin(); it != athletes.end(); ++it)
    {
        if (max_per_country < std::count_if(it, athletes.end(), [it](const Athlete* ath_inner){
            return ath_inner->country == (*it)->country ;
        }))
        {
            return false;
        }
    }
    return true;
}

void Team::print() const
{
    for(const auto ath: athletes)
    {
        printf("%4d %20s %4s %4s %5d\n", ath->points, ath->name.c_str(), discipline_to_string(ath->discipline).c_str(), ath->country.c_str(), ath->price);
    }
    printf("------------------------------\n");
    printf("%4d %30s %5d\n", total_points(), "", total_price());
}
