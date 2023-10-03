#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include <list>




template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator()
        {
            m_current_value = nullptr; // set the value this iterator points to to the nullptr
            m_valid = false;
        }
        inline Iterator(ValueType& v, typename std::list<ValueType>::iterator list, std::list<ValueType>* lp) // separate constructor for an iterator to set it to point to a value
        {
            m_current_value = &v;
//            m_current_list = list;
            m_lp = lp;
            m_current_list = m_lp->begin();
            m_valid = true;
            
        }
//        inline Iterator(const Iterator& other) // copy constructor
//        {
////            cerr << "copy constructor called" << endl;
////            cerr << other.get_value() << endl;
//            m_current_value = other.m_current_value;
////            cerr << *m_current_value << endl;
//        }

        inline ValueType& get_value() const // return the value the iterator points to
        {
        
            return *m_current_list;
        }

        bool is_valid() const // return false if the iterator doesn't point to anything
        {
            if(m_valid == false)
                return false;
            else
                return true;
        }

        inline void advance()
        {
            m_current_list++; // advance the iterator to point to the next value in the list
            if(m_current_list == m_lp->end())
            {
                m_valid = false;
                return;
            }
        }

      private:
        ValueType* m_current_value; // pointer to the current value the iterator points to
        typename std::list<ValueType>::iterator m_current_list; // iterator into each tree nodes linked list
        bool m_valid;
        std::list<ValueType>* m_lp; // pointer to the list
    };
    TreeMultimap()
    {
        m_root = nullptr; // default initialize the root of the tree to the nullptr
    }

    ~TreeMultimap()
    {
        deleteHelper(m_root); // call the helper function to delete all the nodes in the tree
    }

    inline void insert(const KeyType& key, const ValueType& value)
    {
        insertHelper(key, value, m_root);
    }

    inline Iterator find(const KeyType& key) const
    {
        return findHelper(key, m_root);  // make a copy iterator of the one returned from findHelper
    }

  private:
    struct Node // defining the Node struct for the binary search tree
    {
        KeyType m_key; // each node has a key
        std::list<ValueType> m_list; // each node has a list of values
        Node* m_left = nullptr;
        Node* m_right = nullptr;
    };
    Node* m_root = nullptr;
    
    // this actually finds the value
    inline Iterator findHelper(const KeyType& key, Node* root) const
    {
        if(root == nullptr) // if this node is the nullptr then the key isnt in the tree
        {
            Iterator i;
            return i; // return the invalid iterator object
        }
        if(key == root->m_key) // if the key is this node's key
        {
            Iterator i((root->m_list.front()), root->m_list.begin(), &root->m_list); // set the iterator's current value to point to the first value in this list,
            return i;
        }
        else if(key < root->m_key) // if the key is less than this root's key
        {
            return findHelper(key,root->m_left);
        }
        else if(key > root->m_key)
        {
            return findHelper(key,root->m_right);
        }
        Iterator i;
        return i;
    }
    
    // this actually inserts the value
    inline void insertHelper(const KeyType& key, const ValueType& value, Node*& root)
    {
        if(root == nullptr) // if the tree is empty
        {
            root = new Node;  // make the root pointer point to a new node
            root->m_key = key; // set the root's key to this key
            root->m_list.push_back(value); // insert this value into the roots linked list
            root->m_left = nullptr;
            root->m_right = nullptr;
//            cerr << "made new node" << endl;
//            cerr << key << endl;
//            cerr << value << endl;
            
            return;
        }
        
        if(key == root->m_key) // if this key is the root's key
        {
            root->m_list.push_back(value); // push back its value into the list
            return;
        }
        else if(key < root->m_key)
        {
            insertHelper(key, value, root->m_left);
            return;
        }
        else if(key > root->m_key)
        {
            insertHelper(key, value, root->m_right);
            return;
        }
    }
    
    // this actually deletes the tree node
    inline void deleteHelper(Node* root)
    {
        if(root == nullptr)
            return;
        deleteHelper(root->m_left);
        deleteHelper(root->m_right);
        delete root;
        root = nullptr;
    }
};

//inline void testIterator()
//{
//    TreeMultimap<int,int>::Iterator it;
//    if(!it.is_valid())
//        std::cout << "This will print!" << std::endl;
//}

#endif // TREEMULTIMAP_INCLUDED
