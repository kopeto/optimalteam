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
    std::sort(athletes.begin(), athletes.end(), [](Athlete a1, Athlete a2){
        return a1.points > a2.points;
    });
    return athletes;
}

static int n = 0;

void solver(Team& current_team, std::vector<Athlete>& athletes, int last_incorpored_idx, int remaining_budget)
{
    //TRIVIAL CASE
    if(current_team.size() == TEAM_SIZE )
    {
        n++;
        //Apply Team constraints
        // NO CONSTRAIN BY NOW. ONLY BUDGET
        if( 
            Team::candidate.points() < current_team.points() 
            && current_team.at_least_1_per_discipline()
            && current_team.per_country_max(MAX_PER_COUNTRY)
        )
        {
            Team::candidate.athletes.assign(current_team.athletes.begin(), current_team.athletes.end());
        }
    }
    //INTERMEDIATE CASES
    else
    {
        while(++last_incorpored_idx < athletes.size())
        {
            // get candidate ath;
            Athlete* candidate = &athletes[last_incorpored_idx];
            if ( remaining_budget > candidate->price)
            {
                current_team.push(candidate);
                solver(current_team, athletes, last_incorpored_idx, remaining_budget-candidate->price);
                current_team.pop();
            }
        }
    }
}

Team Team::candidate;

int main()
{
    auto athletes = get_all_athletes();

    Team current_team;

    solver(current_team, athletes, -1, 20000);

    Team::candidate.print();

    std::cout << n << "\n";
}