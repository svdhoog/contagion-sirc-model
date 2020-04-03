Description
--

This repo contains code for a FLAME model of contagion.

SIRC: Susceptible, Infected, Recovered, Cured

Wiki:

https://en.wikipedia.org/wiki/Compartmental_models_in_epidemiology

Netlogo Demo:

https://www.youtube.com/watch?v=wMHabXx9INo

Transition probability matrix:
--

# Case I: with a cured state

```
    S    I    R    C
S 0.2  0.8    0    0
I   0  0.2  0.8    0
R 0.4    0  0.1  0.4
C   0    0    0    1
```

```
    S    I    R    C
S 1-c    c    0    0
I   0  1-c    c    0
R c/2    0  1-c  c/2
C   0    0    0    1
```

```
    S         I    R    C
S 1-p_si   p_si    0    0
I   0    1-p_ir  p_ir   0
R p_rc/2    0  1-p_rc  p_rc/2
C   0       0     0     1
```

# Case II: without a cured state

```
    S    I    R
S 0.2  0.8    0
I   0  0.2  0.8
R 0.8    0  0.2
```

```
    S    I    R
S 1-c    c    0
I   0  1-c    c
R   c    0  1-c
```

```
    S         I    R    
S 1-p_si   p_si    0
I   0    1-p_ir   p_ir
R p_rc       0  1-p_rc
```

Agent interactions
--

**Without agent interactions:**
- Agents' state transitions only depend on the own transition probabilities:

- c=const_multiplier <0.5: more likely to remain in the current state, than to have a state transition
- c=const_multiplier >0.5: more likely to have a state transition, than to remain in the current state


**With agent interactions**
- Agent state transitions depend on which other agents it meets.

Model sequence 
--

# SIRC Model 0: Non-Interactive
- agents send their IDs and read IDs of all others
- agent transition probabilities are based on their own static transition probability matrix.

**Messages:**
local_status_info

**What to investigate**
- Is there a steady state to which the dynmics converges?

# SIRC Model 1: Global contagion model
- agents send their IDs and read IDs of all others
- infection/contagion via global number of agents (full information model)
- agent transition probabilities are based on the transition probability matrix, and on the total fraction of agents in each state.
- this puts more weight on transition probabilities of states that have more agents.

**Messages:**
local_status_info

**What to investigate**
- Is there a steady state to which the dynmics converges?

# SIRC Model 2: Local contagion model
- static random matching between pairs of agents (once-and-for-all at the start)
- infection/contagion via bilateral interaction only: 1 neighbour
- state transitions are based on the static Markov transition probabilities and the interaction only: weights*probability determine the next state of an agent
- this is a special case of Model 3, with a fixed neighbourhood of one agent

**Messages:**
local_status_info

**What to investigate**

# SIRC Model 3: Neighbourhood network contagion model
- static network with a fixed neighbourhood
- infection/contagion via the fixed network interaction
- state transitions are based on the static Markov transition probabilities, and the interaction weights: weights*probability determine the next state of an agent.

**Messages:**
local_status_info

**What to investigate**
- How does the contagion dynamics change with the size of the neighbourhood?


# SIRC Model 4: Dynamic network contagion model
- dynamic network with changing neighbourhood structure
- state transitions are based on the static Markov transition probabilities, and the interaction weights: weights*probability determine the next state of an agent.
- use (x,y,z) coordinates and a continuous neighbourhood based on an interaction radius

**Messages:**
position_status_info

**What to investigate**
- If we vary the interaction radius, how does this affect the infection rate of the population?

# SIRC 5: Dynamic network contagion model + dynamic transition probability matrix
- dynamic network with changing neighbourhood
- adding a vaccination programme
- transition probabilities are dynamic, starting with the static Markov transition matrix, but updated over time due to vaccination.
- transition probabilities are also agent-specific and depend on the agent's own interaction history (hysteresis)


