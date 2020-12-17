#include <vector>
#include <iostream>
#include <string>
#include <algorithm>


#include "Team.h"
#include "Timer.hpp"

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

void solver(std::vector<Athlete>::const_iterator current_candidate, std::vector<Athlete>::const_iterator last_candidate, Team &current_team, Team &best_team, int remaining_budget, int max_per_country)
{
    //TRIVIAL CASE
    if (current_team.is_full())
    {
        //Apply Team constraints
        if (
                best_team.total_points() < current_team.total_points() 
                && current_team.at_least_1_per_discipline() 
                && current_team.per_country_max(max_per_country)
            )
        {
            best_team.athletes.assign(current_team.athletes.begin(), current_team.athletes.end());
        }
    }
    //RECURSIVE CASE
    else
    {
        while (current_candidate != last_candidate)
        {
            if( (current_team.max_size - current_team.size()) * current_candidate->points + current_team.total_points() < best_team.total_points() )
            {
                return;
            }
            else if ( remaining_budget > current_candidate->price )
            {
                current_team.push(&(*current_candidate));
                solver(std::next(current_candidate), last_candidate, current_team, best_team, remaining_budget - current_candidate->price, max_per_country);
                current_team.pop();
            }
            std::advance(current_candidate,1);
        }
    }
}

int main()
{
    const int TEAM_SIZE = 7;
    const int MAX_PER_COUNTRY = 2;
    const int INITIAL_BUDGET = 25000;

    const auto athletes = get_all_athletes();
    
    Team current_team(TEAM_SIZE);
    Team best_team(TEAM_SIZE);

    {
        Timer t;
        solver(athletes.cbegin(), athletes.cend(), current_team, best_team, INITIAL_BUDGET, MAX_PER_COUNTRY);
    }

    best_team.print();

}