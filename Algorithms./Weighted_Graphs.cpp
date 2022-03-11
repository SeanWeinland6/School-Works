// Porject 3 - MST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include<string>

using namespace std;

//I had to make it a struct to make comparisons easier.
struct Edge 
{
  int start; //The start of the node
  int dest; //The destination node.
  int weight; //Weight between nodes.
};
 
class Adjacency_List 
{
  public:
    int V; //total Verticies
    int E; //total Edges
    Edge* edge; //Edge values.
};
 
//Our matrixList.
class matrix {
public:
    int root;
    int SpotPosition;
};
 
int find(matrix MatrixList[], int i)
{
  //Recursive function to find root.
  if (MatrixList[i].root != i)
  {
    MatrixList[i].root = find(MatrixList, MatrixList[i].root);
  }

  return MatrixList[i].root;
}
 
bool GoodChoice(Adjacency_List* WeightedGraph, int p)
{
  //Used for making sure we aren't using an already used line.
    if (WeightedGraph->edge[p].weight == 100)
    {
      return false;
    }

  return true;
}

bool IsntConnected(Adjacency_List* WeightedGraph, int p)
{
  int back = WeightedGraph->edge[p].dest;
  int front =  WeightedGraph->edge[p].start;
  bool Safe = true;
  for (int i = 0; i < WeightedGraph->E; i++)
  {
    if (WeightedGraph->edge[i].dest == back && WeightedGraph->edge[i].dest == front)
    {
      //Safe
    }
    else if (WeightedGraph->edge[i].dest == back)
    {
      for (int j = 0; j < WeightedGraph->E; j++)
      {
        if (WeightedGraph->edge[i].weight == WeightedGraph->edge[j].weight < 100)
        {
          //Safe
        }
        else
        {
          return false;
        }
      }
    }




  }
  return true;
}

void printMST(vector<Edge> result, Adjacency_List* WeightedGraph)
{
  cout << "Pretty form print MST:\n";
  int MST_Cost = 0;
  for (int i = 0; i < WeightedGraph->V - 1; ++i)
  {

    cout << "[" << result[i].start << "-" << result[i].dest
      << "] = weight: " << result[i].weight << endl;
    MST_Cost = MST_Cost + result[i].weight;
  }
  cout << "MST Cost: " << MST_Cost << endl;
  return;
}

//Pre-Condition: WeightedGraph isn't sorted, Verticies / edges aren't 0. 
 //               Weight's have to be unique.

void MST(Adjacency_List* WeightedGraph)
{
    vector<Edge> result(WeightedGraph->V); // Tnis will store the resultant MST
    Edge next_edge;
    int x = 0;
    int y = 0;
 


    //Sort, it's not efficent, but it works.


    //I(k - 1) : The array isnÅft sorted by weight.
    //Assert(GraphNotSorted(WeightedGraph))

    int Sorter = 0;
    while (WeightedGraph->V != Sorter)
    {
    for (int i = 0; i < WeightedGraph->E - 1; i++)
    {
      if (WeightedGraph->edge[i].weight > WeightedGraph->edge[i+1].weight)
      {
        swap(WeightedGraph->edge[i], WeightedGraph->edge[i + 1]);
      }
    }
    Sorter++;
    }
    //I(K) : Array is now sorted by weight, as well as indices line up with the adjusted weights.

    //	I(P-1): No subsets/MatrixÅfs are made
//Assert(Matrix.empty())
    matrix* MatrixList = new matrix[(WeightedGraph->V)]; //Creates a list of MatrixList.
    // Create V MatrixList with single elements
    for (int i = 0; i < WeightedGraph->V; i++)
    {
        MatrixList[i].root = i; //At the root, it's at position i.
        MatrixList[i].SpotPosition = 0; //The spot in the matrix.
    }
    //	I(P): We can now have subsets/matrixÅfs


    //I(J-2): MST isnÅft created, nor or any edges connected
    //Assert(MatrixMST(Matrix, WeightedGraph))


    // Number of edges to be taken is equal to V-1
    for (int e = 0; e < WeightedGraph->V - 1; e++)
    {
      //I(J - 1) : MST is being created, but isnÅft finished, and edges arenÅft all connected.
      //Assert((MatrixBeingUsed(Matrix))

      for (int i = 0; i < WeightedGraph->E; i++)
      {
        next_edge = WeightedGraph->edge[i];
        x = find(MatrixList, next_edge.start); //Obtains matrix 1
        y = find(MatrixList, next_edge.dest); //Obtains matrix 2
        if (x != y) //We find a path that works.
        {
          result[e] = next_edge; //We list the edge being stored.
          x = find(MatrixList, x); //We find the MatrixList start.
          y = find(MatrixList, y); //We find the end of the matrix.

          //Edge1 UNION Edge2
          //I tried to use levels, in which if one level is high than the other,
          //then it has to connect to the root of the other.
          //Such as X level > Y level, then set Y root = X root.
          //==================
          //Last, if  Edge1=Edge2, it'll just set one of them to the root, 
          //and increase its level.

          if (MatrixList[x].SpotPosition > MatrixList[y].SpotPosition)
          {
            MatrixList[y].root = x;
          }
          else if (MatrixList[x].SpotPosition < MatrixList[y].SpotPosition)
          {
            MatrixList[x].root = y;
          }
          else
          {
            MatrixList[y].root = x;
            MatrixList[x].SpotPosition++;
          }
          //We break out from this loop, and check the next connection/node.
          i = WeightedGraph->E;
        }
      }
    }
    //I(J): MST is created.



    printMST(result, WeightedGraph);

}

//Post-Condition: WeightedGraph is sorted.

//Pre-Condition: WeightedGraph[] isn't sorted, start node & selected are within RANGE of possible nodes.
//                Verticies / edges aren't 0. As well as weight. Weight's have to be unique.
void SSSP(Adjacency_List* WeightedGraph, int startNode, vector<int> selected)
{
  bool AdjustFront = true;
  int choice = 100;
  int choiceVal = 0;
  int ChoiceName = 0;
  vector<Edge> PossibleChoices;
  vector<int> PossibleChoiceVal;

  //I(N-1): SSSP isnÅft found
  for (int p = 0; p < WeightedGraph->V - 1; p++)
  {

  //I(k - 2) : No nodes are selected(with exception to startnode), nor added to vector.
  //Assert(selectedNodes.size() == 1)


    //Picks Candidates.
    for (int i = 0; i < WeightedGraph->E; i++)
    {
      //I(K - 1) : Nodes are being chosen if they match our list of selectable nodes
      for (int j = 0; j < selected.size(); j++)
      {
        if (WeightedGraph->edge[i].start == selected[j] && GoodChoice(WeightedGraph, i)
          || WeightedGraph->edge[i].dest == selected[j] && GoodChoice(WeightedGraph, i))
          //If the node is selectable, store the weight.
        {
          PossibleChoices.push_back(WeightedGraph->edge[i]);
          PossibleChoiceVal.push_back(i);

        }
      }
    }



    //Picks a path.


  //  I(J - 1) : No path is chosen
  //  Assert(SSSP_Incomplete(selectedNodes) == true)

    for (int i = 0; i < PossibleChoices.size(); i++)
    {
      // cout << "A:   " << PossibleChoices[i].weight << "<" << choice << endl;
      if (PossibleChoices[i].weight < choice && PossibleChoices[i].dest != selected.size()-1)
      {

        choice = PossibleChoices[i].weight;
        choiceVal = PossibleChoiceVal[i];
        ChoiceName = PossibleChoices[i].dest;
        //cout << "AS " << ChoiceName << endl;
        //AdjustFront = true;
        
        

      }
    }
    //I(J) : A path is chosen.
    selected.push_back(ChoiceName); //Store the chosen node (Destination)

    //Output
    cout << "[" << WeightedGraph->edge[choiceVal].start << " -> " <<
      WeightedGraph->edge[choiceVal].dest << "] ";
    if (p < WeightedGraph->V - 2)
    {
      cout << "| ";
    }
    //Mark the indicie as used.
    WeightedGraph->edge[choiceVal].weight = 100;


    //Resets parameters.
    choice = 100;
    PossibleChoices.clear();
    PossibleChoiceVal.clear();

  }
  //I(n) = SSSP is achieved.
  return;

}

//Post-Condition: WeightedGraph[] is sorted


// Driver code
int main()
{
  //Initalization
    const int V = 4; // Number of vertices in WeightedGraph
    const int E = 5; // Number of edges in WeightedGraph
    vector<int> SelectedNode;
    SelectedNode.push_back(0);
    Adjacency_List* WeightedGraph = new Adjacency_List;
    WeightedGraph->V = V;
    WeightedGraph->E = E;
  //Make our graph based off our Edge struct and Adjancy List class.
    WeightedGraph->edge = new Edge[E];
    WeightedGraph->edge[0].start = 0;
    WeightedGraph->edge[1].start = 0;
    WeightedGraph->edge[2].start = 0;
    WeightedGraph->edge[3].start = 1;
    WeightedGraph->edge[4].start = 2;
    WeightedGraph->edge[0].dest = 1;
    WeightedGraph->edge[1].dest = 2;
    WeightedGraph->edge[2].dest = 3;
    WeightedGraph->edge[3].dest = 3;
    WeightedGraph->edge[4].dest = 3;
    WeightedGraph->edge[0].weight = 8;
    WeightedGraph->edge[1].weight = 5;
    WeightedGraph->edge[2].weight = 4;
    WeightedGraph->edge[3].weight = 13;
    WeightedGraph->edge[4].weight = 3;
    //Make a second one for the other algorithm
    Adjacency_List* BackupGraph = WeightedGraph;

    //Run out 2 Algorithms.
    MST(WeightedGraph);
    cout << "\n==========================================\n\n";
    SSSP(BackupGraph, 0, SelectedNode);
    
    //Graph looks like one similar to one done in class.
    /*
        (8)
    0 ------ 1
 (5)|   \ (4)| (13)
    2 ------ 3
        (3)
    
    */


   

 
    return 0;
}
 