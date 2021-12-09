#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <string>
#include "EnergyStarDatabaseParser.hpp"

class Node
{
private:
   EnergyStarComputer data;
   Node* left;
   Node* right;
friend class BinarySearchTree;   
};   

class BinarySearchTree
{
public:   
BinarySearchTree()
{  
   root = nullptr;
}
   
void insert(EnergyStarComputer element) 
{  
   Node* new_node = new Node;
   new_node->data = element;
   new_node->left = nullptr;
   new_node->right = nullptr;
   if (root == nullptr) { root = new_node; }
   else { add_node(root, new_node); }
}

   
void print() const
{  
   print(root);
   std::cout << std::endl;
}  

EnergyStarComputer find(double element)
{
   Node* current = root;
   while (current != nullptr)
   {
      if (element < current->data.tecKWH && current->left != nullptr)
      {
         current = current->left;
      }
      else if (element > current->data.tecKWH && current->right != nullptr)
      {
         current = current->right;
      }
      else return current->data;      
   }
   return current->data;
}
 
   void print(Node* parent) const
    {  
      if (parent == nullptr) { return; }
      print(parent->left);
      std::cout << parent->data.modelName << " " << std::endl;
      print(parent->right);
    }

   void add_node(Node* parent, Node* new_node) const
    {  
      if (new_node->data.tecKWH < parent->data.tecKWH)
      {  
          if (parent->left == nullptr) { parent->left = new_node; }
          else { add_node(parent->left, new_node); }
      }
      else if (new_node->data.tecKWH > parent->data.tecKWH)
      {  
          if (parent->right == nullptr) { parent->right = new_node; }
          else { add_node(parent->right, new_node); }
      }
    }
    
    ~BinarySearchTree()
    {
        deleteNodes(this -> root);
    }
    // deletes all nodes recursively in post order
    void deleteNodes(Node *node)
    {
      if (node == nullptr) return;
      deleteNodes(node->left);
      deleteNodes(node->right);
      delete node;
    }
private:
   Node* root;
};

#endif
