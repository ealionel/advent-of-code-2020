# Advent of Code 2020

This repository contains my solutions to **Advent of Code 2020** problems.

Every folder contains a `solution.cpp` file corresponding to the source code of my solution and a `input.txt` corresponding to my input to the problem.

## Build

From the root of the repository, use :

```shell
make build day={DAY}

# For example this will buidl day 1 solution
make build day=1 
```

Program will be built in corresponding `./$(DAY)` directory.

## Testing

From the root of the repository, use :

```shell
make test day={DAY}

# For example this will test day 1 solution with my `input.txt` content
make test day=1
```

Program will be run with corresponding day's `input.txt` in standard input.