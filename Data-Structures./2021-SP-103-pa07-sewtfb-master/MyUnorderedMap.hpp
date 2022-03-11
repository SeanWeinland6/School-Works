#include "MyUnorderedMap.h"



void get_identity(std::string& my_id)
{
  my_id = "sewtfb";
}


template<typename K, typename V>
MyUnorderedMap<K, V>::MyUnorderedMap()
{

}

template<typename K, typename V>
MyUnorderedMap<K, V>::~MyUnorderedMap()
{
  delete[] m_data;
}

template<typename K, typename V>
MyUnorderedMap<K, V>::MyUnorderedMap(const MyUnorderedMap<K, V>& source)
{
  reserve(source.reserved_size);
  for (int i = 0; i < reserved_size; i++)
  {
    if (source.m_data[i].first != "empty")
    {
      insert(source.m_data[i]);
    }

  }


}

template<typename K, typename V>
MyUnorderedMap<K, V>& MyUnorderedMap<K, V>::operator=(const MyUnorderedMap<K, V>& source)
{
  clear();
  reserve(source.reserved_size);
  for (int i = 0; i < reserved_size; i++)
  {
    if (source.m_data[i].first != "empty")
    {
      insert(source.m_data[i]);
    }

  }
  return *this;
}

//First (Key)
//Second (Value)

template<typename K, typename V>
V& MyUnorderedMap<K, V>::at(const K& key)
{
  if (find(key) != nullptr)
  {
    return find(key)->second; //Returns pointer, second is the key (value)
  }
  throw std::out_of_range("Does Not Exist");
}

template<typename K, typename V>
V& MyUnorderedMap<K, V>::operator[](const K& key)
{
  if (reserved_size == 0)
  {
    reserve(1);
  }

  if (find(key) == nullptr)
  {
    MyPair<K, V> Temp(key, V()); //V() decalres the type, but stays nullptr 
    insert(Temp);
  }
  return at(key);
}

template<typename K, typename V>
bool MyUnorderedMap<K, V>::empty() const
{
  if (data_size == 0)
  {
    return true;
  }
  return false;
}

template<typename K, typename V>
int MyUnorderedMap<K, V>::size() const
{
  return data_size;
}

template<typename K, typename V>
void MyUnorderedMap<K, V>::clear()
{
  delete[] m_data;
  reserved_size = 0;
  data_size = 0;
  m_data = nullptr;
}

template<typename K, typename V>
void MyUnorderedMap<K, V>::insert(const MyPair<K, V>& init_pair)
{
  if (reserved_size == 0)
  {
    reserve(1);
  }
  else if (.6 * reserved_size <= data_size)
  {
    reserve(reserved_size * 2);
  }

  //Value is second, key is first
  int index = hash(init_pair.first);
  int temp = index;
  index = (index + 1) % reserved_size;
  if (m_data[temp].first == "empty")
  {
    m_data[temp] = init_pair;
  }
  else
  {
    while (m_data[index].first != "empty" && temp != index)
    {
      index = (index + 1) % reserved_size;
    }
    m_data[index] = init_pair;
  }

  data_size++;
}

template<typename K, typename V>
void MyUnorderedMap<K, V>::erase(const K& key)
{
  if (data_size == 0)
  {
    return;
  }
  if (find(key) != nullptr)
  {
    int index = hash(key);
    m_data[index].first = "empty"; //
  }

  data_size--;

  if (data_size * 10 <= reserved_size)
  {
    reserve(reserved_size * .3);
  }
}

template<typename K, typename V>
MyPair<K, V>* MyUnorderedMap<K, V>::find(const K& key) const
{
  if (data_size == 0)
  {
    return nullptr;
  }

  int index = hash(key);
  int temp = index;
  index = (index + 1) % reserved_size;
  if (m_data[temp].first == key) //No collision
  {
    return &m_data[temp];
  }
  else //Search w/ collision 
  {
    int indexCopy = index;
    while (m_data[index].first != key && temp != index)
    {
      index = (index + 1) % reserved_size;

    }
    if (m_data[index].first == key) 
    {
      return &m_data[index];
    }

  }
  return nullptr;
}

template<typename K, typename V>
void MyUnorderedMap<K, V>::print() const
{
  if (reserved_size > 0)
  {
    std::cout << "(";
    for (int i = 0; i < reserved_size - 1; i++)
    {
      if (m_data[i].first != "empty")
      {
        cout << "[" << m_data[i].first << "]=" << m_data[i].second << "," << endl;
      }
    }
    if (m_data[reserved_size - 1].first != "empty")
    {
      cout << "[" << m_data[reserved_size - 1].first << "]=" << m_data[reserved_size - 1].second << ")" << endl;
    }

  }

}

template<typename K, typename V>
int MyUnorderedMap<K, V>::count(const K& key) const
{
  if (find(key) == nullptr)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

template<typename K, typename V>
void MyUnorderedMap<K, V>::reserve(int new_cap)
{
  MyPair<K, V>* TempPairArray = m_data;
  int old_size = reserved_size;
  reserved_size = new_cap;
  data_size = 0;

  m_data = new MyPair<K, V>[reserved_size];
  for (int i = 0; i < reserved_size; i++)
  {
    m_data[i].first = "empty";
  }

  for (int i = 0; i < old_size; i++)
  {
    if (TempPairArray[i].first != "empty")
    {
      insert(TempPairArray[i]);
    }
  }

  delete[] TempPairArray;


}


void get_virus_frequency(MyUnorderedMap<std::string, int>& in_tree)
{
  std::string word = "";
  char letter;
  std::string wordInput;
  while (getline(std::cin, wordInput));
  {
    cout << "\n hi1" << endl;
    wordInput = wordInput + " ";
    cout << wordInput << endl;
    for (int i = 0; i < wordInput.size(); i++)
    {
      letter = wordInput[i];
      if ((letter >= '0' && letter <= '9') || (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z') || letter == '_')
      {
        word = word + letter;
      }
      else
      {
      //word = wordInput[i];
        cout << "hi2" << endl;

        if (word.length() > 4)
        {
          for (int i = 0; i < word.size() - 4; i++)
          {
            if (word[i] == 'v' || word[i] == 'V')
            {
              if (word[i + 1] == 'i' || word[i + 1] == 'I')
              {
                if (word[i + 2] == 'r' || word[i + 2] == 'R')
                {
                  if (word[i + 3] == 'u' || word[i + 3] == 'U')
                  {
                    if (word[i + 4] == 's' || word[i + 4] == 'S')
                    {
                      if (in_tree.find(word) == nullptr)
                      {
                        in_tree.insert(MyPair<std::string, int>(word, 0));
                      }
                      in_tree[word] = in_tree[word] + 1;
                    }
                  }
                }
              }
            }
          }
        }

        word = "";
      } //else
    }
  }
} 
  template<typename K, typename V>
  int MyUnorderedMap<K, V>::hash(const K& key) const
{
  int sum = 0;
  std::string temp = (std::string)(key);
  for (int i = 0; i < key.length(); i++)
  {
    sum += (int)(key)[i];
  }
  return sum % reserved_size;
}