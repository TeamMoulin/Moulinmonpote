#include <iostream>
using namespace std;

void affPlateau(int v[24])
{
	cout << "Grille exemple:" << endl << endl;
	cout << "1" << "----------------" << "2" << "----------------" << "3" << endl;
	cout << "|                x                x" << endl;
	cout << "|    " << "9" << "-----------" << "10" << "----------" << "11" << "   x" << endl;
	cout << "|    |           x           x    x" << endl;
	cout << "|    |    " << "17" << "-----" << "18" << "-----" << "19" << "   x    x" << endl;
	cout << "|    |    |             x    x    x" << endl;
	cout << "0" << "----" << "8" << "----" << "16" << "            " << "20" << "---" << "12" << "---" << "4" << endl;
	cout << "|    |    |             x    x    x" << endl;
	cout << "|    |    " << "23" << "-----" << "22" << "-----" << "21" << "   x    x" << endl;
	cout << "|    |           x           x    x" << endl;
	cout << "|    " << "15" << "----------" << "14" << "----------" << "13" << "   x" << endl;
	cout << "|                x                x" << endl;
	cout << "7" << "----------------" << "6" << "----------------" << "5" << endl << endl;

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

int placePion(int tab[24], int* tour)
{
	int dm = demandeVal();
	if (tab[dm] == 0)
	{
		tab[dm] = *tour;
		//chgt_tour(tour);
	}
	else { cout << "La case choisie n'est pas disponible"<<endl; placePion(tab, tour); }
	return dm;
}

void supprPion(int tab[24], int* tour, int* dm)
{
	int a = demandeVal();
	if (check_moulin(tab, tour, dm))
	{
		cout<<Il y a un moulin. Choisisez une autre case.;
		supprPion(tab, tour)
	}
	if ((tab[a] != 0) && (tab[a] != *tour))
	{
		tab[a] = 0;
	}
	else { cout << "Vous ne pouvez pas supprimer cette case" << endl; supprPion(tab, tour); }
}

bool check_moulin(int tab[24], int* tour, int* dm)//dm: dernier mouvement
{
bool moulin=false;
//Pairs
if (*dm % 2 == 0)
	{
	
	if (*dm % 8 == 0) 
	{
		moulin = ((tab[*dm + 1]) == *tour) && (tab[*dm + 7] == *tour); if (moulin) { return moulin; }
	} //Sur les carrés(pour 0,8,16), si vrai on retourne le résultat immédiatement
		else 
		{
			moulin = (tab[*dm + 1]) == *tour && (tab[*dm - 1] == *tour); if (moulin) { return moulin; }
		}//Sur les carrés(sauf 0,8,16 qui posent problème), si vrai on retourne le résultat immédiatement
	if (*dm < 8){ moulin=(tab[*dm + 8]) == *tour && (tab[*dm + 16] == *tour); }//Entre les carrés(carré externe)
	if (*dm >= 8 && *dm < 16){ moulin=(tab[*dm - 8]) == *tour && (tab[*dm + 8] == *tour); }//Entre les carrés(carré milieu)	
	if (*dm >= 16){ moulin=(tab[*dm - 8]) == *tour && (tab[*dm - 16] == *tour); }//Entre les carrés(carré interne)
		
	}
//Impairs
if (*dm % 2 == 1) 
	{
		if (*dm % 8 == 1) 
		{ 
			moulin=(tab[*dm - 1]) == *tour && (tab[*dm + 6] == *tour); if (moulin) { return moulin; }
		}//pour 1,9 et 17 (indices précédents), si vrai on retourne le résultat immédiatement
			else
			{ 
				moulin=(tab[*dm - 1]) == *tour && (tab[*dm - 2] == *tour); if (moulin) { return moulin; }
			}//pour les autres valeurs (indices précédents), si vrai on retourne le résultat immédiatement
		if (*dm % 8 == 7) { moulin=(tab[*dm - 7]) == *tour && (tab[*dm - 6] == *tour); }//pour 7,15 et 23 (indices suivants)
		else{moulin= (tab[*dm + 1]) == *tour && (tab[*dm + 2] == *tour);}//pour les autres valeurs (indices suivants)
	}
return moulin;
}

void phase1(int tab[24],int* tour,int* dm) {
	for (int i = 0; i < 18; i++)
	{
		*dm = placePion(tab, tour, dm);
		affPlateau(tab);
		if (check_moulin(tab, tour, dm)) { cout << "oui"<<endl; }
		else { cout << "non"<<endl; }
		chgt_tour(tour);
	}
}

int main()
{
	int tableau[24] = { 0 };
	// 1 si c est le tour de p1 2 si c est le tour de p2 
	int turnP = 1;
	int dm;
	affPlateau(tableau);
	phase1(tableau, &turnP, &dm);
	return 0;
}
