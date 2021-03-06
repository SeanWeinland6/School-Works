/* Abstract dictionary class to inherit when implementing your BST MyMap class
 * It uses the TreeNode class to contain a MyPair object as its data element
 * DO NOT edit this file.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "MyPair.h"

template <typename K, typename V>
class Dictionary
{
    public:
        // Should only update, but NOT insert
        // Should throw std::out_of_range exception
        virtual V & at(const K &key) = 0;

        // Updates or inserts
        virtual V & operator[](const K &key) = 0;

        virtual bool empty() const = 0;

        virtual int size() const = 0;

        virtual void clear() = 0;

        virtual void insert(const MyPair<K, V> &init_pair) = 0;

        // Removes by key
        virtual void erase(const K &key) = 0;

        // Not exactly like the std:: version, but similar.
        virtual MyPair<K, V> * find(const K &key) const = 0;

        // Not actually like the std:: version; backwards in order traversal
        //  print
        // See the print function example in class presentation
        virtual void print() const = 0;

        virtual int count(const K &key) const = 0;
};

#endif
