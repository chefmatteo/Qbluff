# Qbluff - Poker Hand Evaluation Algorithm

A C++ implementation of an efficient poker hand evaluation algorithm using dynamic programming and hash functions.

## What is this?

This project implements a fast algorithm to evaluate poker hands by:

- Using a 3D dynamic programming array to precompute combinations
- Implementing perfect hash functions for binary and quinary representations
- Optimizing memory usage and cache locality

## Files

- `algorithm.md` - Detailed explanation of the algorithm with examples
- `hash_function.cpp` - C++ implementation of the hash functions
- `further_algo.md` - Advanced optimization techniques and improvements
- `sim.cc` - Simulation/testing file

## How to compile and run

```bash
# Compile the hash function
g++ -std=c++17 -O2 hash_function.cpp -o hash_function

# Run the program
./hash_function
```

## What the algorithm does

1. **Binary Hash**: Finds the position of a binary number with exactly k ones in lexicographical order
2. **Quinary Hash**: Handles poker hands where each rank can have 0-4 cards
3. **Dynamic Programming**: Uses a 3D array to precompute all possible combinations

## Performance

- **Current**: ~1,000 hands/second
- **With optimizations**: Up to 500,000+ hands/second (see `further_algo.md`)

## Use cases

- Poker hand evaluation
- Game theory research
- Combinatorial optimization
- Learning dynamic programming techniques

## Requirements

- C++17 compiler
- Standard library support
- No external dependencies

## License

This is a research/educational project. Feel free to use and modify.
