#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <set>

#include "Team.h"

auto get_all_athletes()
{
    int n;
    std::cin >> n;
    std::vector<Athlete> athletes(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> athletes[i].name;
        std::cin >> athletes[i].price;
        std::cin >> athletes[i].points;
        std::cin >> athletes[i].country;
        std::cin >> athletes[i].discipline;
    }
    //sort by points
    std::sort(athletes.begin(), athletes.end(), [](Athlete a1, Athlete a2) {
        return a1.points > a2.points;
    });
    return athletes;
}

static int n = 0;

void solver(Team &current_team, std::vector<Athlete> &athletes, int last_incorpored_idx, int remaining_budget, int max_per_country)
{
    //TRIVIAL CASE
    if (current_team.size() == current_team.max_size)
    {
        n++;
        //Apply Team constraints
        // NO CONSTRAIN BY NOW. ONLY BUDGET
        if (
            Team::candidate.points() < current_team.points() && current_team.at_least_1_per_discipline() && current_team.per_country_max(max_per_country))
        {
            Team::candidate.athletes.assign(current_team.athletes.begin(), current_team.athletes.end());
        }
    }
    //INTERMEDIATE CASES
    else
    {
        while (++last_incorpored_idx < athletes.size())
        {
            // get candidate ath;
            Athlete *candidate = &athletes[last_incorpored_idx];
            if ( remaining_budget > candidate->price
                && current_team.max_size - current_team.size() + last_incorpored_idx < athletes.size()
                && (current_team.max_size - current_team.size()) * athletes[last_incorpored_idx+1].points + current_team.points() > Team::candidate.points()
                )
            {
                current_team.push(candidate);
                solver(current_team, athletes, last_incorpored_idx, remaining_budget - candidate->price, max_per_country);
                current_team.pop();
            }
        }
    }
}

#define TEAM_SIZE 7
#define MAX_PER_COUNTRY 2
#define INITIAL_BUDGET 20000

Team Team::candidate(TEAM_SIZE);

int main()
{
    auto athletes = get_all_athletes();

    Team current_team(TEAM_SIZE);

    solver(current_team, athletes, -1, INITIAL_BUDGET, MAX_PER_COUNTRY);

    Team::candidate.print();

    std::cout << n << "\n";
}