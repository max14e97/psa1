#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>
using namespace std;

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

  /** Height of this BST. */
  unsigned int iheight;
  
public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(0), isize(0), iheight(0) {  }


  /** Default destructor.
      Delete every node in this BST.
   */ // TODO
  virtual ~BST() {
    deleteAll(root);
  }

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return  true if the item was added to this BST
   *  as a result of this call to insert,
   *  false if an item equal to this one was already in this BST.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=)  For the reasoning
   *  behind this, see the assignment writeup.
   */ // TODO
  virtual bool insert(const Data& item) {
    //If root doesn't exist, make a new node as root and return true
    if(!root){
      root = new BSTNode<Data>(item);
      iheight = 1;
      isize = 1;
      return 1;
    }

    //use two temp variables to keep track of our position in the tree
    BSTNode<Data> * temp = root;
    BSTNode<Data> * lastTemp = root;
    //since we checked for !root already, we start with height = 1
    int tempHeight = 1;

    //loop through the sub-tree. Use temp to mark the current node and
    //lastTemp to mark the parent of the current node (temp in last iteration)
    //The loop breaks when we reached a null pointer.
    while(temp){
      //if item is smaller than current, go to left
      if(item < temp->data){
        lastTemp = temp;
        temp = temp->left;
      }
      //if item is larger, go to right
      else if(temp->data < item){
        lastTemp = temp;
        temp = temp->right;
      }
      //if neither, return false
      else{
        return 0;
      }
      
      //increment temp height to keep track of the height in this sub tree
      ++tempHeight;
    }

    //After loop breaks, use lastTemp to access to the parent of the null
    //pointer. Compare the item with its data. If it's smaller, put the new
    //node on the left.
    if(item < lastTemp->data){
      lastTemp->left = new BSTNode<Data>(item);
      lastTemp->left->parent = lastTemp;
    }
    //If item is larger, put the new node on the right
    else{
      lastTemp->right = new BSTNode<Data>(item);
      lastTemp->right->parent = lastTemp;
    }

    //if iheight is smaller than the temp height we kept track of, update
    //iheight to the new height after insertion
    if(iheight < tempHeight){
      iheight = tempHeight;
    }
    
    //increment size
    ++isize;

    //return true for successful
    return 1;
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=).  For the reasoning
   *  behind this, see the assignment writeup.
   */ // TODO
  virtual iterator find(const Data& item) const {
    //Check if root exists
    if(!root) return 0;
    
    //use a temp variable to keep track of where we are
    BSTNode<Data> * temp = root;
    
    //loop through the possible positions of the item
    while(temp){
      //if item is smaller, go left
      if(item < temp->data){
        temp = temp->left;
      }
      //if item is larger, go right
      else if(temp->data < item){
        temp = temp->right;
      }
      //if neither, we found it
      else{
        iterator result(temp);
        return result;
      }
    }

    //if it's not in the tree, return null pointer
    return end();
  }

  
  /** Return the number of items currently in the BST.
   */ // TODO
  unsigned int size() const {
    return isize;
  }
  
  /** Return the height of the BST.
   */ // TODO
  unsigned int height() const {
    return iheight;
  }


  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const {
    return (!isize);
  }

  /** Return an iterator pointing to the first item in the BST (not the root).
   */ // TODO
  iterator begin() const {
    return typename BST<Data>::iterator(first(root));
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(0);
  }

  /** Perform an inorder traversal of this BST.
   */
  void inorder() const {
    inorder(root);
  }


private:

  /** Recursive inorder traversal 'helper' function */

  /** Inorder traverse BST, print out the data of each node in ascending order.
      Implementing inorder and deleteAll base on the pseudo code is an easy way to get started.
   */ // TODO
  void inorder(BSTNode<Data>* n) const {
    /* Pseudo Code:
      if current node is null: return;
      recursively traverse left sub-tree
      print current node data
      recursively traverse right sub-tree
    */
    // if current node is null, return
    if(n == 0) return;
    
    //traverse left sub-tree
    inorder(n->left);

    //print data
    std::cout << n->data << endl;

    //traverse right sub-tree
    inorder(n->right);
  }

  /** Find the first element of the BST
   */ 
  static BSTNode<Data>* first(BSTNode<Data>* curr) {
    if(curr == 0) return 0;
    while(curr->left != 0) curr = curr->left;
    return curr;
  }

  /** do a postorder traversal, deleting nodes
   */ // TODO
  static void deleteAll(BSTNode<Data>* n) {
    /* Pseudo Code:
      if current node is null: return;
      recursively delete left sub-tree
      recursively delete right sub-tree
      delete current node
    */
    //If current is null, return
    if(n == 0) return;
    
    //delete left sub-tree
    deleteAll(n->left);
    //delete right sub-tree
    deleteAll(n->right);

    //delete current node
    delete(n);
  }


 };


#endif //BST_HPP
