#include <iostream>
#include <vector>
using namespace std;

void affPlateau(vector<int> v)
{
	cout<<v[0]<<"xxxxxxxxxxxxxxxx"<<v[1]<<"xxxxxxxxxxxxxxxx"<<v[2]<<endl;
	/*cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
	cout<<"xxxxx"<<v[9]<<"xxxxxxxxxxx"<<v[10]<<"xxxxxxxxxxx"<<v[11]<<"xxxxx"<<endl;
	cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
	cout<<"xxxxxxxxxx"<<v[17]<<"xxxxxx"<<v[18]<<"xxxxxx"<<v[19]<<"xxxxxxxxxx"<<endl;*/
	cout<<"x                x                x"<<endl;
	cout<<"x    "<<v[9]<<"xxxxxxxxxxx"<<v[10]<<"xxxxxxxxxxx"<<v[11]<<"    x"<<endl;
	cout<<"x    x           x           x    x"<<endl;
	cout<<"x    x    "<<v[17]<<"xxxxxx"<<v[18]<<"xxxxxx"<<v[19]<<"    x    x"<<endl;
	cout<<"x    x    x             x    x    x"<<endl;
	cout<<v[0]<<"xxxx"<<v[8]<<"xxxx"<<v[16]<<"             "<<v[20]<<"xxxx"<<v[12]<<"xxxx"<<v[4]<<endl;
	cout<<"x    x    x             x    x    x"<<endl;
	cout<<"x    x    "<<v[23]<<"xxxxxx"<<v[22]<<"xxxxxx"<<v[21]<<"    x    x"<<endl;
	cout<<"x    x           x           x    x"<<endl;
	cout<<"x    "<<v[15]<<"xxxxxxxxxxx"<<v[14]<<"xxxxxxxxxxx"<<v[13]<<"    x"<<endl;
	cout<<"x                x                x"<<endl;
	cout<<v[7]<<"xxxxxxxxxxxxxxxx"<<v[6]<<"xxxxxxxxxxxxxxxx"<<v[5]<<endl;
}
int main()
{
	vector<int> tab={0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0};
	affPlateau(tab);
	return 0;
}