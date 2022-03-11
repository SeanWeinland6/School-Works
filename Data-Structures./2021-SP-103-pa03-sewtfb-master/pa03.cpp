/* The duty of main here is to interact with the user, take in input, and manage
    wrapping output and runtime.
 * Declar any NON-REQUIRED functions above main if needed (it is not likely that
    you'll need to)
 */

#include "maze.h"


int main()
{
  int Rows; 
  int startRow;
  int startCol;
  int counter = 0; //Since we have a while loop, our counter for which map we're doing will be tracked manually.
  std::cin >> Rows;
  while (Rows != 0) //Decided to use a while loop so that if 0 is ever inputted the program will end.
  {

    //We make our matrix, fill it, then solve it.
    std::string* matrix = build_matrix(Rows);
    fill_matrix(matrix, Rows);
    find_start(matrix, Rows, startRow, startCol);
    //std::cout << startRow << "<- rows Col ->" << startCol << endl; //For debug
    std::cout << "Map " << counter << " -- ";
    if (find_exit(matrix, startRow, startCol) == true)
    {
      std::cout << "Solution found:" << endl;
    }
    else
    {
      std::cout << "No solution found:" << endl;
    }
    matrix[startRow][startCol] = 'N'; //We replace the 'N' at the beginning, since our method of pathing with @'s will write over it.
    print_matrix(matrix, Rows);
    delete_matrix(matrix);
    std::cout << endl; //This is to match formatting.
    counter++;
    std::cin >> Rows; //As previously stated, 0 results in ending the program.
  }




    return 0;
}
