/* Here in the .cpp you should define and implement everything declared
    in the .h file
 */

#include "maze.h"


void get_identity(string &my_id)
{
  my_id = "sewtfb";
}


string * build_matrix(int rows)
{
  std::string* matrix;
  matrix = new string[rows];
    return matrix;
}


void fill_matrix(string *matrix, int rows)
{
  std::string mapLine;
  std::cin.ignore(); //The approach that I used is to cin ignore (since we had already used cin once to determine our coloumns)
                      //So we just get line inside of a loop.
  
  for(int i = 0; i < rows; i++)
  { 
    std::getline(std::cin, mapLine, '\n');
    matrix[i] = mapLine;
  }
  
}


void print_matrix(string *matrix, int rows)
{
  for (int i = 0; i < rows; i++)
  {
  //  std::cout << "R" << i << "    ";  <-This was for debug
    std::cout << matrix[i] << endl;
  }
 // std::cout << endl; //Feels out of place, but this helps match outputs.
 //Turns out it was... Removed and now I pass both tests. Neat.
}


void delete_matrix(string *&matrix)
{
  delete[] matrix;
  matrix = nullptr;
}


void find_start(string *matrix, int rows, int &row, int &col)
{
  int MazeSize = 0;
  for (int i = 0; i < rows; i++)
  {
    MazeSize = matrix[i].size(); //Since we don't know the exact size (col) we use the .size() built in function. To get it,
    for (int j = 0; j < MazeSize; j++) //Then we use it as the "size" in that direction, similar to our 2nd dimension in a pointer of arrays.
    {
      if (matrix[i][j] == 'N')
      {
        row = i;
        col = j;
        return;
      }
    }
  }
}


bool find_exit(string *matrix, int row, int col)
{
  const char routeSymbol = '@';
  const char whiteSpace = ' ';
  if (at_end(matrix, row, col) == true) //Since this is a recurring function, it'll always check at the beginning if we're at the end of the maze.
  {
    return true;
  }
  matrix[row][col] = 'N'; //Starting Position
  if (valid_move(matrix, row, col, "NORTH") && find_exit(matrix, row - 1, col)) //Tries each direction and tests it, which
  {                                                                             //serves as our recursive section of this function.
    matrix[row][col] = routeSymbol;
    return true;
  }
  else if (valid_move(matrix, row, col, "EAST") && find_exit(matrix, row, col + 1))
  {
    matrix[row][col] = routeSymbol;
    return true;
  }
  else if (valid_move(matrix, row, col, "SOUTH") && find_exit(matrix, row + 1, col))
  {
    matrix[row][col] = routeSymbol;
    return true;
  }
  else if (valid_move(matrix, row, col, "WEST") && find_exit(matrix, row, col - 1))
  {
    matrix[row][col] = routeSymbol;
    return true;
  }

  
  matrix[row][col] = whiteSpace;   //When backtracking it covers up the @'s with a " ", which is a whitespace. It took a little bit too long for me to figure out this step.
  return false;
}


bool at_end(string *matrix, int row, int col) //If current coordinates are at the end, return true.
{
  if (matrix[row][col] == 'E')
  {
    return true;
  }
  return false;
}


bool valid_move(string *matrix, int row, int col, string direction)
{
  const char whitespace = ' ';
  const char end = 'E';
  if (direction == "NORTH")
  {
    //Sees if spot is open OR the end. This occurs for each direction
    if ((matrix[row - 1][col] == end) || (matrix[row - 1][col] == whitespace))
    {
      return true;
    }
  }
  else if (direction == "EAST")
  {
    if ((matrix[row][col + 1] == end) || (matrix[row][col + 1] == whitespace))
    {
      return true;
    }
  }
  else if (direction == "WEST")
  {
    if ((matrix[row][col - 1] == end) || (matrix[row][col - 1] == whitespace))
    {
      return true;
    }
  }
  else if (direction == "SOUTH")
  {
    if ((matrix[row + 1][col] == end) || (matrix[row + 1][col] == whitespace))
    {
    return true;
    }
  }
    return false;
}
