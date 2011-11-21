#include "BdTreeLib/BdTreeSample.h"
#include "BdTreeLib/BdTree.h"
#include <fstream>
#include<sstream>
#include<algorithm>
using namespace std;

/*
void f1(string S)
{
cout<<S<<"   ";
}
*/

int main()
{

string attributeNames[] = { "STABILITY", "ERROR", "SIGN", "WIND", "MAGNITUDE", "VISIBILITY" };
vector<string> attribNames(attributeNames, attributeNames + sizeof(attributeNames)/sizeof(string)) ;

//cout<<"CP 1"<<endl;
//for_each(attribNames.begin(), attribNames.end(), f1);

BdTree bt1(attribNames, 6);

ifstream finp("trainingSamples.dat");

string line;
while(getline(finp, line))
	{
		stringstream ss1(line);
		int tmp;
		
		vector<int> attribVals;
		bool concept;
		
		ss1>>tmp;
		if(tmp==1) concept = true;
		else concept = false;
		
		for(int i = 0; i<6; i++)
			{
				ss1>>tmp;
				attribVals.push_back(tmp);
			}	
	
		BdTreeSample curSample(attribVals, concept);
		bt1.addNextSample(curSample);
	}

bt1.displaySamples();

return 0;
}

