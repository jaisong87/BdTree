 /****************************************************
 *
 * BdTreeLib -  Decision Tree for binary classification ( could be Extrended )
 *
 * BdTreeSample.cpp - This is a container for samples(X -> Y ) that are to be fed to the decisionTree. 
 * We can easily add support to more data types by making some changes here
 *
 * Initial Version : Jaison George ( jaisong87@gmail.com ) 
 *
 **********************************************************/

#ifndef __BDTREE_SAMPLE_H__
#define __BDTREE_SAMPLE_H__
#include<vector>
#include<string>
using namespace std;

//These are samples for learning
//This is a container class to contain the sample

class BdTreeSample {
vector<int> numericAttributes; // Only Integer attributes are currently allowed. It is easy to extend this
bool decision;

public:
BdTreeSample(vector<int> inpSample, bool curDecision): numericAttributes(inpSample), decision(curDecision) { } //avoiding cpp file
bool getDecision() { return decision; }
vector<int> getNumericAttributes() { return numericAttributes; }
};

#endif
