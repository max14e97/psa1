#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>
using namespace std;

template<typename Data>
class BSTNode {

public:

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d) : data(d) {
    left = right = parent = 0;
  }

  BSTNode<Data>* left;
  BSTNode<Data>* right;
  BSTNode<Data>* parent;
  Data const data;   // the const Data in this node.

  /** Return the successor of this BSTNode in a BST, or 0 if none.
   ** PRECONDITION: this BSTNode is a node in a BST.
   ** POSTCONDITION:  the BST is unchanged.
   ** RETURNS: the BSTNode that is the successor of this BSTNode,
   ** or 0 if there is none.
   */ // TODO
  BSTNode<Data>* successor() {
    //create a temp pointer to loop through sub-tree
    BSTNode<Data> * temp;

    //if right child exists, go to right child using temp
    if(right){
      temp = right;
      
      //loop through left sub-tree of the right child and return the
      //smallest one
      while(temp->left){
        temp = temp->left;
      }
      return temp;
    }
    //if right child doesn't exist, go to parent using temp
    else{
      temp = parent;

      //loop through parent and compare data.
      while(temp){
        //if parent is smaller, that's the successor
        if(data < temp->data){
          return temp;
        }
        //if parent is larger, go to parent of the parent
        else{
          temp = temp->parent;
        }
      }
      
      //return null if we can't find a successor
      return 0;
    }
  }

}; 

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
ostream & operator<<(ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << setw(10) << n.parent; // address of its parent
  stm << "; l:" << setw(10) << n.left;   // address of its left child
  stm << "; r:" << setw(10) << n.right;  // address of its right child
  stm << "; d:" << n.data;               // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
