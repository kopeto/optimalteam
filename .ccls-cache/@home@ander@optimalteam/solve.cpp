#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex>
#include "Team.h"
#include "Timer.hpp"

auto get_all_athletes()
{
    int n;
    std::cin >> n;
    std::vector<Athlete> athletes(n);
    std::for_each (athletes.begin(), athletes.end(), [](Athlete& athlete) {
        std::cin >> athlete.name;
        std::cin >> athlete.price;
        std::cin >> athlete.points;
        std::cin >> athlete.country;
        std::string discipline;
        std::cin >> discipline;
        athlete.discipline = str_to_discipline(discipline);
    });

    //sort by points
    std::sort(athletes.begin(), athletes.end(), [](Athlete a1, Athlete a2) {
        return a1.points > a2.points;
    });
    return athletes;
}


auto get_all_athletes_from_file(std::string filename)
{

  const std::regex re("\\t+");
  std::string line;
  std::vector<Athlete> athletes;
  std::ifstream input;
  input.open(filename);

  if(!input.is_open())
  {
    std::cerr << "Error opening file " << filename << "\n";
    exit(EXIT_FAILURE);
  }
  while(std::getline(input, line))
  {
    std::vector<std::string> tokens{
                std::sregex_token_iterator (line.begin(), line.end(), re, -1),
                std::sregex_token_iterator ()
                };
    
    Athlete ath;
    ath.name = tokens[0];
    ath.price = std::stoi(tokens[1]);
    ath.points = std::stoi(tokens[2]);
    ath.country = tokens[3];
    ath.discipline = str_to_discipline(tokens[4]);

    athletes.push_back(ath);
  }
  
  //sort by points
  std::sort(athletes.begin(), athletes.end(), [](Athlete a1, Athlete a2) {
      return a1.points > a2.points;
  });
  return athletes;
}

void solver(std::vector<Athlete>::const_iterator current_candidate, std::vector<Athlete>::const_iterator last_candidate, Team &current_team, Team &best_team, const int remaining_budget, const int max_per_country)
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
            if( static_cast<int>(current_team.max_size - current_team.size()) * current_candidate->points + current_team.total_points() < best_team.total_points() )
            {
                return;
            }
            else if ( remaining_budget >= current_candidate->price )
            {
                current_team.push(&(*current_candidate));
                solver(std::next(current_candidate), last_candidate, current_team, best_team, remaining_budget - current_candidate->price, max_per_country);
                current_team.pop();
            }
            std::advance(current_candidate,1);
        }
    }
}

int main(int argc,char** argv)
{
    constexpr int TEAM_SIZE  {7};
    constexpr int MAX_PER_COUNTRY = {2};
    constexpr int INITIAL_BUDGET = {20000};

  std::vector<Athlete> athletes;

  if(argc == 1)
    athletes = get_all_athletes();
  else  
    athletes = get_all_athletes_from_file(argv[1]);

  Team current_team(TEAM_SIZE);
  Team best_team(TEAM_SIZE);

  {
      Timer t;
      solver(athletes.cbegin(), athletes.cend(), current_team, best_team, INITIAL_BUDGET, MAX_PER_COUNTRY);
  }

  best_team.print();
}
