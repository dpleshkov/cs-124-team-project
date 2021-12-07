#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <string>

struct ComputerSuggestion
{
	std::string modelName;
    std::string brandName;
    std::string modelNumber;
    std::string type;
    double sleepWattage = -1;
    double longIdleWattage = -1;
    double shortIdleWattage = -1;
    double tecKWH = -1;
};

class Node
{
private:
   ComputerSuggestion data;
   Node* left;
   Node* right;
friend class BinarySearchTree;   
};   

/*
   This class implements a binary search tree whose
   nodes hold strings.
*/
class BinarySearchTree
{
public:   
BinarySearchTree()
{  
   root = nullptr;
}
   
void insert(ComputerSuggestion element) 
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

ComputerSuggestion find(double element)
{
   Node* current = root;
   while (current != nullptr)
   {
      if (element < current->data.tecKWH && current->left != nullptr)
      {
         current = current->left;
         //std::cout << "here";
      }
      else if (element > current->data.tecKWH && current->right != nullptr)
      {
         current = current->right;
         //std::cout << "bam";
      }
      else return current->data;      
   }
   return current->data;
}


private:   
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

   Node* root;
};

#endif
