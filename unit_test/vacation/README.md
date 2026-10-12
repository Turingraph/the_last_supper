There are n visitors and each visitor own a home.

Everyone of them will visit another home the next day.

There should be only one person in a home at a time.

Display the vacation record using write command.

Note
*	This exercise is incomplete because 2 agents sometimes visit the same home within the same day.

You:  First, understand why two visitors can enter the same home
Me: Because there is no synchonize mechanism that check within each loop that the home is occupied by the agent and the reset function that "unlock" everyhome once the i-th day is past.
You: Your mutex is probably not protecting the resource you need
Me: Yes, but at least it prevent the compiler to print (a.k.a. write) non-sense.
