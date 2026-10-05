Yes. There are several **very directly relevant arXiv papers**, and one is almost uncannily close to the kind of system you've been describing.

 ### Especially relevant to your idea

 1. **[Approximate lumpability for Markovian agent-based models using local symmetries](<https://arxiv.org/abs/1804.00910>)** — KhudaBukhsh et al.\
    This is probably the first one I'd read for _your_ project. It considers **Markovian agent-based models where agents have local states and interact with neighbors on a graph**, then develops a method for reducing the enormous joint state space through **approximate lumpability**. The paper even discusses approximation error using KL divergence.  arXiv
    That's remarkably close to:
    $$
   \text{agents}+\text{local state}+\text{graph interactions}
      \rightarrow
      \text{smaller Markov model}.
   $$
2. **[Spectral State Compression of Markov Processes](<https://arxiv.org/abs/1802.02920>)** — Zhang & Wang.\
    This looks at learning a **low-dimensional Markov model from empirical trajectories**, using spectral decomposition. It explicitly studies representability, aggregability, and lumpability and provides error bounds for the resulting compression.  arXiv
    This is particularly relevant if your simulator produces trajectories rather than an explicitly constructed gigantic transition matrix.
3. **[State Aggregation Learning from Markov Transition Data](<https://arxiv.org/abs/1811.02619>)** — Duan, Ke & Wang.\
    This develops a data-driven method for mapping a large Markov state space into a smaller set of **meta-states**, using spectral information from observed transitions.  arXiv
    That fits your idea of running the high-dimensional simulation and then asking:
    > "Can I discover a much smaller state representation that approximately preserves the dynamics?"

 ### There's also a very recent one

 **[Finding the Smallest Possible Exact Aggregation of a Markov Chain](<https://arxiv.org/abs/2507.11157>)** (2025) investigates reducing Markov chains while looking for very small exact aggregations, including an Arnoldi-iteration approach and comparisons with Exlump aggregation.  arXiv

 That's useful to keep in mind because it shows this is still an active research area rather than a solved "just use PCA" problem.

---

 ## The one I'd put at the top of your reading list

 I'd start with **KhudaBukhsh et al.**

 Your proposed simulator has something like:

 $$
X_t =
(\text{agent states},\text{network},\text{relationships},\ldots)
$$

 and potentially:

 $$
X_t\rightarrow X_{t+1}.
$$

 The full state space can become enormous:

 $$
|S|\approx
(\text{number of possible agent states})^m
\times
(\text{possible graphs}).
$$

 You then want something like:

 $$
\phi:S\rightarrow\{1,\ldots,K\}
$$

 with

 $$
K\ll |S|
$$

 while preserving as much of the Markov dynamics as possible.

 That's essentially the **state aggregation / lumpability** problem.

 And the particularly interesting connection to your project is that their model explicitly involves **agents whose local states change through interactions with neighboring agents on a graph**.  arXiv

 So your journey from:

 **Pthreads → multi-agent simulation → dynamic graph → Markov chain → dimensional reduction**

 actually lands you surprisingly close to an established research topic.

 If you eventually implement this in _Polygamy Threads_, the "run a huge concurrent agent simulation → automatically produce an approximate low-dimensional Markov model" feature could be considerably more mathematically interesting than simply adding PageRank or a collection of centrality algorithms.