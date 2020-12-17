#include <string>

enum struct Discipline{
    C1M,
    C1W,
    K1M,
    K1W
};

struct Athlete
{
    std::string name;
    int price;
    int points;
    std::string country;
    Discipline discipline;
};