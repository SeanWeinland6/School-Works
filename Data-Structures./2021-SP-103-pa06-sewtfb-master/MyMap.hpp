#include "MyMap.h"
/* Define all your MyMap-related functions here, including the get_identity
    function
 * You do not need to include MyMap.h in this hpp header file. It includes
    this file at the bottom.
 */


void get_identity(std::string& my_id)
{
  my_id = "sewtfb";
}

void get_letter_frequency(MyMap<char, int>& in_tree)
{
  std::string tempString;
  char tempChar;
  while (std::getline(cin, tempString))
  {
    for (int i = 0; i < tempString.size(); i++)
    {
      tempChar = tempString[i];
      MyPair<char, int> Pair(tempChar, 0);
      if (!(in_tree.find(tempChar)))
      {
        in_tree.insert(Pair);
      }
      in_tree.find(tempChar)->second++;
    }
  }
  
  return; //God save the queen 
}



template<typename K, typename V> //K is int, V is string (the letter we'll store)
MyMap<K, V>::MyMap()
{
}

template<typename K, typename V>
MyMap<K, V>::~MyMap()
{
  clear();
  //Do we delete the root too?
}

template<typename K, typename V>
MyMap<K, V>::MyMap(const MyMap<K, V>& source)
{
  if (source.root != nullptr)
  {
    root = clone(source.root);
  }
  else
  {
    root = nullptr;
  }

}

template<typename K, typename V>
MyMap<K, V>& MyMap<K, V>::operator=(const MyMap<K, V>& source)
{
  clear();
  if (source.root != nullptr)
  {
    root = clone(source.root);
  }
  else
  {
    root = nullptr;
  }

  return *this;
}

template<typename K, typename V>
V& MyMap<K, V>::at(const K& key)
{
  if (find(key) == nullptr)
  {
    throw std::out_of_range("Out of Range");
  }
  return at_helper(root, key);
}

template<typename K, typename V>
V& MyMap<K, V>::operator[](const K& key)
{
  if (find(key) == nullptr)
  {
    insert(MyPair<K, V>(key, V()));
  }
  return at(key);
}

template<typename K, typename V>
bool MyMap<K, V>::empty() const
{
  return root == nullptr;
}

template<typename K, typename V>
int MyMap<K, V>::size() const
{
  return size_helper(root);
}

template<typename K, typename V>
void MyMap<K, V>::clear()
{
  if (!(empty()))
  {
    clear_helper(root);
    root = nullptr;
  }
  return;

}

template<typename K, typename V>
void MyMap<K, V>::insert(const MyPair<K, V>& init_pair)
{
  MyPair<K, V>* tempPair = find(init_pair.first); //FInds pos
  if (tempPair == nullptr) //If it isn't found
  {
    insert_helper(root, init_pair);
    return;
  }
  else //If it is found
  { 
    tempPair->second = init_pair.second;
    return;
  }
  
}

template<typename K, typename V>
void MyMap<K, V>::erase(const K& key)
{
  erase_helper(root, key);
}

template<typename K, typename V>
MyPair<K, V>* MyMap<K, V>::find(const K& key) const
{
  return find_helper(root, key);
}

template<typename K, typename V>
void MyMap<K, V>::print() const
{
  print_helper(root, "   "); //Indent = 3 Spaces
}

template<typename K, typename V>
int MyMap<K, V>::count(const K& key) const
{
  return count_helper(root, key);
}


//===========
//Helper Functions
//===========
//First = Key (Char)
//Second = Value (Int)


template<typename K, typename V>
V& MyMap<K, V>::at_helper(TreeNode<MyPair<K, V>>*& rt, const K& key)
{
  
  return find_helper(rt, key)->second; //Gets pointer
}

template<typename K, typename V>
int MyMap<K, V>::size_helper(TreeNode<MyPair<K, V>>* rt) const
{
  if (rt == nullptr)
  {
    return 0;
  }
  return 1 + size_helper(rt->left) + size_helper(rt->right);
}

template<typename K, typename V>
void MyMap<K, V>::clear_helper(TreeNode<MyPair<K, V>>*& rt)
{
  if (rt == nullptr)
  {
    return;
  }
  clear_helper(rt->left);
  clear_helper(rt->right);
  delete rt;
  rt = nullptr;

}

template<typename K, typename V>
void MyMap<K, V>::insert_helper(TreeNode<MyPair<K, V>>*& rt, const MyPair<K, V>& init_pair)
{
  if (rt == nullptr)
  { 
    rt = new TreeNode<MyPair<K, V>>(init_pair, nullptr, nullptr);
    return;
  }
  else if (rt->data.first < init_pair.first) //Move Right 
  { //Greatest in bottom left
    insert_helper(rt->right, init_pair);
  }
  else //Moves Left
  {
    insert_helper(rt->left, init_pair);
  }
}

template<typename K, typename V>
TreeNode<MyPair<K, V>>* MyMap<K, V>::get_min(TreeNode<MyPair<K, V>>* rt)
{
  if (rt->left == nullptr)
  {
    return rt;
  }
  return get_min(rt->left);
}

template<typename K, typename V>
void MyMap<K, V>::erase_helper(TreeNode<MyPair<K, V>>*& rt, const K& key)
{
  if (rt == nullptr)
  {
    return;
  }
  else if (rt->data.first < key) //Move Right, left is too small
  { //Greatest in bottom left
    erase_helper(rt->right, key);
  }
  else if (rt->data.first > key) //Moves Left (Compares keys)
  {
    erase_helper(rt->left, key);
  }
  else
  {
    if (rt->right == nullptr && rt->left == nullptr)
    {
      delete rt;
      rt = nullptr;
      return;
    }
    else if (rt->left == nullptr)
    {
      TreeNode<MyPair<K, V>>* tempNode = new TreeNode<MyPair<K, V>>(rt->data, nullptr, rt->right);
      rt = rt->right;
      delete tempNode;
    }
    else if (rt->right == nullptr)
    {
      TreeNode<MyPair<K, V>>* tempNode = new TreeNode<MyPair<K, V>>(rt->data, rt->left, nullptr);
      rt = rt->left;
      delete tempNode;
    }
    else
    {
      TreeNode<MyPair<K, V>>* tempNode = get_min(rt->right);
      rt->data = tempNode->data;
      erase_helper(rt->right, tempNode->data.first);
    }
  }
}

template<typename K, typename V>
MyPair<K, V>* MyMap<K, V>::find_helper(TreeNode<MyPair<K, V>>* rt, const K& key) const
{
  if (rt == nullptr)
  {
    return nullptr;
  }
  else if (rt->data.first == key)
  {
    return &rt->data;
  }
  else if (key < rt->data.first)
  {
    return find_helper(rt->left, key);
  }
  else
  {
    return find_helper(rt->right, key);
  }
  
}

template<typename K, typename V>
void MyMap<K, V>::print_helper(TreeNode<MyPair<K, V>>* rt, std::string indent) const
{
  if (rt == nullptr)
  {
    cout << indent << "[empty]" << endl;
    return;
  }
  print_helper(rt->right, indent + "  ");
  cout << indent << "[" << rt->data.first << "]=" << rt->data.second << endl;
  print_helper(rt->left, indent + "  ");
      
}

template<typename K, typename V>
int MyMap<K, V>::count_helper(TreeNode<MyPair<K, V>>* rt, const K& key) const
{
  if (find_helper(rt, key) == nullptr)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}


template<typename K, typename V>
TreeNode<MyPair<K, V>>* MyMap<K, V>::clone(const TreeNode<MyPair<K, V>>* rt)
{
  if (rt != nullptr)
  {
    return new TreeNode<MyPair<K, V>>(rt->data, clone(rt->left), clone(rt->right));
  }
  else
  {
    return nullptr;
  }

}