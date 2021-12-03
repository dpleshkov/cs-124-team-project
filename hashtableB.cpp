#include "hashtableB.h"
#include <iostream>
#include <string>
#include <vector>

hashtable::hashtable(int nbuckets){
    for (int i = 0; i < nbuckets; i++){
        buckets.push_back(nullptr);
    }
}

//basics of creating a hash table
//user inputs name, converts to hashcode, point on hash table
int hashtable::hashCode(std::string name){
    int h = 0;
    for(int i = 0; i < name.length(); i++){
        h = 101*h + name[i]; 
    }
    int h_compressed = h % buckets.size();
    if(h_compressed < 0){ h_compressed = -h_compressed; }
    return h_compressed;
}
