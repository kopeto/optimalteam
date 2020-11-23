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

### Athletes file
It should look like:

<N> 
<paddler's name> <price> <points> <country> <discipline>
.
.
.

N is Number of rows with paddlers info.