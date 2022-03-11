Programming assignment 6 (PA06)
===============================

## What is this repository?
The files listed here are the starting point for your assignment.
Only add source files, like `pa06.cpp` (not compiled files, e.g. `a.out`), to the Git repository.

## Note (actuall do this)!!
Thoroughly read the Canvas page [How to: Homework Submissions](https://mst.instructure.com/courses/51336/pages/how-to-homework-submissions) for good tips, tricks, hints, and instructions on programming assignments, including how to submit via Git.

## Assignment Description
Help Tank find Morpheus and the others in The Matrix by creating a
**dictionary** to automate the deciphering of known symbols in code!

![matrix](tank_matrix.jpg)

You will implement a dictionary (abstract data type) using a **binary search tree** (BST)
data structure that will have similar functionality to std::map.
  - https://en.cppreference.com/w/cpp/container/map

Your tasks are:

1. to write the **MyMap** functions

2. to write a function, **get_letter_frequency()**, that accepts an
arbitrary number of characters from standard input and builds a MyMap containing the
number of occurrences for each character in the input, i.e., if the letter 'a' occurs
43 times in the input, map['a'] should return 43.
  - an example of the behavior of this function is at the end of pa06.cpp.

## Some more notes
* We gave you a working `pa06.cpp`
* We gave the sample input (`sample_input.txt`) and the sample output (`pa06_output.txt`)
* We also gave you a similar file `pa06_std.cpp` with the std:: versions of the map functions

## Grading
This assignment will be graded based on the successful implementation of the functions in the header file using unit testing, and the correct output of main (if applicable). Each function's performance on its own unit test will be worth a certain subset of those points. A correct submission will result in a grade of 100%. Besides program correctness, you should ensure that your work maintains a high standard in code readability and documentation (i.e. all code should be well-commented).

### Compilation
As a hard rule, any program that does not compile will receive an automatic grade of 10% of the total mark.

## Due date
Please see the canvas assignment schedule for all due dates.
