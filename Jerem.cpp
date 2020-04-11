#include <iostream>
#include <windows.h>
using namespace std;

void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void coutstr(string a, int nombre)
{
	for (int i = 0; i < nombre; i++)
	{
		cout << a;
	}
}

void coutc(int couleur, int sortie, int fond) //Affichage couleur
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 16 * couleur + fond);
	cout << sortie;
	SetConsoleTextAttribute(handle, 15);

}

void affichePion(int tableau[24], int position)
{
	if (tableau[position] == 1)
		coutc(1, position, 15);
	if (tableau[position] == 2)
	{
		coutc(4, position, 15);
	}
	if (tableau[position] == 0)
	{
		coutc(0, position, 14);
	}
}

void affPlateau(int v[24])
{
	ClearScreen();
	cout << endl;
	coutstr(" ", 16); cout << "           Grille de jeu" << endl;
	coutstr(" ", 16); affichePion(v, 1); coutstr("-", 16); affichePion(v, 2); coutstr("-", 16); affichePion(v, 3); cout << endl;
	coutstr(" ", 16); cout << "|                |                |" << endl;
	coutstr(" ", 16); cout << "|    "; affichePion(v, 9); cout << "-----------"; affichePion(v, 10); cout << "----------"; affichePion(v, 11); cout << "   |" << endl;
	coutstr(" ", 16); cout << "|    |           |           |    |" << endl;
	coutstr(" ", 16); cout << "|    |   "; affichePion(v, 17); cout << "------"; affichePion(v, 18); cout << "-----"; affichePion(v, 19); cout << "   |    |" << endl;
	coutstr(" ", 16); cout << "|    |    |             |    |    |" << endl;
	coutstr(" ", 16); affichePion(v, 0); cout << "----"; affichePion(v, 8); cout << "---"; affichePion(v, 16); cout << "             "; affichePion(v, 20); cout << "---"; affichePion(v, 12); cout << "---"; affichePion(v, 4); cout << endl;
	coutstr(" ", 16); cout << "|    |    |             |    |    |" << endl;
	coutstr(" ", 16); cout << "|    |   "; affichePion(v, 23); cout << "------"; affichePion(v, 22); cout << "-----"; affichePion(v, 21); cout << "   |    |" << endl;
	coutstr(" ", 16); cout << "|    |           |           |    |" << endl;
	coutstr(" ", 16); cout << "|   "; affichePion(v, 15); cout << "-----------"; affichePion(v, 14); cout << "----------"; affichePion(v, 13); cout << "   |" << endl;
	coutstr(" ", 16); cout << "|                |                |" << endl;
	coutstr(" ", 16); affichePion(v, 7); coutstr("-", 16); affichePion(v, 6); coutstr("-", 16); affichePion(v, 5); cout << endl << endl;
}

int demandeVal()
{
	int position;
	cin>>position;
	if(position>23||position<0)
	{
		cout<<"Cette positon n'existe pas."<<endl;
		demandeVal();
	}
	return(position);
}

void chgt_tour(int turn[2])
{
	int a = turn[0];
	turn[0] = turn[1];
	turn[1] = a;
}

int placePion(int tab[24], int turn[2],int* dm)
{
	cout <<"Joueur "<<turn[0]<< ",entrez la position entre 0 et 23 ou vous voulez placer votre pion : ";
	*dm = demandeVal();
	if (tab[*dm] == 0)
	{
		tab[*dm] = turn[0];
	}
	else { cout << "La case choisie n'est pas disponible"<<endl; placePion(tab, turn,dm); }
	return *dm;
}

bool check_move(int spion, int promove)//spion:pion qu'on veut déplacer, promove:case ou l'on veut déplacer le pion
{
	bool move = false;
	//Pairs
	if (spion % 2 == 0)
	{
		if (spion % 8 == 0)
		{
			move = (spion + 1 == promove) || (spion + 7 == promove); 
			if (move) 
			{
				return move;
			}
		} //Sur les carrés(pour 0,8,16), si vrai on retourne le résultat immédiatement
		else
		{
			move = (spion + 1 == promove) || (spion - 1 == promove); 
			if (move) 
			{
				return move;
			}
		}//Sur les carrés(sauf 0,8,16 qui posent problème), si vrai on retourne le résultat immédiatement
		if (spion < 8) 
		{
			move = (spion + 8 == promove);
		}//Entre les carrés(carré externe)
		if (spion >= 8 && spion < 16) 
		{
			move = (spion - 8 == promove) || (spion + 8 == promove);
		}//Entre les carrés(carré milieu)	
		if (spion >= 16) 
		{
			move = (spion - 8 == promove);
		}//Entre les carrés(carré interne)
	}
	//Impairs
	if (spion % 2 == 1)
	{
		if (spion % 8 == 7) 
		{
			move = (spion - 7 == promove) || (spion - 1 == promove);
		}//pour 7,15 et 23 (indices suivants/précédents)
		else 
		{
			move = (spion - 1 == promove) || (spion + 1 == promove);
		}//pour les autres valeurs (indices suivants/précédents)
	}
	return move;
}

bool check_BlockPartout(int tab[24], int spion)//spion:pion qu'on veut déplacer, promove:case ou l'on veut déplacer le pion
{
	bool move = false;
	//Pairs
	if (spion % 2 == 0)
	{
		if (spion % 8 == 0)
		{
			move = (tab[spion + 1] == 0) || (tab[spion + 7] == 0);
			if (move)
			{
				return move;
			}
		} //Sur les carrés(pour 0,8,16), si vrai on retourne le résultat immédiatement
		else
		{
			move = (tab[spion + 1] == 0) || (tab[spion - 1] == 0);
			if (move)
			{
				return move;
			}
		}//Sur les carrés(sauf 0,8,16 qui posent problème), si vrai on retourne le résultat immédiatement
		if (spion < 8)
		{
			move = (tab[spion + 8] == 0);
		}//Entre les carrés(carré externe)
		if (spion >= 8 && spion < 16)
		{
			move = (tab[spion - 8] == 0) || (tab[spion + 8] == 0);
		}//Entre les carrés(carré milieu)	
		if (spion >= 16)
		{
			move = (tab[spion - 8] == 0);
		}//Entre les carrés(carré interne)
	}
	//Impairs
	if (spion % 2 == 1)
	{
		if (spion % 8 == 7)
		{
			move = (tab[spion - 7] == 0) || (tab[spion - 1] == 0);
		}//pour 7,15 et 23 (indices suivants/précédents)
		else
		{
			move = (tab[spion - 1] == 0) || (tab[spion + 1] == 0);
		}//pour les autres valeurs (indices suivants/précédents)
	}
	return move;
}
//si libre renvoie vrai,sinon si tout est bloque renvoie false, verifie pour un pion

bool BlockPartout(int tab[24], int turn[2])
{
	bool toutBlock = true;
	int spion = 0;
	while (toutBlock && spion < 24)
	{
		if ( tab[spion] == turn[0])
		{
			toutBlock = !(check_BlockPartout(tab, spion ));
		}
		spion++;
	}
	return toutBlock;
}
//si tous les pions sont bloques renvoie vrai, sinon renvoie faux

bool check_moulin(int tab[24], int turn[2], int* dm,int a)//dm: dernier mouvement, a: 1 si joueur adverse, 0 si joueur actuel
{
	bool moulin=false;
	//Pairs
	if (*dm % 2 == 0)
	{
		if (*dm % 8 == 0) 
		{
			moulin = ((tab[*dm + 1]) == turn[a]) && (tab[*dm + 7] == turn[a]); 
			if (moulin) 
			{
				return moulin;
			}
		} //Sur les carrés(pour 0,8,16), si vrai on retourne le résultat immédiatement
		else 
		{
			moulin = (tab[*dm + 1]) == turn[a] && (tab[*dm - 1] == turn[a]); 
			if (moulin) 
			{
				return moulin;
			}
		}//Sur les carrés(sauf 0,8,16 qui posent problème), si vrai on retourne le résultat immédiatement
	if (*dm < 8)
	{
		moulin = (tab[*dm + 8]) == turn[a] && (tab[*dm + 16] == turn[a]);
	}//Entre les carrés(carré externe)
	if (*dm >= 8 && *dm < 16)
	{
		moulin = (tab[*dm - 8]) == turn[a] && (tab[*dm + 8] == turn[a]);
	}//Entre les carrés(carré milieu)	
	if (*dm >= 16)
	{
		moulin = (tab[*dm - 8]) == turn[a] && (tab[*dm - 16] == turn[a]);
	}//Entre les carrés(carré interne)
	}
	//Impairs
	if (*dm % 2 == 1) 
	{
		if (*dm % 8 == 1) 
		{ 
			moulin=(tab[*dm - 1]) == turn[a] && (tab[*dm + 6] == turn[a]);
			if (moulin) 
			{
				return moulin;
			}
		}//pour 1,9 et 17 (indices précédents), si vrai on retourne le résultat immédiatement
			else
			{ 
				moulin=(tab[*dm - 1]) == turn[a] && (tab[*dm - 2] == turn[a]);
				if (moulin) 
				{
					return moulin;
				}
			}//pour les autres valeurs (indices précédents), si vrai on retourne le résultat immédiatement
		if (*dm % 8 == 7) 
		{
			moulin = (tab[*dm - 7]) == turn[a] && (tab[*dm - 6] == turn[a]);
		}//pour 7,15 et 23 (indices suivants)
		else
		{
			moulin = (tab[*dm + 1]) == turn[a] && (tab[*dm + 2] == turn[a]);
		}//pour les autres valeurs (indices suivants)
	}
return moulin;
}

bool MoulinPartout(int tab[24], int turn[2])
{
	bool toutMoul = true;
	int cpt = 0;
	while (toutMoul && cpt < 24)
	{
		if ((tab[cpt] != 0) && (tab[cpt] == turn[1]))
		{
			toutMoul = check_moulin(tab, turn, &cpt,1);
		}
		cpt++;
	}
	return toutMoul;
}

void move_pion(int tab[24], int turn[2], int* dm) {
	int promove;
	int spion;
	cout << "Joueur " << turn[0] << ",entrez le pion entre 0 et 23 que vous voulez deplacer : ";
	spion = demandeVal();
	if (tab[spion] == turn[0])
	{
		if (check_BlockPartout(tab,spion))
		{
			cout << "Joueur " << turn[0] << ",entrez la position entre 0 et 23 ou vous voulez deplacer votre pion : ";
			promove = demandeVal();
			if (tab[promove] == 0)
			{
				if (check_move(spion, promove))
				{
					tab[spion] = 0;
					*dm = promove;
					tab[*dm] = turn[0];
				}
				else
				{
					cout << "Vous ne pouvez pas deplacer le pion ici" << endl; 
					move_pion(tab, turn, dm);
				}
			}
			else
			{
				cout << "Cette case est deja occupee par un pion" << endl; 
				move_pion(tab, turn, dm);
			}
		}
		else
		{
			cout << "Ce pion est bloque" << endl; 
			move_pion(tab, turn, dm);
		}
	}
	else
	{
		cout << "Cette case est vide ou le pion appartient au joueur adverse" << endl;
		move_pion(tab, turn, dm);
	}
}

void move_pionIII(int tab[24], int turn[2], int* dm)//deplacement d'un pion lorsqu'un joueur n'a plus que 3 pions
{
	int promove;
	int spion;
	cout << "Joueur " << turn[0] << ",entrez le pion entre 0 et 23 que vous voulez deplacer : ";
	spion = demandeVal();
	if (tab[spion] == turn[0])
	{
		cout << "Joueur " << turn[0] << ",entrez la position entre 0 et 23 ou vous voulez deplacer votre pion : ";
		promove = demandeVal();
		if (tab[promove] == 0)
		{
			tab[spion] = 0;
			*dm = promove;
			tab[*dm] = turn[0];
		}
		else
		{
			cout << "Cette case est deja occupee par un pion " << endl;
			move_pionIII(tab, turn, dm);
		}
	}
	else
	{
		cout << "Cette case est vide ou le pion appartient au joueur adverse" << endl;
		move_pionIII(tab, turn, dm);
	}
}

void supprPion(int tab[24], int turn[2],int pions[2])
{
	cout << "Joueur " << turn[0] << ",entrez le numero du pion entre 0 et 23 que vous voulez supprimer : ";
	int valsuppr = demandeVal();
	if (tab[valsuppr] == turn[1])
	{
		if (MoulinPartout(tab, turn))//Cas ou tous les pions adverses font parti d'un moulin
		{
			tab[valsuppr] = 0;
			(pions[turn[1]-1])--;
		}
		else
		{
			if (check_moulin(tab, turn, &valsuppr,1))
			{
				cout << "Ce pion fait parti d'un moulin !" << endl; supprPion(tab, turn, pions);
			}
			else
			{
				tab[valsuppr] = 0;
				(pions[turn[1]-1])--;
			}
		}
	}
	else 
	{
		cout << "Vous ne pouvez pas supprimer cette case" << endl; supprPion(tab, turn, pions);
	}
}

void phase1(int tab[24],int* tour,int* dm,int pions[2]) {
	for (int i = 0; i < 18; i++)
	{
		*dm = placePion(tab, tour,dm);
		affPlateau(tab);
		if (check_moulin(tab, tour, dm,0)) 
		{
			supprPion(tab, tour, pions); affPlateau(tab);
		}
		chgt_tour(tour);
	}
}

void phase2(int tab[24], int turn[2], int* dm, int pions[2])
{
	while ((pions[0] > 3 || pions[1] > 3))
	{
		if (pions[turn[0] - 1] == 3)
		{
			move_pionIII(tab, turn, dm);
			affPlateau(tab);
		}
		else
		{
			if (!(BlockPartout(tab, turn)))
			{
				move_pion(tab, turn, dm);
				affPlateau(tab);
			}
			else
			{
				cout << "Le joueur " << turn[1] << " a gagne le jeu. (pions tous bloques) " << endl;
				return;
			}
		}
		if (check_moulin(tab, turn, dm, 0))
		{
			supprPion(tab, turn, pions);
			affPlateau(tab);
		}
		if (pions[turn[1] - 1] < 3)
		{
			cout << "Le joueur " << turn[0] << " a gagne le jeu. " << endl;
			return;
		}
		chgt_tour(turn);
	}
	for (int i = 0; i < 40; i++)
	{
		cout << "Il reste "<<40-i<<" coups avant le match nul." << endl;
		move_pionIII(tab, turn, dm);
		affPlateau(tab);
		if (check_moulin(tab, turn, dm, 0))
		{
			cout << "Le joueur " << turn[0] << " a gagne le jeu." << endl;
			return;
		}
		chgt_tour(turn);
	}
	cout << "Match nul" << endl;
	return;
}

int main()
{
	int tableau[24] = { 0 };
	int pions[2] = { 9,9 }; //nbr de pions des 2 joueurs
	int turn[2] = { 1,2 };//turn[0]:joueur actuel turn[1]: autre joueur
	int dermove;
	affPlateau(tableau);
	phase1(tableau, turn, &dermove, pions);
	phase2(tableau, turn, &dermove, pions);
	return 0;
}
