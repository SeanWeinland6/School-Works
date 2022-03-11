#include "MyVector.h"
/* Define all your MyVector-related functions here, including the swap and the
    get_identity functions.
 * You do not need to include MyVector.h in this hpp header file. It includes
    this file at the bottom.
 */


void get_identity(string& my_id)
{
  my_id = "sewtfb";
}


template<typename T>
void MySwap(T& a, T& b)
{
  T tempA = a;
  a = b;
  b = tempA;
}

template<typename T>
MyVector<T>::MyVector()
{
  reserved_size = 0;
  data_size = 0;
  m_data = new T[reserved_size];
}

// We're giving you this one for free and as a guide for the syntax.
template <typename T>
MyVector<T>::~MyVector()
{
    delete[] m_data;
}


// Make sure this does a deep copy
template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& source)
{
  /*
  T* p = nullptr;
  p.*m_data = source.*m_data;
  p.reserved_size = source.reserved_size;
  p.data_size = source.data_size;
  */


  data_size = source.data_size;
  reserved_size = source.reserved_size;
  delete[] m_data; //Deletes the lhs' array first.
  m_data = new T[reserved_size]; //WE create the array.
  for (int i = 0; i < data_size; i++)
  {
    m_data[i] = source.m_data[i]; //Copies the memory
  }

return *this;
}

// Make sure this does a deep copy
template<typename T>
MyVector<T>::MyVector(const MyVector<T>& source)
{
  //m_data = new T[*source.m_data]; //Should deep copy
  reserved_size = source.reserved_size;
  data_size = source.data_size;
  m_data = new T[reserved_size];
  for (int i = 0; i < data_size; i++)
  {
    m_data[i] = source.m_data[i];
  }



}


// Returns the element of the array by reference, so it can be read or
//  written.
template<typename T>
T& MyVector<T>::operator[](int i)
{
  return m_data[i];
}


// Another example: remember when writing an implementation in hpp,
// return type first, then scope just before the function name.
//========================
        // Purpose: Returns the element stored at the index by reference
        // Parameters: index - The location of the element to be returned.
        // This one should throw an std::out_of_range exception if and when
        //  out-of-bounds
template <typename T>
T & MyVector<T>::at(int index)
{
  if (index >= reserved_size)
  {
    throw std::out_of_range("Out-Of-Bounds"); //Or just use ""
  }
  else
  {
    return m_data[index]; //Uses overloaded [] to perform this.
  }
}

// Purpose: Returns the element stored at the front of the vector
template<typename T>
T& MyVector<T>::front()
{
  return m_data[0]; 
}

// Purpose: Returns the element stored at the back of the vector
template <typename T>
T& MyVector<T>::back()
{
  return m_data[data_size-1]; //We do -1 here because the data_size is what the next value will be, but it hasn't been made yet.
} 

// Purpose: Returns the MAXIMUM number of elements that can be stored in
//  the current Vector
template <typename T>
int MyVector<T>::capacity()
{
  return reserved_size;
}


// Purpose: Grow the MyVector capacity to ensure that there is enough
//    room for a specific number of elements
// Parameters: new_cap - the new amount of space to be reserved
// Postconditions: Increases MyVector's current capacity to new_cap if
//    new_cap > current_capacity
//    By default, you should DOUBLE the capacity of the current array
//    when it fills up.
// NOTE: reserve SHOULD NOT do the actual checking of whether it's            <====================================
//    full; this should be done within other functions as their
//    operations change the data size.
// NOTE 2: A special case is needed to grow the initial MyVector to 1,        <=========== Shoved into insert
//    then 2, 4, etc. since the default capacity is 0
template<typename T>
void MyVector<T>::reserve(int new_cap)
{

 /* if (new_cap == 0 || reserved_size == 0 || data_size == 0) //Special Case
  {
    //If 0, it'll increase by one, then call the function again. So that it can at can function as expected.
    //reserve(new_cap + 1);
    //reserved_size = 1;
    new_cap = 1;
    reserved_size = new_cap;
    m_data = new T[reserved_size];
    return;
  }
  */

  if (new_cap > reserved_size) //Normal Case, makes sure that the new_cap is above the capacity just incase. Though I conditional shouldn't be needed.
  {
    reserved_size = new_cap;
    T* tempArray = new T[reserved_size];
    for (int i = 0; i < data_size; i++)
    {
      tempArray[i] = m_data[i];
    }
    delete[] m_data;
    m_data = tempArray;
 //   MySwap(m_data, tempArray);
   // delete[] tempArray;
    //tempArray = nullptr;
    return;
  }

//  if (new_cap < data_size)
  //{
 // }
  
  

  /*else 
  {
    if (reserved_size == 0) //Special Case
    {
      //If 0, it'll increase by one, then call the function again. So that it can at can function as expected.
      reserve(new_cap + 1);
    }
    else //If anything other than 0 it'll double it.
    {
    reserve(new_cap * 2); //It'll double the new_cap since it's the base capacity anyway. Two birds, one stone.
    }
  }*/







}




// If your array hits the point at which its data size is LESS THAN 1/4
//    of the capacity, this function should be called.
// It should shrink MyVector such that it is 2x as big as the data size.
// NOTE: shrink_to_fit SHOULD NOT do the actual checking of 1/4 full
template<typename T>
void MyVector<T>::shrink_to_fit()
{
  reserved_size = data_size*2;
}

// Fills MyVector with count of T value (e.g., assign(5, a) would be
//    [a, a, a, a, a])
// This REPLACES the current array.
template<typename T>
void MyVector<T>::assign(int count, const T& value)
{
  //Clear the function, then we assign the new stuff.
  //clear() 
  //I had originally through clear, but we want to keep the last values.
  //delete[] m_data; 
  //m_data = nullptr;

  //Couldn't you delete the last array, null ptr it, create your new away
  
  //Use Clear, Set Capactiy to count, loop for count times then call the insert function
  //
  clear();
  m_data = new T[count];
  for (int i = 0; i < count; i++)
  {
    insert(i, value); 
  }
}


// Purpose: Clears the MyVector
// Postconditions: current size set to 0, capacity size set to 0, and
//    elements are deallocated and data is set to nullptr
template<typename T>
void MyVector<T>::clear()
{
  /*for (int i = 0; i < data_size; i++)
  {
    //Spits our error since you can't turn an int to null_ptr
    m_data[i] = nullptr;
    //m_data[i] = 0;
  }*/
  delete[] m_data;
  m_data = nullptr;
  data_size = 0;
  reserved_size = 0;
  
}

// Purpose: appends the value x to the end of an MyVector
// Parameters: x is value to be added to MyVector
// Postconditions: current size is incremented by 1; if max size is
//     reached, the storage array should expand to have a bigger reserve
template<typename T>
void MyVector<T>::push_back(const T& x)
{
  if (reserved_size == 0)
  {
    reserve(1);
  }
  else if (data_size >= reserved_size)//We expand if full
  {
    reserve(reserved_size*2); //We can send either, it doesn't matter since it'll be the same #.
  }
  m_data[data_size] = x; //We append
  data_size++; //We increment
  // ===============================================================Fixed.
  

}

// Purpose: Removes the last element of the vector
// Postconditions: if the size of the list is greater than 0
//     size is decremented by one after the removal.
//     if the size of the list is less than 1/4 the max size after the
//     update, shrink the storage array
template<typename T>
void MyVector<T>::pop_back()
{
  //Causes error
  //m_data[data_size] = nullptr; //We deallocate the last element.
  //Maybe a fix?
  m_data[data_size] = 0;
  if (data_size > 0) //Postcondition 1
  {
    data_size--;
  }
  if (data_size < (reserved_size / 4)) //Postcondition 2
  {
    shrink_to_fit();
  }

}

// Purpose: inserts the value x at the position i, i.e. before the value
//          currently at i in MyVector
// Parameters: x is value to be added to MyVector
//             i is the position to insert x at
// Postconditions: current size is incremented by 1; if max size is
//     reached, the storage array should expand to have a bigger reserve  <============ SO WE DOUBLE IT AS INSTRUCTED.
template<typename T>
void MyVector<T>::insert(int i, const T& x)
{
  if (reserved_size == 0)
  {
    reserve(1);
  }
  else if (data_size >= reserved_size)//We expand if full
  {
    reserve(reserved_size * 2); //We can send either, it doesn't matter since it'll be the same #.
  }
  data_size++; //Increments
  //m_data[i] = nullptr; -> Got rid of this since you wouldn't have a value here in the firstplace.
  //Don't need to nullptr a literal
  m_data[i] = x; //Inserts the value
    
}

// Purpose: Removes the element at index i in the array
// Parameters: i, the index of the element to remove
// Postconditions: if the size of the list is greater than 0
//     size is decremented by one after the removal.
//     if the size of the list is less than 1/4 the max size after the
//     update, shrink the storage array
template<typename T>
void MyVector<T>::erase(int i)
{
  //Gives Errors
  //m_data[i] = nullptr;
  //Maybe a fix
 /* T* P;
  P = new T[reserved_size]
  for (int p = 0; p < data_size-1; p++)
  {
    P[p] = m_data[i];
  }
  delete[] m_data;
  m_data = nullptr;
  m_data = P;
  delete[] P;
  nullptr P;
  */
  //m_data[data_size] = 0;
  /*for (int j = i; j < data_size - 1; j++)
  {
    m_data[j] = m_data[j + 1];
  }*/
  do
  {
    m_data[i] = m_data[i + 1];
    i++;
  }   while (i < data_size - 1);



  if (data_size > 0) //Postcondition 1
  {
    data_size--;
  }
  if (data_size < (reserved_size / 4)) //Postcondition 2
  {
    shrink_to_fit();
  }
  //Could add return;
}


// Returns the size of the actual data stored in the array list
template<typename T>
int MyVector<T>::size()
{
  return data_size;
}