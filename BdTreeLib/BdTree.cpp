#include "BdTree.h"

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

void BdTree::displaySamples()
{
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

for(int i=0;i<training.size();i++,cout<<endl)
	{
	BdTreeSample curSample = training[i];

	vector<int> numericAttribs = curSample.getNumericAttributes();

	  for(int i=0;i<numericAttribs.size();i++)
                        cout<<setw(reqWidth)<<numericAttribs[i];	
	
	  cout<<setw(reqWidth)<<(curSample.getDecision()?"YES":"NO");	
	}

}
