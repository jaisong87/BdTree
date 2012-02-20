 /****************************************************
 *
 * BdTreeLib -  Decision Tree for binary classification ( could be Extrended )
 *
 * BdTree.cpp - This file contains the implementation of BdTee class for Decision Tree based classification
 *
 * Initial Version : Jaison George ( jaisong87@gmail.com ) 
 *
 **********************************************************/
#include "BdTree.h"


int nodeCount = 0; // A static variable used for labelling nodes. Should have been private
int level = -1; // used in printing XML like tree structure 

/* A debugging routine that was written for checking nodes 
 * in the decision tree
 */
void printDetails( decisionRule * curNode)
{
	cout<<" --------------------------------------- "<<endl;
	if(curNode->giveDecision)
	{
		cout<<" Decision       : "<<((curNode->decision)?("YES"):("NO"))<<endl;	
	}
	else {
		cout<<"	ID             : "<<curNode->id<<endl;
		cout<<" AnswerToParent : "<<curNode->answerToParentsQuestion<<endl;
		cout<<" Question       : "<<curNode->attribute<<endl;   
	}
	cout<<" Parent 	       : "<<curNode->parent<<endl;
	cout<<" ------------------------------------------ "<<endl;
}

//This is being done for facilitating readable output to stdout
void printTabs(int level)
{
for(int i=0;i<level;i++)
	cout<<"  ";
}

// Count P, N and return Plog(P) + (1-P)log(1-P)
//This should be multiplied by the ratio of size of the bucked to get remainder
float getEntropy(vector<BdTreeSample> sampleSet)
{
	if( sampleSet.size() == 0 ) return 0; 
	int nPlus = 0 ;
	int nMinus = 0;
	int n = 0;
	for(int i = 0 ; i < sampleSet.size(); i++)
	{ 
		n++;
		if(true == sampleSet[i].getDecision()) nPlus++;
		else nMinus++;
	}
	float p = float(nPlus)/n;
	float entropy = 0.0;
	if(p >0.0) entropy -= p*log(p);
	if((1-p)>0.0) entropy-=(1-p)*log(1-p);
	return (entropy);
}

/* Accept the next Input for training
 * A small validation on consistency with the number of dimensions
 */
bool BdTree::addNextSample(BdTreeSample nextSample)
{
	if(numberOfNumericAttributes != nextSample.getNumericAttributes().size()) 
	{
		cout<<"Number of numeric attributes("<<nextSample.getNumericAttributes().size()<<") is inconsistent with the number of attributes allowed in this tree"<<endl;
		return false;
	}

	training.push_back(nextSample);
	return true;
}

/* This is more of a debug function
 * Could be used to display the Inputs
 */
void BdTree::displaySamples()
{
	//Find the right width for displaying the attributes so that it is readable
	int reqWidth = 5;
	if(attributeNames.size() == numberOfNumericAttributes)
	{
		for(int i=0;i<attributeNames.size();i++) 
			reqWidth = (attributeNames[i].length()+5 > reqWidth) ? (attributeNames[i].length()+5) :(reqWidth); 

		for(int i=0;i<attributeNames.size();i++)
			cout<<setw(reqWidth)<<attributeNames[i];

		cout<<setw(reqWidth)<<"DECISION"<<endl;
	}
	else {
		cout<<"Mismatch between attributeNames and numberOfAttributes"<<endl;
	}

	//Displaying the attributes with width reqWidth
	for(int i=0;i<training.size();i++,cout<<endl)
	{
		BdTreeSample curSample = training[i];

		vector<int> numericAttribs = curSample.getNumericAttributes();

		for(int i=0;i<numericAttribs.size();i++)
			cout<<setw(reqWidth)<<numericAttribs[i];	

		cout<<setw(reqWidth)<<(curSample.getDecision()?"YES":"NO");	
	}

}

/*  This function starts training on the inputSet
 *  The actual function for training is learnTree
 */
void BdTree::startTraining()
{
	cout<<"Start training ..."<<endl;
	learnTree(decisionTree, training);
	decisionTree->parent = -1; //Parent for the root is -1
	cout<<"Done with training ..."<<endl;
	cout<<"There are "<<nodeCount<<" nodes "<<endl;
}

/* This function uses divide and conquer to split the input based on best attributes and learn the decision tree
 * Currently it supports INFO_GAIN and GAIN_RATIO for finding the best attribute
 * The function stack can grow upto |m|*|d| ( Should be able to support 10,000 samples using 100 dimensions ) 
 */
void BdTree::learnTree(decisionRule* &node, vector<BdTreeSample> localSamples)
{
	level++;
	nodeCount++; 		 // Every node has a numer ( running counter ) 
	printTabs(level); cout<<"Learning for Node#"<<nodeCount<<" at level#"<<level<<endl;
	printTabs(level); cout<<"{"<<endl;
	node = new decisionRule; // Dynamic memory allocation ( ptr is passed by reference )
	node->id = nodeCount;    // Assign the node id

	float rootEntropy = getEntropy(localSamples); // Calculate Entropy of current node ( 0 means leaf and we are done )

        // TODO - If there are inputs having same X and different Y , this algorithm will go into an infinite loop. Need to FIX THIS

	// Writing some debug data to logfile BdTreelog001
	string fname = "BdTreelog001";
	ofstream flog(fname.c_str(), ios::app);

	flog<<"---------------------------------------------------------------------------"<<endl;
	flog<<" Learning on "<<localSamples.size() << " samples with entropy "<<rootEntropy<<endl;
	for(int i=0;i< attributeNames.size();i++)
		flog<<setw(8)<<attributeNames[i];
	flog<<endl;

	for(int i=0;i < localSamples.size();i++)
	{
		vector<int> attribVals = localSamples[i].getNumericAttributes();
		bool decision = localSamples[i].getDecision();
		for(int j = 0; j < attribVals.size(); j++)
			flog<<setw(8)<<attribVals[j]<<' '; 
		flog<<setw(8)<<(decision?"YES":"NO")<<endl;
	}
	//////////////////////// Done writing to logFile for debug purposes ///////////////////////////////

	// Check if this is a leafNode.
        // If yes, give the decision
	if(rootEntropy == 0.0 )
	{
		node->giveDecision = true;
		node->decision = localSamples[0].getDecision();
		printTabs(level); cout<<"Decision made : "<<((node->decision)?"YES":"NO")<<endl; //XML like output
		printTabs(level); cout<<"}"<<endl; //XML like output
		level--;
		return;
	}

	// We are not in a leaf. We got work
	node->giveDecision = false; //We need to split. Find the best attribute for splitting

	int bestAttrib = 0; 	// Index of the best attribute for splitting
	float bestGain = 0.0;	// best value for gain  
	string curAttr;         

	// This loop tries out split for every attribute and finally picks the best choice
	for(int i=0;i<numberOfNumericAttributes; i++)
	{
		curAttr = attributeNames[i];
		map<int, vector<BdTreeSample> > children; // buckets of samples ( bucketing based on attributeVal )		

		for(int j = 0;j<localSamples.size();j++)
		{ 
			vector<int> attribs = localSamples[j].getNumericAttributes();
			children[attribs[i]].push_back(localSamples[j]); // Splitting localSamples across buckets based on attribute-i
		}				
			
		float remainder = 0.0;
		float IntrinsicValue = 0.0; 		

		for(map<int, vector<BdTreeSample> >::iterator itr = children.begin(); itr != children.end(); itr++)
		{
			vector<BdTreeSample> Vi = itr->second;
			if(Vi.size() > 0 )
			{
				float childEntropy = getEntropy(Vi);
				float wt = Vi.size()/(float)localSamples.size();

				remainder += wt*childEntropy;	

				if(wt > 0.0 && wt < 1.0 ) 
					IntrinsicValue += -1*wt*log(wt);
			}
		}				

		float InfoGain = rootEntropy - remainder;
		float gain = InfoGain;
	
		if(GAIN_RATIO == attrSelector )
			gain = gain/IntrinsicValue;		
		
		if(gain >= bestGain)
		{
			bestAttrib = i;
			bestGain = InfoGain;
		}
	}

	node->attribute = attributeNames[bestAttrib];
	printTabs(level); cout<<"Splitting using "<<attributeNames[bestAttrib]<<endl; // XML like output

	//We know the best attribute now. Use it.
	int i = bestAttrib;
	{
		map<int, vector<BdTreeSample> > children;

		for(int j = 0;j<localSamples.size();j++)
		{
			vector<int> attribs = localSamples[j].getNumericAttributes();
			int curVal = attribs[i];
			children[curVal].push_back(localSamples[j]); // Splitting localSamples across buckets based on attribute-i
		}
		
		for(map<int, vector<BdTreeSample> >::iterator itr = children.begin(); itr != children.end(); itr++)
		{
			vector<BdTreeSample> Vi = itr->second;
			int attribValue = itr->first;
			if(Vi.size() > 0 )
			{
				printTabs(level); cout<<"Learning on subTree for "<<attributeNames[bestAttrib]<<" : "<<attribValue<<endl; ////XML like output
				//Do the recursive call here
				learnTree(node->subRules[attribValue], Vi );	 
				node->subRules[attribValue]->parent = node->id;	
				node->subRules[attribValue]->answerToParentsQuestion = attribValue;	
			}
		}
	}

	// printDetails(node);
printTabs(level); cout<<"}"<<endl; //XML like output	
level--;
}

