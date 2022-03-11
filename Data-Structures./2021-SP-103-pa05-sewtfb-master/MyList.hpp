#include "MyList.h"
/* Define all your MyList-related functions here, including the get_identity
    function
 * You do not need to include MyList.h in this hpp header file. It includes
    this file at the bottom.
 */

void get_identity(string& my_id)
{
  my_id = "sewtfb";
}

// Here is where you will initialize your list (of size 0) with a
//  sentinel node
template<typename T>
MyList<T>::MyList() //Good
{
  m_sentinel = new Node<T>(m_sentinel, m_sentinel);
  m_sentinel->m_next = m_sentinel;
  m_sentinel->m_prev = m_sentinel;
  m_size = 0;

  //std::cout << "Hello world" << endl;
}



template<typename T> //Good
MyList<T>::~MyList() //Remove the head (m_prev), goto next element more or less? But we can't do that...
{
  clear();
  delete m_sentinel;
}


template<typename T>
MyList<T>::MyList(const MyList<T>& source) //Good
{
  m_sentinel = new Node<T>(m_sentinel, m_sentinel);
  m_sentinel->m_next = m_sentinel;
  m_sentinel->m_prev = m_sentinel;
  m_size = 0;
  Node<T>* Temp1 = source.m_sentinel->m_next;
  for (int i = 0; i < source.m_size; i++)
  {
    Node<T>* Temp2 = Temp1;
    push_back(Temp2->m_element);
    Temp1 = Temp1->m_next;
  }




}
template<typename T>
MyList<T>& MyList<T>::operator=(const MyList<T>& source) //Good
{
  Node<T>* temp1 = source.m_sentinel->m_next;
  clear();
  for (int i = 0; i < source.m_size; i++)
  {
    Node<T>* temp2 = temp1; //1 points to 2nd
    push_back(temp2->m_element); //Creates the node itself
    temp1 = temp1->m_next;
  }
  
  return *this;
}

template<typename T>
T& MyList<T>::front()
{
  return m_sentinel->m_next->m_element;
}


template<typename T>
T& MyList<T>::back()
{
  return m_sentinel->m_prev->m_element;
}


// Assigns new contents (#count elements, each initialized to a copy of
//  value) to the list and replace its current contents
//  (size should be modified accordingly)
template<typename T>
void MyList<T>::assign(int count, const T& value)
{
  clear();
  for (int i = 0; i < count; i++)
  {
    push_back(value);
  }

}

// Default list size of 0, with one sentinel node as in the
//  default constructor
template<typename T>
void MyList<T>::clear()
{
  m_size = 0;
  Node<T>* temp1 = m_sentinel->m_next;
  while (m_sentinel != temp1)
  {
    Node<T>* temp2 = temp1;
    temp1 = temp1->m_next;
    delete temp2;
  }
  m_sentinel->m_next = m_sentinel;
  m_sentinel->m_prev = m_sentinel;
}

template<typename T>
void MyList<T>::push_front(const T& x)
{
  Node<T>* p = new Node<T>(x, m_sentinel, m_sentinel->m_next); //Creates x, then points to 
  m_sentinel->m_next->m_prev = p; //Takes first item
  m_sentinel->m_next = p;
  m_size++;

}

template<typename T>
void MyList<T>::push_back(const T& x)
{
  //Use p?
  Node<T>*p = new Node<T>(x , m_sentinel->m_prev, m_sentinel); //A new node that's attatched to the right side (tail)
  m_sentinel->m_prev->m_next = p; //Sets the m_next of the node to the left of it to the node we just made.
    m_sentinel->m_prev = p; //Attatch our current sentinel's left side to Node P
    m_size++; //Increase size

}

template<typename T>
void MyList<T>::pop_back()
{
  erase(m_size - 1);
  //m_size--; //We already have m_size being edited by erase.
}

template<typename T>
void MyList<T>::pop_front()
{
  erase(0); //We get rid of the newest element
}
// Simplified version (not exactly like std::list.insert) that inserts x
//  before element at position i.
// Note: You should be able to insert in an empty list
template<typename T>
void MyList<T>::insert(int i, const T& x)
{
  /*
  int z_size = m_size;
  Node<T>* temp1 = m_sentinel;
  for (int j = 0; j < z_size; j++)
  {
    Node<T>* temp2 = temp1;
    temp1 = temp1->m_next;
    if (i == j)
    {
      Node<T>* t = new Node<T>(x, temp2, temp1);
      temp1->m_prev = t;
      temp2->m_next = t;
      m_size++;
      std::cout << "I hit insert" << endl;

    }
  }*/

  if (m_size == 0)
  {
    this->push_back(x);
  }
  else
  {
    Node <T>* temp1 = m_sentinel;
    for (int k = 0; k < i + 1; k++)
    {
      temp1 = temp1->m_next;
    }
    Node<T>* P = new Node<T>(x, temp1->m_prev, temp1);
    temp1->m_prev->m_next = P;
    temp1->m_prev = P;
    m_size++;
  }



}

// Removes all elements in list that are equal to value
template<typename T>
void MyList<T>::remove(T value) //Good
{
  Node<T>* temp1 = m_sentinel->m_next;
  for (int i = 0; i < m_size; i++)
  {
    Node<T>* temp2 = temp1;
    temp1 = temp1->m_next;
    if (value == temp2->m_element)
    {
      temp2->m_prev->m_next = temp2->m_next;
      temp2->m_next->m_prev = temp2->m_prev;
      delete temp2;
      m_size--;
    }
 
  }

}

// Removes element at position i
template<typename T>
void MyList<T>::erase(int i) //Good
{

  Node<T>* temp1 = m_sentinel->m_next;
  for (int j = 0; j < m_size; j++)
  {
    Node<T>* temp2 = temp1;
    temp1 = temp1->m_next;
    if (i == j)
    {
      temp2->m_prev->m_next = temp2->m_next;
      temp2->m_next->m_prev = temp2->m_prev;
      delete temp2;
      m_size--;
    }
    
  }

}

// Reverses the order of the elements in the list
template<typename T>
void MyList<T>::reverse() //Good
{
  Node<T>* temp1 = m_sentinel->m_next;
  for (int i = 0; i < m_size; i++)
  {
    Node<T>* temp2 = temp1;
    T element = temp1->m_element;
    temp1 = temp1->m_next;
    erase(i);
    push_front(element);
    //back() = m_element;

  }

}

template<typename T>
bool MyList<T>::empty() //Good
{
  if (m_size == 0)
  {
    return true;
  }
  else
  {
    return false;
  }

}

template<typename T>
int MyList<T>::size() //Good
{
  return m_size;
}



