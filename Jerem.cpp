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
	cout << "7" << "xxxxxxxxxxxxxxxx" << "6" << "xxxxxxxxxxxxxxxx" << "5" << endl << endl;

	cout << "Grille de jeu:" << endl << endl;

	cout << v[1] << "xxxxxxxxxxxxxxxx" << v[2] << "xxxxxxxxxxxxxxxx" << v[3] << endl;
	cout << "x                x                x" << endl;
	cout << "x    " << v[9] << "xxxxxxxxxxx" << v[10] << "xxxxxxxxxxx" << v[11] << "    x" << endl;
	cout << "x    x           x           x    x" << endl;
	cout << "x    x    " << v[17] << "xxxxxx" << v[18] << "xxxxxx" << v[19] << "    x    x" << endl;
	cout << "x    x    x             x    x    x" << endl;
	cout << v[0] << "xxxx" << v[8] << "xxxx" << v[16] << "             " << v[20] << "xxxx" << v[12] << "xxxx" << v[4] << endl;
	cout << "x    x    x             x    x    x" << endl;
	cout << "x    x    " << v[23] << "xxxxxx" << v[22] << "xxxxxx" << v[21] << "    x    x" << endl;
	cout << "x    x           x           x    x" << endl;
	cout << "x    " << v[15] << "xxxxxxxxxxx" << v[14] << "xxxxxxxxxxx" << v[13] << "    x" << endl;
	cout << "x                x                x" << endl;
	cout << v[7] << "xxxxxxxxxxxxxxxx" << v[6] << "xxxxxxxxxxxxxxxx" << v[5] << endl;
}


int demandeVal()
{
	int position;
	cout<<"Entrez la position entre 0 et 23 ou vous voulez placer votre pion : ";
	cin>>position;
	if(position>23||position<0)
	{
		cout<<"Cette positon n'existe pas."<<endl;
		demandeVal();
	}
	return(position);
}

void chgt_tour(int* tour) {
	if (*tour == 1) { *tour = 2; }
	else { *tour = 1; }
}

void placePion(int tab[24], int* tour)
{
	int a = demandeVal();
	if (tab[a] == 0)
	{
		tab[a] = *tour;
		chgt_tour(tour);

	}
	else { cout << "La case choisie n'est pas disponible"<<endl; placePion(tab, tour); }
}

void supprPion(int tab[24], int* tour)
{
	int a = demandeVal();
	if ((tab[a] != 0) && (tab[a] != *tour))
	{
		tab[a] = 0;
	}
	else { cout << "Vous ne pouvez pas supprimer cette case" << endl; supprPion(tab, tour); }
}

bool check_moulin(int tab[24], int* tour, int* dermove)
{
	//Pairs
	if (*dermove % 8 == 0) { return((tab[*dermove + 1]) == *tour) && (tab[*dermove + 7] == *tour); }//pour 0,8,16 (vertical)
	if (*dermove % 2 == 0 && (*dermove % 8 == 0)) { return((tab[*dermove + 1]) == *tour) && (tab[*dermove - 1] == *tour); }//pour les autres pairs(horizontaux)
	//Impairs
	if (*dermove % 8 == 1) { return((tab[*dermove - 1]) == *tour) && (tab[*dermove + 6] == *tour); }//pour 1,9 et 17
	if (*dermove % 8 == 7) { return((tab[*dermove - 7]) == *tour) && (tab[*dermove - 6] == *tour); }//pour 7,15 et 23
	if (*dermove % 2 == 1 && *dermove % 8 != 1) { return((tab[*dermove - 1]) == *tour) && (tab[*dermove - 2] == *tour); }//impairs sauf 1,9 et 17
	if (*dermove % 2 == 1 && *dermove % 8 != 7) { return((tab[*dermove + 1]) == *tour) && (tab[*dermove + 2] == *tour); }//impairs sauf 7,15 et 23
}

void phase1(int tab[24],int* tour) {
	for (int i = 0; i < 18; i++)
	{
		placePion(tab, tour);
		affPlateau(tab);
	}
}

int main()
{
	int tableau[24] = { 0 };
	// 1 si c est le tour de p1 2 si c est le tour de p2 
	int turnP = 1;
	int dermove;
	affPlateau(tableau);
	phase1(tableau, &turnP);
	return 0;
}
