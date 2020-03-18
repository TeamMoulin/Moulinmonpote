#include <iostream>
using namespace std;

void affPlateau(int v[24])
{
	cout << "Grille exemple:" << endl << endl;
	cout << "1" << "xxxxxxxxxxxxxxxx" << "2" << "xxxxxxxxxxxxxxxx" << "3" << endl;
	cout << "x                x                x" << endl;
	cout << "x    " << "9" << "xxxxxxxxxxx" << "10" << "xxxxxxxxxx" << "11" << "   x" << endl;
	cout << "x    x           x           x    x" << endl;
	cout << "x    x    " << "17" << "xxxxx" << "18" << "xxxxx" << "19" << "   x    x" << endl;
	cout << "x    x    x             x    x    x" << endl;
	cout << "0" << "xxxx" << "8" << "xxxx" << "16" << "            " << "20" << "xxx" << "12" << "xxx" << "4" << endl;
	cout << "x    x    x             x    x    x" << endl;
	cout << "x    x    " << "23" << "xxxxx" << "22" << "xxxxx" << "21" << "   x    x" << endl;
	cout << "x    x           x           x    x" << endl;
	cout << "x    " << "15" << "xxxxxxxxxx" << "14" << "xxxxxxxxxx" << "13" << "   x" << endl;
	cout << "x                x                x" << endl;
	cout << "7" << "xxxxxxxxxxxxxxxx" << "6" << "xxxxxxxxxxxxxxxx" << "5" << endl<<endl;

	cout << "Grille de jeu:" << endl << endl;

	cout<<v[1]<<"xxxxxxxxxxxxxxxx"<<v[2]<<"xxxxxxxxxxxxxxxx"<<v[3]<<endl;
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

void chgt_tour(int* tour) {
	if (*tour == 1) { *tour = 2; }
	else { *tour = 1; }
}

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

// positionEntre = position entré par le joueur
void placePion(int tab[24], int* tour)
{
	int a=demandeVal();
	if (tab[a]== 0)
	{
		tab[a] = *tour;
		chgt_tour(tour);
	}
	else
	placePion(tab,tour);
}

void suprPion(int tab[24], int* tour)
{
	int a=demandeVal();
	if (tab[a] != 0 && tab[a] != *tour)
	{
		tab[a] = 0;
	}
	else
	placePion(tab,tour);
}



void phase1 (int tab[24], int* tour)
{
	for (int i = 1; i < 18; ++i)
	{
		placePion(tab, tour);
		affPlateau(tab);


	}
}

int main()
{
	int tableau[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	// 1 pour j1, 2 pour j2
	int turnP = 1;

	affPlateau(tableau);
	phase1(tableau,&turnP);
	return 0;


}