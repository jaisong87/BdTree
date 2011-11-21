# ifndef __BDTREE_H__
# define __BDTREE_H__
#include "BdTreeSample.h"
#include<iostream>
#include<iomanip>
using namespace std;

class BdTree {
int numberOfNumericAttributes; 
vector<BdTreeSample> training;
vector<string> attributeNames;


public:
//Constructor needs to know about the number of Attributes and attributeNames to validate against each sample
BdTree(vector<string> attribNames, int numAttributes) : attributeNames(attribNames), numberOfNumericAttributes(numAttributes) {}

bool addNextSample(BdTreeSample);

//learnTree

//PrintTheTree

void displaySamples();

};

#endif
