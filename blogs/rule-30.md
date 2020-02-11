Pseudorandom number generator produces numbers that seem random but are generated deterministically.

a sequence of numbers whose properties approximate the properties of sequences of random numbers.

The PRNG-generated sequence is not truly random, because it is completely determined by an initial value, called the PRNG's seed (which may include truly random values)

Random number generators can be true hardware random-number generators

Good statistical properties are a central requirement for the output of a PRNG.
https://en.wikipedia.org/wiki/Statistical_randomness intended to measure how unpredictable their results are

### What is rule 30
A cellular automaton (pl. cellular automata, abbrev. CA) is a discrete model studied in computer science, mathematics, physics, complexity science, theoretical biology and microstructure modeling. Cellular automata are also called cellular spaces, tessellation automata, homogeneous structures, cellular structures, tessellation structures, and iterative arrayss

Rule 30 is an elementary cellular automaton introduced by Stephen Wolfram in 1983
elementary cellular automaton is a one-dimensional cellular automaton where there are two possible states (labeled 0 and 1) and the rule to determine the state of a cell in the next generation depends only on the current state of the cell and its two immediate neighbors.
one of the simplest possible models of computation

Rule 30 displayssx aperiodic, chaotic behaviour.
This rule is of particular interest because it produces complex, seemingly random patterns from simple, well-defined rules
It shows how simple rules produce complex structures and behaviour in nature.

a pattern resembling Rule 30 appears on the shell of the widespread cone snail species Conus textile
Rule 30 has also been used as a random number generator in Mathematica,[3] a

it is not cryptographically secure, but is suitable for simulation, as long as you avoid the occasional bad seed, like 0.

### The rules
an infinite one-dimensional array of cellular automaton cells with only two states is considered, with each cell in some initial state
At discrete time intervals, every cell spontaneously changes state based on its current state and the state of its two neighbors

current pattern 	111 	110 	101 	100 	011 	010 	001 	000
new state for center cell 	0 	0 	0 	1 	1 	1 	1 	0

The corresponding formula is [left_cell XOR (central_cell OR right_cell)]

Example for few iterations

IMAGE

The cellular automata we are discussing have a state consisting of a row of cells; each cell can be in either of two states, 0 or 1. Unlike the cellular automata of the previous exercise, the row contains a finite number of cells and is considered to “wrap around” at the ends. A new state is generated based on the current state by assigning to each cell in the new state a value determined by the same-indexed cell in the previous state as well as the two cells immediately adjacent to it. The chart below shows the rule that determines the cell value in the new state

### Properties

The following pattern emerges from an initial state in a single cell with state 1 (shown as black) is surrounded by cells with state 0 (white).

BIG IMAGE

the vertical axis represents time
any horizontal cross-section of the image represents the state of all the cells in the array at a specific point in the pattern's evolution

such as the frequent appearance of white triangles and a well-defined striped pattern on the left side;

however the structure as a whole has no discernible pattern
The number of black cells at generation n {\displaystyle n} n is given by the sequence

    1, 3, 3, 6, 4, 9, 5, 12, 7, 12, 11, 14, 12, 19, 13, 22, 15, 19, ... (sequence A070952 in the OEIS)

and is approximately n {\displaystyle n} n.


### Pseudorandom number generation
it passes many standard tests for randomness, and Wolfram previously used this rule in the Mathematica product for creating random integers


### Extra crunch
The Cambridge North railway station is decorated with architectural panels displaying the evolution of Rule 30
https://upload.wikimedia.org/wikipedia/commons/thumb/7/75/Cmglee_Cambridge_North_cladding_detail.jpg/500px-Cmglee_Cambridge_North_cladding_detail.jpgs

https://writings.stephenwolfram.com/2017/06/oh-my-gosh-its-covered-in-rule-30s/

https://writings.stephenwolfram.com/data/uploads/2017/05/1.png


# Example

https://www.wolframcloud.com/objects/demonstrations/UsingRule30ToGeneratePseudorandomRealNumbers

### Test of random ness

https://www.wolframscience.com/nks/notes-10-9--tests-of-randomness/

# References
 - https://www.stephenwolfram.com/publications/academic/random-sequence-generation-cellular-automata.pdf
