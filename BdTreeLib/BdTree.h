/**********************************************************
 *
 * BdTreeLib -  Decision Tree for binary classification ( could be Extrended )
 *
 * BdTree.h - This file contains the BdTee class for Decision Tree based classification
 *
 * Initial Version : Jaison George ( jaisong87@gmail.com ) 
 *
 **********************************************************/
# ifndef __BDTREE_H__
# define __BDTREE_H__
#include "BdTreeSample.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<set>
#include<cmath>
#include<map>
using namespace std;

/* This is a structure that contains information about a particular node in the decisionTree
 * If the node is not a leaf node , then attribute gets set indicating which attribute is used to split
 * In non-leaf nodes , the map[ attributeVal -> decisionRule ] specifies which subtree to go to for a given attributeValue
 *  BdTree will contain a tree of these decisionRules
 */
struct decisionRule {
	int answerToParentsQuestion; // This is an attrbute value ( This value should get displayed in edge) 
	string attribute;            // Attribute used by this node for splitting ( This value should get displayed in the node/vertex )
	map<int, decisionRule*> subRules; // It is a mapping of attributeValue to subtree
	bool giveDecision; // This gets set if we are giving out decisions at this level
	bool decision;     // Decision that we are giving 
	int id;            // Id of this node ( useful in displaying and printing )
	int parent;	   // Id of the parent (useful in displaying and printing )
};

//This is just an enum for more readability
enum attributeSelector { INFO_GAIN =0, GAIN_RATIO }; //Three types of operators in this decision-tree

/*
 *
 */
class BdTree {

int numberOfNumericAttributes; // For validation while taking in input. Dimensionality should be consistent
vector<BdTreeSample> training; // Training-set  
vector<string> attributeNames; // Names of attributes like STABILITY, SPEED etc. Useful in debugging and visualization

attributeSelector attrSelector; // Currently Information gain and gain ratio are used

decisionRule * decisionTree; // Root of the decisionTree

public:

//Constructor needs to know about the number of Attributes and attributeNames to validate against each sample
BdTree(vector<string> attribNames, int numAttributes, attributeSelector sel = INFO_GAIN) : attributeNames(attribNames), numberOfNumericAttributes(numAttributes), attrSelector(sel) {}

bool addNextSample(BdTreeSample); // Function that accepts the next Sample [ BdTree Sample is a container with vector-X and label Y ]

void startTraining(); // Just trigger the training

void displaySamples(); // Displays the set of training Samples

void learnTree(decisionRule* &, vector<BdTreeSample>); //

/* TODO 
 * int predictLabel(vector<int> attributes);
 * void constructTreeDiagram(); // Use graphviz-dot or some other graph drawing tool and generate the tree graphically for visualization purposes
 */
};

#endif
