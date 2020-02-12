A pseudorandom number generator produces numbers deterministically but they behave aperiodic (random) most of the times for most use-cases. The generator accepts a seed value (ideally a true random number) and starts producing the sequence as a function of this seed and/or previous number of the sequence. These are Pseudorandom because they are not truly random as they can be determined algorithmically if seed value is known. True random numbers are generated from blood volume pulse, atmospheric pressure, thermal noise, quantum phenomenon etc.

There are lots of [techniques](https://en.wikipedia.org/wiki/List_of_random_number_generators#Pseudorandom_number_generators_(PRNGs)) to generate Pseudorandom numbers like: [Blum Blum Shub algorithm](https://en.wikipedia.org/wiki/Blum_Blum_Shub), [Middle-square method](https://en.wikipedia.org/wiki/Middle-square_method), [Lagged Fibonacci generator](https://en.wikipedia.org/wiki/Lagged_Fibonacci_generator), etc. Today we dive deep into [Rule 30](https://en.wikipedia.org/wiki/Rule_30) that uses Cellular Automata. This method passes many standard tests for randomness, and was used in [Mathematica](https://www.wolfram.com/mathematica/online/) for generating random integers.

# Cellular Automaton
Before we dive into Rule 30, we will spend some time understanding [Cellular Automaton](https://en.wikipedia.org/wiki/Cellular_automaton). A Cellular Automaton is a discrete model consisting a regular grid, of any dimension, and each cell of the grid has finite number of states and a neighborhood definition. There are rules that determines how these cells interact and transitions into next generation. The rules are mostly mathematical/programmable functions that depends on current state of the cell and its neighbourhood.

![Cellular Automata](https://user-images.githubusercontent.com/4745789/74338745-c610a900-4dc8-11ea-8060-d6999fd18cc8.png)

In above Cellular Automaton we see each cell has 3 finite states `0` (red), `1` (black) and unoccupied `-1` (grey) and grid is a finite grid of size 9 x 9. The first generation of grid is populated at random and the rules of transitioning into next generation are

 - `0` (red) transitions into `1` (black)
 - `1` (black) transitions into `0` (red)
 - `-1` (grey) stays `-1` (grey)

From the rules we see above we deduce that the transition function does not take into consideration the neighbours of a particular cell rather it solely depends on the current state of the cell.

The diagram also shows sample neighboods (green) of a cell (black) but the rules we define do not consider it. When cells transitions from one generation to the next they oscillate between red and green and could be seen as below.

GIF WITH DEMO.

Cellular Automata was originally conceptualized in 1940s by [Stanislaw Ulam](https://en.wikipedia.org/wiki/Stanislaw_Ulam) and [John von Neumann](https://en.wikipedia.org/wiki/John_von_Neumann); it find its application in computer science, mathematics, physics, complexity science, theoretical biology and microstructure modeling. In the 1980s, [Stephen Wolfram](https://en.wikipedia.org/wiki/Stephen_Wolfram) did a systematic study of one-dimensional cellular automata (elementary cellular automata) on which Rule 30 is based.

# Rule 30
Rule 30 is an elementary (one-dimensional) cellular automaton where each cell has two possible states (labeled `0` (grey) and `1`
(black)). Neighbourhood of a cell is its two immediate neighbours (on its left and right). The next state (generation) of the cell depends on its current state and its neighbourhood adhereing the following rule.

RULE IMAGE

This rule is called rule 30 because above.

current pattern 	111 	110 	101 	100 	011 	010 	001 	000
new state for center cell 	0 	0 	0 	1 	1 	1 	1 	0

The corresponding formula is [left_cell XOR (central_cell OR right_cell)]

Example for few iterations

IMAGE

The cellular automata we are discussing have a state consisting of a row of cells; each cell can be in either of two states, 0 or 1. Unlike the cellular automata of the previous exercise, the row contains a finite number of cells and is considered to “wrap around” at the ends. A new state is generated based on the current state by assigning to each cell in the new state a value determined by the same-indexed cell in the previous state as well as the two cells immediately adjacent to it. The chart below shows the rule that determines the cell value in the new state

an infinite one-dimensional array of cellular automaton cells with only two states is considered, with each cell in some initial state
At discrete time intervals, every cell spontaneously changes state based on its current state and the state of its two neighbors

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



### Extra crunch
Rule 30 displayssx aperiodic, chaotic behaviour.
This rule is of particular interest because it produces complex, seemingly random patterns from simple, well-defined rules
It shows how simple rules produce complex structures and behaviour in nature.

a pattern resembling Rule 30 appears on the shell of the widespread cone snail species Conus textile
Rule 30 has also been used as a random number generator in Mathematica,[3] a

it is not cryptographically secure, but is suitable for simulation, as long as you avoid the occasional bad seed, like 0.

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
 - www.cs.indiana.edu/~dgerman/2005midwestNKSconference/dgelbm.pdf
 - https://rosettacode.org/wiki/Elementary_cellular_automaton/Random_Number_Generator
 - http://www.prism.gatech.edu/~kshah84/CAPaper.pdf
 - https://rosettacode.org/wiki/Elementary_cellular_automaton/Random_Number_Generator#Python
 - https://www.quora.com/How-can-I-generate-random-numbers-using-the-Rule-30-Cellular-Automaton
