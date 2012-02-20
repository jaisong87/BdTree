 /****************************************************
 *
 * BdTreeLib -  Decision Tree for binary classification ( could be Extrended ) 
 *
 * This is a sample program that uses BdTreeLib. Make changes here to try different inputs
 *
 * Initial Version : Jaison George ( jaisong87@gmail.com ) 
 *
 **********************************************************/

#include "BdTreeLib/BdTreeSample.h"
#include "BdTreeLib/BdTree.h"
#include <fstream>
#include<sstream>
#include<algorithm>
using namespace std;

int main()
{

string attributeNames[] = { "STABILITY", "ERROR", "SIGN", "WIND", "MAGNITUDE", "VISIBILITY" }; // attribute labels
vector<string> attribNames(attributeNames, attributeNames + sizeof(attributeNames)/sizeof(string)) ; // convert to vector<string>
int dimensionality = 6;

BdTree bt1(attribNames, dimensionality , INFO_GAIN );

ifstream finp("trainingSamples.dat"); // Input File ( Format Inp1 Inp2 Inp3 Inp4 Inp5 Inp6\n)

string line; 
while(getline(finp, line)) // This is one (X,Y) 
	{
		stringstream ss1(line);
		int tmp;
		
		vector<int> attribVals;
		bool concept;
		
		ss1>>tmp;
		if(tmp==1) concept = true; // Got Y 
		else concept = false;
		
		for(int i = 0; i < dimensionality ; i++) // Get all 6 X values
			{
				ss1>>tmp;
				attribVals.push_back(tmp);
			}	
	
		BdTreeSample curSample(attribVals, concept); //  Create Sample
		bt1.addNextSample(curSample); // Add this sample also
	}

//bt1.displaySamples();
bt1.startTraining(); // Train
return 0;
}
