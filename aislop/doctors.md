Yes. And given your situation, I would **look for computational biology/bioinformatics people rather than approaching a random medical doctor first**. They are much more likely to understand why a C/Pthreads + graph/Markov/NumPy project could be useful.

 Since you're in Thailand, you actually have some good avenues.

 ### 1\. Thailand Bioinformatics Association

 Bioinformatics Association of Thailand  is probably one of the most directly relevant communities. Its site explicitly brings together Thai bioinformatics researchers and welcomes researchers, academics, students, and people interested in **Bioinformatics, ML, and Data Science**.  Bat Thailand

 Bioinformatics Association of Thailand

 This is much closer to the person you're looking for than simply searching for "doctor."

 ### 2\. Chulalongkorn's computational biology community

 Chulalongkorn University  has an interdisciplinary **M.Sc./Ph.D. program in Bioinformatics and Computational Biology**, with researchers working at the intersection of biology and computation. Their community also holds networking activities involving researchers, experts, and students.  CUII Bioinformatics+1

 Chulalongkorn Bioinformatics & Computational Biology

 You don't necessarily need to enroll. Their public events are opportunities to meet people who already understand both sides.

 ### 3\. Mahidol / Siriraj

 Mahidol University  has a **Division of Medical Bioinformatics at Siriraj Hospital**, with research activity involving medical bioinformatics, genomics, and pharmacogenomics.  Mahidol University

 Mahidol Division of Medical Bioinformatics

 This is another particularly good target because these are people who already work at the boundary between **medicine and computation**.

 ### 4\. Conferences and workshops

 There's a particularly relevant opportunity coming up: **ICCBB 2026** (International Conference on Computational Biology and Bioinformatics) is scheduled for **November 13–15, 2026 in Bangkok**. Its topics include computational systems biology, drug discovery, biomedical informatics, biological-network analysis, ML/AI, cancer genomics, and computational biochemistry.  ICCBB+1

 ICCBB 2026

 There's also **ICABB 2026**, held jointly in Bangkok on the same dates, covering bioinformatics, biomedical engineering, computational biology, drug design, molecular simulation, cancer-related topics, and more.  ICABB

 ICABB 2026

 You don't have to present anything. **Going there and talking to people may be more valuable initially than trying to convince someone to use your library.**

 ### 5\. Look for the _right_ kind of collaborator

 I'd rank your potential contacts roughly like this—not as a judgment of importance, but by how directly their work matches your software:

 1. **Computational biologist**
2. **Bioinformatician**
3. **Systems biologist**
4. **Biomedical data scientist**
5. **Pharmacology researcher who does computational modeling**
6. **Biomedical engineer**
7. **Experimental biologist interested in computational methods**
8. Clinician/doctor who also does computational research

 A random physician may have very little use for your library. A computational biologist studying dynamic biological networks might immediately understand what you're trying to do.

 ### And don't approach them with "please use my library"

 I'd approach it more like:

 > "I'm a 42 Coding School student developing an open-source stochastic multi-agent simulation library in C/Python. It models dynamic interaction networks and state transitions. I'm interested in learning whether this abstraction corresponds to anything useful in computational biology. I'm not trying to make medical claims—I would like feedback from someone who understands the domain."

 That is a **much easier request to say yes to**.

 Then show them a tiny example rather than a 30-page description:

```
agent
 ├── type
 ├── state
 ├── compatibility
 └── interaction capacity

        ↓

dynamic graph

        ↓

state transition

        ↓

new graph
```

 And ask:

 > **"Is there a real biological problem where this abstraction would be useful, or am I modeling the wrong thing?"**

 That question is extremely valuable because you're asking them to **correct your model**, rather than asking them to endorse it.

 ### One more thing

 You don't need to wait until V2 to meet these people.

 I'd actually start building relationships **while V1 is being developed**, but don't ask them to use unfinished software yet. Go to a workshop, join the Thai bioinformatics community, talk to researchers, and learn what problems they actually have.

 Then your development loop can become:

 $$
\text{42/Pthreads}
\rightarrow
\text{library}
\rightarrow
\text{researcher feedback}
\rightarrow
\text{better abstraction}
\rightarrow
\text{Python/NumPy}
\rightarrow
\text{real research prototype}.
$$

 That is probably a much more realistic path from where you are now to eventually collaborating with biomedical researchers than trying to independently invent a medically meaningful model first.