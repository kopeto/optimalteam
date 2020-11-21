#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>

#include <set>
#include <cstdio>

enum class Discipline
{
    C1M,
    C1W,
    K1M,
    K1W
};

enum class Country
{
    ESP,
    FRA,
    GER,
    CZE,
    SVK,
    SLO,
    SUI,
    AND,
    POR,
    BRA,
    SWE,
    NOR,
    AUS,
    AUT,
    CHN,
    JPN,
    LIB,
    ITA
};

#define TEAM_SIZE 7
#define INITIAL_BUDGET 25000
#define MAX_PER_COUNTRY 2
#define MIN_PER_CATEGORY 1

struct Athlete
{
    std::string name;
    int price;
    int points;
    std::string country;
    std::string discipline;
};

struct Team
{
    std::array<Athlete *, TEAM_SIZE> athletes{nullptr};

    //C1M C1W K1M K1W
    unsigned int category_count[4] = {0, 0, 0, 0};

    int total_price() const
    {
        int price = 0;
        for (const auto ath : athletes)
        {
            if (ath)
                price += ath->price;
        }
        return price;
    }

    int total_points() const
    {
        int points = 0;
        for (const auto ath : athletes)
        {
            if (ath)
                points += ath->points;
        }
        return points;
    }

    int count_members() const
    {
        return category_count[0] + category_count[1] + category_count[2] + category_count[3];
    }

    bool per_country_allowed(const Athlete &ath)
    {
        int count = 0;
        for (const auto team_member : athletes)
        {
            if (team_member && team_member->country == ath.country)
            {
                ++count;
                if (count >= MAX_PER_COUNTRY)
                    return false;
            }
        }
        return true;
    }

    bool at_least_1_per_cat() const
    {
        if (category_count[0] && category_count[1] && category_count[2] && category_count[3])
            return true;
        else
        {
            printf("Discipline missing an athlete.\n");
            return false;
        }
    }

    bool team_is_full() const
    {
        for (const auto ath : athletes)
        {
            if (!ath)
            {
                printf("Team is not full.\n");
                return false;
            }
        }
        return true;
    }

    bool per_country_max() const
    {
        std::multiset<std::string> countries;
        for (const auto ath : athletes)
        {
            countries.insert(ath->country);
            if (countries.count(ath->country) > MAX_PER_COUNTRY)
            {
                printf("Max athletes per country surpassed: %s\n", ath->country.c_str());

                return false;
            }
        }
        return true;
    }

    bool budget_not_exceeded()
    {
        if (INITIAL_BUDGET >= total_price())
            return true;
        else
        {
            printf("Initial budget exceeded: %d < %d", INITIAL_BUDGET, total_price());
            return false;
        }
    }

    bool validate()
    {
        return at_least_1_per_cat()&&team_is_full()&&per_country_max()&&budget_not_exceeded();
    }

    void print() const
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

        printf("Price:  %4d\n", total_price());
        printf("Points: %4d\n", total_points());
    }
};

void get_all_athletes(std::vector<Athlete> &athletes, int n)
{
    for (int i = 0; i < n; ++i)
    {
        std::cin >> athletes[i].name;
        std::cin >> athletes[i].price;
        std::cin >> athletes[i].points;
        std::cin >> athletes[i].country;
        std::cin >> athletes[i].discipline;
    }
}

bool initial_team(std::vector<Athlete> &athletes, Team &team)
{
    std::sort(athletes.begin(), athletes.end(), [](Athlete v1, Athlete v2) {
        return v1.price < v2.price;
    });

    bool found = false;
    int i = 0;

    for (auto &ath : athletes)
    {
        if (ath.discipline == "C1M" && team.per_country_allowed(ath))
        {
            team.athletes[0] = &ath;
            team.category_count[0]++;
            break;
        }
    }
    for (auto &ath : athletes)
    {
        if (ath.discipline == "C1W" && team.per_country_allowed(ath))
        {
            team.athletes[1] = &ath;
            team.category_count[1]++;

            break;
        }
    }
    for (auto &ath : athletes)
    {
        if (ath.discipline == "K1M" && team.per_country_allowed(ath))
        {
            team.athletes[2] = &ath;
            team.category_count[2]++;

            break;
        }
    }
    for (auto &ath : athletes)
    {
        if (ath.discipline == "K1W" && team.per_country_allowed(ath))
        {
            team.athletes[3] = &ath;
            team.category_count[3]++;

            break;
        }
    }

    team.validate();
}

void init_team(std::vector<Athlete> &athletes, Team &team)
{
    int members = 0;
    Athlete *candidate = &athletes[0];
    // while (members < TEAM_SIZE)
    // {
    //     ;
    // }
    return;
}

int main()
{
    int n;
    std::cin >> n;

    std::vector<Athlete> athletes(n);
    get_all_athletes(athletes, n);

    Team team;
    //build initial team
    initial_team(athletes, team);

    //for(const auto ath: athletes) std::cout << ath.name << " " << ath.nat << "\n";

    return 0;
}