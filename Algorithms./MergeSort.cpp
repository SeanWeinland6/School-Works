#include <iostream>
#include <vector>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
//#include algorithms.h
using namespace std;
//srand(time(NULL));
void mergeSort(vector<int>& vec, int const begin, int const back);
void merge(vector<int>& vec, int begin, int mid, int back);
void heapSort(int arr[], int size);
void maxHeap(int arr[], int size, int heapHeigh);
int main()
{
  int spot = 1;
  int beginning = 0;
  vector<int> vec;
  const int size = 10;
  int arr[size] = { 17, 3, 4, 5, 6, 7, 8, 9, 13, 10 };
  for (int i = 0; i < size; i++)
  {
    vec.push_back(arr[i]);
  }

  //Unsorted output
  cout << "unsorted\n";
  for (int i = 0; i < size; i++)
  {
    cout << arr[i] << " ";
  }


  //Sorts
  mergeSort(vec, beginning, size - 1);
  heapSort(arr, size);



  //Output
  cout << "\nheap\n";
  for (int i = 0; i < size; i++)
  {
    cout << arr[i] << " ";
  }
  cout << "\nmerge\n";
  for (int i = 0; i < size; i++)
  {
    cout << vec[i] << " ";
  }
    return 0;
}


void mergeSort(vector<int>& vec, int const begin, int const back)
{
  if (begin >= back)
  {
    return;
  }
  int mid_Divisor = (begin + back) / 2;
  //I(k-2): L[] is being created
  mergeSort(vec, begin, mid_Divisor);
  //I(k-1): R[] is being created
  mergeSort(vec, mid_Divisor + 1, back);
  merge(vec, begin, mid_Divisor, back);
  //I(k): Vector[begin ... back] are sorted
}


void merge(vector<int>& vec, int begin, int mid, int back)
{
  int LeftSize = begin;
  int RightSize = mid + 1;
  vector<int> VecInterval;
  //I(k-2): Vector isn't sorted, Intervals are not sorted, aren't order
  while (LeftSize <= mid && RightSize <= back) {

    if (vec[LeftSize] >= vec[RightSize]) {
      VecInterval.push_back(vec[RightSize]);
      ++RightSize;
    }
    else {
      VecInterval.push_back(vec[LeftSize]);
      ++LeftSize;
    }

  }
  //I(k-1): Vector isn't sorted, Intervals are not sorted, are ordered
  while (LeftSize <= mid) 
  {
    VecInterval.push_back(vec[LeftSize]);
    ++LeftSize;
  }

  while (RightSize <= back) 
  {
    VecInterval.push_back(vec[RightSize]);
    ++RightSize;
  }
  //I(k): Vector isn't sorted, intervals are sorted & ordered
  for (int i = begin; i <= back; ++i)
    vec[i] = VecInterval[i-begin];
  //I(n) Vector is sorted
  //assert(vec != VecInterval); //assert(isSorted(vec, begin, mid, back)

}



void heapSort(int arr[], int size)
{
  int heapHeight = (size / 2) - 1;
  //Create Heap
  while (heapHeight >= 0)
  {
    maxHeap(arr, size, heapHeight);
    heapHeight--;
  }
  //I(k - 1) : A[k - 1] is not sorted
  //assert(NotSorted(arr, heapHeight)


  //By using a for loop, we are able to create sectors we've already dealt with
  for (int i = size - 1; i > 0; i--)
  {
    swap(arr[0], arr[i]); 
    maxHeap(arr, i, 0);
  }
  //I(n) is sorted
}



void maxHeap(int arr[], int size, int heapHeigh)
{
  int biggest = heapHeigh; 
  int Lchild = 2 * heapHeigh + 1;
  int Rchild = 2 * heapHeigh + 2;
  //I(k-1): Child and root aren't sorted
  // left > root
  if (Lchild < size && arr[Lchild] > arr[biggest])
  {
    biggest = Lchild; //the biggest is the left side
  }


  // right > root
  if (Rchild < size && arr[Rchild] > arr[biggest])
  {
    biggest = Rchild; //the biggest is the Right side
  }
   //I(k): Child and root aren't sorted
  //If biggest isn't still the current element
  if (biggest != heapHeigh) 
  {
    swap(arr[heapHeigh], arr[biggest]);
    maxHeap(arr, size, biggest);
  }
  //I(n): Child and root are sorted into a max heap
  //assert(IsMaxHeap(arr,size,heapHeigh)
}

