A pseudorandom number generator produces numbers deterministically but they behave aperiodic (random) most of the time for most use-cases. The generator accepts a seed value (ideally a true random number) and starts producing the sequence as a function of this seed and/or a previous number of the sequence. These are Pseudorandom because they are not truly random as they can be determined algorithmically if seed value is known. True random numbers are generated from blood volume pulse, atmospheric pressure, thermal noise, quantum phenomenon, etc.

There are lots of [techniques](https://en.wikipedia.org/wiki/List_of_random_number_generators#Pseudorandom_number_generators_(PRNGs)) to generate Pseudorandom numbers like: [Blum Blum Shub algorithm](https://en.wikipedia.org/wiki/Blum_Blum_Shub), [Middle-square method](https://en.wikipedia.org/wiki/Middle-square_method), [Lagged Fibonacci generator](https://en.wikipedia.org/wiki/Lagged_Fibonacci_generator), etc. Today we dive deep into [Rule 30](https://en.wikipedia.org/wiki/Rule_30) that uses Cellular Automata. This method passes many standard tests for randomness and was used in [Mathematica](https://www.wolfram.com/mathematica/online/) for generating random integers.

# Cellular Automaton
Before we dive into Rule 30, we will spend some time understanding [Cellular Automaton](https://en.wikipedia.org/wiki/Cellular_automaton). A Cellular Automaton is a discrete model consisting of a regular grid, of any dimension, and each cell of the grid has a finite number of states and a neighborhood definition. There are rules that determine how these cells interact and transition into the next generation. The rules are mostly mathematical/programmable functions that depend on the current state of the cell and its neighborhood.

![Cellular Automata](https://user-images.githubusercontent.com/4745789/74360178-9bcfe300-4dea-11ea-8c87-91005e89c881.png)

In the above Cellular Automaton each cell has 2 finite states `0` (denoted by red), `1` (denoted by black). Each cell transitions into next generation by XORing the state values of its 8 neighbors. The first generation of the grid is populated at random. The generation transitions could be visualized as below:

![Cellular Automata Demo](https://media.giphy.com/media/J27aUn6QIWZFnVWzEB/giphy.gif)

Cellular Automata was originally conceptualized in the 1940s by [Stanislaw Ulam](https://en.wikipedia.org/wiki/Stanislaw_Ulam) and [John von Neumann](https://en.wikipedia.org/wiki/John_von_Neumann); it finds its application in computer science, mathematics, physics, complexity science, theoretical biology and microstructure modeling. In the 1980s, [Stephen Wolfram](https://en.wikipedia.org/wiki/Stephen_Wolfram) did a systematic study of one-dimensional cellular automata (elementary cellular automata) on which Rule 30 is based.

# Rule 30
Rule 30 is an elementary (one-dimensional) cellular automaton where each cell has two possible states `0` (red) and `1` (black). Neighbourhood of a cell is its two immediate neighbours (on its left and right). The next state (generation) of the cell depends on its current state and its neighbourhood determined by the following rule

![Rule 30](https://user-images.githubusercontent.com/4745789/74396927-78805480-4e39-11ea-8349-b6774d05a600.png)

The corresponding formula is `left_cell XOR (central_cell OR right_cell)`

Rule 30 is visualized in a 2D grid where each row represents one generation (state). Next generation (state) of the cells is computed and populated in the row below. Each row contains a finite number of cells which “wrap around” at the ends. Rule could be seen in action below

![Rule 30 in action](https://media.giphy.com/media/d9YuURGwsOD8qVt8uE/giphy.gif)

The above pattern emerges from an initial state (row 0) in a single cell with state 1 (shown as black) surrounded by cells with state 0 (red). The next generation (as seen in row 1) is computed using the rule chart shown above. The vertical axis represents time and any horizontal cross-section of the image represents the state of all the cells in the array at a specific point in the pattern's evolution.

![Chaos in Rule 30](https://user-images.githubusercontent.com/4745789/74433188-f1a59900-4e85-11ea-970d-c60af22568ea.png)

The frequent appearance of white triangles and a well-defined striped pattern on the left side. The structure as a whole has no discernible pattern. This property is exploited to generate Pseudo random numbers.

## Pseudorandom Number Generation
Rule 30 displayssx aperiodic, chaotic behaviour.
This rule is of particular interest because it produces complex, seemingly random patterns from simple, well-defined rules

![Pseudorandom Number Rule 30](https://user-images.githubusercontent.com/4745789/74435575-c2455b00-4e8a-11ea-835b-ca5f722dae9e.png)

Note: it is not cryptographically secure, but is suitable for simulation, as long as you avoid the occasional bad seed, like 0.
