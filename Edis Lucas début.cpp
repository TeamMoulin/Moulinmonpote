#include <iostream>
using namespace std;
int demandeVal()
{
	int position;
	cout<<"entrer la position entre 0 et 23 ou vous voulez placer votre pion : ";
	cin>>position;
	if(position>23||position<0)
	{
		cout<<"cette positon n'existe pas.";
		demandeVal();
	}
	return(position);
}


void placePion(int tab[24],positionEntre)
{
	if (tab[positionEntre]== 0)
}
int main()
{
	int tableau[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	// 0 si c est le tour de p1 1 si c est le tour de p2 
	int turnP = 0;
	tableau[240]=11;
	cout<<tableau[240]<<endl;
	return 0;


}
