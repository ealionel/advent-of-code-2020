# Advent of Code 2020

This repository contains my solutions to [**Advent of Code 2020**](https://adventofcode.com/2020/) problems.

Every folder contains a `solution.cpp` file corresponding to the source code of my solution and a `input.txt` corresponding to my input to the problem.

## Build

From the root of the repository, use :

```shell
make build day={DAY}

# For example this will build day 1 solution
make build day=1 
```

Program will be built in corresponding `./$(DAY)` directory.

## Testing

From the root of the repository, use :

```shell
make test day={DAY} input={INPUT_FILE}

# For example this will test day 1 solution with `./1/input.txt` file content
make test day=1

# For example this will test day 1 solution with my `./1/test.txt` file content
make test day=1 input={test.txt}
```

Program will be run with corresponding day's `input.txt` in standard input.

## Summary

* [**Day 1:** Report Repair](./1)
* [**Day 2:** Password Philosophy](./2)
* [**Day 3:** Toboggan Trajectory ](./3)
* [**Day 4:** Passport Processing](./4)
* [**Day 5:** Binary Boarding](./5)
* [**Day 6:** Custom Customs](./6)
* [**Day 7:** Handy Haversacks](./7)
* [**Day 8:** Handheld Halting](./8)
* [**Day 9:** Encoding Error](./9)
* [**Day 10:** Adapter Array](./10)
* [**Day 11:** Seating System](./11)
* [**Day 12:** Rain Risk](./12)
* [**Day 13:** Shuttle Search](./13)