#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;
bool FullBag(int weight[], int Wn, vector<int> V, int size);
vector<int> GreedKnapsack(int weight[], int val[], int Wn, int size);
int SequentialKnapsack(int weight[], int val[], int Wn, int size, vector<int>& V);
int main()
{
  

  //This Case shows greedy failing.
  const int size = 10;
  int CalculatedValue = 0;
  int val[size] = {30, 60, 90, 120 , 150, 180, 210, 240, 270, 300};
  int wt[size] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
  int W = 200;
  

  //This case shows greedy passing.
 /*
  const int size = 3;
  int CalculatedValue = 0;
  int val[size] = {30, 60, 70};
  int wt[size] = {5, 20, 30};
  int W = 30;
  
  
  */

  int tempnum = 0;
  vector<int> GreedyOrder;
  vector<int> SequentialOrder;
  GreedyOrder = GreedKnapsack(wt, val, W, size);
  
  
  cout << "Alloted Weight is: " << W << endl;
  cout << "Greedy Approach:\n " << "I chose the weight(s):{";
  for (auto& v : GreedyOrder)
  {
    //We are using the weights to calculate it's expected value based off the weights from our function.
    for (int i = 0; i < size; i++)
    {
      if (v == wt[i])
      {
        CalculatedValue = CalculatedValue + val[i];
      }
    }
    cout << " " << v;
  }
  cout << " }\n The value comes out to: " << CalculatedValue << endl;
  cout << "==================\n";
  CalculatedValue = SequentialKnapsack(wt, val, W, size, SequentialOrder);

  cout << "Sequential Approach:\n " << "I chose the weight(s):{";
  //We read from the back of the vector since recursion puts the order of selected values in the back.
  for (int i = SequentialOrder.size()-1; tempnum < CalculatedValue; i--)
  {

    cout << " " << wt[SequentialOrder[i] - 1];
    tempnum = tempnum + val[SequentialOrder[i] - 1];
  }


  cout << " }\nThe sequential gets the value: " << tempnum << endl;







  return 0;
}

int SequentialKnapsack(int weight[], int val[], int Wn, int size, vector<int>& V)
{
  //I(K-1): Knapsack highest value isn't found.
  //I didn't have this origianlly, but I realized that it won't stop going. When size or leftover weight isn't existant anymore
  if (Wn == 0 || size == 0)
  {
    return 0;
  }


  //Looks at the last item of the array, and will go from the end to the front of the array.
  //If the weight at that spot is greater than our assigned weight, we go to the next, otherwise goto the else.
  if (Wn < weight[size - 1])
  {
    return SequentialKnapsack(weight, val, Wn, size - 1, V);

  }
  else
  {
    int WithCurrent = val[size - 1] + SequentialKnapsack(weight, val, Wn - weight[size - 1], size - 1, V);
    int WithoutCurrent = SequentialKnapsack(weight, val, Wn, size - 1, V);

    //I(K): The highest value is found
    if (WithCurrent > WithoutCurrent)
    {
      V.push_back(size);
      return WithCurrent;
    }
    else
    {
      return WithoutCurrent;
    }
  }
  //I(n) : WithCurrentValue / WithoutCurrentValue has found the highest values.
}



vector<int> GreedKnapsack(int weight[], int val[], int Wn, int size)
{
  vector <float> V; //V is our ratio Vector
  vector <int> VWeight;
  vector <int> SelectedWeight;
  int BeforeWn = Wn;



  //Calculate our V/W ratio
  //I(K-1): The vector doesn't have ratio's.
  assert(V.empty());
  for (int i = 0; i < size; i++)
  {
    V.push_back(val[i] / weight[i]);
  }
  //I(K): The vector is filled with ratio's'
  assert(!(V.empty()));

  //Maxheap Sort, and match the heap sort with the weight.
  make_heap(V.begin(), V.end());


  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      if (V[i] == val[j] / weight[j])
      {
        VWeight.push_back(weight[j]);
      }
    }
    
  }
  
  //I(R-1): The bag has not been filled.
  assert((SelectedWeight.empty()));
  //We now in order of ratio, check if the weight of our ratio will fit, if it does then we take it.
  for (int i = 0; i < size; i++)
  {
    if (VWeight[i] <= Wn)
    {
      Wn = Wn - VWeight[i];
      SelectedWeight.push_back(VWeight[i]);
    }
  }
  //I(R): The bag has been filled and can't be filled anymore and isn't overfilled
  assert(!(SelectedWeight.empty()) && (0 <= Wn < BeforeWn));
  return SelectedWeight;
}

