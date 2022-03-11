Programming assignment 3 (PA03)
==============================

# Recursive maze navigation
---

## What is this repository?
The files listed here are the starting point for your assignment.
Only add source files, like `pa03.cpp` (not compiled files, e.g. `a.out`), to the Git repository.

## Note (actually do this)!!
Thoroughly read the Canvas page [How to: Homework Submissions](https://mst.instructure.com/courses/51336/pages/how-to-homework-submissions) for good tips, tricks, hints, and instructions on programming assignments, including how to submit via Git.

* Remember, only cpp files should be compiled, not h or hpp, and never include a cpp file via #include.

## Assignment description
Help **Niobe** navigate through the matrix of service tunnels (*1-wide gaps*) outside the matrix by creating a navigation system to find **a path** through this maze.
Your job is to write a program that finds, for every map, a path from wherever you are to the exit.
You can move in any of the four cardinal directions (North, East, West and South). *No diagonal moves are possible.*
You must use **recursive backtracking** to solve the maze to get credit. Other pathfinding algorithms, such as Dijkstra's and A*, cannot be used.

![maze](maze.png)

You will also be printing out each map with a path from the "Start" point to the "Exit".
Mark the path using a trail of the character **'@'**.
<ins>Follow the format as in the sample output.</ins>
Mazes may or may not have a solution, and there may be loops or islands in the maze, though all that are inputted will be *valid enclosed mazes*.

<There will be no rooms but only tunnels>

See the hints below! 'N' is Niobe, and 'E' is exit.

## Input/Output
These are both specified in the sample_*.txt files provided in your repository.

* Input is all via C++ std::cin. Even though sample_input.txt is a file, input is not via fstream or file input; we re-direct via **standard input**: https://en.wikipedia.org/wiki/Standard_streams.
```
./yourprogram < sample_input.txt
```
* The general form of input is:
```
    <number of rows>
    <maze>
    <number of rows>
    <maze>
    0
```

  **Note**: a row of 0 should terminate your program.

* **Hint**: reading lines with white-space
  - In this assignment, you are required to read lines with white spaces (when initializing each maze input into a **string array**). You might attempt to use something like:
```
    cin >> maze[i][j];
```
But that would NOT work well, since the extraction operator>> *ignores* white spaces.
  - Instead, read input with getline and std::string (you may need to re-discover how to discard newlines to do this correctly):
    - http://www.cplusplus.com/reference/string/string/getline/

* sample_output.txt specifies exactly what your program should produce. We will use the Unix program **diff** to compare your output to this file, and if yours does not match, you will lose points.

## Grading
95% of this assignment will be graded based on the successful implementation of the functions in the header file using unit testing, and the correct output of main. Each function's performance on its own unit test will be worth a certain subset of those points, and the output of main will as well. A correct submission will result in a grade of 95%.

Besides program correctness, you should ensure that your work maintains a high standard in code readability and documentation (i.e. all code should be well-commented).

The remaining 5% will be awarded based on run-time for you main, with the student with the fastest run-time in the class receiving a 100%, and the slowest correct submission receiving 95%, and a linear interpolation (not sequential) using your actual time in between.

### Compilation
As a hard rule, any program that does not compile will receive an automatic grade of 10% of the total mark.

## Due date
Please see the canvas assignment schedule for all due dates.
