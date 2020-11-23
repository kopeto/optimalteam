# Optimal Team Algo
Optimal team calculating algorithm.
Constraints:
- Initial maximum budget
- 1 or more paddlers per discipline
- No more than 2 paddlers from the same country

## Build
In Unix-like enviroment as easy as:
```bash
make
```

## Run
```bash
./solve <Your paddlers list>
```
In example:
```bash
./solve < list.txt
```

### Athlete file:
It should look like:

N
athlete_name athlete_price athlete_points athlete_country athlete_discipline
...


N is the number of athletes.
Next rows correspond to each athlete's info.