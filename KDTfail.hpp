#ifndef KDT_HPP
#define KDT_HPP

#include <algorithm> // sort, max, min
#include <iostream>  // cout, cin, and cerr
#include <math.h>    // pow, abs
#include <vector>    // vector<typename>
#include <limits>    // numeric_limits<type>::max()
#include "BST.hpp"

using namespace std;

class Point {
  private:
    double delta = 0.00005;
  public:
    /** x and y point coordinates */
    double x, y;

    /** Default constructor: point at (0, 0) */
    Point(): x(0.0), y(0.0) { }

    /** constructor that defines point location */
    Point(double x, double y): x(x), y(y) { }

    /** Equals operator */
    bool operator == (const Point& other) const {
      return abs(x - other.x) < delta && abs(y - other.y) < delta;
    }

    /** Not-equals operator */
    bool operator != (const Point& other) const {
      return abs(x - other.x) > delta || abs(y - other.y) > delta;
    }

    /** Less than operator */
    bool operator < (const Point& other) const {
      cerr << "This operator should not be called, you will need " <<
        "check the x and y components each time" << endl;
      return false;
    }

    /** Return the squre of the Euclidean distance between two points p1 and p2
     */ // TODO
    static double squareDistance(const Point& p1, const Point& p2) {
      //cout << p1.y << "and" << p2.y << "sum" << (p1.y-p2.y)*(p1.y-p2.y) << endl;
      return (fabs((p1.x-p2.x)*(p1.x-p2.x))+fabs((p1.y-p2.y)*(p1.y-p2.y)));
    }
};

std::ostream& operator << (std::ostream& out, const Point& data) {
  out << "(" << data.x << ", " << data.y << ")";
  return out;
}


bool xLessThan(const Point & p1, const Point & p2) {
  return p1.x < p2.x;
}

bool yLessThan(const Point & p1, const Point & p2) {
  return p1.y < p2.y;
}

class KDT : public BST<Point> {
  public:

    /** Given a vector of Point references, insert a copy into the BST.
     *  Return the number of elements that the fully constructed tree contains
     *  Note. Because of the nature of the KDTree, a simple < operator
     *        will not be sufficient.  You will need to check the x and y 
     *        coordinates individually.  Two functions have been provided
     *        for your convenience above, (xLessThan and yLessThan). You may 
     *        find them useful for the sort function from #include<algorithm>.
     *  Note. Since KDT inherits from BST, you still have access to the 
     *        root, isize, and iheight instance variables and should modify 
     *        them accordingly.
     *  Note. We have also provided a private helper method for the build 
     *        function called buildSubset defined below.
     */ // TODO
    virtual unsigned int build(vector<Point>& items) {
      //check for empty inputs
      if(!items.size()){
        return 0;
      }

      buildSubset(items, 0, items.size(), 0, 1);
      //inorder();
      return isize;
    }


    /** Find the nearest neighbor to a given point
     *  Returns the point in the kd-tree nearest to the parameter item.
     *  Note. THIS IS DIFFERENT THAN HOW THE PREVIOUS FIND FUNCTION WORKS
     *  Note. Since KDT inherits from BST, you still have access to the 
     *        root, isize, and iheight member variables.
     *  Note. The dimension ordering you used to build the tree must be used
     *        to search through it.
     *  Note. We have added a private helper method for your convenience called
     *        findNNHelper defined below.
     */ // TODO
    virtual iterator findNearestNeighbor(const Point& item) const {
      //check for empty tree
      if(!root || !isize){
        return 0;
      }

      BSTNode<Point> * cloestPoint = 0;
      double smallestDistance = BUFSIZ;
      findNNHelper(root, item, &smallestDistance, &cloestPoint, 0);
      
      //cout << *cloestPoint << endl;
      return typename BST<Point>::iterator(cloestPoint);
    }
    
    /** For the kd-tree, the find method should not be used.  Use the function
     *  findNearestNeighbor instead.
     */
    virtual iterator find(const Point& item) const override {
      cerr << "The KD Tree find method should not be called" << endl;
      cerr << "Use findNearestNeighbor instead" << endl;
      return 0;
    }


    /** For the kd-tree, the insert method should not be used.  The tree is
     *  built all at once.  There should be no scenario where you add individual
     * points.
     */
    virtual bool insert(const Point& item) override {
      cerr << "The KD Tree insert method should not be called" << endl;
      return false;

    }
  private:

    /** Recursively add a subset of the array to the KD tree
     *  Parameters items: the list of points that are used to build the kd tree
     *             start: the starting index for this subsection of the tree
     *             end: the non-inclusive ending index for this subtree
     *             dimension: 0 if sorting along the x-axis, and 1 if sorting
     *                        along the y-axis
     *  PostConditions: the parent node should have its left and right children
     *                  set if there are any available points and recursive
     *                  calls should be made for the left and right subtree 
     *                  (again, if there are any remaining points).
     *  NOTE: We gave you two methods: xLessThan and yLessThan.  We expect you
     *        that you will find these methods very helpful.  For your sake, 
     *        please keep this in mind.
     */ // TODO
    BSTNode<Point>* buildSubset(vector<Point> items, unsigned int start, 
                                 unsigned int end, unsigned int dimension, 
                                 unsigned int height) {
      if(!items.size()){
        return 0;
      }

      //sort the items vector based on the dimension
      if(!dimension){
        //if(end < items.size()){
          std::sort(items.begin()+start, items.begin()+end, xLessThan);
      }
      else{
          std::sort(items.begin()+start, items.begin()+end, yLessThan);
      }

      //calculate the median
      unsigned int median = start + ((end - start) / 2);

      //cout << median << endl;

      if(median != start){
      //use a for loop to loop towards the beginning of the vector to find
      //leftmost median
        for(unsigned int i = median; i >= start; --i){
          if(!dimension){
            if(items[i].x == items[median].x){
              median = i;
            }
            else{
              break;
            }
          }
          else{
            if(items[i].y == items[median].y){
              median = i;
            }
            else{
              break;
            }
          }
        }
      }

      //initialize a node containing the leftmost median item
      BSTNode<Point> * current = new BSTNode<Point>(items[median]);
      
      //initialize the root if there is not one.
      if(!root){
        root = current;
      }

      //increment isize
      ++isize;

      //if iheight is less than current height, update it.
      if(iheight < height){
        iheight = height;
      }

      //toggle the dimension.
      if(!dimension){
        dimension = 1;
      }
      else{
        dimension = 0;
      }

      //if median is equal to start, we reached the left end      
      if(1){
        vector<Point> newItems;
        for(unsigned int i = start; i < median; ++i){
          newItems.push_back(items[i]);
        }

        current->left = buildSubset(newItems, 0, median, dimension, height+1);
        if(current->left){
          current->left->parent = current;
        }
      }

      //if median+1 is equal to end, we reached the right end
      if(1){
      //cout << "median" << median << " , end" << end << endl;
        vector<Point> newItems;
        for(unsigned int i = median+1; i < end; ++i){
          newItems.push_back(items[i]);
        }

        current->right = buildSubset(newItems, 0, end-median, dimension, height+1);
        if(current->right){
          current->right->parent = current;
        }
      }

      return current;
    }

    /** Find the node in the subtree with that is closest to the given point p
     *  Parameters: node the root of the subtree being searched
     *              queryPoint the point whose nearest neighbor should be found
     *              smallestSquareDistance the smallest distance value found in
     *                                     the tree so far which can be updated
     *              closestPoint the node corresponding to the current closest
     *                           node in the tree which can be udpated
     *              dimension flags whether the node parameter splits remaining
     *                        nodes in its subtree by the x or y dimension 
     *                        (has the value of either 0 or 1)
     *  Return: a BSTNode object that represents the point in the subtree
     *          closest to the given point p (including the root node)
     */ // TODO
    void  findNNHelper(BSTNode<Point> * node, const Point& queryPoint,
                                 double * smallestSquareDistance, 
                                 BSTNode<Point> ** closestPoint,
                                 unsigned int dimension) const {
      //initialize a local pointer to point to the next node to go
      BSTNode<Point> * nextNode;

      //check which dimension it is and compare the correct parameter of point
      if(!dimension){
        dimension = 1;
        if(queryPoint.x < node->data.x){
          nextNode = node->left;
        }
        else{
          nextNode = node->right;
        }
      }
      else{
        dimension = 0;
        if(queryPoint.y < node->data.y){
          nextNode = node->left;
        }
        else{
          nextNode = node->right;
        }
      }
      
      //if next node exists, recursively call the function again to go down
      //the sub tree.
      if(nextNode){
        findNNHelper(nextNode, queryPoint, smallestSquareDistance, 
                     closestPoint, dimension);
        //cout << "go down" << endl;
      }

      // initialize the distance between query point and node data
      double distance = queryPoint.squareDistance(queryPoint, node->data);
      //cout << "distance " << distance << endl;
      //cout << "sd" << *smallestSquareDistance << endl;

      //check if distance is smaller than the smallest square data
      if(distance < *smallestSquareDistance){
        //if so, update the smallestSquareDistance and cloest point.
        *smallestSquareDistance = distance;
        *closestPoint = node;

        //cout << *node << endl;

        //if we found a new cloest node, we need to go to its other child
        //which we did not visit through the first recursive calls.
        if(!dimension){
          if(node->data.x < queryPoint.x){
            nextNode = node->right;
          }
          else{
            nextNode = node->left;
          }
        }
        else{
          if(node->data.y < queryPoint.y){
            nextNode = node->right;
          }
          else{
            nextNode = node->left;
          }
        }

        //if the other child exists, go to check it as well.
        if(nextNode){
          findNNHelper(nextNode, queryPoint, smallestSquareDistance, 
                       closestPoint, dimension);
        }
      }
    }
};


#endif // KDT_HPP
