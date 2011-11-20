#ifndef __BDTREE_SAMPLE__H
#define __BDTREE_SAMPLE_H
#include<vector>
#include<string>
using namespace std;

//These are samples for learning
//This is a container class to contain the sample

class BdTreeSample {
vector<int> numericAttributes; // Only Integer attributes are currently allowed. It is easy to extend this
bool decision;

public:
BdTreeSample(vector<int> inpSample, bool curDecision): numericAttributes(inpSample), decision(curDecision) { } //I'm lazy to write cpp
bool getDecision() { return decision; }
bool getnumericAttributes() { return numericAttributes; }
};

#endif
