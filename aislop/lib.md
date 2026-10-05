# INTRO

1.	Mesa
2.	GAMMS
3.	MAGESim
4.	WiMAS

# Simulation example

1.	Dating behavior of straight/gay/bi/guy/girl (home alone vacation, duel)
2.	Oxygen and Hydrogen interacting with each other
3.	Philo42
4.	Drug vs Bacteria/Fungi/Virus/Cancer
5.	Pandemic
6.	rock paper sister
7.	nuclear boom

# TLDR

Yes — **there are quite a lot of projects that overlap with the broad idea**, especially if "similar" means _multi-agent agents + dynamic networks + state transitions_. My search turned up several substantial examples.  GitHub+2

 But I wouldn't characterize them as simply "Markov group-bonding libraries." That's a narrower combination, and the existing projects tend to make different design choices.

 ### Examples of nearby projects

 - Mesa  — a general Python agent-based modeling framework with schedulers, spatial structures, visualization, and analysis tools. It's explicitly intended for complex systems and emergent behavior.  GitHub
- GAMMS  — particularly close to your **graph + multi-agent** idea: agents operate in graph-represented environments, with emphasis on scalable multi-agent scenarios and customizable interactions.  GitHub
- MAGESim  — a graph-structured multi-agent simulator with synchronous agent/world updates and customizable behaviors.  GitHub
- Crowd  — a Python social-network simulation framework for developing agent-based models on networks.  GitHub
- WiMAS / MAS-Simulation  — interestingly, this explicitly includes stochastic network models, including a `MarkovNetwork`, alongside agent dynamics.  GitHub
- Starsim  — a more specialized example: agent-based disease modeling with dynamic transmission networks and changing health states.  GitHub

 So **the broad territory is definitely not empty**.

 ### But your particular abstraction is still somewhat unusual

 Your idea isn't merely:

 > "agents connected by a graph."

 It's closer to:

 $$
\text{agent attributes}
+
\text{compatibility profile}
+
\text{bounded number of connections}
+
\text{dynamic rewiring}
+
\text{timed state transitions}
+
\text{concurrent execution}.
$$

 And you're intentionally making the _same underlying engine_ capable of representing things like:

```
person ↔ person
molecule ↔ molecule
drug ↔ cancer cell
philosopher ↔ fork
```

 That's where I'd distinguish your idea from the existing projects.

 For example, Mesa deliberately gives you a **general ABM framework**, whereas your proposed abstraction is much more opinionated about **bounded interaction formation and local state transitions**.  GitHub

 GAMMS and MAGESim are closer in the graph/multi-agent dimension, but their abstractions are centered around agents operating in graph environments rather than your particular "agent has a compatibility set and seeks $k$ relationships" formulation.  GitHub+1

 And WiMAS demonstrates that Markovian network behavior is already a thing in multi-agent simulation, although its focus is communication/network dynamics rather than your relationship-formation abstraction.  GitHub

 ### The bigger lesson for Polygamy Threads

 I **wouldn't try to compete with Mesa**.

 Instead, ask whether you can make this tiny model exceptionally convenient:

 $$
\boxed{
\text{Agent}
\rightarrow
\text{preferences}
\rightarrow
\text{candidate neighbors}
\rightarrow
\text{capacity constraint}
\rightarrow
\text{relationship}
\rightarrow
\text{timed transition}
}
$$

 Then expose the resulting graph/state history to NumPy/SciPy.

 If that requires 500 different abstractions before you can run the first simulation, you've probably reinvented an ABM framework.

 If you can express your dating toy model, simplified chemistry model, and Philo-like resource model with essentially the **same small API**, that's much more interesting.

 So the answer is:

 **Yes, there are lots of adjacent GitHub projects. Your novelty wouldn't be "I made an agent-based graph simulator." It would have to come from the particular constrained-interaction abstraction, implementation approach (e.g. C/PThread), performance characteristics, or exceptionally simple API.**
