# Qbluff - Poker Hand Evaluator

Qbluff is a high-performance C++ library designed for fast and accurate evaluation of poker hands. It supports both standard poker variants (5, 6, and 7-card hands) and Pot Limit Omaha with 4 hole cards (PLO4). The library leverages advanced algorithms, precomputed lookup tables, and efficient combinatorial techniques to deliver rapid hand strength calculations. Qbluff is suitable for use in poker engines, simulations, AI research, and real-time applications where evaluating millions of hands per second is required. Its modular structure allows easy integration and extension for custom poker variants or research purposes.

## 🏗️ Project Structure

```
cpp/
├── evaluation/          # Hand evaluation algorithms
│   ├── core/           # Standard poker (5-7 cards)
│   └── plo/            # PLO4 evaluation
├── math/               # Hash functions & combinatorics
├── database/           # Lookup tables & data structures
├── include/            # Header files
└── examples/           # Example programs
```

## 🚀 Quick Start

### Prerequisites
- **Compiler**: `clang` and `clang++` (recommended) or `gcc`/`g++`
- **Make**: Standard `make` utility

### Building the Library

1. **Navigate to the cpp directory:**
   ```bash
   cd cpp
   ```

2. **Build the library:**
   ```bash
   make
   ```
   This creates `libpheval.a` containing all evaluation functions.

3. **View build information:**
   ```bash
   make info
   ```

4. **Clean build artifacts:**
   ```bash
   make clean
   ```

### What Gets Built

The `make` command compiles and links:
- **Core evaluators**: 5-card, 6-card, 7-card poker hands
- **PLO4 evaluator**: 4-card hole cards + 5-card board
- **Math utilities**: Hash functions, combinatorics, dynamic programming tables
- **Database**: Precomputed lookup tables for fast evaluation
- **C++ wrappers**: Object-oriented interfaces for C++ applications

## 📚 Using the Library

### C++ Example (Recommended)

```cpp
#include "phevaluator/card.h"
#include "phevaluator/rank.h"
#include "phevaluator/phevaluator.h"

using namespace phevaluator;

int main() {
    // Create cards
    Card ace_spades("As");    // Ace of Spades
    Card king_hearts("Kh");   // King of Hearts
    Card queen_diamonds("Qd"); // Queen of Diamonds
    Card jack_clubs("Jc");    // Jack of Clubs
    Card ten_spades("Ts");    // Ten of Spades
    
    // Evaluate 5-card hand
    Rank rank = EvaluateCards(ace_spades, king_hearts, queen_diamonds, jack_clubs, ten_spades);
    
    std::cout << "Hand rank: " << rank.value() << std::endl;
    std::cout << "Description: " << rank.description() << std::endl;
    
    return 0;
}
```

### PLO4 Example

```cpp
#include "phevaluator/card.h"
#include "phevaluator/rank.h"
#include "phevaluator/phevaluator.h"

using namespace phevaluator;

int main() {
    // Board cards (5 community cards)
    Card board1("As"), board2("Kh"), board3("Qd"), board4("Jc"), board5("Ts");
    
    // Player 1 hole cards (4 cards)
    Card h1_1("9s"), h1_2("6s"), h1_3("5s"), h1_4("4s");
    
    // Player 2 hole cards (4 cards)
    Card h2_1("Th"), h2_2("9h"), h2_3("8h"), h2_4("7h");
    
    // Evaluate PLO4 hands
    Rank rank1 = EvaluatePlo4Cards(board1, board2, board3, board4, board5, 
                                  h1_1, h1_2, h1_3, h1_4);
    Rank rank2 = EvaluatePlo4Cards(board1, board2, board3, board4, board5, 
                                  h2_1, h2_2, h2_3, h2_4);
    
    std::cout << "Player 1: " << rank1.description() << std::endl;
    std::cout << "Player 2: " << rank2.description() << std::endl;
    
    return 0;
}
```

## 🔧 Compilation Commands

### Building Examples

```bash
# From the examples directory
clang++ -std=c++17 -I../cpp/include your_example.cc ../libpheval.a -o your_program

# Example: Build PLO4 test
clang++ -std=c++17 -I../cpp/include plo4_example.cc ../libpheval.a -o plo4_test
```

### Building Your Own Programs

```bash
# Basic compilation
clang++ -std=c++17 -I/path/to/cpp/include your_file.cc /path/to/libpheval.a -o your_program

# With optimization
clang++ -std=c++17 -O2 -I/path/to/cpp/include your_file.cc /path/to/libpheval.a -o your_program
```

## 📊 Supported Hand Types

### Standard Poker
- **5-card hands**: All standard poker hands (High Card to Royal Flush)
- **6-card hands**: Best 5-card combination from 6 cards
- **7-card hands**: Best 5-card combination from 7 cards (Texas Hold'em)

### PLO4 (Pot Limit Omaha)
- **4-card hole cards** + **5-card board**
- Evaluates best 5-card combination using exactly 2 hole cards + 3 board cards

## 🎯 Performance Features

- **Fast lookup tables**: Precomputed rankings for instant evaluation
- **Efficient algorithms**: Optimized hash functions and combinatorics
- **Memory efficient**: Compact data structures
- **Cross-platform**: Works on macOS, Linux, and Windows

## 🧪 Testing

### Run Built Examples

```bash
# Test PLO4 evaluation
./plo4_test

# Expected output shows hand comparisons
# Player 1: Flush (Nine-High Flush)
# Player 2: Straight (Ten-High Straight)
```

### Verify Library Symbols

```bash
# Check what functions are available
nm ../libpheval.a | grep -i evaluate

# Check PLO4 functions
nm ../libpheval.a | grep -i plo4
```

## 🚫 What's Not Included

This simplified version does **NOT** include:
- PLO5 (5-card hole cards)
- PLO6 (6-card hole cards)
- 8-card or 9-card evaluation
- Advanced optimization techniques

## 🔍 Troubleshooting

### Common Issues
1. **"Undefined symbols"**: Make sure you're linking against `libpheval.a`
2. **"Header not found"**: Check your `-I` include path points to `cpp/include`
3. **"Library not found"**: Ensure `libpheval.a` is in your library path

### Debug Build

```bash
# Clean and rebuild
cd cpp
make clean
make

# Check library contents
ar -t libpheval.a
nm libpheval.a | grep -i evaluate
```

