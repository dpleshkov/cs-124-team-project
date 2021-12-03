#ifndef HASHTABLEB_H
#define HASHTABLEB_H
#include <string>
#include <vector>

//header function for hash table
//Not sure how to implement function pointer yet
class Node{
/*public:
    Node(int (*callbackFunctionptr)(std::string)){
        this -> callbackptr = callbackFunctionptr;
        this -> callbackptr("string parameter");
    }*/
private:
    //int(*callbackptr)(std::string);
    std::string compName;
    Node *next;
friend class hashtable;
};

class hashtable{
public:
    hashtable(int nbuckets);
    int hashCode(std::string name);
private:
    std::vector<Node*> buckets;
};

#endif