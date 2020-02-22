# Searching Algorithms Server
In this program we created a generic server, which can be used for several projects.

The server solves problem that accepted by the client, and return the solution to the client.

The program is generically written therefore it can accepts and solves varios problems.

## our problem - finding the shortest path in a matrix

In our code, the problem finds the shortest path in a inputed matrix, and return the path with the cost of the nodes in the shortest path.

in order to solve this problem, we used 4 algorethms.


### ALGORITHMS

* **Best first search** - a search algorithm which explores a graph by expanding the most promising node chosen according to a specified rule. 
[read more](https://en.wikipedia.org/wiki/Best-first_search) 

* **Breadth-first search** - an algorithm for traversing or searching tree or graph data structures. It starts at the tree root , and explores all of the neighbor nodes at the present depth prior to moving on to the nodes at the next depth level. [read more](https://en.wikipedia.org/wiki/Breadth-first_search)

* **Depth-first search** -  an algorithm for traversing or searching tree or graph data structures. The algorithm starts at the root node  and explores as far as possible along each branch before backtracking. [read more](https://en.wikipedia.org/wiki/Depth-first_search)

* **A-star** - an informed search algorithm, starting from a specific starting node of a graph, it aims to find a path to the given goal node having the smallest cost . It does this by maintaining a tree of paths originating at the start node and extending those paths one edge at a time until its termination criterion is satisfied. [read more](https://en.wikipedia.org/wiki/A*_search_algorithm)

we preformes an experiment and choose the most effective algorithm.
we can see below the results of the experiment:
![the table](https://github.com/adi-cohen/part2/blob/master/ALGO.jpg)

### Design Patterns in C++

In the following program we used some design patterns, for exemple:

* Single responsibility principle - A class should only have one responsibility.

* Open/closed principle - The systems we built should be open for extension, but closed for modification. 

* bridge - A mechanism that decouples an interface (interface hierarchy) from an implementation (implementation hierarchy).

* etc.

### Test the program

You can test the program by runnig the following command:

```
python3 auto_client.py -vv
```
its runs [python code](https://github.com/adi-cohen/part2/blob/master/auto_client.py) that will be the client.
the client sent [this](https://github.com/adi-cohen/part2/blob/master/matrix_test_in.txt) matrix for the server.

 *pay attention* - you should run the program first and then the python code, so the server listen and wait for the client.

## Authors

Yaron Sofer & Adi Cohen
 BIU
