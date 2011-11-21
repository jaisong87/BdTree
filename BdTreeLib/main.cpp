#include "BdTreeSample.h"
#include "BdTree.h"

int main()
{

/*
vector<string> vs1;
vs1.push_back("ATTRIB1");
vs1.push_back("ATTRIB2");

BdTree bt1(vs1, 2);

for(int a = 10; a<25;a++)
{
vector<int> v1(2,a);
bool ans = a%2;

BdTreeSample sample(v1, ans);

bt1.addNextSample(sample);
}
*/

string attributeNames[] = { "STABILITY", "ERROR", "SIGN", "WIND", "MAGNITUDE", "VISIBILITY" };
vector<string> attrbNames(attributeNames, attributeNames + sizeof(attributeNames)) ;

BdTree bt1(attribNames, 6);

ifstream finp("

return 0;
}
