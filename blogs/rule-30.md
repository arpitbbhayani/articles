A pseudorandom number generator produces numbers deterministically but they seem aperiodic (random) most of the time for most use-cases. The generator accepts a seed value (ideally a true random number) and starts producing the sequence as a function of this seed and/or a previous number of the sequence. These are Pseudorandom (not true random) because if seed value is known they can be determined algorithmically. True random numbers are hardware generated or generated from blood volume pulse, atmospheric pressure, thermal noise, quantum phenomenon, etc.

There are lots of [techniques](https://en.wikipedia.org/wiki/List_of_random_number_generators#Pseudorandom_number_generators_(PRNGs)) to generate Pseudorandom numbers, namely: [Blum Blum Shub algorithm](https://en.wikipedia.org/wiki/Blum_Blum_Shub), [Middle-square method](https://en.wikipedia.org/wiki/Middle-square_method), [Lagged Fibonacci generator](https://en.wikipedia.org/wiki/Lagged_Fibonacci_generator), etc. Today we dive deep into [Rule 30](https://en.wikipedia.org/wiki/Rule_30) that uses a controversial science called [Cellular Automaton](https://en.wikipedia.org/wiki/Cellular_automaton). This method passes many standard tests for randomness and was used in [Mathematica](https://www.wolfram.com/mathematica/online/) for generating random integers.

# Cellular Automaton
Before we dive into Rule 30, we will spend some time understanding [Cellular Automaton](https://en.wikipedia.org/wiki/Cellular_automaton). A Cellular Automaton is a discrete model consisting of a regular grid, of any dimension, with each cell of the grid having a finite number of states and a neighborhood definition. There are rules that determine how these cells interact and transition into the next generation (state). The rules are mostly mathematical/programmable functions that depend on the current state of the cell and its neighborhood.

![Cellular Automata](https://user-images.githubusercontent.com/4745789/74360178-9bcfe300-4dea-11ea-8c87-91005e89c881.png)

In the above Cellular Automaton each cell has 2 finite states `0` (denoted by red), `1` (denoted by black). Each cell transitions into next generation by XORing the state values of its 8 neighbors. The first generation (initial state) of the grid is alloted at random and the state transitions, of entire grid, is as below

![Cellular Automata Demo](https://media.giphy.com/media/J27aUn6QIWZFnVWzEB/giphy.gif)

Cellular Automata was originally conceptualized in the 1940s by [Stanislaw Ulam](https://en.wikipedia.org/wiki/Stanislaw_Ulam) and [John von Neumann](https://en.wikipedia.org/wiki/John_von_Neumann); it finds its application in computer science, mathematics, physics, complexity science, theoretical biology and microstructure modeling. In the 1980s, [Stephen Wolfram](https://en.wikipedia.org/wiki/Stephen_Wolfram) did a systematic study of one-dimensional cellular automata (also called elementary cellular automata) on which Rule 30 is based.

# Rule 30
Rule 30 is an elementary (one-dimensional) cellular automaton where each cell has two possible states `0` (red) and `1` (black). Neighbourhood of a cell is its two immediate neighbours, one on its left and other on right. The next state (generation) of the cell depends on its current state and the state of its neighbours; the transition rules are as illustrated below

![Rule 30](https://user-images.githubusercontent.com/4745789/74396927-78805480-4e39-11ea-8349-b6774d05a600.png)

Above transition rules could be simplified as `left XOR (central OR right)`.

Rule 30 is visualized in a 2D grid where each row represents one generation (state). Next generation (state) of the cells is computed and populated in the row below. Each row contains a finite number of cells which “wrap around” at the ends. Rule could be seen in action below

![Rule 30 in action](https://media.giphy.com/media/d9YuURGwsOD8qVt8uE/giphy.gif)

The above pattern emerges from an initial state (row 0) in a single cell with state 1 (shown as black) surrounded by cells with state 0 (red). The next generation (as seen in row 1) is computed using the rule chart shown above. The vertical axis represents time and any horizontal cross-section of the image represents the state of all the cells in the array at a specific point in the pattern's evolution.

![Chaos in Rule 30](https://user-images.githubusercontent.com/4745789/74433188-f1a59900-4e85-11ea-970d-c60af22568ea.png)

The frequent appearance of white triangles and a well-defined striped pattern on the left side. The structure as a whole has no discernible pattern. This property is exploited to generate Pseudo random numbers.

## Pseudorandom Number Generation
Rule 30 displayssx aperiodic, chaotic behaviour.
This rule is of particular interest because it produces complex, seemingly random patterns from simple, well-defined rules

![Pseudorandom Number Rule 30](https://user-images.githubusercontent.com/4745789/74435575-c2455b00-4e8a-11ea-835b-ca5f722dae9e.png)

The Pseudorandom numbers generated using Rule 30 are not cryptographically secure but are suitable for simulation as long as we do not use bad seed like `0`.

## Something extra

Rule 30 is also seen on the shell of code snail species Conus textile. The Cambridge North railway station is decorated with architectural panels displaying the evolution of Rule 30. Similar to Rule 30, we could also see the patterns that emerge from other rules. Some are random, some are pictureesque while some converge to fixed pattern.

# Conclusion
If you found Rule 30 interesting I urge you to write your own simulation of using [p5 library](https://p5js.org/) and make it generic enough to generate patterns for different rules like 90, 110, 117, etc. The patterns generated using it are quite interesting and you could take this to the next level and extend rule to work in 3D. Programming is fun when it is visual.

It is exciting when two seemingly unrelated fields, Cellular Automata and Cryptography, comes together and create something wonderful. Although this algorithm is not widely used anymore, because of more efficient solutions, it urges us to be creative in using Cellular Automata in more ways than one. This article is first in the series of Cellular Automata, so stay tuned and watch this space for more.
